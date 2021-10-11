#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QSharedPointer>

#include <realtimeplot/plotarea.h>
#include <realtimeplot/pointstream.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    static const int SAMPLE_GENERATION_PERIOD = 5; // 5 ms
    quint64 sampleNumber = 0;

    QList <QSharedPointer<PointStream<point_t>>> dataPoints;

    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
