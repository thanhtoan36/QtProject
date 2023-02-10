#ifndef COLORFILTERCONTROL_H
#define COLORFILTERCONTROL_H

#include "../baseComponent/panelControlBase.h"
#include "baseComponent/selectColorButton.h"
#include "baseComponent/selectButton.h"
#include "baseComponent/customPushButton.h"
#include "colorFilterControl_datatypes.h"
#include "utility.h"
#include <QLabel>

#define PAGE_SIZE 16
enum COLOR_FILTER_MODE
{
    COLOR_FILTER_MODE_TAB1,
    COLOR_FILTER_MODE_TAB2,
    COLOR_FILTER_MODE_HISTORY
};

class ColorFilterControl : public PanelControlBase
{
    Q_OBJECT
    Q_PROPERTY(int currentTab1Page READ currentTab1Page WRITE setCurrentTab1Page NOTIFY currentTab1PageChanged)
    Q_PROPERTY(int currentTab2Page READ currentTab2Page WRITE setCurrentTab2Page NOTIFY currentTab2PageChanged)
    Q_PROPERTY(int currentHistoryPage READ currentHistoryPage WRITE setCurrentHistoryPage NOTIFY currentHistoryPageChanged)
    Q_PROPERTY(COLOR_FILTER_MODE mode READ mode WRITE setMode NOTIFY modeChanged)
public:

    explicit ColorFilterControl(QWidget* parent = nullptr);

    void setDispParamData( COLOR_FILTER_DISP_PARAM *param);

    void ScrollUp();

    void ScrollDown();

    int currentTab1Page() const;
    void setCurrentTab1Page(int newCurrentTab1Page);

    int currentTab2Page() const;
    void setCurrentTab2Page(int newCurrentTab2Page);

    int currentHistoryPage() const;
    void setCurrentHistoryPage(int newCurrentHistoryPage);

    COLOR_FILTER_MODE mode() const;
    void setMode(COLOR_FILTER_MODE newMode);

signals:
    void currentTab1PageChanged();

    void currentTab2PageChanged();

    void currentHistoryPageChanged();

    void modeChanged();

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

private:
    int m_currentTab1Page;
    int m_currentTab2Page;
    int m_currentHistoryPage;
    COLOR_FILTER_MODE m_mode;
};

#endif // COLORFILTERCONTROL_H
