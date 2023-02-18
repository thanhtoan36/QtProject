#include "baseComponent/panelControlBase.h"
#include <QFile>

PanelControlBase::PanelControlBase(QWidget *parent)
    : QWidget{parent},
      m_ui_initialized(false)
{
    QFile style(":/resources/style.css");
    style.open(QFile::ReadOnly);

    setStyleSheet(style.readAll());
}

void PanelControlBase::PrepareUi()
{
    if (m_ui_initialized)
        return;
    m_ui_initialized = true;

    SetupUiComponents();
    // SetupUiEvents();
}

int PanelControlBase::calulateNumberOfPages(int itemCount, int itemsPerPage)
{
    return (itemCount - 1) / itemsPerPage + 1;
}

int PanelControlBase::calculateNumberOfVisibleItems(int itemsCount, int itemsPerPage, int pageIndex)
{
    return (std::min((pageIndex + 1) * itemsPerPage, itemsCount) - 1) % itemsPerPage + 1;
}
