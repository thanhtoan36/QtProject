//--------------------------------------------------------------------------
// [ ファイル名 ] : panelWindow.cpp
// [ 概      要 ] : Window to test panel widgets
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
//  [ 機　能 ] : Attach the panel widget to this window
//  [ 引　数 ] : QSharedPointer<PanelControlBase> panel : panel to attach
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
//  [ 機　能 ] : Detach the panel widget from this window
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
