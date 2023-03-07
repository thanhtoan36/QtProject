//--------------------------------------------------------------------------
// [ ファイル名 ] : inputNumControlHorizon.h
// [ 概      要 ] : 数値入力コントロール水平ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef INPUTNUMCONTROLHORIZON_H
#define INPUTNUMCONTROLHORIZON_H

#include "inputNumControl.h"

class InputNumControlHorizon : public InputNumControl
{
    Q_OBJECT
public:
    explicit InputNumControlHorizon( QWidget *parent = nullptr );

    virtual void SetDispParamData( INPUT_NUM_DISP_PARAM *param ) override;

protected slots:
    void OnPanelSwitchButtonClicked();
    virtual void OnTypeChanged() override;

protected:
    virtual int GroupButtonsPerPage() const override;

private:
    SelectButton m_button_switch_panel_picker;
    SelectButton m_button_switch_panel_encoder;
    SelectButton m_button_switch_panel_input_num;
};

#endif // INPUTNUMCONTROLHORIZON_H
