#ifndef INTERPRETER_H
#define INTERPRETER_H
#define RES 10
#define MIN_FACTOR 0.001
#define PHASE_SHIFT 0
#include <vector>
#include <cmath>
#include <fourier.h>
#include <QImage>
#include <utils.h>

// Class which contains functions and data structures for interpreting sampled data
// gathered from ImageTracer
class Interpreter {
public:
    // dummy
    Interpreter();
    Interpreter(std::vector<double> xVals, std::vector<double> yVals);

    // Creates a new image corresponding to the input xVals and yVals
    QImage getImageOutput(double phase_shift, int width, int xOffset, int height, int yOffset, double margin, int lineWidth);

    // Calculate and return a vector of x-y values calculated from the DFT data
    std::vector<double[2]> calcXYVals(double phase_shift);

    std::vector<double> getXNorms();
    std::vector<double> getYNorms();

    void storeResult();


private:
    // Holds raw output from an FFT
    std::vector<double[2]> xOutput, yOutput;
    std::vector<double[2]> raw_output;

    // Vectors to contain magnitude, normalized magnitude, and phase data respectively
    std::vector<double> xVals, yVals, xMags, yMags, xNorms, yNorms, xPhase, yPhase;

    // Takes a vector of transformed data (with only real inputs)
    // and returns a vector of results over a period
    std::vector<double> calcPeriodSum(std::vector<double> input, std::vector<double> rel_phase, double phase_shift);
};

#endif // INTERPRETER_H

