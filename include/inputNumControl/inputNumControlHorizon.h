//--------------------------------------------------------------------------
// [ ファイル名 ] : inputNumControlHorizon.h
// [ 概      要 ] : InputNumControl horizon widget
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef INPUTNUMCONTROLHORIZON_H
#define INPUTNUMCONTROLHORIZON_H

#include "inputNumControl.h"

class InputNumControlHorizon : public InputNumControl
{
public:
    explicit InputNumControlHorizon(QWidget* parent = nullptr);

protected slots:
    void OnPanelSwitchButtonClicked();
    virtual void OnTypeChanged();

protected:
    virtual int GroupButtonsPerPage() const;

private:
    SelectButton m_button_switch_panel_picker;
    SelectButton m_button_switch_panel_encoder;
    SelectButton m_button_switch_panel_input_num;
};

#endif // INPUTNUMCONTROLHORIZON_H
