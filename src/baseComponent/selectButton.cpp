#include "baseComponent/selectButton.h"
#include <QDebug>
SelectButton::SelectButton(QWidget *parent) : ToggleButton(parent)
{

}

void SelectButton::HandleButtonClicked()
{
    setChecked(true);
}

