//--------------------------------------------------------------------------
// [ ファイル名 ] : dynamicStyleSheet.h
// [ 概      要 ] : 実行時に CSS スタイルシートを生成するヘルパー クラス
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef DYNAMICSTYLESHEET_H
#define DYNAMICSTYLESHEET_H

#include <QObject>
#include <QMap>

class DynamicStyleSheet : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString StyleSheetTemplate READ StyleSheetTemplate WRITE SetStyleSheetTemplate NOTIFY StyleSheetTemplateChanged )
    Q_PROPERTY( QString StyleSheet READ StyleSheet NOTIFY StyleSheetChanged )

public:
    DynamicStyleSheet( QWidget *parent );

    QString StyleSheetTemplate() const;

    void SetStyleSheetTemplate( const QString &value );
    void AppendStyleSheetTemplate( const QString &value );

    void Polish();

    QString StyleSheet() const;
    QString TemplateParam( const QString &key ) const;
    void SetTemplateParam( const QString &key, const QString &value );

signals:
    void StyleSheetTemplateChanged();
    void StyleSheetChanged();

private:
    QString m_stylesheet_template;
    QMap<QString, QString> m_template_params;
};

#endif // DYNAMICSTYLESHEET_H
