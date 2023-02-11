#ifndef DYNAMICSTYLESHEET_H
#define DYNAMICSTYLESHEET_H

#include <QObject>
#include <QMap>

class DynamicStyleSheet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString styleSheetTemplate READ styleSheetTemplate WRITE setStyleSheetTemplate NOTIFY styleSheetTemplateChanged)
    Q_PROPERTY(QString styleSheet READ styleSheet NOTIFY styleSheetChanged)

public:
    DynamicStyleSheet(QWidget *parent);

    QString styleSheetTemplate() const;

    void setStyleSheetTemplate(const QString &newStyleSheetTemplate);
    void appendStyleSheetTemplate(const QString &styleSheet);

    void polish();

    QString styleSheet() const;
    QString templateParam(const QString &key) const;
    void setTemplateParam(const QString &key, const QString &value);

signals:
    void styleSheetTemplateChanged();

    void styleSheetChanged();

private:
    QString m_styleSheetTemplate;
    QMap<QString, QString> m_templateParams;
};

#endif // DYNAMICSTYLESHEET_H
