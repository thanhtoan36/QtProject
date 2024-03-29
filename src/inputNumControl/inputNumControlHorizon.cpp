//--------------------------------------------------------------------------
// [ ファイル名 ] : inputNumControlHorizon.cpp
// [ 概      要 ] : 数値入力コントロール水平ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#include "inputNumControl/inputNumControlHorizon.h"
#include "inputNumControl/inputNumControl_define.h"
#include "utility.h"

//--------------------------------------------------------------------------
//  [ 関数名   ] : InputNumControlHorizon
//  [ 機能名   ] : 数値入力コントロール平水のコンストラクター
//  [ 引数     ] : QWidget *parent: 親ウィジェット
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
InputNumControlHorizon::InputNumControlHorizon( QWidget *parent ) : InputNumControl( parent ),
    m_button_switch_panel_picker( this ),
    m_button_switch_panel_encoder( this ),
    m_button_switch_panel_input_num( this )
{
    setFixedSize( IC_HORIZON_SCREEN_SIZE );

    m_grid.SetGridSize( QSize( 6, 5 ) );
    m_grid.SetCellSize( IC_HORIZON_FIRST_MODE_BUTTON_GEOMETRY.size() );
    m_grid.move( 0, 34 );

    m_label_title.setGeometry( IC_HORIZON_TITLE_GEOMETRY );
    m_label_title.setObjectName( "title_label_with_border" );

    m_button_mode_percent.setGeometry( IC_HORIZON_PERCENT_GEOMETRY );
    m_button_mode_255.setGeometry( IC_HORIZON_255_GEOMETRY );
    m_button_mode_angle.setVisible( false );

    m_button_relative.setVisible( false );
    m_button_absolute.setVisible( false );

    m_button_switch_panel_encoder.setGeometry( IC_HORIZON_ENCODER_GEOMETRY );
    m_button_switch_panel_encoder.SetTextPixelSize( 14 );
    m_button_switch_panel_encoder.setText( "エンコーダ" );

    m_button_switch_panel_picker.setGeometry( IC_HORIZON_PICKER_GEOMETRY );
    m_button_switch_panel_picker.SetTextPixelSize( 14 );
    m_button_switch_panel_picker.setText( "ピッカー" );

    m_button_switch_panel_input_num.setGeometry( IC_HORIZON_NUMBER_GEOMETRY );
    m_button_switch_panel_input_num.SetTextPixelSize( 14 );
    m_button_switch_panel_input_num.setChecked( true );
    m_button_switch_panel_input_num.setText( "数値" );

    m_button_previous_tab.setGeometry( IC_HORIZON_PREV_GEOMETRY );
    m_button_next_tab.setGeometry( IC_HORIZON_NEXT_GEOMETRY );
    m_return_button.setGeometry( IC_HORIZON_RETURN_GEOMETRY );

    QStringList input_num_model =
    {
        "7", "8", "9", "最大",
        "4", "5", "6", "最小",
        "1", "2", "3", "ENTER",
        "0", "ハーフ",
    };

    m_input_num_buttons.clear();

    for( const QString &b : input_num_model )
    {
        auto button = MakeSharedQObject<CustomPushButton>( this );
        button->setFixedSize( IC_HORIZON_FIRST_NUM_BUTTON_GEOMETRY.size() );
        button->setVisible( true );
        button->setText( b );

        connect( button.get(), &QPushButton::clicked, this, [&]()
        {
            emit InputNumButtonClicked( ( ( CustomPushButton * )sender() )->text() );
        } );

        m_input_num_buttons.append( button );
    }

    PlaceChildrenIntoPanel( m_input_num_buttons, IC_HORIZON_FIRST_NUM_BUTTON_GEOMETRY.size(), IC_HORIZON_FIRST_NUM_BUTTON_GEOMETRY.topLeft(), QSize( 4, 4 ) );

    connect( &m_button_switch_panel_picker, &QAbstractButton::clicked, this, &InputNumControlHorizon::OnPanelSwitchButtonClicked );
    connect( &m_button_switch_panel_encoder, &QAbstractButton::clicked, this, &InputNumControlHorizon::OnPanelSwitchButtonClicked );
    connect( &m_button_switch_panel_input_num, &QAbstractButton::clicked, this, &InputNumControlHorizon::OnPanelSwitchButtonClicked );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetDispParamData
//  [ 機　能   ] : コントロールに表示パラメータデータを設定する
//  [ 引　数   ] : INPUT_NUM_DISP_PARAM *param : 各パラメータ
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void InputNumControlHorizon::SetDispParamData( INPUT_NUM_DISP_PARAM *param )
{
    InputNumControl::SetDispParamData( param );
    m_button_mode_angle.setVisible( false );

    if( param->type == INPUT_NUM_TYPE_POSITION )
    {
        m_button_mode_255.setVisible( false );
        m_button_mode_percent.setVisible( false );
    }
    else
    {
        m_button_mode_255.setVisible( true );
        m_button_mode_percent.setVisible( true );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : OnPanelSwitchButtonClicked
//  [ 機　能   ] : ボタンのクリックを処理するイベント
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void InputNumControlHorizon::OnPanelSwitchButtonClicked()
{
    m_button_switch_panel_picker.setChecked( false );
    m_button_switch_panel_encoder.setChecked( false );
    m_button_switch_panel_input_num.setChecked( false );
    ( ( QAbstractButton * )sender() )->setChecked( true );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : OnTypeChanged
//  [ 機　能   ] : タイプ変更を処理するイベント
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void InputNumControlHorizon::OnTypeChanged()
{
    m_button_switch_panel_picker.setVisible( Type() == INPUT_NUM_TYPE_COLOR );
    PlaceChildrenIntoPanel( m_group_buttons, IC_HORIZON_FIRST_MODE_BUTTON_GEOMETRY.size(), IC_HORIZON_FIRST_MODE_BUTTON_GEOMETRY.topLeft(), QSize( GroupButtonsPerPage(), 1 ) );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : GroupButtonsPerPage
//  [ 機能名   ] : ページごとにボタン番号を取得する
//  [ 引数     ] : void
//  [ 戻り値    ] : int: ボタン数
//--------------------------------------------------------------------------
int InputNumControlHorizon::GroupButtonsPerPage() const
{
    return 5;
}
