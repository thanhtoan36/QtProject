#include "colorPickerControl/colorPickerControlHorizon.h"


ColorPickerControlHorizon::ColorPickerControlHorizon(QWidget *parent) : ColorPickerControl(parent),
    m_button_1(this),
    m_button_2(this),
    m_button_3(this)
{
    setFixedSize(CPC_HORIZON_SCREENSIZE);
    m_label_title.setObjectName("title_label_horizon");
    m_button_1.setCheckMarkVisible(true);
    m_button_2.setCheckMarkVisible(true);
    m_button_3.setCheckMarkVisible(true);

    m_slider_background.setVisible(false);
    m_label_setting.setVisible(false);
}

void ColorPickerControlHorizon::SetDispParamDataHorizon(COLOR_PICKER_DISP_PARAM *param)
{
    Q_ASSERT(param);
    SetDispParamData(param);
}

void ColorPickerControlHorizon::SetupUiComponents()
{
    m_label_title.setGeometry(CPC_HORIZON_TITLE_GEOMETRY);
    m_label_title.setText("ピッカー xy");
    setWindowTitle(m_label_title.text());

    m_button_1.setGeometry(CPC_HORIZON_BUTTON_1_GEOMETRY);
    m_button_1.setText("ピッカー");
    m_button_1.setChecked(true);

    m_button_2.setGeometry(CPC_HORIZON_BUTTON_2_GEOMETRY);
    m_button_2.setText("エンコーダ");

    m_button_3.setGeometry(CPC_HORIZON_BUTTON_3_GEOMETRY);
    m_button_3.setText("数値");

    m_button_xy.setGeometry(CPC_HORIZON_BUTTON_XY_GEOMETRY);
    m_button_xy.setText("xy");

    m_button_rgb.setGeometry(CPC_HORIZON_BUTTON_RGB_GEOMETRY);
    m_button_rgb.setText("RGB");

    m_button_previous_tab.setVisible(false);
    m_button_next_tab.setVisible(false);

    m_picker_xy.setGeometry(CPC_HORIZON_PICKER_XY_GEOMETRY);
    m_picker_rgb.setGeometry(CPC_HORIZON_PICKER_RGB_GEOMETRY);

    m_label_title_x.setGeometry(CPC_HORIZON_LABEL_TITLE_X_GEOMETRY);
    m_label_title_x.setText("x");

    m_label_value_x.setGeometry(CPC_HORIZON_LABEL_VALUE_X_GEOMETRY);

    m_slider_x.setGeometry(CPC_HORIZON_SLIDER_X_GEOMETRY);
    m_slider_x.setOrientation(Qt::Vertical);

    m_label_title_y.setGeometry(CPC_HORIZON_LABEL_TITLE_Y_GEOMETRY);
    m_label_title_y.setText("y");

    m_label_value_y.setGeometry(CPC_HORIZON_LABEL_VALUE_Y_GEOMETRY);

    m_slider_y.setGeometry(CPC_HORIZON_SLIDER_Y_GEOMETRY);
    m_slider_y.setOrientation(Qt::Vertical);

    // RGB Tab
    m_label_title_h.setGeometry(CPC_HORIZON_LABEL_TITLE_H_GEOMETRY);
    m_label_title_h.setText("H");

    m_label_value_h.setGeometry(CPC_HORIZON_LABEL_VALUE_H_GEOMETRY);

    m_slider_h.setGeometry(CPC_HORIZON_SLIDER_X_GEOMETRY);
    m_slider_h.setOrientation(Qt::Vertical);

    m_label_title_s.setGeometry(CPC_HORIZON_LABEL_TITLE_S_GEOMETRY);
    m_label_title_s.setText("S");

    m_label_value_s.setGeometry(CPC_HORIZON_LABEL_VALUE_S_GEOMETRY);

    m_slider_s.setGeometry(CPC_HORIZON_SLIDER_S_GEOMETRY);
    m_slider_s.setOrientation(Qt::Vertical);

    m_label_title_v.setGeometry(CPC_HORIZON_LABEL_TITLE_V_GEOMETRY);
    m_label_title_v.setText("V");

    m_label_value_v.setGeometry(CPC_HORIZON_LABEL_VALUE_V_GEOMETRY);

    m_slider_v.setGeometry(CPC_HORIZON_SLIDER_V_GEOMETRY);
    m_slider_v.setOrientation(Qt::Vertical);
}
