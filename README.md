# Real Time Plot

This project provides Qt/C++ primitives to ease building real time plot UI.

# Dependencies

* Qt >= 5.0
* [QCustomPlot](http://www.qcustomplot.com/index.php/introduction) (included in this repo)
* Gcc >= 6
   
# How to Use

Place the folders *realtimeplot* and *QCustoPlot* inside your Qt project folder. The folder *realtimeplot* contains the primitives, while the folder *QCustomPlot* is the 3rd party library of same name.
Notice, that you might need to add the folder *realtimeplot* to the **INCLUDEPATH**, otherwise you'll face errors generating the C++ code correspondent to the UI element *plot.ui*. 

```make
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

```

### The UI element PlotArea 

We have created the UI component *plortarea.ui* which can be added to your application using QDesigner. *PlotArea* is 
a component that inherits the class QCustomPlot and provides a Real Time Plot area similar to Oscilloscopes.

You might want to see QCustomPlot documentation to see what features you have by default in the Plot. Fell free to customize or subclass PlotArea as needed.

## Example

This example instantiates a fixed number of curves each one backed for its own stream of points. The curves are all added to the same PlotArea as you can notice in the *MainWindow*'s constructor.

We simulate a stream of points coming in real time in the **timerEvent**, which runs at the periodicity of **SAMPLE_GENERATION_PERIOD** ms.

You might want to check the file MainWindow.ui to see how we placed the **PlotAre** component to the MainWindow. However, if you need a more dynamic layout you might want to instantiate it programmatically.

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

## TODO

* Implement Circular Buffer
* Optimize the class **Poitstream** to use Circular Buffer
* Implement GraphFactory to handle CGraph Style
