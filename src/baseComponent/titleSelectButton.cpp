//--------------------------------------------------------------------------
// [ ファイル名 ] : titleSelectButton.cpp
// [ 概      要 ] : Represents title select buttons
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "baseComponent/titleSelectButton.h"
#include "baseComponent/designPolicyDefine.h"
#include <QDebug>

#define TITLE_PADDING 1

TitleSelectButton::TitleSelectButton( QWidget *parent ) : SelectButton( parent ),
    m_title_visible( true ),
    m_title(),
    m_title_label( this )
{
    m_title_label.resize( width() - 2 * TITLE_PADDING, 12 );
    m_title_label.move( TITLE_PADDING, height() - m_title_label.height() - TITLE_PADDING );
    m_title_label.setObjectName( "select_button_title_label" );

    SetBackgroundColor( Qt::black );
    SetSelectedBackgroundColor( Qt::black );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : TitleVisible
//  [ 機　能 ] : Get the visibility of title
//  [ 引　数 ] : void
//  [ 戻り値 ] : bool : TRUE if the title is visible, otherwise FALSE
//--------------------------------------------------------------------------
bool TitleSelectButton::TitleVisible() const
{
    return m_title_visible;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetTitleVisible
//  [ 機　能 ] : Set the visibility of title
//  [ 引　数 ] : bool value : new title visibility
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void TitleSelectButton::SetTitleVisible( bool value )
{
    if( m_title_visible == value )
    {
        return;
    }

    m_title_visible = value;
    emit TitleVisibleChanged();

    m_title_label.setVisible( value );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : Title
//  [ 機　能 ] : Get the title text
//  [ 引　数 ] : void
//  [ 戻り値 ] : QString : title text
//--------------------------------------------------------------------------
QString TitleSelectButton::Title() const
{
    return m_title;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetTitle
//  [ 機　能 ] : Set the title text
//  [ 引　数 ] : const QString &value : new title text
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void TitleSelectButton::SetTitle( const QString &value )
{
    if( m_title == value )
    {
        return;
    }

    m_title = value;
    emit TitleChanged();

    m_title_label.setText( value );
}

void TitleSelectButton::resizeEvent( QResizeEvent *event )
{
    SelectButton::resizeEvent( event );
    m_title_label.setGeometry( TITLE_PADDING, height() - m_title_label.height() - TITLE_PADDING,
                               width() - 2 * TITLE_PADDING, m_title_label.height() );
}
