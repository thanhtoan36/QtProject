#ifndef SELECTCOLORBUTTON_H
#define SELECTCOLORBUTTON_H

#include "toggleButton.h"
class SelectColorButton : public ToggleButton
{
    Q_OBJECT
public:
    explicit SelectColorButton(QWidget *parent = nullptr);

protected:
    virtual void UpdateButtonStyles() override;

};

#endif // SELECTCOLORBUTTON_H
