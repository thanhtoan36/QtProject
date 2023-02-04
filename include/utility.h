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

#endif // UTILITY_H
