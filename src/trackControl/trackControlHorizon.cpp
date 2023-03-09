//--------------------------------------------------------------------------
// [ ファイル名 ] : trackControlHorizon.cpp
// [ 概      要 ] : TrackControlHorizon
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "trackControl/trackControlHorizon.h"
#include "trackControl/trackControl_define.h"

//--------------------------------------------------------------------------
//  [ 関数名 ] : TrackControlHorizon
//  [ 機　能 ] : トラックコントロール水平のコンストラクター
//  [ 引　数 ] : QWidget *parent : 親ウィジェット
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
TrackControlHorizon::TrackControlHorizon( QWidget *parent )
    : TrackControl( parent ),
      m_button_emply_field_2( this )
{
    setFixedSize( TC_HORIZON_SCREENSIZE );
    m_label_title.setObjectName( "title_label_with_border" );
    m_label_title.setGeometry( TC_HORIZON_LABEL_TITLE_GEOMETRY );

    m_button_mode_percent.setGeometry( TC_HORIZON_BUTTON_MODE_PERCENT_GEOMETRY );
    m_button_mode_255.setGeometry( TC_HORIZON_BUTTON_MODE_255_GEOMETRY );

    m_button_mode_angle.setGeometry( TC_HORIZON_BUTTON_MODE_ANGLE_GEOMETRY );
    m_button_mode_angle.setEnabled( false );

    m_button_value_mode_relative.setGeometry( TC_HORIZON_BUTTON_VALUEMODE_RELATIVE_GEOMETRY );
    m_button_value_mode_absolute.setGeometry( TC_HORIZON_BUTTON_VALUEMODE_ABSOLUTE_GEOMETRY );

    m_button_emply_field.setGeometry( TC_HORIZON_BUTTON_EMPTY_1_GEOMETRY );
    m_button_emply_field.setDisabled( true );

    m_button_emply_field_2.setGeometry( TC_HORIZON_BUTTON_EMPTY_2_GEOMETRY );
    m_button_emply_field_2.setDisabled( true );

    m_pantilt_control.setGeometry( TC_HORIZON_PANTILTCONTROL_GEOMETRY );
}
