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

protected:
    virtual void SetupUiComponents() override;
    virtual void setupEncoderPages() override;

protected:
    SelectButton m_button_1;
    SelectButton m_button_2;
    SelectButton m_button_3;
};

#endif // ENCODERCONTROLHORIZON_H
