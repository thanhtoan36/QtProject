//--------------------------------------------------------------------------
// [ ファイル名 ] : dynamicStyleSheet.cpp
// [ 概      要 ] : Helper class to generate CSS style sheet at runtime
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "baseComponent/dynamicStyleSheet.h"
#include <QWidget>
#include <QDebug>

DynamicStyleSheet::DynamicStyleSheet( QWidget *parent )
    : QObject( ( QObject * )parent ),
      m_stylesheet_template(),
      m_template_params()
{
    Q_ASSERT( parent );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : StyleSheetTemplate
//  [ 機　能 ] : Get the stylesheet template
//  [ 引　数 ] : void
//  [ 戻り値 ] : QString : the stylesheet template
//--------------------------------------------------------------------------
QString DynamicStyleSheet::StyleSheetTemplate() const
{
    return m_stylesheet_template;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetStyleSheetTemplate
//  [ 機　能 ] : Set the stylesheet template
//  [ 引　数 ] : const QString &value: New stylesheet template
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
//  [ 機　能 ] : Append stylesheet to the current stylesheet
//  [ 引　数 ] : const QString &value: the stylesheet to append
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void DynamicStyleSheet::AppendStyleSheetTemplate( const QString &value )
{
    SetStyleSheetTemplate( StyleSheetTemplate() + "\n" + value );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : Polish
//  [ 機　能 ] : Update parent widget's appearance
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void DynamicStyleSheet::Polish()
{
    static_cast<QWidget *>( parent() )->setStyleSheet( StyleSheet() );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : StyleSheet
//  [ 機　能 ] : Get the generated stylesheet
//  [ 引　数 ] : void
//  [ 戻り値 ] : QString : genrated stylesheet
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
//  [ 機　能 ] : Get the template parameter base on key
//  [ 引　数 ] : const QStrin &key : the key of parameter to get
//  [ 戻り値 ] : QString : value of parameter
//--------------------------------------------------------------------------
QString DynamicStyleSheet::TemplateParam( const QString &key ) const
{
    return m_template_params.value( key );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetTemplateParam
//  [ 機　能 ] : Set the template parameter base on key
//  [ 引　数 ] : const QStrin &key : the key of parameter to set
//              const QStrin &value : the value of parameter to set
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
