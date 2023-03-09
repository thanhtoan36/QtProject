//--------------------------------------------------------------------------
// [ ファイル名 ] : dynamicStyleSheet.cpp
// [ 概      要 ] : 実行時に CSS スタイルシートを生成するヘルパー クラス
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "baseComponent/dynamicStyleSheet.h"
#include <QWidget>
#include <QDebug>

//--------------------------------------------------------------------------
//  [ 関数名 ] : DynamicStyleSheet
//  [ 機　能 ] : Constructor for DynamicStyleSheet
//  [ 引　数 ] : QWidget *parent : parent widget
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
DynamicStyleSheet::DynamicStyleSheet( QWidget *parent )
    : QObject( ( QObject * )parent ),
      m_stylesheet_template(),
      m_template_params()
{
    Q_ASSERT( parent );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : StyleSheetTemplate
//  [ 機　能 ] :スタイルシート テンプレートの取得
//  [ 引　数 ] : void
//  [ 戻り値 ] : QString : スタイルシート テンプレート
//--------------------------------------------------------------------------
QString DynamicStyleSheet::StyleSheetTemplate() const
{
    return m_stylesheet_template;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetStyleSheetTemplate
//  [ 機　能 ] : スタイルシート テンプレートの設定
//  [ 引　数 ] : const QString &value: 新しいスタイルシート テンプレート
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void DynamicStyleSheet::SetStyleSheetTemplate( const QString &value )
{
    if( m_stylesheet_template == value )
    {
        return;
    }

    m_stylesheet_template = value;
    emit StyleSheetTemplateChanged();
    emit StyleSheetChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : AppendStyleSheetTemplate
//  [ 機　能 ] : スタイルシートを現在のスタイルシートに付加する
//  [ 引　数 ] : const QString &value: 付加するスタイルシート
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void DynamicStyleSheet::AppendStyleSheetTemplate( const QString &value )
{
    SetStyleSheetTemplate( StyleSheetTemplate() + "\n" + value );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : Polish
//  [ 機　能 ] : 親ウィジェットの外観の更新
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void DynamicStyleSheet::Polish()
{
    static_cast<QWidget *>( parent() )->setStyleSheet( StyleSheet() );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : StyleSheet
//  [ 機　能 ] : 生成されたスタイルシートの取得
//  [ 引　数 ] : void
//  [ 戻り値 ] : QString : 生成されたスタイルシート
//--------------------------------------------------------------------------
QString DynamicStyleSheet::StyleSheet() const
{
    QString temp = StyleSheetTemplate();

    for( const auto &key : m_template_params.keys() )
    {
        const auto &value = m_template_params.value( key );
        temp.replace( key, value );
    }

    return temp;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : TemplateParam
//  [ 機　能 ] : キーに基づいてテンプレート パラメータを取得する
//  [ 引　数 ] : const QString &key : 取得するパラメータのキー
//  [ 戻り値 ] : QString : パラメータの値
//--------------------------------------------------------------------------
QString DynamicStyleSheet::TemplateParam( const QString &key ) const
{
    return m_template_params.value( key );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetTemplateParam
//  [ 機　能 ] : キーに基づいてテンプレート パラメータを設定する
//  [ 引　数 ] : const QString &key : 設定するパラメータのキー
//              const QString &value : 設定するパラメータの値
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void DynamicStyleSheet::SetTemplateParam( const QString &key, const QString &value )
{
    const auto old_value = TemplateParam( key );

    if( old_value != value )
    {
        m_template_params[key] = value;
        emit StyleSheetChanged();
    }
}
