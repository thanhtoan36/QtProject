#include "baseComponent/customButtonBase.h"

#define CSS_BG_COLOR_NORMAL         "CSS_BG_COLOR_NORMAL"
#define CSS_BORDER_COLOR_NORMAL     "CSS_BORDER_COLOR_NORMAL"
#define CSS_TEXT_COLOR_NORMAL       "CSS_TEXT_COLOR_NOMAL"

#define CSS_BG_COLOR_DISABLED         "CSS_BG_COLOR_DISABLED"
#define CSS_BORDER_COLOR_DISABLED     "CSS_BORDER_COLOR_DISABLED"
#define CSS_TEXT_COLOR_DISABLED       "CSS_TEXT_COLOR_DISABLED"

#define CSS_TEXT_SIZE               "CSS_TEXT_SIZE"

// see: https://linuxhint.com/c-multiline-string-literals/
static const char * g_stylesheet_template = R"~(

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

CustomButtonBase::CustomButtonBase(QWidget *parent) : QPushButton(parent),
    m_styler(this),
    m_background_color(),
    m_border_color(),
    m_text_color(),
    m_disabled_background_color(),
    m_disabled_border_color(),
    m_disabled_text_color(),
    m_text_pixel_size()
{
    setAutoFillBackground(true);
    CssStyler().SetStyleSheetTemplate(g_stylesheet_template);

    // NOTE: Must set all params here (to make sure all css templated arguments are populated)
    SetBackgroundColor(QColor::fromRgb(0, 0, 0));
    SetTextColor(QColor::fromRgb(191, 191, 191));
    SetBorderColor(Qt::darkGray);

    SetDisabledBackgroundColor(QColor::fromRgb(22, 22, 22));
    SetDisabledTextColor(QColor::fromRgb(191, 191, 191));
    SetDisabledBorderColor(Qt::darkGray);

    SetTextPixelSize(16);

    connect(&m_styler, &DynamicStyleSheet::StyleSheetChanged, &m_styler, &DynamicStyleSheet::Polish, Qt::DirectConnection);
    CssStyler().Polish();
}

QColor CustomButtonBase::BackgroundColor() const
{
    return m_background_color;
}

void CustomButtonBase::SetBackgroundColor(const QColor &value)
{
    CssStyler().SetTemplateParam(CSS_BG_COLOR_NORMAL, value.name());
    if (m_background_color == value)
        return;
    m_background_color = value;
    emit BackgroundColorChanged();
}

QColor CustomButtonBase::TextColor() const
{
    return m_text_color;
}

void CustomButtonBase::SetTextColor(const QColor &value)
{
    CssStyler().SetTemplateParam(CSS_TEXT_COLOR_NORMAL, value.name());
    if (m_text_color == value)
        return;
    m_text_color = value;
    emit TextColorChanged();
}

int CustomButtonBase::TextPixelSize() const
{
    return m_text_pixel_size;
}

void CustomButtonBase::SetTextPixelSize(int value)
{
    CssStyler().SetTemplateParam(CSS_TEXT_SIZE, QString::number(value));
    if (m_text_pixel_size == value)
        return;
    m_text_pixel_size = value;
    emit TextPixelSizeChanged();
}

QColor CustomButtonBase::BorderColor() const
{
    return m_border_color;
}

void CustomButtonBase::SetBorderColor(const QColor &value)
{
    CssStyler().SetTemplateParam(CSS_BORDER_COLOR_NORMAL, value.name());
    if (m_border_color == value)
        return;
    m_border_color = value;
    emit BorderColorChanged();
}

DynamicStyleSheet &CustomButtonBase::CssStyler()
{
    return m_styler;
}

QColor CustomButtonBase::DisabledBackgroundColor() const
{
    return m_disabled_background_color;
}

void CustomButtonBase::SetDisabledBackgroundColor(const QColor &value)
{
    CssStyler().SetTemplateParam(CSS_BG_COLOR_DISABLED, value.name());
    if (m_disabled_background_color == value)
        return;
    m_disabled_background_color = value;
    emit DisabledBackgroundColorChanged();
}

QColor CustomButtonBase::DisabledBorderColor() const
{
    return m_disabled_border_color;
}

void CustomButtonBase::SetDisabledBorderColor(const QColor &value)
{
    CssStyler().SetTemplateParam(CSS_BORDER_COLOR_DISABLED, value.name());
    if (m_disabled_border_color == value)
        return;
    m_disabled_border_color = value;
    emit DisabledBorderColorChanged();
}

QColor CustomButtonBase::DisabledTextColor() const
{
    return m_disabled_text_color;
}

void CustomButtonBase::SetDisabledTextColor(const QColor &value)
{
    CssStyler().SetTemplateParam(CSS_TEXT_COLOR_DISABLED, value.name());
    if (m_disabled_text_color == value)
        return;
    m_disabled_text_color = value;
    emit DisabledTextColorChanged();
}
