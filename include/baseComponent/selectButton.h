//--------------------------------------------------------------------------
// [ ファイル名 ] : selectButton.h
// [ 概      要 ] : 選択ボタンを表す
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef SELECTBUTTON_H
#define SELECTBUTTON_H

#include "toggleButton.h"

class SelectButton : public ToggleButton
{
    Q_OBJECT
public:
    explicit SelectButton( QWidget *parent = nullptr );

public slots:
    virtual void OnClicked();

};

#endif // SELECTBUTTON_H
