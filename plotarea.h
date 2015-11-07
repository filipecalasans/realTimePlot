#ifndef PLOTAREA_H
#define PLOTAREA_H

#include <QWidget>

#include "QCustomPlot/qcustomplot.h"
#include "pointstream.h"

namespace Ui {
class PlotArea;
}

class PlotArea : public QCustomPlot
{
    Q_OBJECT

public:
    explicit PlotArea(QWidget *parent = 0);
    ~PlotArea();

    void addPointStream (PointStream *points);
    void update();

    double getWindowLengthInSeconds() const;
    void setWindowLengthInSeconds(double value);

    void timerEvent(QTimerEvent *event);

private:

    static const int PERIOD_OF_FRAMES = 100;
    Ui::PlotArea *ui;
    QMap<PointStream *, QCPGraph *> pointStream;
    double windowLengthInSeconds = 4.0;



};

#endif // PLOTAREA_H
