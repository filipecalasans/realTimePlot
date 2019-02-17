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

    startTimer(PERIOD_OF_FRAMES);
}

PlotArea::~PlotArea()
{
    delete ui;
}

void PlotArea::addPointStream(QSharedPointer<PointStream> points)
{
    QCPGraph *graph = addGraph(axisRect(0)->axis(QCPAxis::atBottom), axisRect(0)->axis(QCPAxis::atLeft));
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
    for(PointStream *stream : pointStream.keys()) {
        QList<QPointF> data = stream->getRecentPoints(stream->getSamplesPerSeconds() * windowLengthInSeconds);
        QCPDataMap *dataMap = new QCPDataMap();
        quint32 windowNumberLastSample = ((quint32)data.last().x())/((quint32)(windowLengthInSeconds*stream->getSamplesPerSeconds()));
        for(int i=data.size()-1; i>=0; i--) {
            const QPointF& point = data[i];
            quint32 windowNumber = static_cast<quint32>(point.x())/
                    (static_cast<quint32>(windowLengthInSeconds*stream->getSamplesPerSeconds()));
            if(windowNumber != windowNumberLastSample) {
                break;
            }
            quint64 pointX = static_cast<quint32>(point.x());
            double x = ((pointX)%((quint64)(windowLengthInSeconds*stream->getSamplesPerSeconds())))/((double)stream->getSamplesPerSeconds());
            dataMap->insert(x, QCPData(x,point.y()));
        }
        pointStream[stream]->setData(dataMap, false);
    }

    //axisRect()->axis(QCPAxis::atLeft)->rescale(true);

    replot();
}








