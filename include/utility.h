#ifndef UTILITY_H
#define UTILITY_H

#include <QSharedPointer>
#include <QPoint>
#include <QSize>
#include <QDebug>

// Same as std::make_shared, but use QObject::deleteLater() to delete
template <class T, class ...Args>
QSharedPointer<T> MakeSharedQObject(Args&&... args)
{
    auto raw_pointer = new T(std::forward<Args>(args)...);
    return QSharedPointer<T>(raw_pointer, &QObject::deleteLater);
}

// Map a value from a range (in) to another (out)
// https://cdn.arduino.cc/reference/en/language/functions/math/map/
float map(float x, float in_min, float in_max, float out_min, float out_max);

template <class T>
T bounded(T value, T min, T max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
#endif // UTILITY_H
