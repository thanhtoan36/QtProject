//--------------------------------------------------------------------------
// [ ファイル名 ] : encoderControlHorizon.cpp
// [ 概      要 ] : EncoderControlHorizon
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "encoderControl/encoderControlHorizon.h"
#include "encoderControl/encoderControl_define.h"

//--------------------------------------------------------------------------
//  [ 関数名 ] : EncoderControlHorizon
//  [ 機　能 ] : エンコーダーコントロー平水のコンストラクター
//  [ 引　数 ] : QWidget * parent : 親ウィジェット
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
EncoderControlHorizon::EncoderControlHorizon( QWidget *parent )
    : EncoderControl( parent ),
      m_button_switch_panel_picker( this ),
      m_button_switch_panel_encoder( this ),
      m_button_switch_panel_input_num( this )
{
    setFixedSize( EC_HORIZON_SCREENSIZE );
    m_encoders_per_page = 5;

    m_encoder_background.setVisible( false );
    m_button_background.SetGridSize( QSize( 1, 5 ) );
    m_button_background.move( EC_HORIZON_BUTTON_PICKER_GEOMETRY.topLeft() );

    m_button_switch_panel_encoder.setChecked( true );

    m_label_title.setGeometry( EC_HORIZON_LABEL_TITLE_GEOMETRY );
    m_label_title.setObjectName( "title_label_with_border" );
    m_label_title.setText( "エンコーダ" );

    m_button_mode_percent.setGeometry( EC_HORIZON_BUTTON_PERCENT_GEOMETRY );
    m_button_mode_255.setGeometry( EC_HORIZON_BUTTON_255_GEOMETRY );
    m_button_mode_angle.setGeometry( EC_HORIZON_BUTTON_ANGLE_GEOMETRY );
    m_button_mode_angle.setVisible( false );

    m_button_previous_page.setGeometry( EC_HORIZON_BUTTON_PREVIOUS_GEOMETRY );
    m_button_next_page.setGeometry( EC_HORIZON_BUTTON_NEXT_GEOMETRY );

    m_button_switch_panel_picker.setGeometry( EC_HORIZON_BUTTON_PICKER_GEOMETRY );
    m_button_switch_panel_picker.setText( "ピッカー" );
    m_button_switch_panel_picker.SetTextPixelSize( 14 );

    m_button_switch_panel_encoder.setGeometry( EC_HORIZON_BUTTON_ENCODER_GEOMETRY );
    m_button_switch_panel_encoder.setText( "エンコーダ" );
    m_button_switch_panel_encoder.SetTextPixelSize( 14 );

    m_button_switch_panel_input_num.setGeometry( EC_HORIZON_BUTTON_INPUT_NUM_GEOMETRY );
    m_button_switch_panel_input_num.setText( "数値" );
    m_button_switch_panel_input_num.SetTextPixelSize( 14 );

    connect( &m_button_switch_panel_picker, &QAbstractButton::clicked, this, &EncoderControlHorizon::OnPanelSwitchButtonClicked );
    connect( &m_button_switch_panel_encoder, &QAbstractButton::clicked, this, &EncoderControlHorizon::OnPanelSwitchButtonClicked );
    connect( &m_button_switch_panel_input_num, &QAbstractButton::clicked, this, &EncoderControlHorizon::OnPanelSwitchButtonClicked );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetDispParamData
//  [ 機　能 ] : コントロールに表示パラメータデータを設定する
//  [ 引　数 ] : ENCODER_DISP_PARAM *param : 各パラメータ
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void EncoderControlHorizon::SetDispParamData( ENCODER_DISP_PARAM *param )
{
    EncoderControl::SetDispParamData( param );

    PlaceChildrenIntoPanel( m_encoder_labels, EC_ENCODER_LABEL_SIZE, EC_HORIZON_ENCODER_LABELS_TOPLEFT + QPoint( EC_ENCODER_WIDTH_PADDING, 0 ), QSize( m_encoders_per_page, 1 ) );
    PlaceChildrenIntoPanel( m_encoders, EC_CUSTOM_ENCODER_SIZE, EC_HORIZON_ENCODER_TOPLEFT, QSize( m_encoders_per_page, 1 ) );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : OnPanelSwitchButtonClicked
//  [ 機　能 ] : パネルスイッチ ボタンがクリックされたときに発生する
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void EncoderControlHorizon::OnPanelSwitchButtonClicked()
{
    m_button_switch_panel_picker.setChecked( false );
    m_button_switch_panel_encoder.setChecked( false );
    m_button_switch_panel_input_num.setChecked( false );
    ( ( QAbstractButton * )sender() )->setChecked( true );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : OnTypeChanged
//  [ 機　能 ] : タイプが変更されたときに発生する。コントロールを更新するため
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void EncoderControlHorizon::OnTypeChanged()
{
    m_button_mode_percent.setVisible( Type() != ENCODER_TYPE_POSITION );
    m_button_mode_255.setVisible( Type() != ENCODER_TYPE_POSITION );
    // m_button_mode_angle.setVisible( Type() != ENCODER_TYPE_POSITION );

    m_button_switch_panel_picker.setVisible( Type() == ENCODER_TYPE_COLOR );
}
