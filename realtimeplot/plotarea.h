#ifndef PLOTAREA_H
#define PLOTAREA_H

#include <QWidget>
#include <QSharedPointer>
#include "QCustomPlot/qcustomplot.h"
#include "pointstream.h"

namespace Ui {
class PlotArea;
}

class PlotArea : public QCustomPlot
{
    Q_OBJECT

public:

    static const int TIME_BETWEEN_FRAMES_MS = 50; //100 ms - 20fps

    explicit PlotArea(QWidget *parent = nullptr);

    ~PlotArea();

    void addPointStream (QSharedPointer<PointStream> points);

    void update();

    double getWindowLengthInSeconds() const;

    void setWindowLengthInSeconds(double value);

    void timerEvent(QTimerEvent *event);

private:

    Ui::PlotArea *ui;
    QMap<PointStream *, QCPGraph *> pointStream;
    QMap<PointStream *, QSharedPointer<PointStream> > references;
    double windowLengthInSeconds = 4.0;
};

#endif // PLOTAREA_H
