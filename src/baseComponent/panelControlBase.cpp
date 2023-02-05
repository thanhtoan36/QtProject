#include "include/baseComponent/panelControlBase.h"
#include <QFile>

PanelControlBase::PanelControlBase(QWidget *parent)
    : QWidget{parent},
      m_ui_initialized(false)
{
    QFile style(":/style.qss");
    style.open(QFile::ReadOnly);

    setStyleSheet(style.readAll());
}

void PanelControlBase::PrepareUi()
{
    if (m_ui_initialized)
        return;
    m_ui_initialized = true;

    // SetupUiComponents();
    SetupUiEvents();
}
