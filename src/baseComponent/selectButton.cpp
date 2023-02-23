//--------------------------------------------------------------------------
// [ ファイル名 ] : selectButton.cpp
// [ 概      要 ] : Represents select buttons
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "baseComponent/selectButton.h"
#include <QDebug>

SelectButton::SelectButton( QWidget *parent ) : ToggleButton( parent )
{
    SetCheckMarkVisible( true );
    connect( this, &QAbstractButton::clicked, this, &SelectButton::OnClicked );
}

void SelectButton::OnClicked()
{
    setChecked( true );
}
