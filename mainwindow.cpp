#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <qmath.h>

#define POINT_STREAM_NUM   1

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i=0; i<POINT_STREAM_NUM; i++) {
        PointStream *stream = new PointStream();
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
    qDeleteAll(dataPoints);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)

    static int frame_count = 0;

    const double sineFrequency = 2.0; // 2Hz
    const double phase = 0.0;

    for(int i=0; i<dataPoints.size(); i++) {
        double value = qSin(2.0*M_PI*sineFrequency*sampleNumber*(((double)SAMPLE_GENERATION_PERIOD/1000.0) + phase));
        //qDebug() << sampleNumber << value;
        QList<QPointF> data;
        data << QPointF(sampleNumber, value);
        dataPoints.at(i)->appendPoints(data);
    }

    if(SAMPLE_GENERATION_PERIOD * frame_count >= PlotArea::PERIOD_OF_FRAMES) {
        //ui->plotArea->update();
        frame_count = -1;
        //qDebug() << "update Plot";
    }

    sampleNumber++;
    frame_count++;

}
