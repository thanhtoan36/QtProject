#ifndef INTENSITYCONTROL_H
#define INTENSITYCONTROL_H

#include "../baseComponent/panelControlBase.h"
#include "baseComponent/customPushButton.h"
#include <QLabel>
#include <QVector>
#include <QSharedPointer>

class IntensityControl : public PanelControlBase
{
    Q_OBJECT
public:
    IntensityControl(QWidget *parent = nullptr);

protected:
    virtual void SetupUiComponents() override;

protected:
    QLabel m_label_title;
    QVector<QSharedPointer<CustomPushButton>> m_menu_buttons;
    QVector<QSharedPointer<CustomPushButton>> m_intensity_buttons;
    CustomPushButton m_return_button;
};

#endif // INTENSITYCONTROL_H
