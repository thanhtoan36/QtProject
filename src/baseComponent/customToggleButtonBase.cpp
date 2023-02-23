//--------------------------------------------------------------------------
// [ ファイル名 ] : customToggleButtonBase.cpp
// [ 概      要 ] : Base class for custom toggle buttons
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include <QDebug>
#include "baseComponent/customToggleButtonBase.h"

#define CSS_BG_COLOR_CHECKED         "CSS_BG_COLOR_SELECTED"
#define CSS_BORDER_COLOR_CHECKED     "CSS_BORDER_COLOR_SELECTED"
#define CSS_TEXT_COLOR_CHECKED       "CSS_TEXT_COLOR_SELECTED"

static const char *g_stylesheet_template = R"~(

CustomToggleButtonBase:checked {
    border-style: inset;

    background: )~" CSS_BG_COLOR_CHECKED R"~(;
    border-color: )~" CSS_BORDER_COLOR_CHECKED R"~(;
    color: )~" CSS_TEXT_COLOR_CHECKED R"~(;
}

)~";

CustomToggleButtonBase::CustomToggleButtonBase( QWidget *parent ) : CustomButtonBase( parent ),
    m_selected_background_color(),
    m_selected_border_color(),
    m_selected_text_color()
{
    setCheckable( true );

    CssStyler().AppendStyleSheetTemplate( g_stylesheet_template );

    SetBackgroundColor( QColor::fromRgb( 13, 13, 13 ) );
    SetTextColor( QColor::fromRgb( 128, 128, 128 ) );

    SetSelectedBackgroundColor( QColor::fromRgb( 89, 89, 89 ) );
    SetSelectedTextColor( QColor::fromRgb( 255, 255, 255 ) );
    SetSelectedBorderColor( QColor::fromRgb( 0, 176, 80 ) );

    SetDisabledBackgroundColor( QColor::fromRgb( 22, 22, 22 ) );
    SetDisabledTextColor( QColor::fromRgb( 191, 191, 191 ) );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SelectedBorderColor
//  [ 機　能 ] : Get the border color when button is selected
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : selected border color
//--------------------------------------------------------------------------
QColor CustomToggleButtonBase::SelectedBorderColor() const
{
    return m_selected_border_color;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetSelectedBorderColor
//  [ 機　能 ] : Set the border color when button is selected
//  [ 引　数 ] : const QColor &value: Selected border color
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void CustomToggleButtonBase::SetSelectedBorderColor( const QColor &value )
{
    CssStyler().SetTemplateParam( CSS_BORDER_COLOR_CHECKED, value.name() );

    if( m_selected_border_color == value )
    {
        return;
    }

    m_selected_border_color = value;
    emit SelectedBorderColorChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SelectedTextColor
//  [ 機　能 ] : Get the text color when button is selected
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : selected text color
//--------------------------------------------------------------------------
QColor CustomToggleButtonBase::SelectedTextColor() const
{
    return m_selected_text_color;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetSelectedTextColor
//  [ 機　能 ] : Set the text color when button is selected
//  [ 引　数 ] : const QColor &value: Selected text color
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void CustomToggleButtonBase::SetSelectedTextColor( const QColor &value )
{
    CssStyler().SetTemplateParam( CSS_TEXT_COLOR_CHECKED, value.name() );

    if( m_selected_text_color == value )
    {
        return;
    }

    m_selected_text_color = value;
    emit SelectedTextColorChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SelectedBackroundColor
//  [ 機　能 ] : Get the backround color when button is selected
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : selected backround color
//--------------------------------------------------------------------------
QColor CustomToggleButtonBase::SelectedBackgroundColor() const
{
    return m_selected_background_color;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetSelectedBorderColor
//  [ 機　能 ] : Set the background color when button is selected
//  [ 引　数 ] : const QColor &value: Selected background color
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void CustomToggleButtonBase::SetSelectedBackgroundColor( const QColor &value )
{
    CssStyler().SetTemplateParam( CSS_BG_COLOR_CHECKED, value.name() );

    if( m_selected_background_color == value )
    {
        return;
    }

    m_selected_background_color = value;
    emit SelectedBackgroundColorChanged();
}
