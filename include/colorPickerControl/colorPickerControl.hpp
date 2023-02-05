#ifndef COLORPICKERCONTROL_H
#define COLORPICKERCONTROL_H

#include "../baseComponent/panelControlBase.h"
#include "colorPickerControl_datatypes.h"

#include "../baseComponent/selectButton.h"
#include "../baseComponent/customPushButton.h"
#include "colorPickerControl/customColorPickerXY.h"
#include "colorPickerControl/customColorPickerRGB.h"

#include <QLabel>
#include <QSlider>

class ColorPickerControl : public PanelControlBase
{
public:
    ColorPickerControl(QWidget *parent = nullptr);
    void SetDispParamData(COLOR_PICKER_DISP_PARAM *param);

protected:
    virtual void SetupUiComponents();
    virtual void SetupUiEvents();

protected:
    COLOR_PICKER_DISP_PARAM m_disp_param;

    QLabel m_control_background;
    QLabel m_label_title;
    SelectButton m_button_xy;
    SelectButton m_button_rgb;

    CustomPushButton m_button_previous_tab; // ◀
    CustomPushButton m_button_next_tab;     // ▶

    QLabel m_label_setting;

    // XY tab
    CustomColorPickerXY m_picker_xy;

    // RGB tab
    CustomColorPickerRGB m_picker_rgb;

    QLabel m_label_title_x;
    QLabel m_label_value_x;
    QSlider m_slider_x;

    QLabel m_label_title_y;
    QLabel m_label_value_y;
    QSlider m_slider_y;

    // RGB tab
    QLabel m_label_title_h;
    QLabel m_label_value_h;
    QSlider m_slider_h;
    QLabel m_label_title_s;
    QLabel m_label_value_s;
    QSlider m_slider_s;
    QLabel m_label_title_v;
    QLabel m_label_value_v;
    QSlider m_slider_v;

    QVector<QWidget*> m_children_xy;
    QVector<QWidget*> m_children_rgb;
};

#endif // COLORPICKERCONTROL_H
