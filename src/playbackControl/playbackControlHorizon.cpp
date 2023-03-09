//--------------------------------------------------------------------------
// [ ファイル名 ] : playbackControlHorizon.cpp
// [ 概      要 ] : PlaybackControlHorizon
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "playbackControl/playbackControlHorizon.h"
#include "playbackControl/playbackControl_define.h"
#include "utility.h"

//--------------------------------------------------------------------------
//  [ 関数名 ] : PlaybackControlHorizon
//  [ 機　能 ] : プレイバックコントロール水平のコンストラクター
//  [ 引　数 ] : QWidget *parent : 親ウィジェット
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
PlaybackControlHorizon::PlaybackControlHorizon( QWidget *parent )
    : PlaybackControl( parent )
{
    setFixedSize( PLC_HORIZON_SCREENSIZE );
    m_column_width = PLC_HORIZON_COLUMN_WIDTH;

    m_list_view.setGeometry( PLC_HORIZON_LIST_GEOMETRY.adjusted( 0, 36, 0, 0 ) );

    m_headers.clear();
    QStringList headers = {"", "キュー", "フェード", "ディレイ", "ウェイト", "リンク", "タイトル" };
    QRect cell( PLC_HORIZON_LIST_GEOMETRY.topLeft(), QSize( 0, 36 ) );

    for( int i = 0; i < m_column_width.length(); i++ )
    {
        cell.setWidth( m_column_width[i] );

        auto label = MakeSharedQObject<QLabel>( this );
        label->setGeometry( cell );
        label->setText( headers[i] );
        label->setObjectName( "playback_header" );

        m_headers.append( label );

        cell.moveLeft( cell.left() + cell.width() );
    }

    m_row_delegate.SetColumnsWidth( m_column_width );
    m_list_view.setItemDelegate( &m_row_delegate );

    m_grid_overlay.setGeometry( PLC_HORIZON_LIST_GEOMETRY );
    m_grid_overlay.SetColumnsWidth( m_column_width );
    m_grid_overlay.raise();
}
