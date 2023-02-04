#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include "customButtonBase.h"

class CustomPushButton : public CustomButtonBase
{
public:
    explicit CustomPushButton(QWidget *parent = nullptr);

    CustomPushButton(QString text, QWidget *parent = nullptr);
};

#endif // CUSTOMPUSHBUTTON_H
