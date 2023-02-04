#ifndef COLORPICKERCONTROL_H
#define COLORPICKERCONTROL_H

#include "../baseComponent/panelControlBase.h"
#include "colorPickerControl_datatypes.h"
#include <QLabel>

class ColorPickerControl : public PanelControlBase
{
public:
    ColorPickerControl(QWidget *parent = nullptr);
    void SetDispParamData(COLOR_PICKER_DISP_PARAM *param);

protected:
    virtual void SetupUiComponents();

protected:
    QLabel m_label_title;

    COLOR_PICKER_DISP_PARAM m_disp_param;
};

#endif // COLORPICKERCONTROL_H
