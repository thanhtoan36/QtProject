//--------------------------------------------------------------------------
// [ ファイル名 ] : panelWindow.h
// [ 概      要 ] : パネル ウィジェットをテストするためのウィンドウ
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef PANELWINDOW_H
#define PANELWINDOW_H

#include <QDialog>
#include <QSharedPointer>

#include "panelControlBase.h"

class PanelWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PanelWindow( QWidget *parent = nullptr );

    void AttachPanelControl( QSharedPointer<PanelControlBase> panel );
    void DetachPanelControl();

signals:

private:
    QSharedPointer<PanelControlBase> m_current_panel_control {};

};

#endif // PANELWINDOW_H
