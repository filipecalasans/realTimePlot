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
               third-party/ \
               third-party/ringbuffer/src/ \

SOURCES += sample/main.cpp\
        sample/mainwindow.cpp \
        third-party/qcustomplot/qcustomplot.cpp \
        third-party/ringbuffer/src/ringbuffer/c/ringbuffer.c \
        third-party/ringbuffer/src/ringbuffer/cpp/ringbufferwrsampleer.cpp \
        lib/realtimeplot/plotarea.cpp \
        lib/realtimeplot/pointstream.cpp

HEADERS  += sample/mainwindow.h \
            third-party/qcustomplot/qcustomplot.h \
            third-party/ringbuffer/src/ringbuffer/c/ringbuffer.h \
            third-party/ringbuffer/src/ringbuffer/cpp/ringbufferwrapper.h \
            lib/realtimeplot/plotarea.h \
            lib/realtimeplot/pointstream.h

FORMS    += sample/mainwindow.ui \
            lib/realtimeplot/plotarea.ui
