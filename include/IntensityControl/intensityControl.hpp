#ifndef INTENSITYCONTROL_H
#define INTENSITYCONTROL_H

#include "../baseComponent/panelControlBase.h"
#include "baseComponent/customPushButton.h"
#include <QLabel>

class IntensityControl : public PanelControlBase
{
public:
    IntensityControl(QWidget *parent = nullptr);

protected:
    virtual void SetupUiComponents();
    virtual void SetupUiEvents();

private:
    QLabel m_label_title;
    CustomPushButton m_ff_button;
    CustomPushButton m_p10_button;
    CustomPushButton m_p5_button;
    CustomPushButton m_p1_button;
    CustomPushButton m_00_button;
    CustomPushButton m_n10_button;
    CustomPushButton m_n5_button;
    CustomPushButton m_n1_button;
    CustomPushButton m_70_button;
    CustomPushButton m_80_button;
    CustomPushButton m_90_button;
    CustomPushButton m_40_button;
    CustomPushButton m_50_button;
    CustomPushButton m_60_button;
    CustomPushButton m_10_button;
    CustomPushButton m_20_button;
    CustomPushButton m_30_button;
    CustomPushButton m_return_button;

    CustomPushButton m_empty1_button;
    CustomPushButton m_empty2_button;
    CustomPushButton m_empty3_button;
    CustomPushButton m_empty4_button;
    CustomPushButton m_empty5_button;
    CustomPushButton m_empty6_button;

};

#endif // INTENSITYCONTROL_H
