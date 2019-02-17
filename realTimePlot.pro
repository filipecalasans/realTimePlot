#-------------------------------------------------
#
# Project created by QtCreator 2015-11-07T00:48:35
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = realTimePlot
TEMPLATE = app

CONFIG += c++17

SOURCES += main.cpp\
        mainwindow.cpp \
    QCustomPlot/qcustomplot.cpp \
    plotarea.cpp \
    pointstream.cpp

HEADERS  += mainwindow.h \
    QCustomPlot/qcustomplot.h \
    plotarea.h \
    pointstream.h

FORMS    += mainwindow.ui \
    plotarea.ui
