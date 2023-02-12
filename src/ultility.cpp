#include "utility.h"
#include <QPoint>
#include <QVector>
#include <QWidget>

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int calulateNumberOfPages(int itemCount, int itemsPerPage)
{
    return (itemCount - 1) / itemsPerPage + 1;
}

int calculateNumberOfVisibleItems(int itemsCount, int itemsPerPage, int pageIndex)
{
    return (std::min((pageIndex + 1) * itemsPerPage, itemsCount) - 1) % itemsPerPage + 1;
}
