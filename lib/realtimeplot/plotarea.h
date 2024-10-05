    #ifndef PLOTAREA_H
#define PLOTAREA_H

#include <chrono>

#include <QWidget>
#include <QSharedPointer>
#include <QTimer>

#include <qcustomplot/qcustomplot.h>

#include "pointstream.h"

namespace Ui {
class PlotArea;
}

/**
 * PlotAre refer to a a graph area where N curves can be ploted.
 * Each curve is backed by a PointStream.
 */  
class PlotArea : public QCustomPlot
{
    Q_OBJECT

public:

    enum class State {
       Stopped = 0,
       Running = 1,
    };
    static constexpr std::chrono::milliseconds TIME_BETWEEN_FRAMES_MS{1000 / 60}; // 60 fps


    explicit PlotArea(QWidget *parent = nullptr);
    ~PlotArea();

    void addPointStream (QSharedPointer<PointStream<point_t>> points);
    
    /// Start periodic plot refresh at $refresh_ms.
    bool start(std::chrono::milliseconds refresh_ms = TIME_BETWEEN_FRAMES_MS);
    /// Stop periodic plot refresh.
    void stop();
    /// Update plot area with the most recent data available in the streams.
    void update();
    State getState();

    double getWindowLengthInSeconds() const;
    void setWindowLengthInSeconds(double value);

protected:

    void timerEvent(QTimerEvent *event);
    /// After window lenght change plot window should be clean and recalculated.
    void setPlotWindowCleaning();
    void handlePlotWindowCleaning();

private:
    Ui::PlotArea *ui;
    QMap<PointStream<point_t>*, QCPGraph *> pointStream;
    QMap<PointStream<point_t>*, QSharedPointer<PointStream<point_t>>> references;
    int timerId;
    double windowLengthInSeconds = 4.0;

    struct CleaningState {
        bool deferred = false;
        bool pending = false;
    } cleaningState;

};

#endif // PLOTAREA_H
