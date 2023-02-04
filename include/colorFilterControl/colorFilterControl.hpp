#ifndef COLORFILTERCONTROL_H
#define COLORFILTERCONTROL_H

#include "../baseComponent/panelControlBase.h"

class QLabel;

class ColorFilterControl : public PanelControlBase
{
public:
    ColorFilterControl();

protected:
    virtual void SetupUiComponents();

protected:
    QLabel *m_label_title;
};

#endif // COLORFILTERCONTROL_H
