#include "baseComponent/toggleButton.h"
#include "baseComponent/designPolicyDefine.h"
#include <QDebug>

ToggleButton::ToggleButton(QWidget *parent) : CustomToggleButtonBase(parent) ,m_check_label(this)
{

}

ToggleButton::ToggleButton(QString text, QWidget *parent):
    CustomToggleButtonBase(text,parent),
    m_check_label(this)
{

}

ToggleButton::ToggleButton(QString text, bool isCheckMark, QWidget *parent):
    CustomToggleButtonBase(text, 18, SELECT_BUTTON_BG_COLOR_UNSELECTED, SELECT_BUTTON_TEXT_COLOR_UNSELECTED,parent),
    m_check_label(this),
    m_is_check_mark_enable(isCheckMark)
{

    m_check_label.setText("✓");
    m_check_label.setStyleSheet("QLabel { background-color : transparent; color : white; }");
    m_check_label.setGeometry(2,2,10,10);
    m_check_label.setVisible(m_check_mark_visible && m_is_check_mark_enable);

    ToggleButton::SetStyleButton();
}

void ToggleButton::SetStyleButton()
{
    QString style_enable = QString("QPushButton { background-color:rgb(%1,%2,%3); color:rgb(%4,%5,%6);}")
            .arg(BackgroundColor().red()).arg(BackgroundColor().green()).arg(BackgroundColor().blue())
            .arg(TextColor().red()).arg(TextColor().green()).arg(TextColor().blue());

    QString style_disable = QString(" QPushButton:disabled { background-color:rgb(%1,%2,%3); color:rgb(%4,%5,%6);}")
            .arg(SELECT_BUTTON_BG_COLOR_DISABLE.red()).arg(SELECT_BUTTON_BG_COLOR_DISABLE.green()).arg(SELECT_BUTTON_BG_COLOR_DISABLE.blue())
            .arg(SELECT_BUTTON_TEXT_COLOR_DISABLE.red()).arg(SELECT_BUTTON_TEXT_COLOR_DISABLE.green()).arg(SELECT_BUTTON_TEXT_COLOR_DISABLE.blue());

    setStyleSheet(style_enable + style_disable);
}

bool ToggleButton::IsCheckMarkEnable() const
{
    return m_is_check_mark_enable;
}

void ToggleButton::setIsCheckMarkEnable(bool isCheckMark)
{
    m_is_check_mark_enable = isCheckMark;
    m_check_label.setVisible(m_check_mark_visible && m_is_check_mark_enable);
}

void ToggleButton::HandleButtonClicked()
{
    qDebug() << "ToggleButton::handleButtonClicked";
    if (ButtonState() == CustomToggleButtonBase::TOGGLE_BUTTON_STATE_OFF)
    {
        SetButtonState(CustomToggleButtonBase::TOGGLE_BUTTON_STATE_ON);
    }
    else
    {
        SetButtonState(CustomToggleButtonBase::TOGGLE_BUTTON_STATE_OFF);
    }
}

void ToggleButton::HandleButtonStateChanged(uint8_t state)
{
    qDebug() << "ToggleButton::HandleButtonStateChanged " <<state;
    if (state == CustomToggleButtonBase::TOGGLE_BUTTON_STATE_OFF)
    {
        SetBackgroundColor(SELECT_BUTTON_BG_COLOR_UNSELECTED);
        SetTextColor(SELECT_BUTTON_TEXT_COLOR_UNSELECTED);
        SetCheckMarkVisible(false);
    }
    else
    {
        SetBackgroundColor(SELECT_BUTTON_BG_COLOR_SELECTED);
        SetTextColor(SELECT_BUTTON_TEXT_COLOR_SELECTED);
        SetCheckMarkVisible(true);
    }
}

void ToggleButton::SetCheckMarkVisible(bool visible)
{
    m_check_mark_visible = visible;
    m_check_label.setVisible(m_check_mark_visible && m_is_check_mark_enable);
}
