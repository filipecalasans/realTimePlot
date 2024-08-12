#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qmath.h>
#include <QDebug>
#include <QTranslator>

#define POINT_STREAM_NUM 4

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i=0; i<POINT_STREAM_NUM; i++) {
        QSharedPointer<PointStream<point_t>> stream(new PointStream<point_t>());
        stream->setSamplesPerSeconds(1000/SAMPLE_GENERATION_PERIOD);
        dataPoints << stream;
        ui->plotArea->addPointStream(stream);
    }

    ui->playPauseButton->setText("Play");
    ui->plotArea->setWindowLengthInSeconds(4.0);

    connect(ui->playPauseButton, &QPushButton::released, this, [=]() {
        qDebug() << "Play/Pause Clicked";
        auto state = ui->plotArea->getState();
        if (state == PlotArea::State::Running) {
            ui->plotArea->stop();
            ui->playPauseButton->setText(QPushButton::tr("Play"));
        } else {
            Q_ASSERT(ui->plotArea->start());
            ui->playPauseButton->setText(QPushButton::tr("Pause"));
        }
    });

    dataGenerationTimer = startTimer(SAMPLE_GENERATION_PERIOD);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_ASSERT(dataGenerationTimer == event->timerId());

    constexpr double freq = 1.0; // 2Hz
    const double samplePeriod = static_cast<double>(SAMPLE_GENERATION_PERIOD)/1000.0;
    constexpr double twoPi = 2.0*M_PI;

    for(int i=0; i<dataPoints.size(); i++) {
        double phase = (i*M_PI)/dataPoints.size();
        double value = qSin(phase + twoPi*freq*sampleNumber*samplePeriod);
        //qDebug() << sampleNumber << value;
        QVector<point_t> data;
        point_t point = {
            .x = static_cast<double>(sampleNumber),
            .y = value,
        };

        data << point;
        dataPoints.at(i)->appendPoints(data);
    }

    sampleNumber++;
}
