#ifndef INPUTNUMCONTROLHORIZON_H
#define INPUTNUMCONTROLHORIZON_H

#include "inputNumControl.hpp"

class InputNumControlHorizon : public InputNumControl
{
public:
    explicit InputNumControlHorizon(QWidget* parent = nullptr);

protected slots:
    void onPanelSwitchButtonClicked();
    virtual void onTypeChanged();

protected:
    virtual int groupButtonsPerPage() const;

private:
    SelectButton m_button_switch_panel_picker;
    SelectButton m_button_switch_panel_encoder;
    SelectButton m_button_switch_panel_input_num;
};

#endif // INPUTNUMCONTROLHORIZON_H
