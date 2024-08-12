#ifndef POINTSTREAM_H
#define POINTSTREAM_H

#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QPointF>
#include <QMutex>
#include <QMutexLocker>
#include <QVector>
#include <memory>

#include <ringbuffer/cpp/ringbufferwrapper.h>

typedef struct {
    double x;
    double y;
} point_t;

template<typename T = point_t, class=typename std::enable_if< std::is_pod<T>::value >::type>
class PointStream
{
public:

    static constexpr size_t DEFAULT_MAX_BUFFER_SIZE = (1 << 20);

    explicit PointStream() : 
        PointStream(DEFAULT_MAX_BUFFER_SIZE)
    {
    
    }

    explicit PointStream(size_t maxSize) :
        maxSize(maxSize)
    {
        buffer = std::make_unique<RingBufferWrapper>(maxSize);
        if (!buffer->isValid()) {
            qDebug() << "Error: Couldn't initialize the ring buffer.";
            QCoreApplication::exit(1);
        }
    }

    int getSamplesPerSeconds() const
    {
        return samplesPerSeconds;
    }

    void setSamplesPerSeconds(int value)
    {
        samplesPerSeconds = value;
    }

    QVector<T> getRecentPoints(size_t numPoints)
    {
        QVector<T> temp;
        temp.reserve(numPoints);
        {   
            size_t bufferNumElements = buffer->numElements<T>();
            QMutexLocker locker(&mutex);
            temp.resize(std::min(numPoints, bufferNumElements));
            buffer->peekMultiple(reinterpret_cast<uint8_t*>(temp.data()), temp.size() * sizeof(T));
        }
        return temp;
    }

    void appendPoints(const QVector<T> &newPoints)
    {
        QMutexLocker locker(&mutex);
        buffer->appendMultiple(reinterpret_cast<const uint8_t*>(newPoints.data()), sizeof(point_t) * newPoints.size());
    }

    void discardPoints(size_t numPoints)
    {
        QMutexLocker locker(&mutex);
        buffer->discardMultiple(sizeof(T) * numPoints);
    }

    void flush() {
        QMutexLocker locker(&mutex);
        buffer->clean();
    }

    size_t getStreamSize() const 
    { 
        return buffer->numElements<T>(); 
    }

private:

    QMutex mutex;
    int samplesPerSeconds = 1; //1Hz
    size_t maxSize = DEFAULT_MAX_BUFFER_SIZE;
    std::unique_ptr<RingBufferWrapper> buffer;
};

#endif // POINTSTREAM_H
