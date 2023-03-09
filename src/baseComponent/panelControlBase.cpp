//--------------------------------------------------------------------------
// [ ファイル名 ] : panelControlBase.cpp
// [ 概      要 ] : パネル ウィジェットの基底クラス
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#define SCREEN_BACKGROUND_COLOR QColor(34, 43, 53) // 画面の背景色

#include "baseComponent/panelControlBase.h"

static const char *g_stylesheet = R"(
QWidget {
    font-size: 16px;
    font-weight: bold;
}
QLabel {
    color: rgb(191,191,191);
    qproperty-alignment: AlignCenter;
}
QLabel#encoder_label {
    background-color: black;
    border: 1px solid gray;
}
QLabel#title_label_with_border {
    border: 1px solid gray;
    font-weight: bold;
    background-color: rgb(51, 63, 79);
    color: rgb(217, 217, 217);
}
QLabel#title_label {
    font-weight: bold;
    background-color: rgb(51, 63, 79);
    color: rgb(217, 217, 217);
}
QLabel#graph_axis_label {
    font-size: 14px;
    color: darkgray;
}
QLabel#select_button_title_label {
    font-size: 11px;
    color: rgb(217, 217, 217);
    background-color: rgb(87, 87, 87);
}

QLabel#control_background {
    background: #595959;
}

QSlider::groove:horizontal {
    height: 10px;
    background: #adb9ca;
}
QSlider::handle:horizontal {
    width: 28px;
    margin: -11px 0;
    border-radius: 15px;
    border: 1px solid gray;
    background: #4472c4;
}
QSlider::groove:vertical {
    width: 10px;
    background: #adb9ca;
}
QSlider::handle:vertical {
    height: 28px;
    margin: 0 -11px;
    border-radius: 15px;
    border: 1px solid gray;
    background: #4472c4;
}

QListWidget#playback_list {
    font-size: 18px;
    border: 1px solid gray;

    background-color: transparent;
    alternate-background-color: rgb(51, 63, 89);

    color: rgb(191,191,191);
}
QListWidget#playback_list::item:selected {
    background-color: transparent;
    border: 1px solid rgb(18, 110, 67);
    color: rgb(198, 89, 21);
}
QLabel#playback_header {
    color: rgb(191, 191, 191);
    background-color: rgb(51, 63, 79);
}
)";

//--------------------------------------------------------------------------
//  [ 関数名 ] : PanelControlBase
//  [ 機　能 ] : Constructor for PanelControlBase
//  [ 引　数 ] : QWidget *parent : parent widget
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
PanelControlBase::PanelControlBase( QWidget *parent )
    : QWidget{parent},
      m_background( this )
{
    m_background.SetGridSize( QSize( 1, 1 ) );
    m_background.SetCellSize( size() );

    m_background.SetBackgroundColor( SCREEN_BACKGROUND_COLOR );
    m_background.SetGridLineColor( Qt::transparent );

    setStyleSheet( g_stylesheet );
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

//--------------------------------------------------------------------------
//  [ 関数名 ] : resizeEvent
//  [ 機　能 ] : Event when resize
//  [ 引　数 ] : QResizeEvent *event: resize event data
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PanelControlBase::resizeEvent( QResizeEvent *event )
{
    Q_UNUSED( event );
    m_background.SetCellSize( size() );
}
