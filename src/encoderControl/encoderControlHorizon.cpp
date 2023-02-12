#include "encoderControl/encoderControlHorizon.h"
#include "encoderControl/encoderControl_define.hpp"
#include "utility.h"

EncoderControlHorizon::EncoderControlHorizon(QWidget *parent)
    : EncoderControl(parent),
      m_button_1(this),
      m_button_2(this),
      m_button_3(this)
{
    setFixedSize(EC_SCREENSIZE_HORIZON);
    setEncoderMatrixSize(QSize(EC_MAX_ENCODER_ITEMS_HORIZON, 1));

    m_encoder_background.setVisible(false);
    m_button_background.setGridSize(QSize(1, 5));
    m_button_background.move(EC_HORIZON_BUTTON_1_GEOMETRY_HORIZON.topLeft());
}

void EncoderControlHorizon::SetDispParamDataHorizon(ENCODER_DISP_PARAM *param)
{
    SetDispParamData(param);

    const auto encodersPerPage = encoderMatrixSize().width() * encoderMatrixSize().height();
    placeChildrenIntoPanel(m_encoder_labels, EC_ENCODER_LABEL_SIZE, EC_ENCODER_LABELS_TOPLEFT_HORIZON + QPoint(EC_ENCODER_WIDTH_PADDING, 0), encodersPerPage);
    placeChildrenIntoPanel(m_encoders, EC_CUSTOM_ENCODER_SIZE, EC_ENCODER_TOPLEFT_HORIZON, encodersPerPage);
}

void EncoderControlHorizon::SetupUiComponents()
{
    m_label_title.setGeometry(EC_LABEL_TITLE_GEOMETRY_HORIZON);
    m_label_title.setObjectName("title_label_horizon");
    m_label_title.setText("エンコーダ");

    m_button_mode_percent.setGeometry(EC_BUTTON_PERCENT_GEOMETRY_HORIZON);
    m_button_mode_percent.setText("%");
    m_button_mode_255.setGeometry(EC_BUTTON_255_GEOMETRY_HORIZON);
    m_button_mode_255.setText("255");
    m_button_empty1.setGeometry(EC_BUTTON_EMPTY_1_GEOMETRY_HORIZON);
    m_button_empty1.setEnabled(false);

    m_button_previous_tab.setGeometry(EC_BUTTON_PREVIOUS_GEOMETRY_HORIZON);
    m_button_previous_tab.setText("◀");

    m_button_next_tab.setGeometry(EC_BUTTON_NEXT_GEOMETRY_HORIZON);
    m_button_next_tab.setText("▶");

    m_button_1.setGeometry(EC_HORIZON_BUTTON_1_GEOMETRY_HORIZON);
    m_button_1.setText("ピッカー");
    m_button_1.setChecked(true);

    m_button_2.setGeometry(EC_HORIZON_BUTTON_2_GEOMETRY_HORIZON);
    m_button_2.setText("エンコーダ");

    m_button_3.setGeometry(EC_HORIZON_BUTTON_3_GEOMETRY_HORIZON);
    m_button_3.setText("数値");
}

void EncoderControlHorizon::setupEncoderPages()
{
    const auto encodersPerPage = encoderMatrixSize().width() * encoderMatrixSize().height();

    updateChildrenVisibility(m_encoders, currentEncoderPage(), encodersPerPage);
    updateChildrenVisibility(m_encoder_labels, currentEncoderPage(), encodersPerPage);
}
