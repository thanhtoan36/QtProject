//--------------------------------------------------------------------------
// [ ファイル名 ] : libraryControlHorizon.cpp
// [ 概      要 ] : ライブラリコントロール水平ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#include "libraryControl/libraryControlHorizon.h"
#include "libraryControl/libraryControl_define.h"

#define BASE_BUTTON_WIDTH LC_HORIZON_FIRST_BUTTON_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT LC_HORIZON_FIRST_BUTTON_GEOMETRY.height()

LibraryControlHorizon::LibraryControlHorizon( QWidget *parent ) : LibraryControl( parent )
{
    setFixedSize( LC_HORIZON_SCREENSIZE );
    SetLibraryStartPoint( LC_HORIZON_FIRST_BUTTON_GEOMETRY.topLeft() );
    SetModeStartPoint( LC_HORIZON_ALL_GEOMETRY.topLeft() );

    m_mode_buttons_grid_size = QSize( 10, 1 );
    m_lib_buttons_grid_size = QSize( 10, 3 );

    m_grid.SetGridSize( QSize( 11, 5 ) );
    m_grid.SetCellSize( QSize( BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT ) );
    m_grid.move( 0, 34 );

    m_title_label.setGeometry( LC_HORIZON_TITLE_GEOMETRY );
    m_title_label.setObjectName( "title_label_with_border" );

    m_history_button.setGeometry( LC_HORIZON_HISTORY_GEOMETRY );
    m_up_button.setGeometry( LC_HORIZON_UP_GEOMETRY );
    m_down_button.setGeometry( LC_HORIZON_DOWN_GEOMETRY );
    m_return_button.setGeometry( LC_HORIZON_RETURN_GEOMETRY );
    m_setting_label.setVisible( false );
    m_title_button.setGeometry( LC_HORIZON_TITLE_BUTTON_GEOMETRY );
    m_register_button.setGeometry( LC_HORIZON_REGISTER_GEOMETRY );
    m_delete_button.setGeometry( LC_HORIZON_DELETE_GEOMETRY );
    m_empty_button.setVisible( false );
}
