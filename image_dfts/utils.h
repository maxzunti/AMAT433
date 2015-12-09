#ifndef UTILS
#define UTILS
#include <XY.h>
#include <cmath>
#include <math.h>
#include <fourier.h>



// Treat an xy point as an offset from 0 and convert the relative phase on a unit circle
// (starting from x = 1, y = 0, and traversed CCW (as is standard))
double offsetToPhase(XY point);

QColor nextRainbowCol(int bgRed, int bgGreen, int bgBlue);

void drawFT(std::vector<double> vals, QString name, int width, int height, int R, int G, int B);

void drawGraph(QImage base, std::vector<double> vals, double R, double G, double B);

QImage clearImage(QImage);

double maxVal(std::vector<double> vec1, std::vector<double> vec2);

#endif // UTILS

