#include "baseComponent/customToggleButtonBase.h"
#include <QDebug>
CustomToggleButtonBase::CustomToggleButtonBase(QWidget *parent) : CustomButtonBase(parent)
{
    connect(this,&CustomToggleButtonBase::ButtonStateChange,this,&CustomToggleButtonBase::HandleButtonStateChanged);
}

CustomToggleButtonBase::CustomToggleButtonBase(QString text, QWidget *parent) : CustomButtonBase(text,parent)
{
    connect(this,&CustomToggleButtonBase::ButtonStateChange,this,&CustomToggleButtonBase::HandleButtonStateChanged);
}

CustomToggleButtonBase::CustomToggleButtonBase(QString text, int fontSize, QColor backgroundColor, QColor textColor, QWidget *parent):
     CustomButtonBase(text,fontSize,backgroundColor,textColor,parent)
{
    connect(this,&CustomToggleButtonBase::ButtonStateChange,this,&CustomToggleButtonBase::HandleButtonStateChanged);
}

void CustomToggleButtonBase::SetStyleButton()
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

CustomToggleButtonBase::ToggleButtonState CustomToggleButtonBase::ButtonState() const
{
    return m_button_state;
}

void CustomToggleButtonBase::SetButtonState(ToggleButtonState state)
{
    m_button_state = state;
    emit ButtonStateChange(m_button_state);
}

void CustomToggleButtonBase::HandleButtonClicked()
{
    qDebug() << "CustomToggleButtonBase::handleButtonClicked";
    if (m_button_state == TOGGLE_BUTTON_STATE_OFF)
    {
        m_button_state = TOGGLE_BUTTON_STATE_ON;
    }
    else
    {
        m_button_state = TOGGLE_BUTTON_STATE_OFF;
    }
}

void CustomToggleButtonBase::HandleButtonStateChanged(uint8_t state)
{
    Q_UNUSED(state)
    qDebug() << "CustomToggleButtonBase::HandleButtonStateChanged";
}
