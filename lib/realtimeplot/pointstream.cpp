#include "pointstream.h"

#include <QDebug>
#include <QMutexLocker>

PointStream::PointStream(QObject *parent) : QObject(parent),
    maxSize(MAX_BUFFER_SIZE)
{
    points.reserve(maxSize*2);
}

PointStream::PointStream(int maxSize, QObject *parent) : QObject(parent),
    maxSize(maxSize)
{
     points.reserve(maxSize*2);
}

QVector<QPointF> PointStream::getRecentPoints(int numPoints)
{
    QVector<QPointF> temp;
    temp.reserve(numPoints);
    {
        QMutexLocker locker(&mutex);
        int begin = points.size() - numPoints;
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

void PointStream::appendPoints(const QVector<QPointF> &newPoints)
{
    QMutexLocker locker(&mutex);
    if(points.size() + newPoints.size() > maxSize) {
        discardPoints(maxSize - (points.size() + newPoints.size()));
    }

    points.append(newPoints);
}

void PointStream::discardPoints(int numPoints)
{
    QMutexLocker locker(&mutex);
    for(int i=0; i<numPoints; i++) {

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

