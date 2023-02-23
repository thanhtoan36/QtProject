//--------------------------------------------------------------------------
// [ ファイル名 ] : panelControlBase.cpp
// [ 概      要 ] : Base class for panel widgets
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "baseComponent/panelControlBase.h"
#include "baseComponent/designPolicyDefine.h"
#include <QFile>

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
//  [ 機　能 ] : Get the number of pages
//  [ 引　数 ] : int item_count : number of items to put into pages
//              int items_per_page : number of items each page has
//  [ 戻り値 ] : int : number of pages
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
//  [ 機　能 ] : Get the number of visible items in this page
//  [ 引　数 ] : int item_count : number of items in all pages
//              int items_per_page : number of items each page has
//              int page_index : the current page
//  [ 戻り値 ] : int : number of visible items
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
