#-------------------------------------------------
#
# Project created by QtCreator 2015-12-05T15:48:03
#
#-------------------------------------------------

QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = image_dfts
TEMPLATE = app


SOURCES += main.cpp \
    image_tracer.cpp \
    utils.cpp \
    fourier.cpp \
    interpreter.cpp

HEADERS  += \
    image_tracer.h \
    XY.h \
    utils.h \
    fourier.h \
    interpreter.h


LIBS += -lfftw3 -lm


FORMS    +=
