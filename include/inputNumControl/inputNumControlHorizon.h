#ifndef INPUTNUMCONTROLHORIZON_H
#define INPUTNUMCONTROLHORIZON_H

#include "inputNumControl.hpp"

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
