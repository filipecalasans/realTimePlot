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
    plotLayout()->addElement(0, 0, wideAxisRect);

    startTimer(PERIOD_OF_FRAMES);
}

PlotArea::~PlotArea()
{
    delete ui;
}

void PlotArea::addPointStream(PointStream *points)
{
    QCPGraph *graph = addGraph(axisRect(0)->axis(QCPAxis::atBottom), axisRect(0)->axis(QCPAxis::atLeft));

    /*
     * Adiciona uma Fonte de pontos e uma nova curva associada
     * a essa fonte de pontos na área de plotagem.
     *
     * Add a new point stream and a graph that is associated
     * to this pointStream to the Plot Area.
     */
    pointStream.insert(points, graph);
}

double PlotArea::getWindowLengthInSeconds() const
{
    return windowLengthInSeconds;
}

void PlotArea::setWindowLengthInSeconds(double value)
{
    windowLengthInSeconds = value;
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
        quint32 windowNumberLastSample = ((quint32)data.last().x())%((quint32)(windowLengthInSeconds*stream->getSamplesPerSeconds()));
        for(int i=data.size()-1; i>=0; i++) {
            QPointF point = data[i];
            quint32 windowNumber = ((quint32)point.x())%((quint32)(windowLengthInSeconds*stream->getSamplesPerSeconds()));
            if(windowNumber != windowNumberLastSample) {
                break;
            }
            double x = ((double)stream->getSamplesPerSeconds())/point.x();
            dataMap->insert(x, QCPData(x,point.y()));
        }
        pointStream[stream]->setData(dataMap, false);
    }

    axisRect()->axis(QCPAxis::atLeft)->rescale(true);

    replot();
}








