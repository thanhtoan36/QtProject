#include "baseComponent/selectButton.h"
#include <QDebug>

SelectButton::SelectButton(QWidget *parent) : ToggleButton(parent)
{
    setCheckMarkVisible(true);
    connect(this, &QAbstractButton::clicked, this, &SelectButton::onClicked);
}

void SelectButton::onClicked()
{
    setChecked(true);
}
