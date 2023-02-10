#include "baseComponent/selectColorButton.h"

SelectColorButton::SelectColorButton(QWidget *parent) : ToggleButton(parent)
{
    SetTextColor(QColor(Qt::black));
}

void SelectColorButton::UpdateButtonStyles()
{
    QString style_enable = QString("QPushButton { background-color:rgb(%1,%2,%3); color:rgb(%4,%5,%6); border-style: solid; border-width: 1px;border-color: gray;}")
            .arg(BackgroundColor().red()).arg(BackgroundColor().green()).arg(BackgroundColor().blue())
            .arg(TextColor().red()).arg(TextColor().green()).arg(TextColor().blue());
    QString style_disable = QString(" QPushButton:disabled { background-color:rgb(22,22,22); color:rgb(191,191,191); border-style: solid; border-width: 1px;border-color: gray; }");

    QString style_check = QString("QPushButton:checked { background-color:rgb(%1,%2,%3); color:rgb(%4,%5,%6); border-style: solid; border-width: 1px;border-color: rgb(0,176,80);}")
            .arg(BackgroundColor().red()).arg(BackgroundColor().green()).arg(BackgroundColor().blue())
            .arg(TextColor().red()).arg(TextColor().green()).arg(TextColor().blue());

    setStyleSheet(style_enable + style_disable + style_check);
}
