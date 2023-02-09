#include "encoderControl/encoderControl.hpp"
#include "encoderControl/encoderControl_define.hpp"

#include <QDebug>

EncoderPanelControl::EncoderPanelControl(QWidget *parent)
    : PanelControlBase(parent),
      m_label_title(this),

      m_button_mode_percent(this),
      m_button_mode_255(this),
      m_button_empty1(this),
      m_test_encoder(this)
{
    setFixedSize(EC_SCREENSIZE);
}

void EncoderPanelControl::SetDispParamData(ENCODER_DISP_PARAM *param)
{
    Q_ASSERT(param);
}

void EncoderPanelControl::SetupUiComponents()
{
    m_label_title.setGeometry(EC_LABEL_TITLE_GEOMETRY);
    m_label_title.setObjectName("title_label");
    m_label_title.setText("エンコーダ");

    m_button_mode_percent.setGeometry(EC_BUTTON_PERCENT_GEOMETRY);
    m_button_mode_percent.setText("%");
    m_button_mode_255.setGeometry(EC_BUTTON_255_GEOMETRY);
    m_button_mode_255.setText("255");
    m_button_empty1.setGeometry(EC_BUTTON_EMPTY_1_GEOMETRY);
    m_button_empty1.setEnabled(false);

    m_test_encoder.setFixedSize(EC_ENCODER_SIZE);
    m_test_encoder.move(EC_ENCODER_PLACEMENT_START);
}

void EncoderPanelControl::SetupUiEvents()
{
}
