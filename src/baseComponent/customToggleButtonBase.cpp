//--------------------------------------------------------------------------
// [ ファイル名 ] : customToggleButtonBase.cpp
// [ 概      要 ] : カスタム トグル ボタンの基底クラス
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

//--------------------------------------------------------------------------
//  [ 関数名 ] : CustomToggleButtonBase
//  [ 機　能 ] : CustomToggleButtonBaseのコンストラクター
//  [ 引　数 ] : QWidget *parent : 親ウィジェット
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
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
//  [ 機　能 ] : ボタン選択時の枠線の色の取得
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : 選択した枠線のの色
//--------------------------------------------------------------------------
QColor CustomToggleButtonBase::SelectedBorderColor() const
{
    return m_selected_border_color;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetSelectedBorderColor
//  [ 機　能 ] : ボタン選択時の枠線の色の設定
//  [ 引　数 ] : const QColor &value: 選択した枠線のの色
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
//  [ 機　能 ] : ボタン選択時の文字色の取得
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : 選択した文字色
//--------------------------------------------------------------------------
QColor CustomToggleButtonBase::SelectedTextColor() const
{
    return m_selected_text_color;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetSelectedTextColor
//  [ 機　能 ] : ボタン選択時の文字色の設定
//  [ 引　数 ] : const QColor &value: 選択した文字色
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
//  [ 機　能 ] : ボタン選択時の背景色の取得
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : 選択した背景色
//--------------------------------------------------------------------------
QColor CustomToggleButtonBase::SelectedBackgroundColor() const
{
    return m_selected_background_color;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetSelectedBackgroundColor
//  [ 機　能 ] : ボタン選択時の背景色の設定
//  [ 引　数 ] : const QColor &value: 選択した背景色
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
