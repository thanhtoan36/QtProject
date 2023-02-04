#include "baseComponent/selectButton.h"
#include <QDebug>
SelectButton::SelectButton(QWidget *parent) : ToggleButton(parent)
{

}

SelectButton::SelectButton(QString text, bool isCheckMark, QWidget *parent):
    ToggleButton(text,isCheckMark,parent)
{

}

void SelectButton::HandleButtonClicked()
{
    qDebug() << "SelectButton::handleButtonClicked";
    if (ButtonState() == CustomToggleButtonBase::TOGGLE_BUTTON_STATE_OFF)
    {
        SetButtonState(CustomToggleButtonBase::TOGGLE_BUTTON_STATE_ON);
    }
}

