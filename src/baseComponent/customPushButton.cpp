#include "baseComponent/customPushButton.h"


CustomPushButton::CustomPushButton(QWidget *parent) : CustomButtonBase(parent)
{

}

CustomPushButton::CustomPushButton(QString text, QWidget *parent) :
    CustomButtonBase(text,8,QColor::fromRgb(0,0,0),QColor::fromRgb(191,191,191),parent)
{

}
