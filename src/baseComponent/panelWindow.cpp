//--------------------------------------------------------------------------
// [ ファイル名 ] : panelWindow.cpp
// [ 概      要 ] : パネル ウィジェットをテストするためのウィンドウ
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "baseComponent/panelWindow.h"

PanelWindow::PanelWindow( QWidget *parent )
    : QDialog{parent}
{
    // Turn off window border and default buttons
    setWindowFlags( Qt::CustomizeWindowHint | Qt::FramelessWindowHint );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : AttachPanelControl
//  [ 機　能 ] : パネル ウィジェットをこのウィンドウに取り付ける
//  [ 引　数 ] : QSharedPointer<PanelControlBase> panel : 取り付けるパネル
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PanelWindow::AttachPanelControl( QSharedPointer<PanelControlBase> panel )
{
    DetachPanelControl();

    if( panel )
    {
        panel->setParent( this );
        m_current_panel_control = panel;
        setFixedSize( panel->size() );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : DetachPanelControl
//  [ 機　能 ] : パネル ウィジェットをこのウィンドウから取り外す
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PanelWindow::DetachPanelControl()
{
    if( m_current_panel_control )
    {
        m_current_panel_control->disconnect( this );
        m_current_panel_control->setParent( nullptr );
    }

    m_current_panel_control = nullptr;
    close();
}
