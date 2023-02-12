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

int calulateNumberOfPages(int itemCount, int itemsPerPage);
int calculateNumberOfVisibleItems(int itemsCount, int itemsPerPage, int pageIndex);

template <class T>
void placeChildrenIntoPanel(const QVector<QSharedPointer<T>> &children, QSize childSize, QPoint topLeft, int itemsPerRow, int maxColumns = 1) {
    for (int i  = 0; i < children.length(); ++i) {
        const int visualIndex = i % (itemsPerRow * maxColumns);
        const int row = visualIndex / itemsPerRow;
        const int col = visualIndex % itemsPerRow;

        auto &child = children[i];
        child->move(topLeft + QPoint(col * childSize.width(), row * childSize.height()));
    }
}

template <class T>
void updateChildrenVisibility(const QVector<QSharedPointer<T>> &children, int currentPage, int itemsPerPage) {
    int pageBeginIndex = currentPage * itemsPerPage;
    int pageEndIndex = (currentPage + 1) * itemsPerPage;

    for (int i  = 0; i < children.length(); ++i) {
        auto &child = children[i];
        child->setVisible(i >= pageBeginIndex && i < pageEndIndex);
    }
}

#endif // UTILITY_H
