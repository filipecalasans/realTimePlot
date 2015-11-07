#-------------------------------------------------
#
# Project created by QtCreator 2015-11-07T00:48:35
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = realTimePlot
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    QCustomPlot/qcustomplot.cpp \
    QCustomPlot/plotarea.cpp

HEADERS  += mainwindow.h \
    QCustomPlot/qcustomplot.h \
    QCustomPlot/plotarea.h

FORMS    += mainwindow.ui \
    QCustomPlot/plotarea.ui
