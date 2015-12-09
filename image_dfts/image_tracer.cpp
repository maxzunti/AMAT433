#include <image_tracer.h>
#include <iostream>

ImageTracer::ImageTracer() {
    // Dummy constructor
    // Don't use me!
}

ImageTracer::ImageTracer(QImage input, double dist, int tol) {
    in = input;
    step_distance = dist;
    tolerance = tol;

    current_point = XY(0.0, 0.0);
    // Arbitrary choice
    momentum = XY(0.5, -0.5);
    startPos = XY(0.0, 0.0);
    endPos = XY(0.0, 0.0);

    t = 0.0;
    num_steps = 0;

    x_vals.clear();
    y_vals.clear();

    xHalf = in.width() / 2.0;
    yHalf = in.height() / 2.0;
}

// Trace the curently stored image, return a new Image
// XXX should probably just return fourier coeffs
void ImageTracer::traceImage() {
    startPos = getStart();
    current_point = startPos;
    while (!checkIfStart() && num_steps <= 100000) {
        x_vals.push_back(current_point[0]);
        y_vals.push_back(current_point[1]);
        num_steps++;
        nextPos();
    }
    std::cout << "current_point[1] = " << current_point[1] << std::endl;
    std::cout << "y_vals[" << y_vals.size() - 1 << "] = " << y_vals[y_vals.size() - 1] << std::endl;
    std::cout << "Total steps: " << num_steps << std::endl;
    illustrateTrace();
    drawSinAndCos();
}



// Use current point and momentum to get the next point in the image
// IDEA: Based on the current momentum, sweep out a circle near the momentum (+ and - similtaneously)
// and choose the point that is step_distance away and most centered on a line
// (assuming that a line will likely have a width of more than 1 pixel)
void ImageTracer::nextPos() {
        using namespace std;
        double init_angle = offsetToPhase(momentum);
        double angle = init_angle;
        double angle_offset = 0.0;
        const double angle_step = M_PI / 180.0;
        int neg = 1;
        static int a = 0;
        a++;

        // Find the line closest to the momentum
        while (!isPop(XY(
                         current_point[0] + (step_distance * cos(angle + (neg * angle_offset))),
                         current_point[1] + (step_distance * sin(angle + (neg * angle_offset)))
                         ))
               && angle_offset <= M_PI) {
            neg *= -1;
            // Only increment the angle after sweeping both ways
            if (neg > 0) {
                angle_offset += angle_step;
            }
        }
        if (angle_offset >= M_PI)
            cout << "ERROR" << endl;
        angle += neg * angle_offset;
        angle_offset = 0.0;
        // The below code is intended to help find the center position of the new
        // point in a relatively thick line; however, its current implementation
        // doesn't seem to help things/be necessary.
      /*  // Found the line, now find the avg of its pos on the circle:
        double line_steps = 0.0;

        while (isPop(XY(
                         current_point[0] + (step_distance * cos(angle + angle_offset)),
                         current_point[1] + (step_distance * sin(angle + angle_offset))
                         ))
               &&
               // If we go completely around, maintain original direction
               line_steps <= 359) {
               //&&
               // Only sweep 30 degrees either way
               // Arbitrary limit
               //angle <= init_angle + 30.0 * (M_PI / 180.0)) {
            line_steps++;
            angle_offset = angle_offset + (neg * angle_step);

            if (line_steps == 360.0)
                cout << "went around" << endl;
            if (a == 1) {
                            cout << "offset " << angle_offset << endl;
                    cout << current_point[1] + (step_distance * sin(angle + angle_offset)) << endl;
            }
        }
        angle_offset = angle - (angle_offset / 2.0);*/

        // Update current position and momentum

        // XXX Potentially weight momentum as a function of the last few steps
        // Test first, though
        XY prev_point = current_point;
        current_point = XY(
                    current_point[0] + (step_distance * cos(angle)),
                    current_point[1] + (step_distance * sin(angle))
                );
        momentum = current_point - prev_point;
}

