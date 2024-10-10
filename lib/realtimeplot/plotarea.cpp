#include "plotarea.h"
#include "ui_plotarea.h"

#include <chrono>
#include <qmath.h>

PlotArea::PlotArea(QWidget *parent) :
    QCustomPlot(parent),
    timerId(0),
    ui(new Ui::PlotArea)
{
    ui->setupUi(this);

    plotLayout()->clear();

    QCPAxisRect *wideAxisRect = new QCPAxisRect(this);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->removeAxis(wideAxisRect->axis(QCPAxis::atRight));
    wideAxisRect->removeAxis(wideAxisRect->axis(QCPAxis::atTop));
    wideAxisRect->axis(QCPAxis::atLeft)->setRange(-1.5, 1.5);
    plotLayout()->addElement(0, 0, wideAxisRect);
}

PlotArea::~PlotArea()
{
    delete ui;
}

void PlotArea::addPointStream(QSharedPointer<PointStream<point_t>> points)
{
    QCPGraph *graph = addGraph(axisRect(0)->axis(QCPAxis::atBottom),
                               axisRect(0)->axis(QCPAxis::atLeft));
    QPen pen;
    pen.setColor(QColor(Qt::red));
    pen.setWidth(1);
    graph->setPen(pen);
    graph->setLineStyle(QCPGraph::lsLine);

    /*
     * Keep a reference container to store shared pointer.
     */
    pointStream.insert(points.get(), graph);
    references.insert(points.get(), points);
}

double PlotArea::getWindowLengthInSeconds() const
{
    return windowLengthInSeconds;
}

void PlotArea::setWindowLengthInSeconds(double value)
{
    const bool shortening = value < windowLengthInSeconds;
    windowLengthInSeconds = value;
    axisRect()->axis(QCPAxis::atBottom)->setRange(0, windowLengthInSeconds);
    if (shortening) {
        setPlotWindowCleaning();
    }
}

void PlotArea::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    update();
}

void PlotArea::setPlotWindowCleaning() {
    if (getState() == State::Stopped) {
        cleaningState.deferred = true;
        return;
    }
    cleaningState.pending = true;
}

void PlotArea::handlePlotWindowCleaning() {
    bool clean = false;
    if (cleaningState.pending) {
        Q_ASSERT(getState() == State::Running);
        clean = true;
        cleaningState.pending = false;
    }
    if (cleaningState.deferred && getState() == State::Running) {
        clean = true;
        cleaningState.deferred = false;
    }
    // Do the cleaning if conditions are satisfied.
    if (clean) {
        for (auto& stream : pointStream.keys()) {
            stream->flush();
        }
    }
}

bool PlotArea::start(std::chrono::milliseconds refresh_ms) {
    if (timerId != 0) {
        return false;
    }
    timerId = startTimer(std::chrono::milliseconds(refresh_ms));
    return timerId != 0;
}

void PlotArea::stop() {
    if (timerId != 0) {
        killTimer(timerId);
        timerId = 0;
    }
}

PlotArea::State PlotArea::getState() {
    return timerId == 0 ? State::Stopped : State::Running;
}

void PlotArea::update()
{
    handlePlotWindowCleaning();


    for(auto* stream : pointStream.keys()) {
        size_t numPointsPerWindow = static_cast<quint32>(
                    stream->getSamplesPerSeconds() * windowLengthInSeconds);

        const auto streamSize = stream->getStreamSize();
        if (streamSize >= numPointsPerWindow) {
            stream->discardPoints(streamSize - streamSize % numPointsPerWindow);
        }

        // Read exhibition window.
        QVector<point_t> data = stream->getRecentPoints(numPointsPerWindow);
        if(data.isEmpty()){
            continue;
        }

        QCPDataMap *dataMap = new QCPDataMap();
        qreal lastX = data.last().x;
        quint32 windowNumberLastSample = static_cast<quint32>(lastX) / numPointsPerWindow;

        /* TODO: Resample the point stream to adjust to the widget resolution */
        for(int i=data.size()-1; i>=0; i--) {
            /*
             * Read
             */
            const point_t& point = data[i];
            const double x = static_cast<double>(windowLengthInSeconds * i) / static_cast<double>(numPointsPerWindow);
            dataMap->insert(x, QCPData(x, point.y));
        }
        pointStream[stream]->setData(dataMap, false);
    }
    replot();
}








