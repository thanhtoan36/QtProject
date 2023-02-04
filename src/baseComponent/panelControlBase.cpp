#include "include/baseComponent/panelControlBase.h"

PanelControlBase::PanelControlBase(QWidget *parent)
    : QWidget{parent}
{
}

void PanelControlBase::PrepareUi()
{
    if (m_ui_initialized)
        return;
    m_ui_initialized = true;

    SetupUiComponents();
    SetupUiEvents();
}
