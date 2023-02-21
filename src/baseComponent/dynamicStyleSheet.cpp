#include "baseComponent/dynamicStyleSheet.h"
#include <QWidget>
#include <QDebug>

DynamicStyleSheet::DynamicStyleSheet(QWidget *parent)
    : QObject((QObject*)parent),
      m_stylesheet_template(),
      m_template_params()
{
    Q_ASSERT(parent);
}

QString DynamicStyleSheet::StyleSheetTemplate() const
{
    return m_stylesheet_template;
}

void DynamicStyleSheet::SetStyleSheetTemplate(const QString &value)
{
    if (m_stylesheet_template == value)
        return;
    m_stylesheet_template = value;
    emit StyleSheetTemplateChanged();
    emit StyleSheetChanged();
}

void DynamicStyleSheet::AppendStyleSheetTemplate(const QString &value)
{
    SetStyleSheetTemplate(StyleSheetTemplate() + "\n" + value);
}

void DynamicStyleSheet::Polish()
{
    static_cast<QWidget*>(parent())->setStyleSheet(StyleSheet());
}

QString DynamicStyleSheet::StyleSheet() const
{
    QString temp = StyleSheetTemplate();
    for (const auto &key : m_template_params.keys()) {
        const auto &value = m_template_params.value(key);
        temp.replace(key, value);
    }
    return temp;
}

QString DynamicStyleSheet::TemplateParam(const QString &key) const
{
    return m_template_params.value(key);
}

void DynamicStyleSheet::SetTemplateParam(const QString &key, const QString &value)
{
    const auto old_value = TemplateParam(key);
    if (old_value != value) {
        m_template_params[key] = value;
        emit StyleSheetChanged();
    }
}
