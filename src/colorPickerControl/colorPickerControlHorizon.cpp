#include "colorPickerControl/colorPickerControlHorizon.h"


ColorPickerControlHorizon::ColorPickerControlHorizon(QWidget *parent) : ColorPickerControl(parent),
    m_button_switch_panel_picker(this),
    m_button_switch_panel_encoder(this),
    m_button_switch_panel_input_num(this)
{
    setFixedSize(CPC_HORIZON_SCREENSIZE);
    m_label_title.setObjectName("title_label_with_border");

    m_slider_background.setVisible(false);
    m_label_setting.setVisible(false);
    m_menu_background.setGridSize(QSize(1, 5));
    m_menu_background.setCellSize(CPC_HORIZON_BUTTON_1_GEOMETRY.size());
    m_menu_background.move(CPC_HORIZON_BUTTON_1_GEOMETRY.topLeft());

    m_label_title.setGeometry(CPC_HORIZON_TITLE_GEOMETRY);

    m_button_switch_panel_picker.setGeometry(CPC_HORIZON_BUTTON_1_GEOMETRY);
    m_button_switch_panel_picker.setText("ピッカー");
    m_button_switch_panel_picker.setChecked(true);
    m_button_switch_panel_picker.setTextPixelSize(13);
    m_button_switch_panel_encoder.setGeometry(CPC_HORIZON_BUTTON_SWITCH_PANEL_ENCODER_GEOMETRY);
    m_button_switch_panel_encoder.setText("エンコーダ");
    m_button_switch_panel_encoder.setTextPixelSize(13);
    m_button_switch_panel_input_num.setGeometry(CPC_HORIZON_BUTTON_SWITCH_PANEL_NUMBER_GEOMETRY);
    m_button_switch_panel_input_num.setText("数値");
    m_button_switch_panel_input_num.setTextPixelSize(13);

    m_button_previous_menu_page.setVisible(false);
    m_button_next_menu_page.setVisible(false);

    m_picker_xy.setGeometry(CPC_HORIZON_PICKER_XY_GEOMETRY);
    m_picker_rgb.setGeometry(CPC_HORIZON_PICKER_RGB_GEOMETRY);

    m_label_title_x.setGeometry(CPC_HORIZON_LABEL_TITLE_X_GEOMETRY);
    m_label_value_x.setGeometry(CPC_HORIZON_LABEL_VALUE_X_GEOMETRY);

    m_slider_x.setGeometry(CPC_HORIZON_SLIDER_X_GEOMETRY);
    m_slider_x.setOrientation(Qt::Vertical);

    m_label_title_y.setGeometry(CPC_HORIZON_LABEL_TITLE_Y_GEOMETRY);
    m_label_value_y.setGeometry(CPC_HORIZON_LABEL_VALUE_Y_GEOMETRY);

    m_slider_y.setGeometry(CPC_HORIZON_SLIDER_Y_GEOMETRY);
    m_slider_y.setOrientation(Qt::Vertical);

    // RGB Tab
    m_label_title_h.setGeometry(CPC_HORIZON_LABEL_TITLE_H_GEOMETRY);
    m_label_value_h.setGeometry(CPC_HORIZON_LABEL_VALUE_H_GEOMETRY);

    m_slider_h.setGeometry(CPC_HORIZON_SLIDER_X_GEOMETRY);
    m_slider_h.setOrientation(Qt::Vertical);

    m_label_title_s.setGeometry(CPC_HORIZON_LABEL_TITLE_S_GEOMETRY);
    m_label_value_s.setGeometry(CPC_HORIZON_LABEL_VALUE_S_GEOMETRY);

    m_slider_s.setGeometry(CPC_HORIZON_SLIDER_S_GEOMETRY);
    m_slider_s.setOrientation(Qt::Vertical);

    m_label_title_v.setGeometry(CPC_HORIZON_LABEL_TITLE_V_GEOMETRY);
    m_label_value_v.setGeometry(CPC_HORIZON_LABEL_VALUE_V_GEOMETRY);

    m_slider_v.setGeometry(CPC_HORIZON_SLIDER_V_GEOMETRY);
    m_slider_v.setOrientation(Qt::Vertical);

    m_label_setting.setVisible(false);
    placeChildrenIntoPanel(pickerTypeButtons(), CPC_HORIZON_BUTTON_XY_GEOMETRY.size(), CPC_HORIZON_BUTTON_XY_GEOMETRY.topLeft(), QSize(1, 2), BottomToTop);

    connect(&m_button_switch_panel_picker, &QAbstractButton::clicked, this, &ColorPickerControlHorizon::onPanelSwitchButtonClicked);
    connect(&m_button_switch_panel_encoder, &QAbstractButton::clicked, this, &ColorPickerControlHorizon::onPanelSwitchButtonClicked);
    connect(&m_button_switch_panel_input_num, &QAbstractButton::clicked, this, &ColorPickerControlHorizon::onPanelSwitchButtonClicked);
}

void ColorPickerControlHorizon::onPanelSwitchButtonClicked()
{
    m_button_switch_panel_picker.setChecked(false);
    m_button_switch_panel_encoder.setChecked(false);
    m_button_switch_panel_input_num.setChecked(false);
    ((QAbstractButton*)sender())->setChecked(true);
}
