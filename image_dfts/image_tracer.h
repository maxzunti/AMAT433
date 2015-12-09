#ifndef IMAGE_TRACER
#define IMAGE_TRACER
#include <QImage>
#include <XY.h>
#include <QColor>
#include <utils.h>

// Structure with functions for tracing images
// Really just an organizational structure to contain everything needed
// for tracing a single image

// The idea is to trace the lines of a single image from beginning to end
// (beginning to beginning if periodic) and output some Fourier coefficients
// corresponding to
// z = z(t),
// where
// z(t) =  x(t) + iy(t)
// and x and y are paramatized in t such that
// x = cos(t) and y = isin(t)
// This way, we can write z(t) in terms of Euler's formula, and think of
// x and y as tracing different circles which will combine to trace
// the complete image

// After tracing, the ImageTracer can return vectors of the x and y values corresponding to the image
// along with the step distance and total period
// This effectively generates a time-dependent complex function corresponding to an image
struct ImageTracer {
public:
    // Dummy constructor
    ImageTracer();
    ImageTracer(QImage input, double dist, int tol);

    // Trace the image currently stored by ImageTracer
    void traceImage();

    // Get an output image which shows how tracing is performed
    QImage getOut();

    std::vector<double> getXVals();
    std::vector<double> getYVals();

    // Currently no function to update the image held

private:
    // Output and input images
    QImage in;
    QImage out;
    // Track the current point of the image
    XY current_point;
    // Track the current "momentum" of tracing
    // We use this to choose which line to follow in the case of multiple nearby/overlapping lines
    XY momentum;

    // Beginning and ending points of the trace
    XY startPos;
    XY endPos;

    // step_distances determines the approximate spatial distance we should step each iterationm
    // which in turn determines momentum
    // Higher distances are less accurate overall, but small ones may yield momentum too small
    // to accurately trace
    double step_distance;

    // Tolerance determines the effective area of space that we search for the next section of line
    int tolerance;

    // Track the parameter t where z = z(t)
    // t increases until we've traversed the whole image
    double t;
    // The step size of t every trace iteration
    // This should really be arbitrary, since the actual length of the image's "period"
    // is also arbitrary
    // The only necessary condition is that it remains constant
    const double step = 1.0;
    // Track the number of steps taken through the image
    int num_steps;

    // Store the x and y values
    // Not using an XY vector for the sake of simplicity, doubles are just easier and quicker
    // w/o relying on XY pointers
    std::vector<double> x_vals;
    std::vector<double> y_vals;

    double xHalf;
    double yHalf;

    // Check if a given pixel is populated
    // Right now, if it has R, G, and B values all below 200
    bool isPop(XY point);

    // Use current point and momentum to get the next point in the image
    void nextPos();

    // Choose a suitable starting position
    XY getStart();

    // Check if we've arrived back at our starting position
    bool checkIfStart();

    // XXX how to deal with images that aren't CTS?
    // Connect closest point to closest point (or connect along edges)
    // Remove the differences after
    // Worry about this later
    // XXX Maybe restructure to trace Lines (and treat them as a separate class)
    // then combine all the lines at the end

    // Draw the process of image tracing to the QImage "out"
    void illustrateTrace();
    void drawSinAndCos();


};

#endif // IMAGE_TRACER