// Check if a given XY point is populated (or points within tolerance are populated)
bool ImageTracer::isPop(XY point) {
    bool populated = false;
    using namespace std;
    for (int i = -tolerance; i <= tolerance; i++) {
        for (int j = -tolerance; j <= tolerance; j++) {
            // Check bounds
            if (point[0] + i > 0 && point[0] + i < in.width() &&
                point[1] + j > 0 && point[1] + j < in.height()) {
                QColor pixColor = QColor(in.pixel((int) (point[0] + i), (int) point[1] + j));
                if (pixColor.red() <= 200 &&
                    pixColor.green() <= 200 &&
                    pixColor.blue() <= 200) {
                    populated = true;
                }
            }
        }
    }
    return populated;
}

// Choose a suitable starting position
// Right now, naively choose the position with the highest y value
XY ImageTracer::getStart() {
    XY point = XY(0.0, 0.0);
    int i = 0, j = 0;
    while (i < in.height()) {
        while (j < in.width()) {
            point = XY(j, i);
            if (isPop(point)) {
                return point;
            }
            j++;
        }
        i++;
        j = 0;
    }
    return XY(-1.0, -1.0);

}

// Check if we've arrived back at our starting position
bool ImageTracer::checkIfStart() {
    // Arbitrary check to make sure we're far enough away
    // Should probably actually check distance from start
    if (num_steps < 15)
        return false;
    if (current_point.getDistance(startPos) < 5.0)
        return true;
    return false;
}

// Use the established x and y values to draw a trace-pattern output image
// This image is best used for testing purposes
void ImageTracer::illustrateTrace() {
    out = clearImage(QImage(in.width(), in.height(), QImage::Format_RGB32));

    int R = 0;
    std::cout << "size = " << x_vals.size() << std::endl;
    for (int i = 0; i < x_vals.size(); i++) {
        for (int k = -1; k <= 1; k++) {
            for (int j = -1; j <= 1; j++) {

                //currCol = nextRainbowCol(currCol.red(), currCol.green(), currCol.blue());
                //out.setPixel(x_vals[i], y_vals[i], qRgb(currCol.red(), currCol.green(), currCol.blue()));
                out.setPixel(x_vals[i]+k, y_vals[i]+j, qRgb(R, 0, 0));

            }
        }
        R += 3;
    }
    for (int k = -3; k <= 3; k++) {
        for (int j = -3; j <= 3; j++) {
            out.setPixel(startPos[0] + k, startPos[1] + j, qRgb(0, 0, 255));
        }
    }
    out.save("test_output.png");
}

// Pretty lazy code
void ImageTracer::drawSinAndCos() {
    QImage Re = clearImage(QImage(num_steps, (2.2)*xHalf, QImage::Format_RGB32));
    for (int i = 0; i < num_steps; i++) {
        for (int k = -1; k <= 1; k++) {
            for (int j = -1; j <= 1; j++)
                Re.setPixel(i+k, (2.2 * xHalf) - x_vals[i]+j, qRgb(255, 0, 0));
        }
        Re.setPixel(i, xHalf * 1.1, qRgb(0.0, 0.0, 0.0));
    }
    Re.save("real.png");

    QImage Im = clearImage(QImage(num_steps, (2.2)*yHalf, QImage::Format_RGB32));
    for (int i = 0; i < num_steps; i++) {
        for (int k = -1; k <= 1; k++) {
            for (int j = -1; j <= 1; j++)
                Im.setPixel(i+k, (2.2 * yHalf) - y_vals[i]+j, qRgb(0, 0, 255));
        }
        Im.setPixel(i, yHalf * 1.1, qRgb(0.0, 0.0, 0.0));
    }
    Im.save("im.png");
}

QImage ImageTracer::getOut() {
    return out;
}

std::vector<double> ImageTracer::getXVals() {
    std::vector<double> x_ret;
    x_ret.clear();
    for (int i = 0; i < x_vals.size(); i++) {
        x_ret.push_back(x_vals[i] - xHalf);
    }
    return x_ret;
}
std::vector<double> ImageTracer::getYVals() {
    std::vector<double> y_ret;
    y_ret.clear();
    for (int i = 0; i < y_vals.size(); i++) {
        y_ret.push_back(y_vals[i] - yHalf);
    }
    return y_ret;
}


