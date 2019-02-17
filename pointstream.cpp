#include "pointstream.h"

#include <QDebug>
#include <QMutexLocker>

PointStream::PointStream(QObject *parent) : QObject(parent)
{
    points.reserve(MAX_BUFFER_SIZE*2);
}

QList<QPointF> PointStream::getRecentPoints(int numPoints)
{
    QList<QPointF> temp;
    temp.reserve(numPoints);

    {
        QMutexLocker locker(&mutex);
        int begin = points.count() - numPoints;
        if(begin < 0) {
            begin = 0;
        }

        for(auto& p : points)
        {
            temp << p;
        }
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
    QMutexLocker locker(&mutex);
    if(points.size() + newPoints.size() > MAX_BUFFER_SIZE) {
        discardPoints(MAX_BUFFER_SIZE - (points.size() + newPoints.size()));
    }

    points.append(newPoints);
}

void PointStream::discardPoints(int numPoints)
{
    QMutexLocker locker(&mutex);
    for(int i=0; i<numPoints; i++) {

        /* Verification recommended in Qt docummentation */
        if(!points.isEmpty()) {
            points.takeFirst();
        }
        else {
            return;
        }
    }
}

const QPointF& PointStream::getSample(int sampleNum)
{
    static const QPointF empty;
    QMutexLocker locker(&mutex);
    if(sampleNum < getStreamSize()) { return empty; }
    return points[sampleNum];
}

