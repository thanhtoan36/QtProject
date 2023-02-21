#include "baseComponent/selectButton.h"
#include <QDebug>

SelectButton::SelectButton(QWidget *parent) : ToggleButton(parent)
{
    SetCheckMarkVisible(true);
    connect(this, &QAbstractButton::clicked, this, &SelectButton::OnClicked);
}

void SelectButton::OnClicked()
{
    setChecked(true);
}
