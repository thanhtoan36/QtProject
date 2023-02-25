//--------------------------------------------------------------------------
// [ ファイル名 ] : panelControlBase.cpp
// [ 概      要 ] : パネル ウィジェットの基底クラス
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "baseComponent/panelControlBase.h"
#include <QFile>

#define SCREEN_BACKGROUND_COLOR QColor(34, 43, 53) // 画面の背景色

PanelControlBase::PanelControlBase( QWidget *parent )
    : QWidget{parent},
      m_background( this )
{
    m_background.SetGridSize( QSize( 1, 1 ) );
    m_background.SetCellSize( size() );

    m_background.SetBackgroundColor( SCREEN_BACKGROUND_COLOR );
    m_background.SetGridLineColor( Qt::transparent );

    QFile style( ":/resources/style.css" );
    style.open( QFile::ReadOnly );

    setStyleSheet( style.readAll() );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : CalculateNumberOfPages
//  [ 機　能 ] : ページ数取得
//  [ 引　数 ] : int item_count : ページに入れるアイテムの数
//              int items_per_page : 各ページのアイテムの数
//  [ 戻り値 ] : int : ページ数
//--------------------------------------------------------------------------
int PanelControlBase::CalulateNumberOfPages( int item_count, int items_per_page )
{
    if( items_per_page == 0 )
    {
        return 0;
    }

    return ( item_count - 1 ) / items_per_page + 1;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : CalculateNumberOfVisibleItems
//  [ 機　能 ] : このページに表示されているアイテムの数を取得する
//  [ 引　数 ] : int item_count : 全ページのアイテムの数
//              int items_per_page : 各ページのアイテムの数
//              int page_index : 現在のページ
//  [ 戻り値 ] : int : 表示されているアイテムの数
//--------------------------------------------------------------------------
int PanelControlBase::CalculateNumberOfVisibleItems( int item_count, int items_per_page, int page_index )
{
    if( items_per_page == 0 )
    {
        return 0;
    }

    return ( std::min( ( page_index + 1 ) * items_per_page, item_count ) - 1 ) % items_per_page + 1;
}

void PanelControlBase::resizeEvent( QResizeEvent *event )
{
    Q_UNUSED( event );
    m_background.SetCellSize( size() );
}
