#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include "customButtonBase.h"

class CustomPushButton : public CustomButtonBase
{
public:
    explicit CustomPushButton(QWidget *parent = nullptr);

    CustomPushButton(QString text, QWidget *parent = nullptr);

public slots:
    virtual void HandleButtonClicked() override;

protected:
    virtual void UpdateButtonStyles() override;
};

#endif // CUSTOMPUSHBUTTON_H
