//--------------------------------------------------------------------------
// [ ファイル名 ] : selectButton.cpp
// [ 概      要 ] : 選択ボタンを表す
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "baseComponent/selectButton.h"
#include <QDebug>

//--------------------------------------------------------------------------
//  [ 関数名 ] : SelectButton
//  [ 機　能 ] : SelectButtonのコンストラクター
//  [ 引　数 ] : QWidget *parent : 親ウィジェット
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
SelectButton::SelectButton( QWidget *parent ) : ToggleButton( parent )
{
    SetCheckMarkVisible( true );
    connect( this, &QAbstractButton::clicked, this, &SelectButton::OnClicked );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : OnClicked
//  [ 機　能 ] : クリック時のイベント
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void SelectButton::OnClicked()
{
    setChecked( true );
}
