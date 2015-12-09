#include <interpreter.h>

// Dummy, don't use me
Interpreter::Interpreter() { }

Interpreter::Interpreter(std::vector<double> xVals, std::vector<double> yVals) {
    this->xVals = xVals;
    this->yVals = yVals;

    xOutput = performReTransform(xVals);
    yOutput = performReTransform(yVals);

    xMags = getMags(xOutput);
    yMags = getMags(yOutput);

    xNorms = normalize(xMags);
    yNorms = normalize(yMags);

    xPhase = getPhase(xOutput);
    yPhase = getPhase(yOutput);

}

QImage Interpreter::getImageOutput(double phase_shift, int width, int xOffset, int height, int yOffset, double margin, int lineWidth) {
    double xHalf = width / 2.0, yHalf = height / 2.0;
    double xMag = xHalf * margin, yMag = yHalf * margin;
    QImage newImage = clearImage(QImage(width, height, QImage::Format_RGB32));

    std::vector<double[2]> XYVals = calcXYVals(phase_shift);       // Normalized, calculated image values
    for (int i = 0; i < XYVals.size(); i++) {
        XYVals[i][0] = (XYVals[i][0] * xMag) + xHalf + xOffset;
        XYVals[i][1] = (XYVals[i][1] * yMag) + yHalf + yOffset;
    }

    // Do the actual drawing
    // Doesn't really need to be a separate loop. but w/e
    for (int i = 0; i < XYVals.size(); i++) {
        for (int j = -lineWidth; j <= lineWidth; j++) {
            for (int k = -lineWidth; k <= lineWidth; k++) {
                newImage.setPixel(XYVals[i][0] + j, XYVals[i][1] + k, qRgb(0, 0, 0));
            }
        }
    }

    return newImage;
}

std::vector<double> Interpreter::calcPeriodSum(std::vector<double> input, std::vector<double> rel_phase, double phase_shift) {
    std::vector<int> sig_inds;
    int maxMag = getMaxIndex(input, false, 0, input.size() - 1);    // Get max value in max
    double min = (input[maxMag]) * MIN_FACTOR;                           // Arbitrary threshold for inclusion
    for (int i = 1; i <= input.size() / 2; i++) {              // For all freqs
        if (input[i] >= min) {
            sig_inds.push_back(i);
        }
    }
    // Output to file
    for (int i = 0; i < sig_inds.size(); i++) {
        int index = sig_inds[i];
        std::cout << "k " << index << "\tR " << input[index] << "\tphase " << rel_phase[index] << std::endl;
    }
    std::cout << std::endl;


    std::cout << "Number of terms kept = " << sig_inds.size() << std::endl;
    std::vector<double> output;
    double a = 0.0;
    while ( a < 2.0 * M_PI) {
        double res = 0;
        for (int i = 0; i < sig_inds.size(); i++) {
            int index = sig_inds[i];
            res += input[index] * (cos((a * index) + rel_phase[index] + phase_shift));
        }
        output.push_back(res);
        a += M_PI / (180.0 * RES);
    }
    return output;
}


std::vector<double[2]> Interpreter::calcXYVals(double phase_shift) {
    std::vector<double> x, y;
    std::cout << "X: " << std::endl;
    x = calcPeriodSum(xMags, xPhase, phase_shift);
    std::cout << "Y: " << std::endl;
    y = calcPeriodSum(yMags, yPhase, phase_shift);

    // Normalize x and y according to a normalization factor equal to 1 / (max in
    // x U y)
    double max = maxVal(x, y);

    // Pair the x and y results into a single (now normalized) vector
    double temp_arr[x.size()][2];
    for (int i = 0; i < x.size(); i++) {
        temp_arr[i][0] = x[i] / max;
        temp_arr[i][1] = y[i] / max;
    }
    std::vector<double[2]> XYVals(temp_arr, temp_arr + x.size());
    return XYVals;
}

/*void Interpreter::storeResult(std::vector<double> x, std::vector<double> y) {

    std::vector<double> XYVals = calcXYVals(0.0);
}*/


std::vector<double> Interpreter::getXNorms() { return xNorms; }
std::vector<double> Interpreter::getYNorms() { return yNorms; }
