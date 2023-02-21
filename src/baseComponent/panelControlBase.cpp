#include "baseComponent/panelControlBase.h"
#include <QFile>
#define SCREEN_BACKGROUND_COLOR qRgb(34, 43, 53)  // background color of panels

PanelControlBase::PanelControlBase(QWidget *parent)
    : QWidget{parent},
      m_background(this)
{
    m_background.setGridSize(QSize(1, 1));
    m_background.setCellSize(size());

    m_background.setBackgroundColor(SCREEN_BACKGROUND_COLOR);
    m_background.setGridLineColor(Qt::transparent);

    QFile style(":/resources/style.css");
    style.open(QFile::ReadOnly);

    setStyleSheet(style.readAll());
}

int PanelControlBase::CalulateNumberOfPages(int item_count, int items_per_page)
{
    if (items_per_page == 0)
        return 0;
    return (item_count - 1) / items_per_page + 1;
}

int PanelControlBase::CalculateNumberOfVisibleItems(int item_count, int items_per_page, int page_index)
{
    if (items_per_page == 0)
        return 0;
    return (std::min((page_index + 1) * items_per_page, item_count) - 1) % items_per_page + 1;
}

void PanelControlBase::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    m_background.setCellSize(size());
}
