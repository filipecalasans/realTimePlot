#include "plotarea.h"
#include "ui_plotarea.h"

#include <qmath.h>

PlotArea::PlotArea(QWidget *parent) :
    QCustomPlot(parent),
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

    startTimer(TIME_BETWEEN_FRAMES_MS);
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
    windowLengthInSeconds = value;
    axisRect()->axis(QCPAxis::atBottom)->setRange(0, windowLengthInSeconds);
}

void PlotArea::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    update();
}

void PlotArea::update()
{
    for(auto* stream : pointStream.keys()) {
        size_t numPointsPerWindows = static_cast<quint32>(
                    stream->getSamplesPerSeconds() * windowLengthInSeconds);

        // Read exhibition window.
        QVector<point_t> data = stream->getRecentPoints(numPointsPerWindows);
        QCPDataMap *dataMap = new QCPDataMap();

        if(data.isEmpty()){
            continue;
        }

        qreal lastX = data.last().x;
        quint32 windowNumberLastSample = static_cast<quint32>(lastX)/numPointsPerWindows;

        /* TODO: Resample the point stream to adjust to the widget resolution */
        for(int i=data.size()-1; i>=0; i--) {
            /*
             * Read
             */
            const point_t& point = data[i];
            quint64 pointX = static_cast<quint64>(point.x);
            quint32 windowNumber = pointX/numPointsPerWindows;

            double x = ((pointX)%(static_cast<quint64>(numPointsPerWindows)))/
                    static_cast<double>(stream->getSamplesPerSeconds());
            dataMap->insert(x, QCPData(x, point.y));
        }
        pointStream[stream]->setData(dataMap, false);

        // Discard points from the exhibition window if the windows has filled up.
        if (stream->getStreamSize() >= numPointsPerWindows) {
            stream->discardPoints(numPointsPerWindows);
        }
    }

    //axisRect()->axis(QCPAxis::atLeft)->rescale(true);
    replot();
}








