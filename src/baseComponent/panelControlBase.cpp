#include "baseComponent/panelControlBase.h"
#include <QFile>

PanelControlBase::PanelControlBase(QWidget *parent)
    : QWidget{parent}
{
    QFile style(":/resources/style.css");
    style.open(QFile::ReadOnly);

    setStyleSheet(style.readAll());
}

int PanelControlBase::calulateNumberOfPages(int itemCount, int itemsPerPage)
{
    if (itemsPerPage == 0)
        return 0;
    return (itemCount - 1) / itemsPerPage + 1;
}

int PanelControlBase::calculateNumberOfVisibleItems(int itemsCount, int itemsPerPage, int pageIndex)
{
    if (itemsPerPage == 0)
        return 0;
    return (std::min((pageIndex + 1) * itemsPerPage, itemsCount) - 1) % itemsPerPage + 1;
}
