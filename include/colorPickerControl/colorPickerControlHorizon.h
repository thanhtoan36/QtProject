#ifndef COLORPICKERCONTROLHORIZON_H
#define COLORPICKERCONTROLHORIZON_H

#include "colorPickerControl.hpp"
#include "colorPickerControlHorizon_define.h"

class ColorPickerControlHorizon : public ColorPickerControl
{
    Q_OBJECT
public:
    explicit ColorPickerControlHorizon(QWidget* parent = nullptr);

protected slots:
    void OnPanelSwitchButtonClicked();

private:
    SelectButton m_button_switch_panel_picker;
    SelectButton m_button_switch_panel_encoder;
    SelectButton m_button_switch_panel_input_num;
};

#endif // COLORPICKERCONTROLHORIZON_H
