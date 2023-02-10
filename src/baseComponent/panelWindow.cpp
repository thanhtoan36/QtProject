#include "baseComponent/panelWindow.h"

#define SCREEN_BACKGROUND_COLOR qRgb(34, 43, 53)  // background color of panels

PanelWindow::PanelWindow(QWidget *parent)
    : QDialog{parent}
{
    // Turn off window border and default buttons
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    QPalette palette {};
    palette.setColor(QPalette::Window, SCREEN_BACKGROUND_COLOR);
    palette.setColor(QPalette::Foreground, Qt::white);

    setAutoFillBackground(true);
    setPalette(palette);
}

void PanelWindow::AttachPanelControl(QSharedPointer<PanelControlBase> panel)
{
    DetachPanelControl();

    if (panel) {
        panel->setParent(this);
        m_current_panel_control = panel;

        connect(panel.get(), &QWidget::windowTitleChanged, this, &QWidget::setWindowTitle);
        // connect(panel.get(), &QWidget::windowIconChanged, this, &QWidget::setWindowIcon);

        setWindowTitle(panel->windowTitle());
        // setWindowIcon(panel->windowIcon());
        setFixedSize(panel->size());

        // show();
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
