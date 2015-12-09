#include <iostream>
#include <QFileInfo>
#include <QImage>
#include <QRgb>
#include <QColor>
#include <XY.h>
#include <image_tracer.h>
#include <fourier.h>
#include <interpreter.h>
#include <cstring>
#include <sstream>


int main(int argc, char *argv[])
{
    // currently unused parameters
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    // Owl2.ping - works with 3.2, 0, and various MIN_TERMS

    QString inputName = "owl2.png";

    // Input files must be copied to the build directory
    QImage in = QImage(inputName, "PNG");

    // TEST1.png WORKS WITH 5.0 and 0 as trace params

    ImageTracer tracer(in, 3.2, 0);
    tracer.traceImage();

    std::vector<double> outX = tracer.getXVals();
    std::vector<double> outY = tracer.getYVals();
    std::vector<double> xVals, yVals;

    for (int j = 0; j < outX.size(); j++) {
        xVals.push_back(outX[j]);
        yVals.push_back(outY[j]);
    }

    Interpreter interp(xVals, yVals);
    //std::vector<double[2]> XYres = interp.calcXYVals();

    // Make images for a gif
    double a = 0.0;
    int i = 0;
    std::stringstream sstm;
   /* while (a <= 2*M_PI) {
        i++;
        sstm.str("");
        sstm.clear();
        sstm << "gif/" << i << "_pic.png";
        QImage gif = interp.getImageOutput(a, 500, 0, 500, 0, 0.8, 1);
        const std::string tmp = sstm.str();
        const char * name = tmp.c_str();
        QString qs = QString(name);
        gif.save(name);
        a += (2 * M_PI / 180.0);

    }*/


    QImage reconstructed = interp.getImageOutput(0.0, 500, 0, 500, 0, 0.8, 1);
    reconstructed.save("rebuilt.png");

    drawFT(interp.getXNorms(), QString("X_FT.png"), 500, 500, 255, 0, 0);
    drawFT(interp.getYNorms(), QString("Y_FT.png"), 500, 500, 0, 0, 255);

    return 0;
}
