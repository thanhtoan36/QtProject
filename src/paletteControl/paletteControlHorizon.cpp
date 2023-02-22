//--------------------------------------------------------------------------
// [ ファイル名 ] : paletteControlHorizon.cpp
// [ 概      要 ] : PaletteControlHorizon
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "paletteControl/paletteControlHorizon.h"
#include "paletteControl/paletteControlHorizon_define.h"

#define BUTTON_SIZE PC_HORIZON_BUTTON1_GEOMETRY.size()

PaletteControlHorizon::PaletteControlHorizon( QWidget *parent ) : PaletteControl( parent )
{
    setFixedSize( PC_HORIZON_SCREEN_SIZE );
    SetPaletteStartPoint( PC_HORIZON_BUTTON_TOP_LEFT );
    SetMenuStartPoint( PC_HORIZON_MENU_TOP_LEFT );
    m_mode_button_grid_size = QSize( 1, 3 );
    m_palette_button_grid_size = QSize( 4, 4 );
    m_title_label.setObjectName( "title_label_with_border" );

    m_grid.SetGridSize( QSize( 6, 5 ) );
    m_grid.SetCellSize( BUTTON_SIZE );
    m_grid.move( 0, 34 );

    m_title_label.setGeometry( PC_HORIZON_TITLE_GEOMETRY );

    m_button_previous_palette_page.setGeometry( PC_HORIZON_UP_BUTTON_GEOMETRY );
    m_button_next_palette_page.setGeometry( PC_HORIZON_DOWN_BUTTON_GEOMETRY );

    m_button_next_mode_page.setGeometry( PC_HORIZON_DOWN_MODE_GEOMETRY );
    m_button_next_mode_page.setText( "▼" );

    m_button_previous_mode_page.setGeometry( PC_HORIZON_UP_MODE_GEOMETRY );
    m_button_previous_mode_page.setText( "▲" );

    m_revert_button.setGeometry( PC_HORIZON_RETURN_GEOMETRY );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : OnTypeChanged
//  [ 機　能 ] : Update title & palette button grid sizej
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PaletteControlHorizon::OnTypeChanged()
{
    switch( Type() )
    {
        case PALETTE_TYPE_GOBO:
            m_title_label.setText( "ゴボ" );
            m_mode_button_grid_size = QSize( 1, 3 );
            m_palette_button_grid_size = QSize( 4, 4 );
            break;

        case PALETTE_BEAM_SHUTTER:
            m_title_label.setText( "モード" );
            m_mode_button_grid_size = QSize( 1, 3 );
            m_palette_button_grid_size = QSize( 4, 4 );
            break;

        case PALETTE_TYPE_CONTROL:
            m_title_label.setText( "モード" );
            m_mode_button_grid_size = QSize( 0, 3 );
            m_palette_button_grid_size = QSize( 4, 4 );
            break;

        default:
            break;
    }

    UpdateModePages();
}
