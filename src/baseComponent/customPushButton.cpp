#include "baseComponent/customPushButton.h"
#include "baseComponent/designPolicyDefine.h"

CustomPushButton::CustomPushButton(QWidget *parent) : CustomButtonBase(parent)
{
    SetBackgroundColor(PUSH_BUTTON_BG_COLOR_ENABLE);
    SetTextColor(PUSH_BUTTON_TEXT_COLOR_ENABLE);
    SetFontSize(18);
}

CustomPushButton::CustomPushButton(QString text, QWidget *parent) :
    CustomButtonBase(text,18,QColor::fromRgb(0,0,0),QColor::fromRgb(191,191,191),parent)
{

}

void CustomPushButton::HandleButtonClicked()
{

}

void CustomPushButton::UpdateButtonStyles()
{
    QString style_enable = QString("QPushButton { background-color:rgb(0,0,0); color:rgb(191,191,191); border-style: solid; border-width: 1px;border-color: gray}");
    QString style_disable = QString(" QPushButton:disabled { background-color:rgb(22,22,22); color:rgb(191,191,191); border-style: solid; border-width: 1px;border-color: gray}");

    setStyleSheet(style_enable + style_disable);
}
