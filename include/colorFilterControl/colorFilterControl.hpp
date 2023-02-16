#ifndef COLORFILTERCONTROL_H
#define COLORFILTERCONTROL_H

#include "../baseComponent/panelControlBase.h"
#include "baseComponent/selectColorButton.h"
#include "baseComponent/selectButton.h"
#include "baseComponent/customPushButton.h"
#include "baseComponent/gridBackground.h"
#include "colorFilterControl_datatypes.h"
#include "utility.h"
#include <QLabel>

enum COLOR_FILTER_MODE
{
    COLOR_FILTER_MODE_TAB1,
    COLOR_FILTER_MODE_TAB2,
    COLOR_FILTER_MODE_HISTORY
};
struct COLOR_FILTER_BUTTON_DATA
{
    QString text;
    QColor color;
    bool operator==(COLOR_FILTER_BUTTON_DATA a) const {
          if(a.text==text && a.color== color)
             return true;
          else
             return false;
    }
};

class ColorFilterControl : public PanelControlBase
{
    Q_OBJECT
    Q_PROPERTY(int currentTBTabPage READ currentTBTabPage WRITE setCurrentTBTabPage NOTIFY currentTBTabPageChanged)
    Q_PROPERTY(int currentCustomTabPage READ currentCustomTabPage WRITE setCurrentCustomTabPage NOTIFY currentCustomTabPageChanged)
    Q_PROPERTY(int currentHistoryPage READ currentHistoryPage WRITE setCurrentHistoryPage NOTIFY currentHistoryPageChanged)
    Q_PROPERTY(COLOR_FILTER_MODE mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(COLOR_FILTER_BUTTON_DATA currentTBTabButtonCheck READ currentTBTabButtonCheck WRITE setCurrentTBTabButtonCheck NOTIFY currentTBTabButtonCheckChanged)
    Q_PROPERTY(COLOR_FILTER_BUTTON_DATA currentCustomTabButtonCheck READ currentCustomTabButtonCheck WRITE setCurrentCustomTabButtonCheck NOTIFY currentCustomTabButtonCheckChanged)
    Q_PROPERTY(COLOR_FILTER_BUTTON_DATA currentHistoryTabButtonCheck READ currentHistoryTabButtonCheck WRITE setCurrentHistoryTabButtonCheck NOTIFY currentHistoryTabButtonCheckChanged)
public:

    explicit ColorFilterControl(QWidget* parent = nullptr);

    void setDispParamData( COLOR_FILTER_DISP_PARAM *param);

    void ScrollUp();

    void ScrollDown();

    int currentTBTabPage() const;
    void setCurrentTBTabPage(int newCurrentTab1Page);

    int currentCustomTabPage() const;
    void setCurrentCustomTabPage(int newCurrentTab2Page);

    int currentHistoryPage() const;
    void setCurrentHistoryPage(int newCurrentHistoryPage);

    COLOR_FILTER_MODE mode() const;
    void setMode(COLOR_FILTER_MODE newMode);

    void onModeChanged();

    void updateTBTabPage();

    void updateCustomTabPage();

    void updateHistoryPage();

    int maxTBTabPages() const;

    int maxCustomTabPages() const;

    int maxHistoryPages() const;

    void onTBTabButtonChecked(const int index, QObject* sender);

    void onCustomTabButtonChecked(const int index, QObject* sender);

    void onHistoryButtonChecked(const int index, QObject* sender);

    const COLOR_FILTER_BUTTON_DATA currentTBTabButtonCheck() const;
    void setCurrentTBTabButtonCheck(const COLOR_FILTER_BUTTON_DATA& newCurrentTBTabButtonCheck);

    const COLOR_FILTER_BUTTON_DATA currentCustomTabButtonCheck() const;
    void setCurrentCustomTabButtonCheck(const COLOR_FILTER_BUTTON_DATA& newCurrentCustomTabButtonCheck);

    const COLOR_FILTER_BUTTON_DATA currentHistoryTabButtonCheck() const;
    void setCurrentHistoryTabButtonCheck(const COLOR_FILTER_BUTTON_DATA& newCurrentHistoryTabButtonCheck);


signals:
    void currentTBTabPageChanged();

    void currentCustomTabPageChanged();

    void currentHistoryPageChanged();

    void modeChanged();

    void currentTBTabButtonCheckChanged();

    void currentCustomTabButtonCheckChanged();

    void currentHistoryTabButtonCheckChanged();

protected:
    virtual void SetupUiComponents();
    virtual void SetupUiEvents();
    virtual void addButtonToHistory(QSharedPointer<SelectColorButton>& button);


protected:
    GridBackground m_grid;
    QLabel m_title_label;
    SelectButton m_tb_tab_button;
    SelectButton m_custom_tab_button;
    CustomPushButton m_next_button;
    CustomPushButton m_prev_button;
    ToggleButton m_history_button;
    CustomPushButton m_up_button;
    CustomPushButton m_down_button;
    CustomPushButton m_back_button;
    QLabel m_setting_label;
    SelectButton m_title_button;
    CustomPushButton m_empty_button;
    SelectButton m_register_button;
    SelectButton m_delete_button;

    QVector<QWidget*> m_children_tb_tab;
    QVector<QWidget*> m_children_custom_tab;
    QVector<QWidget*> m_children_history;

    QVector<QSharedPointer<SelectColorButton>> m_tb_tab_buttons;
    QVector<QSharedPointer<SelectColorButton>> m_custom_tab_buttons;
    QVector<QSharedPointer<SelectColorButton>> m_history_buttons;

    uint32_t m_current_scroll_step = 0;

private:
    int m_currentTBTabPage;
    int m_currentCustomTabPage;
    int m_currentHistoryPage;
    COLOR_FILTER_MODE m_mode;
    COLOR_FILTER_MODE m_previous_tab;
    COLOR_FILTER_BUTTON_DATA m_currentTBTabButtonCheck;
    COLOR_FILTER_BUTTON_DATA m_currentCustomTabButtonCheck;
    COLOR_FILTER_BUTTON_DATA m_currentHistoryTabButtonCheck;
};

#endif // COLORFILTERCONTROL_H
