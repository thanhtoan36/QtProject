#ifndef COLORPICKERCONTROLHORIZON_H
#define COLORPICKERCONTROLHORIZON_H

#include "colorPickerControl.hpp"
#include "colorPickerControlHorizon_define.h"

class ColorPickerControlHorizon : public ColorPickerControl
{
    Q_OBJECT
public:
    explicit ColorPickerControlHorizon(QWidget* parent = nullptr);
    void SetDispParamDataHorizon(COLOR_PICKER_DISP_PARAM *param);

protected:
    virtual void SetupUiComponents() override;

private:
    SelectButton m_button_1;
    SelectButton m_button_2;
    SelectButton m_button_3;
};

#endif // COLORPICKERCONTROLHORIZON_H
