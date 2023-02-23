//--------------------------------------------------------------------------
// [ ファイル名 ] : toggleButton.cpp
// [ 概      要 ] : Represents toggle buttons
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "baseComponent/toggleButton.h"
#include <QDebug>
#include <QTimer>

ToggleButton::ToggleButton( QWidget *parent )
    : CustomToggleButtonBase( parent ),
      m_check_label( this )
{
    m_check_label.setText( "✓" );
    m_check_label.setStyleSheet( "QLabel { background-color: transparent; color : white; }" );
    m_check_label.setGeometry( 3, 3, 12, 12 );

    connect( this, &QAbstractButton::toggled, this, [&]( bool )
    {
        m_check_label.setVisible( isChecked() && CheckMarkVisible() );
    } );
    connect( this, &ToggleButton::CheckMarkVisibleChanged, this, [&]()
    {
        m_check_label.setVisible( isChecked() && CheckMarkVisible() );
    } );

    SetCheckMarkVisible( false );
    m_check_label.setVisible( isChecked() && CheckMarkVisible() );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : CheckMarkVisible
//  [ 機　能 ] : Get the visibility of checkmark
//  [ 引　数 ] : void
//  [ 戻り値 ] : bool : checkmark visibility
//--------------------------------------------------------------------------
bool ToggleButton::CheckMarkVisible() const
{
    return m_check_mark_vsible;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetCheckMarkVisible
//  [ 機　能 ] : Set the visibility of checkmark
//  [ 引　数 ] : bool value : new checkmark visibility
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ToggleButton::SetCheckMarkVisible( bool value )
{
    if( m_check_mark_vsible == value )
    {
        return;
    }

    m_check_mark_vsible = value;
    emit CheckMarkVisibleChanged();
}
