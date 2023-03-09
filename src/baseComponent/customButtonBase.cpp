//--------------------------------------------------------------------------
// [ ファイル名 ] : customButtonBase.cpp
// [ 概      要 ] : ボタンの基底クラス
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "baseComponent/customButtonBase.h"

#define CSS_BG_COLOR_NORMAL         "CSS_BG_COLOR_NORMAL"
#define CSS_BORDER_COLOR_NORMAL     "CSS_BORDER_COLOR_NORMAL"
#define CSS_TEXT_COLOR_NORMAL       "CSS_TEXT_COLOR_NOMAL"

#define CSS_BG_COLOR_DISABLED         "CSS_BG_COLOR_DISABLED"
#define CSS_BORDER_COLOR_DISABLED     "CSS_BORDER_COLOR_DISABLED"
#define CSS_TEXT_COLOR_DISABLED       "CSS_TEXT_COLOR_DISABLED"

#define CSS_TEXT_SIZE               "CSS_TEXT_SIZE"

// see: https://linuxhint.com/c-multiline-string-literals/
static const char *g_stylesheet_template = R"~(

CustomButtonBase {
    border-style: solid;
    border-width: 1px;
    font-size: )~" CSS_TEXT_SIZE R"~(px;

    background: )~" CSS_BG_COLOR_NORMAL R"~(;
    border-color: )~" CSS_BORDER_COLOR_NORMAL R"~(;
    color: )~" CSS_TEXT_COLOR_NORMAL R"~(;
}
CustomButtonBase:pressed {
    border-width: 2px;
    border-style: inset;
}
CustomButtonBase:disabled {
    background: )~" CSS_BG_COLOR_DISABLED R"~(;
    border-color: )~" CSS_BORDER_COLOR_DISABLED R"~(;
    color: )~" CSS_TEXT_COLOR_DISABLED R"~(;
}

)~";

