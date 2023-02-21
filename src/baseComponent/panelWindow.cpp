#include "baseComponent/panelWindow.h"

PanelWindow::PanelWindow(QWidget *parent)
    : QDialog{parent}
{
    // Turn off window border and default buttons
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
}

void PanelWindow::AttachPanelControl(QSharedPointer<PanelControlBase> panel)
{
    DetachPanelControl();

    if (panel) {
        panel->setParent(this);
        m_current_panel_control = panel;
        setFixedSize(panel->size());
    }
}

void PanelWindow::DetachPanelControl()
{
    if(m_current_panel_control) {
        m_current_panel_control->disconnect(this);
        m_current_panel_control->setParent(nullptr);
    }
    m_current_panel_control = nullptr;
    close();
}
