# Real Time Plot

Real Time plot is a library based on QCustomPlot which provides Qt/C++ primitives to ease building real time plot UI.

# Features

* Dynamic Window-length.
* Multi-plot lines in the same graph area.
* Dynamic Refresh rate.
* Play/Pause presentation.
* Defines custom Qt UI element that can be used in the QtCreator editor for static layouts.

# Dependencies

* Qt >= 5.11
* [QCustomPlot](http://www.qcustomplot.com/index.php/introduction) (included in this repo)
* Gcc >= 6

# How to Build

The project supports `qmake` and `CMake` build systems. Both are supported by QtCreator, and can be used to build and debug.

We recommend leveraging QtCreator when you have more than one Qt version installed in your system. QtCreator provides a nice interface to select the desired `toolchain` making sure `CMake` and `qmake` identify the correct Qt Version.

# How to Build Nix OSes

Use the script `build.sh` to build the project in Linux/MacOS. The script accepts passing
the QT5_DIR env variable where you can specify any custom Qt5 installation path.

```bash
# Build
./build.sh

# Or build with custom QT installation path
QT5_DIR=$HOME/my/qt ./build.sh

# Run the app example
./run-sample.sh
```


# How to Build macOS (Brew)

Use the script `build-macOs.sh` to build the project in macOS.

```bash
# Install Qt5 using brew.
$ brew install qt5

# Build macOS
./build-macOs.sh

# Run the app example
./run-sample.sh
```


# How to use this library on CMake based projects

Currently, we export `realtimeplot.cmake`  and `qcustomplot.cmake` inside the folder `external`. They are generated when you run `cmake` for the first time, which can be imported from your top level CMake project. 

NOTE: Please link your application binary to `realtimeplot`.

Find a minimal example below that creates a `cmake` project for an application in a different directory tree.

```cmake
cmake_minimum_required(VERSION 3.1.0)
project(real_time_plot VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include("../realTimePlot/exported/qcustomplot.cmake")
include("../realTimePlot/exported/realtimeplot.cmake")

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

add_executable(test_import main.cpp)
target_link_libraries(test_import realtimeplot)
```

This `CMakeLists.txt` builds a single `main.cpp` into `**test_import**` binary and links to realtimeplot. In order to validate that we are able to use real time plot, `main.cpp` imports from the library as follow:


```cpp
#include <QDebug>
#include <iostream>

#include <realtimeplot/plotarea.h>

int main(int argc, char** argv)
{
  Q_UNUSED(argc)
  Q_UNUSED(argv)
  qDebug() << "Testing...";
  return 0;
}
```

## How to use this library on qmake based projects

In this case, you will need to place the source in your project so it can be compiled. You will need
to include the folders `lib` and `third-party`, the former contains the realtimeplot library, and the latter contains `QCustomPlot`. Also make sure you update the variable `INCLUDEPATH`, so you can properly find the headers.

```make
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

SOURCES += app/main.cpp\
        app/mainwindow.cpp \
        third-party/qcustomplot/qcustomplot.cpp \
        third-party/ringbuffer/src/ringbuffer/c/ringbuffer.c \
        third-party/ringbuffer/src/ringbuffer/cpp/ringbufferwrapper.cpp \
        lib/realtimeplot/plotarea.cpp \
        lib/realtimeplot/pointstream.cpp

HEADERS  += app/mainwindow.h \
            third-party/qcustomplot/qcustomplot.h \
            third-party/ringbuffer/src/ringbuffer/c/ringbuffer.h \
            third-party/ringbuffer/src/ringbuffer/cpp/ringbufferwrapper.h \
            lib/realtimeplot/plotarea.h \
            lib/realtimeplot/pointstream.h

FORMS    += app/mainwindow.ui \
            lib/realtimeplot/plotarea.ui
```

### The UI element *PlotArea*

*PlotArea* is an UI component that inherits the class *QCustomPlot* and provides Real Time Plot similar to an Oscilloscope.

You might want to see the QCustomPlot documentation to see what features it provides by default. Feel free to customize or subclass *PlotArea* as needed.

## Example

This example instantiates a fixed number of curves, each one backed by its own stream of points. The curves are added to the same *PlotArea* as you can notice in the *MainWindow*'s constructor.

We simulate a real-time stream of points in the **timerEvent** handler, which runs at the periodicity of **SAMPLE_GENERATION_PERIOD**.

You can check the file MainWindow.ui to see how we placed the **PlotArea** component to the MainWindow. However, if you need a more dynamic layout I recomment you to instantiate it programmatically, so you can have full control over the layout.

```c++
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <qmath.h>

#define POINT_STREAM_NUM 4

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i=0; i<POINT_STREAM_NUM; i++) {
        QSharedPointer<PointStream> stream(new PointStream());
        stream->setSamplesPerSeconds(1000/SAMPLE_GENERATION_PERIOD);
        dataPoints << stream;
        ui->plotArea->addPointStream(stream);
    }

    ui->plotArea->setWindowLengthInSeconds(4.0);

    startTimer(SAMPLE_GENERATION_PERIOD);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)

    constexpr double twoPi = 2.0*M_PI;
    constexpr double freq = 1.0; // 2Hz
    const double samplePeriod =
        static_cast<double>(SAMPLE_GENERATION_PERIOD)/1000.0;

    for(int i=0; i<dataPoints.size(); i++) {
        double phase = (i*M_PI)/dataPoints.size();
        double value = qSin(phase + twoPi*freq*sampleNumber*samplePeriod);
        //qDebug() << sampleNumber << value;
        QVector<QPointF> data;
        data << QPointF(sampleNumber, value);
        dataPoints.at(i)->appendPoints(data);
    }

    sampleNumber++;
}

```

![](example.gif)

