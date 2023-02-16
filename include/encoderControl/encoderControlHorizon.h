#ifndef ENCODERCONTROLHORIZON_H
#define ENCODERCONTROLHORIZON_H

#include "encoderControl/encoderControl.hpp"
#include "baseComponent/selectButton.h"

class EncoderControlHorizon : public EncoderControl
{
    Q_OBJECT
public:
    EncoderControlHorizon(QWidget *parent = nullptr);
    void SetDispParamDataHorizon(ENCODER_DISP_PARAM *param);

protected slots:
    void onPanelSwitchButtonClicked();

protected:
    virtual void SetupUiComponents() override;
    virtual void setupEncoderPages() override;

protected:
    SelectButton m_button_switch_panel_picker;
    SelectButton m_button_switch_panel_encoder;
    SelectButton m_button_switch_panel_input_num;
};

#endif // ENCODERCONTROLHORIZON_H
