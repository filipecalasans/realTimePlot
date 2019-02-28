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

INCLUDEPATH += realtimeplot

SOURCES += main.cpp\
        mainwindow.cpp \
        QCustomPlot/qcustomplot.cpp \
        realtimeplot/plotarea.cpp \
        realtimeplot/pointstream.cpp

HEADERS  += mainwindow.h \
            QCustomPlot/qcustomplot.h \
            realtimeplot/plotarea.h \
            realtimeplot/pointstream.h

FORMS    += mainwindow.ui \
            realtimeplot/plotarea.ui
