//--------------------------------------------------------------------------
// [ ファイル名 ] : trackControlHorizon.cpp
// [ 概      要 ] : TrackControlHorizon
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "trackControl/trackControlHorizon.h"
#include "trackControl/trackControl_define.h"

TrackControlHorizon::TrackControlHorizon( QWidget *parent )
    : TrackControl( parent ),
      m_button_emply_field_2( this )
{
    setFixedSize( TC_SCREENSIZE_HORIZON );
    m_label_title.setObjectName( "title_label_with_border" );
    m_label_title.setGeometry( TC_LABEL_TITLE_GEOMETRY_HORIZON );

    m_button_mode_percent.setGeometry( TC_BUTTON_MODE_PERCENT_GEOMETRY_HORIZON );
    m_button_mode_255.setGeometry( TC_BUTTON_MODE_255_GEOMETRY_HORIZON );

    m_button_mode_angle.setGeometry( TC_BUTTON_MODE_ANGLE_GEOMETRY_HORIZON );
    m_button_mode_angle.setEnabled( false );

    m_button_value_mode_relative.setGeometry( TC_BUTTON_VALUEMODE_RELATIVE_GEOMETRY_HORIZON );
    m_button_value_mode_absolute.setGeometry( TC_BUTTON_VALUEMODE_ABSOLUTE_GEOMETRY_HORIZON );

    m_button_emply_field.setGeometry( TC_BUTTON_EMPTY_1_GEOMETRY_HORIZON );
    m_button_emply_field.setDisabled( true );

    m_button_emply_field_2.setGeometry( TC_BUTTON_EMPTY_2_GEOMETRY_HORIZON );
    m_button_emply_field_2.setDisabled( true );

    m_pantilt_control.setGeometry( TC_PANTILTCONTROL_GEOMETRY_HORIZON );
}