//--------------------------------------------------------------------------
//  [ 関数名 ] : CustomButtonBase
//  [ 機　能 ] : CustomButtonBaseのコンストラクター
//  [ 引　数 ] : QWidget *parent : 親ウィジェット
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
CustomButtonBase::CustomButtonBase( QWidget *parent ) : QPushButton( parent ),
    m_styler( this ),
    m_background_color(),
    m_border_color(),
    m_text_color(),
    m_disabled_background_color(),
    m_disabled_border_color(),
    m_disabled_text_color(),
    m_text_pixel_size()
{
    setAutoFillBackground( true );
    CssStyler().SetStyleSheetTemplate( g_stylesheet_template );

    // NOTE: ここですべてのパラメーターを設定する必要がある (すべての css テンプレート引数が入力されていることを確認するため)
    SetBackgroundColor( QColor::fromRgb( 0, 0, 0 ) );
    SetTextColor( QColor::fromRgb( 191, 191, 191 ) );
    SetBorderColor( Qt::darkGray );

    SetDisabledBackgroundColor( QColor::fromRgb( 22, 22, 22 ) );
    SetDisabledTextColor( QColor::fromRgb( 191, 191, 191 ) );
    SetDisabledBorderColor( Qt::darkGray );

    SetTextPixelSize( 16 );

    connect( &m_styler, &DynamicStyleSheet::StyleSheetChanged, &m_styler, &DynamicStyleSheet::Polish, Qt::DirectConnection );
    CssStyler().Polish();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : BackgroundColor
//  [ 機　能 ] : 背景色取得
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : 背景色
//--------------------------------------------------------------------------
QColor CustomButtonBase::BackgroundColor() const
{
    return m_background_color;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetBackgroundColor
//  [ 機　能 ] : 背景色設定
//  [ 引　数 ] : const QColor &value : 新しい背景色
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void CustomButtonBase::SetBackgroundColor( const QColor &value )
{
    CssStyler().SetTemplateParam( CSS_BG_COLOR_NORMAL, value.name() );

    if( m_background_color == value )
    {
        return;
    }

    m_background_color = value;
    emit BackgroundColorChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : TextColor
//  [ 機　能 ] : 文字色取得
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : 文字色
//--------------------------------------------------------------------------
QColor CustomButtonBase::TextColor() const
{
    return m_text_color;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetTextColor
//  [ 機　能 ] : 文字色設定
//  [ 引　数 ] : QColor color : 新しい文字色
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void CustomButtonBase::SetTextColor( const QColor &value )
{
    CssStyler().SetTemplateParam( CSS_TEXT_COLOR_NORMAL, value.name() );

    if( m_text_color == value )
    {
        return;
    }

    m_text_color = value;
    emit TextColorChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : TextPixelSize
//  [ 機　能 ] : 文字サイズ取得
//  [ 引　数 ] : void
//  [ 戻り値 ] : int : 文字サイズ
//--------------------------------------------------------------------------
int CustomButtonBase::TextPixelSize() const
{
    return m_text_pixel_size;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetTextPixelSize
//  [ 機　能 ] : 文字サイズ設定
//  [ 引　数 ] : int value : 新しい文字サイズ
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void CustomButtonBase::SetTextPixelSize( int value )
{
    CssStyler().SetTemplateParam( CSS_TEXT_SIZE, QString::number( value ) );

    if( m_text_pixel_size == value )
    {
        return;
    }

    m_text_pixel_size = value;
    emit TextPixelSizeChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : BorderColor
//  [ 機　能 ] : ボタンの枠線の色を取得する
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : 枠線の色
//--------------------------------------------------------------------------
QColor CustomButtonBase::BorderColor() const
{
    return m_border_color;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetBorderColor
//  [ 機　能 ] : ボタンの枠線の色を設定する
//  [ 引　数 ] : const QColor &value : 新しい枠線の色
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void CustomButtonBase::SetBorderColor( const QColor &value )
{
    CssStyler().SetTemplateParam( CSS_BORDER_COLOR_NORMAL, value.name() );

    if( m_border_color == value )
    {
        return;
    }

    m_border_color = value;
    emit BorderColorChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : CssStyler
//  [ 機　能 ] : 現在のスタイラーを取得する
//  [ 引　数 ] : void
//  [ 戻り値 ] : DynamicStyleSheet &: 現在のスタイラー
//--------------------------------------------------------------------------
DynamicStyleSheet &CustomButtonBase::CssStyler()
{
    return m_styler;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : DisabledBackgroundColor
//  [ 機　能 ] : ボタン無効時の背景色取得
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor :無効な背景色
//--------------------------------------------------------------------------
QColor CustomButtonBase::DisabledBackgroundColor() const
{
    return m_disabled_background_color;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetDisabledBackgroundColor
//  [ 機　能 ] : ボタン無効時の背景色設定
//  [ 引　数 ] : const QColor &value : 新しい無効な背景色
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void CustomButtonBase::SetDisabledBackgroundColor( const QColor &value )
{
    CssStyler().SetTemplateParam( CSS_BG_COLOR_DISABLED, value.name() );

    if( m_disabled_background_color == value )
    {
        return;
    }

    m_disabled_background_color = value;
    emit DisabledBackgroundColorChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : DisabledBorderColor
//  [ 機　能 ] : ボタン無効時の枠線の色の取得
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : 無効な文字色
//--------------------------------------------------------------------------
QColor CustomButtonBase::DisabledBorderColor() const
{
    return m_disabled_border_color;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetDisabledBorderColor
//  [ 機　能 ] : ボタン無効時の枠線の色の取得
//  [ 引　数 ] : const QColor &value : 新しい無効な枠線の色
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void CustomButtonBase::SetDisabledBorderColor( const QColor &value )
{
    CssStyler().SetTemplateParam( CSS_BORDER_COLOR_DISABLED, value.name() );

    if( m_disabled_border_color == value )
    {
        return;
    }

    m_disabled_border_color = value;
    emit DisabledBorderColorChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : DisabledTextColor
//  [ 機　能 ] : ボタン無効時の文字色の取得
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : 無効な文字色
//--------------------------------------------------------------------------
QColor CustomButtonBase::DisabledTextColor() const
{
    return m_disabled_text_color;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetDisabledTextColor
//  [ 機　能 ] : ボタン無効時の文字色の設定
//  [ 引　数 ] : const QColor &value : 新しい無効な文字色
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void CustomButtonBase::SetDisabledTextColor( const QColor &value )
{
    CssStyler().SetTemplateParam( CSS_TEXT_COLOR_DISABLED, value.name() );

    if( m_disabled_text_color == value )
    {
        return;
    }

    m_disabled_text_color = value;
    emit DisabledTextColorChanged();
}
