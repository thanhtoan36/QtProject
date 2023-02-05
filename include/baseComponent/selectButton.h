#ifndef SELECTBUTTON_H
#define SELECTBUTTON_H

#include "toggleButton.h"

class SelectButton : public ToggleButton
{
    Q_OBJECT
public:
    explicit SelectButton(QWidget *parent = nullptr);
    SelectButton(QString text, bool isCheckMark, QWidget *parent = nullptr);

public slots:
    virtual void HandleButtonClicked() override;
};

#endif // SELECTBUTTON_H
