#ifndef POINTSTREAM_H
#define POINTSTREAM_H

#include <QObject>
#include <QPointF>

class PointStream : public QObject
{
    Q_OBJECT
public:

    static const int MAX_BUFFER_SIZE = 20000;

    explicit PointStream(QObject *parent = 0);

    void appendPoints(const QList<QPointF>&newPoints);
    QList<QPointF> getRecentPoints(int numPoints);

    int getSamplesPerSeconds() const;
    void setSamplesPerSeconds(int value);
    void discardPoints(int numPoints);

private:

    int samplesPerSeconds = 1; //1Hz
    QList<QPointF> points;

};

#endif // POINTSTREAM_H
