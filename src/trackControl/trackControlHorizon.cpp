#include "trackControl/trackControlHorizon.h"
#include "trackControl/trackControl_define.hpp"

TrackControlHorizon::TrackControlHorizon(QWidget *parent)
    : TrackControl(parent),
      m_button_emply_field_2(this)
{
   setFixedSize(TC_SCREENSIZE_HORIZON);
   m_label_title.setObjectName("title_label_horizon");
}

void TrackControlHorizon::SetDispParamDataHorizon(TRACK_DISP_PARAM *param)
{
    SetDispParamData(param);
}

void TrackControlHorizon::SetupUiComponents()
{
    m_label_title.setGeometry(TC_LABEL_TITLE_GEOMETRY_HORIZON);
    m_label_title.setText("トラック");
    setWindowTitle(m_label_title.text());

    m_button_mode_percent.setGeometry(TC_BUTTON_MODE_PERCENT_GEOMETRY_HORIZON);
    m_button_mode_percent.setText("%");

    m_button_mode_255.setGeometry(TC_BUTTON_MODE_255_GEOMETRY_HORIZON);
    m_button_mode_255.setText("255");

    m_button_mode_angle.setGeometry(TC_BUTTON_MODE_ANGLE_GEOMETRY_HORIZON);
    m_button_mode_angle.setText("°角度");
    m_button_mode_angle.setEnabled(false);

    m_button_value_mode_relative.setGeometry(TC_BUTTON_VALUEMODE_RELATIVE_GEOMETRY_HORIZON);
    m_button_value_mode_relative.setText("相対");

    m_button_value_mode_absolute.setGeometry(TC_BUTTON_VALUEMODE_ABSOLUTE_GEOMETRY_HORIZON);
    m_button_value_mode_absolute.setText("絶対");

    m_button_emply_field.setGeometry(TC_BUTTON_EMPTY_1_GEOMETRY_HORIZON);
    m_button_emply_field.setDisabled(true);

    m_button_emply_field_2.setGeometry(TC_BUTTON_EMPTY_2_GEOMETRY_HORIZON);
    m_button_emply_field_2.setDisabled(true);

    m_pantilt_control.setGeometry(TC_PANTILTCONTROL_GEOMETRY_HORIZON);
}
