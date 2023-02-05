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
    setChecked(true);
}

