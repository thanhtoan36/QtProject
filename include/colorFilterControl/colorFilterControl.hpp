#ifndef COLORFILTERCONTROL_H
#define COLORFILTERCONTROL_H

#include "../baseComponent/panelControlBase.h"
#include "baseComponent/selectColorButton.h"
#include "baseComponent/selectButton.h"
#include "baseComponent/customPushButton.h"
#include "colorFilterControl_datatypes.h"
#include "utility.h"
#include <QLabel>

class ColorFilterControl : public PanelControlBase
{
public:
    explicit ColorFilterControl(QWidget* parent = nullptr);

    void setDispParamData( COLOR_FILTER_DISP_PARAM *param);

    void ScrollUp();

    void ScrollDown();

protected:
    virtual void SetupUiComponents();
    virtual void SetupUiEvents();

protected:
    QLabel m_title_label;
    SelectButton m_tab1_button;
    SelectButton m_tab2_button;
    CustomPushButton m_next_button;
    CustomPushButton m_prev_button;
    ToggleButton m_history_button;
    CustomPushButton m_up_button;
    CustomPushButton m_down_button;
    CustomPushButton m_back_button;
    QLabel m_setting_label;
    SelectButton m_title_button;
    SelectButton m_empty_button;
    SelectButton m_register_button;
    SelectButton m_delete_button;

    QVector<QWidget*> m_children_tab1;
    QVector<QWidget*> m_children_tab2;
    QVector<QWidget*> m_children_history;

    QVector<QSharedPointer<SelectColorButton>> m_tab1_buttons;
    QVector<QSharedPointer<SelectColorButton>> m_tab2_buttons;
    QVector<QSharedPointer<SelectColorButton>> m_history_buttons;

    uint32_t m_current_scroll_step = 0;

};

#endif // COLORFILTERCONTROL_H
