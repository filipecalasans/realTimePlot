#ifndef POINTSTREAM_H
#define POINTSTREAM_H

#include <QObject>
#include <QPointF>
#include <QMutex>
#include <QVector>
#include <QQueue>

class PointStream : public QObject
{
    Q_OBJECT
public:

    static const int MAX_BUFFER_SIZE = 20000;

    explicit PointStream(QObject *parent = nullptr);
    explicit PointStream(int maxSize, QObject *parent = nullptr);

    void appendPoints(const QVector<QPointF>&newPoints);
    QVector<QPointF> getRecentPoints(int numPoints);

    int getSamplesPerSeconds() const;
    void setSamplesPerSeconds(int value);
    void discardPoints(int numPoints);

    const QPointF& getSample(int sampleNum);
    int getStreamSize() const { return points.size(); }

private:

    QMutex mutex;
    int samplesPerSeconds = 1; //1Hz
    QVector<QPointF> points;
    int maxSize = MAX_BUFFER_SIZE;
    quint32 padding;
};

#endif // POINTSTREAM_H
