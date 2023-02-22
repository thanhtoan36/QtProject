#ifndef SELECTBUTTON_H
#define SELECTBUTTON_H

#include "toggleButton.h"

class SelectButton : public ToggleButton
{
    Q_OBJECT
public:
    explicit SelectButton( QWidget *parent = nullptr );

public slots:
    virtual void OnClicked();

};

#endif // SELECTBUTTON_H
