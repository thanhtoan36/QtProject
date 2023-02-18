#ifndef COLORFILTERCONTROLHORIZON_H
#define COLORFILTERCONTROLHORIZON_H

#include "colorFilterControl.hpp"
class ColorFilterControlHorizon : public ColorFilterControl
{
    Q_OBJECT
public:
    explicit ColorFilterControlHorizon(QWidget * parent = nullptr);
    void SetDispParamDataHorizon(COLOR_FILTER_DISP_PARAM *param);

protected:
    virtual void addButtonToHistory(QSharedPointer<SelectColorButton>& button) override;

private:
    CustomPushButton m_empty1_button;
    CustomPushButton m_up_tab_button;
    CustomPushButton m_down_tab_button;

};

#endif // COLORFILTERCONTROLHORIZON_H
