//--------------------------------------------------------------------------
// [ ファイル名 ] : groupControlHorizon.cpp
// [ 概      要 ] : グループコントロール垂直ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#include "groupControl/groupControlHorizon.h"
#include "groupControl/groupControl_define.h"

//--------------------------------------------------------------------------
//  [ 関数名   ] : GroupControlHorizon
//  [ 機能名   ] : グループ制御の水平コンストラクター
//  [ 引数     ] : QWidget *parent: 親ウィジェット
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
GroupControlHorizon::GroupControlHorizon( QWidget *parent ) : GroupControl( parent )
{
    setFixedSize( GC_HORIZON_SCREEN_SIZE );
    m_buttons_grid_size = QSize( 10, 4 );
    m_title_label.setObjectName( "title_label_with_border" );

    m_grid.SetGridSize( QSize( 11, 5 ) );
    m_grid.SetCellSize( GC_HORIZON_FIRST_BUTTON_GEOMETRY.size() );
    m_grid.move( 0, 34 );

    m_title_label.setGeometry( GC_HORIZON_TITLE_GEOMETRY );

    m_history_button.setGeometry( GC_HORIZON_HISTORY_GEOMETRY );

    m_up_button.setGeometry( GC_HORIZON_UP_GEOMETRY );
    m_down_button.setGeometry( GC_HORIZON_DOWN_GEOMETRY );

    m_back_button.setGeometry( GC_HORIZON_RETURN_GEOMETRY );
    m_setting_label.setVisible( false );

    m_title_button.setGeometry( GC_HORIZON_TITLE_BUTTON_GEOMETRY );
    m_empty_button.setVisible( false );

    m_register_button.setGeometry( GC_HORIZON_REGISTER_GEOMETRY );
    m_delete_button.setGeometry( GC_HORIZON_DELETE_GEOMETRY );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetDispParamData
//  [ 機　能   ] : Set the display parameters data for the control
//  [ 引　数   ] : GROUP_DISP_PARAM *param : the parameters
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControlHorizon::SetDispParamData( GROUP_DISP_PARAM *param )
{
    Q_ASSERT( param );
    GroupControl::SetDispParamData( param );
    PlaceChildrenIntoPanel( m_group_buttons, GC_HORIZON_FIRST_BUTTON_GEOMETRY.size(), GC_HORIZON_FIRST_BUTTON_GEOMETRY.topLeft(), m_buttons_grid_size );
    PlaceChildrenIntoPanel( m_history_buttons, GC_HORIZON_FIRST_BUTTON_GEOMETRY.size(), GC_HORIZON_FIRST_BUTTON_GEOMETRY.topLeft(), m_buttons_grid_size );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : AddButtonToHistory
//  [ 機　能   ] : Add button to history page
//  [ 引　数   ] : QSharedPointer<TitleSelectButton> &button: button need to add
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControlHorizon::AddButtonToHistory( QSharedPointer<TitleSelectButton> &button )
{
    GroupControl::AddButtonToHistory( button );
    PlaceChildrenIntoPanel( m_history_buttons, GC_HORIZON_FIRST_BUTTON_GEOMETRY.size(), GC_HORIZON_FIRST_BUTTON_GEOMETRY.topLeft(), m_buttons_grid_size );
}
