#ifndef UTILITY_H
#define UTILITY_H

#include <QSharedPointer>

// Same as std::make_shared, but use QObject::deleteLater() to delete
template <class T, class ...Args>
QSharedPointer<T> MakeSharedQObject(Args&&... args)
{
    auto raw_pointer = new T(std::forward<Args>(args)...);
    return QSharedPointer<T>(raw_pointer, &QObject::deleteLater);
}

// Map a value from a range (in) to another (out)
// https://cdn.arduino.cc/reference/en/language/functions/math/map/
// float map(float x, float in_min, float in_max, float out_min, float out_max) {
    // return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
// }

#endif // UTILITY_H
