//--------------------------------------------------------------------------
// [ ファイル名 ] : colorFilterControlHorizon.cpp
// [ 概      要 ] : ColorFilterControl horizon widget
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#include "colorFilterControl/colorFilterControlHorizon.h"
#include "colorFilterControl/colorFilterControlHorizon_define.h"

#define BUTTONS_GRID_SIZE QSize(4, 4)
#define BUTTONS_PER_PAGE (BUTTONS_GRID_SIZE.width() * BUTTONS_GRID_SIZE.height())

#define BASE_BUTTON_X CFC_HORIZON_BUTTON1_GEOMETRY.x()
#define BASE_BUTTON_Y CFC_HORIZON_BUTTON1_GEOMETRY.y()

#define BASE_BUTTON_WIDTH CFC_HORIZON_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT CFC_HORIZON_BUTTON1_GEOMETRY.height()

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

    m_empty_button.setGeometry( CFC_HORIZON_EMPTY2_GEOMETRY );
    m_empty_button.setEnabled( false );

    m_register_button.setGeometry( CFC_HORIZON_REGISTER_BUTTON_GEOMETRY );
    m_delete_button.setGeometry( CFC_HORIZON_DELETE_BUTTON_GEOMETRY );
    m_back_button.setGeometry( CFC_HORIZON_BACK_BUTTON_GEOMETRY );

    m_setting_label.setVisible( false );
    m_button_next_header_buttons_page.setVisible( false );
    m_button_previous_header_buttons_page.setVisible( false );

    PlaceChildrenIntoPanel( HeaderButtons(), CFC_HORIZON_TB_TAB_GEOMETRY.size(), CFC_HORIZON_TB_TAB_GEOMETRY.topLeft(), QSize( 1, m_header_buttons_per_page ) );
    SetupHeaderTabButtons();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetDispParamData
//  [ 機　能   ] : Set the display parameters data for the control
//  [ 引　数   ] : COLOR_FILTER_DISP_PARAM *param : the parameters
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void ColorFilterControlHorizon::setDispParamData( COLOR_FILTER_DISP_PARAM *param )
{
    Q_ASSERT( param );
    ColorFilterControl::setDispParamData( param );
    PlaceChildrenIntoPanel( m_tb_tab_buttons, CFC_HORIZON_BUTTON1_GEOMETRY.size(), CFC_HORIZON_BUTTON1_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE );
    PlaceChildrenIntoPanel( m_custom_tab_buttons, CFC_HORIZON_BUTTON1_GEOMETRY.size(), CFC_HORIZON_BUTTON1_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE );
    PlaceChildrenIntoPanel( m_history_buttons, CFC_HORIZON_BUTTON1_GEOMETRY.size(), CFC_HORIZON_BUTTON1_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : AddButtonToHistory
//  [ 機　能 ] : Add button to history list
//  [ 引　数 ] : QSharedPointer<SelectButton> button: button need to add
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControlHorizon::AddButtonToHistory( QSharedPointer<SelectButton> button )
{
    ColorFilterControl::AddButtonToHistory( button );
    PlaceChildrenIntoPanel( m_history_buttons, CFC_HORIZON_BUTTON1_GEOMETRY.size(), CFC_HORIZON_BUTTON1_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE );
}
