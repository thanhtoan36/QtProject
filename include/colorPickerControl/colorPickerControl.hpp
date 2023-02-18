#ifndef COLORPICKERCONTROL_H
#define COLORPICKERCONTROL_H

#include "baseComponent/panelControlBase.h"
#include "baseComponent/gridBackground.h"
#include "colorPickerControl_datatypes.h"

#include "baseComponent/selectButton.h"
#include "baseComponent/customPushButton.h"
#include "colorPickerControl/customColorPickerXY.h"
#include "colorPickerControl/customColorPickerRGB.h"
#include "baseComponent/gridBackground.h"

#include <QLabel>
#include <QSlider>

class ColorPickerControl : public PanelControlBase
{
    Q_OBJECT

    Q_PROPERTY(ColorPickerType pickerType READ pickerType WRITE setPickerType NOTIFY pickerTypeChanged)
    Q_PROPERTY(QColor pickerColor READ pickerColor WRITE setPickerColor NOTIFY pickerColorChanged)

public:
    ColorPickerControl(QWidget *parent = nullptr);
    void SetDispParamData(COLOR_PICKER_DISP_PARAM *param);

    ColorPickerType pickerType() const;
    void setPickerType(ColorPickerType newPickerType);

    QColor pickerColor() const;
    void setPickerColor(const QColor &newPickerColor);

signals:
    void pickerTypeChanged();
    void pickerColorChanged();

protected slots:
    void onPickerTypeChanged();
    void onPickerTypeButtonClicked();

protected:
    void pauseSliderEvents();
    void resumeSliderEvents();

    void addPickerTypeButton(ColorPickerType type, const QString &text);
    QVector<QSharedPointer<SelectButton> > pickerTypeButtons() const;

protected:
    struct PickerButton
    {
        ColorPickerType type;
        QSharedPointer<SelectButton> button;
    };
    QVector<PickerButton> m_pickertype_buttons;

    GridBackground m_menu_background;
    GridBackground m_slider_background;

    QLabel m_label_title;

    CustomPushButton m_button_previous_tab; // ◀
    CustomPushButton m_button_next_tab;     // ▶

    QLabel m_label_setting;

    // XY tab
    CustomColorPickerXY m_picker_xy;

    QLabel m_label_title_x;
    QLabel m_label_value_x;
    QSlider m_slider_x;

    QLabel m_label_title_y;
    QLabel m_label_value_y;
    QSlider m_slider_y;

    // RGB tab
    CustomColorPickerRGB m_picker_rgb;
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
    ColorPickerType m_pickerType;
    QColor m_pickerColor;

private:
};

#endif // COLORPICKERCONTROL_H
