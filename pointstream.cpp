#include "pointstream.h"

#include <QDebug>

PointStream::PointStream(QObject *parent) : QObject(parent)
{
    points.reserve(MAX_BUFFER_SIZE);
}

QList<QPointF> PointStream::getRecentPoints(int numPoints)
{
    QList<QPointF> temp;

    int begin = points.count() - numPoints;
    if(begin < 0) {
        begin = 0;
    }

    for(int i=begin; i<points.count(); i++) {
        temp << points[i];
    }

    return temp;
}

int PointStream::getSamplesPerSeconds() const
{
    return samplesPerSeconds;
}

void PointStream::setSamplesPerSeconds(int value)
{
    samplesPerSeconds = value;
}

void PointStream::appendPoints(const QList<QPointF> &newPoints)
{
    if(points.size() + newPoints.size() > MAX_BUFFER_SIZE) {
        discardPoints(MAX_BUFFER_SIZE - (points.size() + newPoints.size()));
    }

    points.append(newPoints);

}

void PointStream::discardPoints(int numPoints) {
    qDebug() << "------------------------------------------>> DISCARD" << numPoints;
    for(int i=0; i<numPoints; i++) {
        //Recomendação do Qt para QList<T>.takeFirst()
        //Verification recommended in Qt docummentation
        if(!points.isEmpty()) {
            points.takeFirst();
        }
        else {
            return;
        }
    }
}

