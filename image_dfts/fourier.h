#ifndef FOURIER_H
#define FOURIER_H
#include <fftw3.h>
#include <stdarg.h>
#include <vector>
#include <cmath>
#include <iostream>

// Perform a Fourier transform on z(t) = cos(t) + isin(t)
std::vector<double[2]> performTransform(std::vector<double> xVals, std::vector<double> yVals);

std::vector<double[2]> performReTransform(std::vector<double> reals);

// Return unnormalized fft magnitudes
std::vector<double> getMags(std::vector<double[2]> transformed_vals);

// Return the phase of each component in a vector
std::vector<double> getPhase(std::vector<double[2]> transformed_vals);

// Return a vector normalized s.t. the largest element has mag 1
// (not counting the DC offset)
std::vector<double> normalize(std::vector<double> in_vec);

// Return the index of the maximum value in vec which is strictly below threshold
// Only works for + values
// Pass a negative threshold for no threshold
int getMaxIndex(std::vector<double> vec, bool negative, int minIndex, int maxIndex);

#endif // FOURIER_H

