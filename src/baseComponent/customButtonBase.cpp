#include "baseComponent/customButtonBase.h"

#define CSS_BG_COLOR_NORMAL         "CSS_BG_COLOR_NORMAL"
#define CSS_BORDER_COLOR_NORMAL     "CSS_BORDER_COLOR_NORMAL"
#define CSS_TEXT_COLOR_NORMAL       "CSS_TEXT_COLOR_NOMAL"

#define CSS_BG_COLOR_DISABLED         "CSS_BG_COLOR_DISABLED"
#define CSS_BORDER_COLOR_DISABLED     "CSS_BORDER_COLOR_DISABLED"
#define CSS_TEXT_COLOR_DISABLED       "CSS_TEXT_COLOR_DISABLED"

#define CSS_TEXT_SIZE               "CSS_TEXT_SIZE"

// The R"~(  )~" parts are to support writting string literals in multiple lines,
// see: https://linuxhint.com/c-multiline-string-literals/
static const char * stylesheetTemplate = R"~(

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
    m_stylesheetTemplate(stylesheetTemplate),
    m_backgroundColor(),
    m_borderColor(),
    m_textColor(),
    m_disabledBackgroundColor(),
    m_disabledBorderColor(),
    m_disabledTextColor(),
    m_textPixelSize()
{
    setAutoFillBackground(true);
    cssStyler().setStyleSheetTemplate(stylesheetTemplate);

    // NOTE: Must set all params here (to make sure all css templated arguments are populated)
    setBackgroundColor(QColor::fromRgb(0, 0, 0));
    setTextColor(QColor::fromRgb(191, 191, 191));
    setBorderColor(Qt::darkGray);

    setDisabledBackgroundColor(QColor::fromRgb(22, 22, 22));
    setDisabledTextColor(QColor::fromRgb(191, 191, 191));
    setDisabledBorderColor(Qt::darkGray);

    setTextPixelSize(16);

    connect(&m_styler, &DynamicStyleSheet::styleSheetChanged, &m_styler, &DynamicStyleSheet::polish, Qt::DirectConnection);
    cssStyler().polish();
}

QColor CustomButtonBase::backgroundColor() const
{
    return m_backgroundColor;
}

void CustomButtonBase::setBackgroundColor(const QColor &newBackgroundColor)
{
    cssStyler().setTemplateParam(CSS_BG_COLOR_NORMAL, newBackgroundColor.name());
    if (m_backgroundColor == newBackgroundColor)
        return;
    m_backgroundColor = newBackgroundColor;
    emit backgroundColorChanged();
}

QColor CustomButtonBase::textColor() const
{
    return m_textColor;
}

void CustomButtonBase::setTextColor(const QColor &newTextColor)
{
    cssStyler().setTemplateParam(CSS_TEXT_COLOR_NORMAL, newTextColor.name());
    if (m_textColor == newTextColor)
        return;
    m_textColor = newTextColor;
    emit textColorChanged();
}

int CustomButtonBase::textPixelSize() const
{
    return m_textPixelSize;
}

void CustomButtonBase::setTextPixelSize(int newTextPixelSize)
{
    cssStyler().setTemplateParam(CSS_TEXT_SIZE, QString::number(newTextPixelSize));
    if (m_textPixelSize == newTextPixelSize)
        return;
    m_textPixelSize = newTextPixelSize;
    emit textPixelSizeChanged();
}

QColor CustomButtonBase::borderColor() const
{
    return m_borderColor;
}

void CustomButtonBase::setBorderColor(const QColor &newBorderColor)
{
    cssStyler().setTemplateParam(CSS_BORDER_COLOR_NORMAL, newBorderColor.name());
    if (m_borderColor == newBorderColor)
        return;
    m_borderColor = newBorderColor;
    emit borderColorChanged();
}

DynamicStyleSheet &CustomButtonBase::cssStyler()
{
    return m_styler;
}

QColor CustomButtonBase::disabledBackgroundColor() const
{
    return m_disabledBackgroundColor;
}

void CustomButtonBase::setDisabledBackgroundColor(const QColor &newDisabledBackgroundColor)
{
    cssStyler().setTemplateParam(CSS_BG_COLOR_DISABLED, newDisabledBackgroundColor.name());
    if (m_disabledBackgroundColor == newDisabledBackgroundColor)
        return;
    m_disabledBackgroundColor = newDisabledBackgroundColor;
    emit disabledBackgroundColorChanged();
}

QColor CustomButtonBase::disabledBorderColor() const
{
    return m_disabledBorderColor;
}

void CustomButtonBase::setDisabledBorderColor(const QColor &newDisabledBorderColor)
{
    cssStyler().setTemplateParam(CSS_BORDER_COLOR_DISABLED, newDisabledBorderColor.name());
    if (m_disabledBorderColor == newDisabledBorderColor)
        return;
    m_disabledBorderColor = newDisabledBorderColor;
    emit disabledBorderColorChanged();
}

QColor CustomButtonBase::disabledTextColor() const
{
    return m_disabledTextColor;
}

void CustomButtonBase::setDisabledTextColor(const QColor &newDisabledTextColor)
{
    cssStyler().setTemplateParam(CSS_TEXT_COLOR_DISABLED, newDisabledTextColor.name());
    if (m_disabledTextColor == newDisabledTextColor)
        return;
    m_disabledTextColor = newDisabledTextColor;
    emit disabledTextColorChanged();
}
