#ifndef COLORFILTERCONTROLHORIZON_H
#define COLORFILTERCONTROLHORIZON_H

#include "colorFilterControl.hpp"
class ColorFilterControlHorizon : public ColorFilterControl
{
    Q_OBJECT
public:
    explicit ColorFilterControlHorizon(QWidget * parent = nullptr);
    virtual void setDispParamData(COLOR_FILTER_DISP_PARAM *param) override;

protected:
    virtual void addButtonToHistory(QSharedPointer<SelectButton> button) override;

};

#endif // COLORFILTERCONTROLHORIZON_H
