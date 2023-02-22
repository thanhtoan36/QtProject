//--------------------------------------------------------------------------
// [ ファイル名 ] : encoderControlHorizon.h
// [ 概      要 ] : EncoderControlHorizon
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef ENCODERCONTROLHORIZON_H
#define ENCODERCONTROLHORIZON_H

#include "encoderControl/encoderControl.h"
#include "baseComponent/selectButton.h"

class EncoderControlHorizon : public EncoderControl
{
    Q_OBJECT
public:
    EncoderControlHorizon(QWidget *parent = nullptr);
    virtual void SetDispParamData(ENCODER_DISP_PARAM *param) override;

protected slots:
    void OnPanelSwitchButtonClicked();

protected:
    virtual void SetupEncoderPages() override;

protected:
    SelectButton m_button_switch_panel_picker;
    SelectButton m_button_switch_panel_encoder;
    SelectButton m_button_switch_panel_input_num;
};

#endif // ENCODERCONTROLHORIZON_H
