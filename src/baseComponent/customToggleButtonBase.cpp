#include <QDebug>
#include "baseComponent/customToggleButtonBase.h"

#define CSS_BG_COLOR_CHECKED         "CSS_BG_COLOR_SELECTED"
#define CSS_BORDER_COLOR_CHECKED     "CSS_BORDER_COLOR_SELECTED"
#define CSS_TEXT_COLOR_CHECKED       "CSS_TEXT_COLOR_SELECTED"

static const char * stylesheetTemplate = R"~(

CustomToggleButtonBase:checked {
    border-width: 2px;
    border-style: inset;

    background: )~" CSS_BG_COLOR_CHECKED R"~(;
    border-color: )~" CSS_BORDER_COLOR_CHECKED R"~(;
    color: )~" CSS_TEXT_COLOR_CHECKED R"~(;
}

)~";

CustomToggleButtonBase::CustomToggleButtonBase(QWidget *parent) : CustomButtonBase(parent),
    m_selectedBackgroundColor(),
    m_selectedBorderColor(),
    m_selectedTextColor()
{
    setCheckable(true);

    cssStyler().appendStyleSheetTemplate(stylesheetTemplate);

    setBackgroundColor(QColor::fromRgb(13, 13, 13));
    setTextColor(QColor::fromRgb(128, 128, 128));

    setSelectedBackgroundColor(QColor::fromRgb(89, 89, 89));
    setSelectedTextColor(QColor::fromRgb(255, 255, 255));
    setSelectedBorderColor(QColor::fromRgb(0, 176, 80));

    setDisabledBackgroundColor(QColor::fromRgb(22, 22, 22));
    setDisabledTextColor(QColor::fromRgb(191, 191, 191));
}

QColor CustomToggleButtonBase::selectedBorderColor() const
{
    return m_selectedBorderColor;
}

void CustomToggleButtonBase::setSelectedBorderColor(const QColor &newSelectedBorderColor)
{
    cssStyler().setTemplateParam(CSS_BORDER_COLOR_CHECKED, newSelectedBorderColor.name());
    if (m_selectedBorderColor == newSelectedBorderColor)
        return;
    m_selectedBorderColor = newSelectedBorderColor;
    emit selectedBorderColorChanged();
}

QColor CustomToggleButtonBase::selectedTextColor() const
{
    return m_selectedTextColor;
}

void CustomToggleButtonBase::setSelectedTextColor(const QColor &newSelectedTextColor)
{
    cssStyler().setTemplateParam(CSS_TEXT_COLOR_CHECKED, newSelectedTextColor.name());
    if (m_selectedTextColor == newSelectedTextColor)
        return;
    m_selectedTextColor = newSelectedTextColor;
    emit selectedTextColorChanged();
}

QColor CustomToggleButtonBase::selectedBackgroundColor() const
{
    return m_selectedBackgroundColor;
}

void CustomToggleButtonBase::setSelectedBackgroundColor(const QColor &newSelectedBackgroundColor)
{
    cssStyler().setTemplateParam(CSS_BG_COLOR_CHECKED, newSelectedBackgroundColor.name());
    if (m_selectedBackgroundColor == newSelectedBackgroundColor)
        return;
    m_selectedBackgroundColor = newSelectedBackgroundColor;
    emit selectedBackgroundColorChanged();
}
