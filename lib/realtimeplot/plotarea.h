#ifndef PLOTAREA_H
#define PLOTAREA_H

#include <QWidget>
#include <QSharedPointer>
#include <qcustomplot/qcustomplot.h>

#include "signal/pointstream.h"

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

    void addPointStream (QSharedPointer<PointStream<point_t>> points);

    void update();

    double getWindowLengthInSeconds() const;

    void setWindowLengthInSeconds(double value);

    void timerEvent(QTimerEvent *event);

private:

    Ui::PlotArea *ui;
    QMap<PointStream<point_t> *, QCPGraph *> pointStream;
    QMap<PointStream<point_t> *, QSharedPointer<PointStream<point_t> > > references;
    double windowLengthInSeconds = 4.0;
};

#endif // PLOTAREA_H
