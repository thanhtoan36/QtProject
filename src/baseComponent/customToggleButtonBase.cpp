#include "baseComponent/customToggleButtonBase.h"
#include <QDebug>
CustomToggleButtonBase::CustomToggleButtonBase(QWidget *parent) : CustomButtonBase(parent)
{
    setCheckable(true);
}

CustomToggleButtonBase::CustomToggleButtonBase(QString text, QWidget *parent) : CustomButtonBase(text,parent)
{
    setCheckable(true);
}

CustomToggleButtonBase::CustomToggleButtonBase(QString text, int fontSize, QColor backgroundColor, QColor textColor, QWidget *parent):
     CustomButtonBase(text,fontSize,backgroundColor,textColor,parent)
{
    setCheckable(true);
}

void CustomToggleButtonBase::UpdateButtonStyles()
{
    QString style = QString("QPushButton { background-color:rgb(%1,%2,%3); color:rgb(%4,%5,%6);}")
            .arg(BackgroundColor().red()).arg(BackgroundColor().green()).arg(BackgroundColor().blue())
            .arg(TextColor().red()).arg(TextColor().green()).arg(TextColor().blue());

    QString style_press = QString(" QPushButton:pressed { background-color:rgb(%1,%2,%3); color:rgb(%4,%5,%6);}")
            .arg(m_press_background_color.red()).arg(m_press_background_color.green()).arg(m_press_background_color.blue())
            .arg(m_press_text_color.red()).arg(m_press_text_color.green()).arg(m_press_text_color.blue());

    setStyleSheet(style + style_press);
}

const QColor &CustomToggleButtonBase::PressBackgroundColor() const
{
    return m_press_background_color;
}

void CustomToggleButtonBase::SetPressBackgroundColor(const QColor &backgroundColor)
{
    m_press_background_color = backgroundColor;
}

const QColor &CustomToggleButtonBase::PressTextColor() const
{
    return m_press_text_color;
}

void CustomToggleButtonBase::SetPressTextColor(const QColor &textColor)
{
    m_press_text_color = textColor;
}

void CustomToggleButtonBase::HandleButtonClicked()
{
    qDebug() << "CustomToggleButtonBase::handleButtonClicked";
    toggle();
}
