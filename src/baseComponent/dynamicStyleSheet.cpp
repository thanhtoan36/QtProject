#include "baseComponent/dynamicStyleSheet.h"
#include <QWidget>
#include <QDebug>

DynamicStyleSheet::DynamicStyleSheet(QWidget *parent)
    : QObject((QObject*)parent),
      m_styleSheetTemplate(),
      m_templateParams()
{
    Q_ASSERT(parent);
}

QString DynamicStyleSheet::styleSheetTemplate() const
{
    return m_styleSheetTemplate;
}

void DynamicStyleSheet::setStyleSheetTemplate(const QString &newStyleSheetTemplate)
{
    if (m_styleSheetTemplate == newStyleSheetTemplate)
        return;
    m_styleSheetTemplate = newStyleSheetTemplate;
    emit styleSheetTemplateChanged();
    emit styleSheetChanged();
}

void DynamicStyleSheet::appendStyleSheetTemplate(const QString &styleSheet)
{
    setStyleSheetTemplate(styleSheetTemplate() + "\n" + styleSheet);
}

void DynamicStyleSheet::polish()
{
    static_cast<QWidget*>(parent())->setStyleSheet(styleSheet());
}

QString DynamicStyleSheet::styleSheet() const
{
    QString temp = styleSheetTemplate();
    for (const auto &key : m_templateParams.keys()) {
        const auto &value = m_templateParams.value(key);
        temp.replace(key, value);
    }
    return temp;
}

QString DynamicStyleSheet::templateParam(const QString &key) const
{
    return m_templateParams.value(key);
}

void DynamicStyleSheet::setTemplateParam(const QString &key, const QString &value)
{
    const auto oldValue = templateParam(key);
    if (oldValue != value) {
        m_templateParams[key] = value;
        emit styleSheetChanged();
    }
}
