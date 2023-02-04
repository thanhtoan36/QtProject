#ifndef PANELWINDOW_H
#define PANELWINDOW_H

#include <QPointer>
#include <QDialog>

#include "panelControlBase.h"

class PanelWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PanelWindow(QWidget *parent = nullptr);

    void AttachPanelControl(QPointer<PanelControlBase> panel);
    void DetachPanelControl();

signals:

private:
    QPointer<PanelControlBase> m_current_panel_control {};

};

#endif // PANELWINDOW_H
