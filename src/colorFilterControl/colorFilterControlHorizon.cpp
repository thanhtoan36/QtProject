//--------------------------------------------------------------------------
// [ ファイル名 ] : colorFilterControlHorizon.cpp
// [ ファイル名 ]カラーフィルターコントロール水平ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#include "colorFilterControl/colorFilterControlHorizon.h"
#include "colorFilterControl/colorFilterControl_define.h"

#define BUTTONS_GRID_SIZE QSize(4, 4)
#define BUTTONS_PER_PAGE (BUTTONS_GRID_SIZE.width() * BUTTONS_GRID_SIZE.height())

#define BASE_BUTTON_X CFC_HORIZON_FIRST_BUTTON_GEOMETRY.x()
#define BASE_BUTTON_Y CFC_HORIZON_FIRST_BUTTON_GEOMETRY.y()

#define BASE_BUTTON_WIDTH CFC_HORIZON_FIRST_BUTTON_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT CFC_HORIZON_FIRST_BUTTON_GEOMETRY.height()

ColorFilterControlHorizon::ColorFilterControlHorizon( QWidget *parent ) : ColorFilterControl( parent )
{
    setFixedSize( CFC_HORIZON_SCREENSIZE );
    m_header_buttons_per_page = 3;

    m_grid.SetGridSize( QSize( 7, 5 ) );
    m_grid.SetCellSize( QSize( 78, 48 ) );
    m_grid.move( 0, 34 );

    m_title_label.setGeometry( CFC_HORIZON_TITLE_GEOMETRY );
    m_title_label.setObjectName( "title_label_with_border" );

    m_history_button.setGeometry( CFC_HORIZON_HISTORY_BUTTON_GEOMETRY );

    m_button_next_header_buttons_page.setGeometry( CFC_HORIZON_UP_BUTTON_GEOMETRY );
    m_button_next_header_buttons_page.setText( "▲" );

    m_button_previous_header_buttons_page.setGeometry( CFC_HORIZON_DOWN_BUTTON_GEOMETRY );
    m_button_previous_header_buttons_page.setText( "▼" );

    m_button_next_filter_buttons_page.setGeometry( CFC_HORIZON_UP2_BUTTON_GEOMETRY );
    m_button_previous_filter_buttons_page.setGeometry( CFC_HORIZON_DOWN2_BUTTON_GEOMETRY );

    m_title_button.setGeometry( CFC_HORIZON_TITLE_BUTTON_GEOMETRY );

    m_empty_button.setVisible( false );

    m_register_button.setGeometry( CFC_HORIZON_REGISTER_BUTTON_GEOMETRY );
    m_delete_button.setGeometry( CFC_HORIZON_DELETE_BUTTON_GEOMETRY );
    m_back_button.setGeometry( CFC_HORIZON_BACK_BUTTON_GEOMETRY );

    m_setting_label.setVisible( false );
    m_button_next_header_buttons_page.setVisible( false );
    m_button_previous_header_buttons_page.setVisible( false );

    PlaceChildrenIntoPanel( HeaderButtons(), CFC_HORIZON_FIRST_TAB_GEOMETRY.size(), CFC_HORIZON_FIRST_TAB_GEOMETRY.topLeft(), QSize( 1, m_header_buttons_per_page ) );
    SetupHeaderTabButtons();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetDispParamData
//  [ 機　能   ] : コントロールの表示パラメータデータを設する·
//  [ 引　数   ] : COLOR_FILTER_DISP_PARAM *param : 各パラメータ
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void ColorFilterControlHorizon::SetDispParamData( COLOR_FILTER_DISP_PARAM *param )
{
    Q_ASSERT( param );
    ColorFilterControl::SetDispParamData( param );
    PlaceChildrenIntoPanel( m_tb_tab_buttons, CFC_HORIZON_FIRST_BUTTON_GEOMETRY.size(), CFC_HORIZON_FIRST_BUTTON_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE );
    PlaceChildrenIntoPanel( m_custom_tab_buttons, CFC_HORIZON_FIRST_BUTTON_GEOMETRY.size(), CFC_HORIZON_FIRST_BUTTON_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE );
    PlaceChildrenIntoPanel( m_history_buttons, CFC_HORIZON_FIRST_BUTTON_GEOMETRY.size(), CFC_HORIZON_FIRST_BUTTON_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : AddButtonToHistory
//  [ 機　能 ] : ボタンを最近使ったものリストに追加する
//  [ 引　数 ] : QSharedPointer<SelectButton> button: 要追加のボタン
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControlHorizon::AddButtonToHistory( QSharedPointer<SelectButton> button )
{
    ColorFilterControl::AddButtonToHistory( button );
    PlaceChildrenIntoPanel( m_history_buttons, CFC_HORIZON_FIRST_BUTTON_GEOMETRY.size(), CFC_HORIZON_FIRST_BUTTON_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : OnModeChanged
//  [ 機　能 ] : モード変更を処理するイベント
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControlHorizon::OnModeChanged()
{
    for( const auto &button : qAsConst( m_header_buttons ) )
    {
        button.button->setChecked( button.mode == Mode() );
    }

    for( auto &btn : m_custom_tab_buttons )
    {
        btn->setVisible( Mode() == COLOR_FILTER_MODE_CUSTOM );
    }

    for( auto &btn : m_children_custom_tab )
    {
        btn->setVisible( Mode() == COLOR_FILTER_MODE_CUSTOM );
    }

    for( auto &btn : m_history_buttons )
    {
        btn->setVisible( Mode() == COLOR_FILTER_MODE_HISTORY );
    }

    for( auto &btn : m_tb_tab_buttons )
    {
        btn->setVisible( Mode() == COLOR_FILTER_MODE_TB );
    }

    for( auto &btn : m_children_tb_tab )
    {
        btn->setVisible( Mode() == COLOR_FILTER_MODE_TB );
    }

    if( Mode() == COLOR_FILTER_MODE_TB )
    {
        m_title_label.setText( "カラーフィルタ" );
        UpdateTBTabPage();
        m_history_button.setChecked( false );
        m_button_next_filter_buttons_page.setEnabled( CurrentTBTabPage() > 0 );
        m_button_previous_filter_buttons_page.setEnabled( CurrentTBTabPage() < MaxTBTabPages() - 1 );

        m_button_next_filter_buttons_page.setVisible( m_tb_tab_buttons.length() > BUTTONS_PER_PAGE );
        m_button_previous_filter_buttons_page.setVisible( m_tb_tab_buttons.length() > BUTTONS_PER_PAGE );
    }
    else if( Mode() == COLOR_FILTER_MODE_CUSTOM )
    {
        m_title_label.setText( "カラーフィルタ" );
        UpdateCustomTabPage();
        m_history_button.setChecked( false );
        m_button_next_filter_buttons_page.setEnabled( CurrentCustomTabPage() > 0 );
        m_button_previous_filter_buttons_page.setEnabled( CurrentCustomTabPage() < MaxCustomTabPages() - 1 );

        m_button_next_filter_buttons_page.setVisible( m_custom_tab_buttons.length() > BUTTONS_PER_PAGE );
        m_button_previous_filter_buttons_page.setVisible( m_custom_tab_buttons.length() > BUTTONS_PER_PAGE );
    }
    else if( Mode() == COLOR_FILTER_MODE_HISTORY )
    {
        m_title_label.setText( "カラーフィルタ (最近使ったもの)" );
        m_history_button.setChecked( true );
        UpdateHistoryPage();

        m_button_next_filter_buttons_page.setEnabled( CurrentHistoryPage() > 0 );
        m_button_previous_filter_buttons_page.setEnabled( CurrentHistoryPage() < MaxHistoryPages() - 1 );

        m_button_next_filter_buttons_page.setVisible( m_history_buttons.length() > BUTTONS_PER_PAGE );
        m_button_previous_filter_buttons_page.setVisible( m_history_buttons.length() > BUTTONS_PER_PAGE );
    }
}
