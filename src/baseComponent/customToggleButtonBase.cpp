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

CustomToggleButtonBase::CustomToggleButtonBase(QWidget *parent) : CustomButtonBase(parent),
    m_selected_background_color(),
    m_selected_border_color(),
    m_selected_text_color()
{
    setCheckable(true);

    CssStyler().AppendStyleSheetTemplate(g_stylesheet_template);

    SetBackgroundColor(QColor::fromRgb(13, 13, 13));
    SetTextColor(QColor::fromRgb(128, 128, 128));

    SetSelectedBackgroundColor(QColor::fromRgb(89, 89, 89));
    SetSelectedTextColor(QColor::fromRgb(255, 255, 255));
    SetSelectedBorderColor(QColor::fromRgb(0, 176, 80));

    SetDisabledBackgroundColor(QColor::fromRgb(22, 22, 22));
    SetDisabledTextColor(QColor::fromRgb(191, 191, 191));
}

QColor CustomToggleButtonBase::SelectedBorderColor() const
{
    return m_selected_border_color;
}

void CustomToggleButtonBase::SetSelectedBorderColor(const QColor &value)
{
    CssStyler().SetTemplateParam(CSS_BORDER_COLOR_CHECKED, value.name());
    if (m_selected_border_color == value)
        return;
    m_selected_border_color = value;
    emit SelectedBorderColorChanged();
}

QColor CustomToggleButtonBase::SelectedTextColor() const
{
    return m_selected_text_color;
}

void CustomToggleButtonBase::SetSelectedTextColor(const QColor &value)
{
    CssStyler().SetTemplateParam(CSS_TEXT_COLOR_CHECKED, value.name());
    if (m_selected_text_color == value)
        return;
    m_selected_text_color = value;
    emit SelectedTextColorChanged();
}

QColor CustomToggleButtonBase::SelectedBackgroundColor() const
{
    return m_selected_background_color;
}

void CustomToggleButtonBase::SetSelectedBackgroundColor(const QColor &value)
{
    CssStyler().SetTemplateParam(CSS_BG_COLOR_CHECKED, value.name());
    if (m_selected_background_color == value)
        return;
    m_selected_background_color = value;
    emit SelectedBackgroundColorChanged();
}
