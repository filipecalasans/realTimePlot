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

INCLUDEPATH += lib/ \
               third-party/

SOURCES += app/main.cpp\
        app/mainwindow.cpp \
        third-party/qcustomplot/qcustomplot.cpp \
        lib/realtimeplot/plotarea.cpp \
        lib/realtimeplot/pointstream.cpp

HEADERS  += app/mainwindow.h \
            third-party/qcustomplot/qcustomplot.h \
            lib/realtimeplot/plotarea.h \
            lib/realtimeplot/pointstream.h

FORMS    += app/mainwindow.ui \
            lib/realtimeplot/plotarea.ui
