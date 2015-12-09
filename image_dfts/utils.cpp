#include <utils.h>
#include <iostream>
#include <QColor>

// Treat an xy point as an offset from 0 and convert the relative phase on a unit circle
// (starting from x = 1, y = 0, and traversed CCW (as is standard))
double offsetToPhase(XY point) {
    using namespace std;
    //cout << "x = " << point[0] << "     y = " << point[1] << "    atan2(y, x) == " << atan2(point[1], point[0]) << endl;
    return atan2(point[1], point[0]);
}


QColor nextRainbowCol(int bgRed, int bgGreen, int bgBlue) {
    if (bgRed == 255.0 && bgGreen == 181.0 && bgBlue < 255.0) {
        bgBlue++;
    } else if (bgBlue == 255.0 && bgGreen == 181.0 && bgRed > 181.0) {
        bgRed--;
    } else if (bgBlue == 255.0 && bgRed == 181.0 && bgGreen < 255.0) {
        bgGreen++;
    } else if (bgRed == 181.0 && bgGreen == 255.0 && bgBlue > 181.0) {
        bgBlue--;
    } else if (bgGreen == 255.0 && bgBlue == 181.0 && bgRed < 255.0) {
        bgRed++;
    } else if (bgRed == 255.0 && bgBlue == 181.0 && bgGreen > 181.0) {
        bgGreen--;
    } else {
        std::cout << "Error when updating color" << std::endl;
    }
    return QColor(bgRed, bgGreen, bgBlue);
}

void drawFT(std::vector<double> vals, QString name, int width, int height, int R, int G, int B) {
    int scl = 0.9 * height;
    int N = vals.size();
    int lWidth = 1;
    QImage FT = clearImage(QImage((vals.size()) / 2, 500, QImage::Format_RGB32));
    for (int i = 1; i < vals.size() / 4; i++) {
        for (int k = -lWidth; k <= lWidth; k++) {
            for (int j = -lWidth; j <= lWidth; j++) {
                int tnum = scl*vals[i] - 1;
                for (int q = height - tnum; q < height; q++) {
                    FT.setPixel((4*i)+k, q, qRgb(R, G, B));
                }
                FT.setPixel((4*i) + k, height - 1 + j, qRgb(0.0, 0.0, 0.0));
                FT.setPixel((4*i) + k + 1, height - 1 + j, qRgb(0.0, 0.0, 0.0));
                FT.setPixel((4*i) + k + 2, height - 1 + j, qRgb(0.0, 0.0, 0.0));
                FT.setPixel((4*i) + k + 3, height - 1 + j, qRgb(0.0, 0.0, 0.0));
                FT.setPixel((4*i) + k, 0, qRgb(0.0, 0.0, 0.0));
                FT.setPixel((4*i) + k + 2, 0, qRgb(0.0, 0.0, 0.0));

            }
        }
    }
    for (int i = 0; i < height; i++) {
        for (int k = -0; k <= 0; k++) {
            for (int j = -0; j <= 0; j++) {
        FT.setPixel(k, i + j, qRgb(0.0, 0.0, 0.0));
        FT.setPixel(k + (vals.size() / 4 - 1), j, qRgb(0.0, 0.0, 0.0));
            }
        }
    }
    FT.save(name);
}


QImage clearImage(QImage image) {
    QImage Re = QImage(image.width(), image.height(), QImage::Format_RGB32);
    for (int i = 0; i < Re.width(); i++) {
        for (int j = 0; j < Re.height(); j++) {
            Re.setPixel(i, j, qRgb(255, 255, 255));
        }
    }
    return Re;
}

double maxVal(std::vector<double> vec1, std::vector<double> vec2) {
    int x_mindex = getMaxIndex(vec1, true, 0, vec1.size() - 1);
    int x_maxdex = getMaxIndex(vec1, false, 0, vec1.size() - 1);
    int y_mindex = getMaxIndex(vec2, true, 0, vec2.size() - 1);
    int y_maxdex = getMaxIndex(vec2, false, 0, vec2.size() - 1);
    double max = vec1[x_maxdex];
    if (max < -1.0 * vec1[x_mindex])  // If x[x_mindex] is pos, then x[x_maxdex] is lt x[x_mindex] already
        max = -1.0 * vec1[x_mindex];
    if (max < vec2[y_maxdex])
        max = vec2[y_maxdex];
    if (max < -1.0 * vec2[y_mindex])
        max = -1.0 * vec2[y_mindex];
    return max;
}
