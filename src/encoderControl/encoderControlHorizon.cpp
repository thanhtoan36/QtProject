#include "encoderControl/encoderControlHorizon.h"
#include "encoderControl/encoderControl_define.hpp"

EncoderControlHorizon::EncoderControlHorizon(QWidget *parent)
    : EncoderControl(parent),
      m_button_switch_panel_picker(this),
      m_button_switch_panel_encoder(this),
      m_button_switch_panel_input_num(this)
{
    setFixedSize(EC_SCREENSIZE_HORIZON);
    m_encoders_per_page = 5;

    m_encoder_background.setVisible(false);
    m_button_background.setGridSize(QSize(1, 5));
    m_button_background.move(EC_HORIZON_BUTTON_1_GEOMETRY_HORIZON.topLeft());

    m_button_switch_panel_encoder.setChecked(true);

    m_label_title.setGeometry(EC_LABEL_TITLE_GEOMETRY_HORIZON);
    m_label_title.setObjectName("title_label_with_border");

    m_button_mode_percent.setGeometry(EC_BUTTON_PERCENT_GEOMETRY_HORIZON);
    m_button_mode_255.setGeometry(EC_BUTTON_255_GEOMETRY_HORIZON);
    m_button_mode_angle.setGeometry(EC_BUTTON_ANGLE_GEOMETRY_HORIZON);

    m_button_previous_page.setGeometry(EC_BUTTON_PREVIOUS_GEOMETRY_HORIZON);
    m_button_next_page.setGeometry(EC_BUTTON_NEXT_GEOMETRY_HORIZON);

    m_button_switch_panel_picker.setGeometry(EC_HORIZON_BUTTON_1_GEOMETRY_HORIZON);
    m_button_switch_panel_picker.setText("ピッカー");
    m_button_switch_panel_encoder.setGeometry(EC_HORIZON_BUTTON_2_GEOMETRY_HORIZON);
    m_button_switch_panel_encoder.setText("エンコーダ");
    m_button_switch_panel_input_num.setGeometry(EC_HORIZON_BUTTON_3_GEOMETRY_HORIZON);
    m_button_switch_panel_input_num.setText("数値");

    connect(&m_button_switch_panel_picker, &QAbstractButton::clicked, this, &EncoderControlHorizon::OnPanelSwitchButtonClicked);
    connect(&m_button_switch_panel_encoder, &QAbstractButton::clicked, this, &EncoderControlHorizon::OnPanelSwitchButtonClicked);
    connect(&m_button_switch_panel_input_num, &QAbstractButton::clicked, this, &EncoderControlHorizon::OnPanelSwitchButtonClicked);
}

void EncoderControlHorizon::SetDispParamData(ENCODER_DISP_PARAM *param)
{
    EncoderControl::SetDispParamData(param);

    placeChildrenIntoPanel(m_encoder_labels, EC_ENCODER_LABEL_SIZE, EC_ENCODER_LABELS_TOPLEFT_HORIZON + QPoint(EC_ENCODER_WIDTH_PADDING, 0), QSize(m_encoders_per_page, 1));
    placeChildrenIntoPanel(m_encoders, EC_CUSTOM_ENCODER_SIZE, EC_ENCODER_TOPLEFT_HORIZON, QSize(m_encoders_per_page, 1));
}

void EncoderControlHorizon::OnPanelSwitchButtonClicked()
{
    m_button_switch_panel_picker.setChecked(false);
    m_button_switch_panel_encoder.setChecked(false);
    m_button_switch_panel_input_num.setChecked(false);
    ((QAbstractButton*)sender())->setChecked(true);
}

void EncoderControlHorizon::SetupEncoderPages()
{
    UpdateChildrenVisibility(m_encoders, CurrentEncoderPage(), m_encoders_per_page);
    UpdateChildrenVisibility(m_encoder_labels, CurrentEncoderPage(), m_encoders_per_page);
}
