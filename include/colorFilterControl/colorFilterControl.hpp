#ifndef COLORFILTERCONTROL_H
#define COLORFILTERCONTROL_H

#include "../baseComponent/panelControlBase.h"
#include "baseComponent/selectColorButton.h"
#include "baseComponent/selectButton.h"
#include "baseComponent/customPushButton.h"
#include "baseComponent/gridBackground.h"
#include "colorFilterControl_datatypes.h"
#include <QLabel>

enum ColorFilterMode
{
    COLOR_FILTER_MODE_TB,
    COLOR_FILTER_MODE_CUSTOM,
    COLOR_FILTER_MODE_HISTORY
};

struct ColorFilterButton
{
    QString text;
    QColor color;
    bool operator==(const ColorFilterButton &rhs) const
    {
        return text == rhs.text && color == rhs.color;
    }
};

class ColorFilterControl : public PanelControlBase
{
    Q_OBJECT
    Q_PROPERTY(int currentTBTabPage READ currentTBTabPage WRITE setCurrentTBTabPage NOTIFY currentTBTabPageChanged)
    Q_PROPERTY(int currentCustomTabPage READ currentCustomTabPage WRITE setCurrentCustomTabPage NOTIFY currentCustomTabPageChanged)
    Q_PROPERTY(int currentHistoryPage READ currentHistoryPage WRITE setCurrentHistoryPage NOTIFY currentHistoryPageChanged)
    Q_PROPERTY(ColorFilterMode mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(ColorFilterButton currentTBTabButtonCheck READ currentTBTabButtonCheck WRITE setCurrentTBTabButtonCheck NOTIFY currentTBTabButtonCheckChanged)
    Q_PROPERTY(ColorFilterButton currentCustomTabButtonCheck READ currentCustomTabButtonCheck WRITE setCurrentCustomTabButtonCheck NOTIFY currentCustomTabButtonCheckChanged)
    Q_PROPERTY(ColorFilterButton currentHistoryTabButtonCheck READ currentHistoryTabButtonCheck WRITE setCurrentHistoryTabButtonCheck NOTIFY currentHistoryTabButtonCheckChanged)
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

    ColorFilterMode mode() const;
    void setMode(ColorFilterMode newMode);

    int maxTBTabPages() const;
    int maxCustomTabPages() const;
    int maxHistoryPages() const;

    void onTBTabButtonChecked(const int index, QObject* sender);
    void onCustomTabButtonChecked(const int index, QObject* sender);
    void onHistoryButtonChecked(const int index, QObject* sender);

    const ColorFilterButton currentTBTabButtonCheck() const;
    void setCurrentTBTabButtonCheck(const ColorFilterButton& newCurrentTBTabButtonCheck);

    const ColorFilterButton currentCustomTabButtonCheck() const;
    void setCurrentCustomTabButtonCheck(const ColorFilterButton& newCurrentCustomTabButtonCheck);

    const ColorFilterButton currentHistoryTabButtonCheck() const;
    void setCurrentHistoryTabButtonCheck(const ColorFilterButton& newCurrentHistoryTabButtonCheck);

signals:
    void currentTBTabPageChanged();
    void currentCustomTabPageChanged();
    void currentHistoryPageChanged();
    void modeChanged();
    void currentTBTabButtonCheckChanged();
    void currentCustomTabButtonCheckChanged();
    void currentHistoryTabButtonCheckChanged();

protected:
    virtual void addButtonToHistory(QSharedPointer<SelectColorButton>& button);
    void onModeChanged();
    void updateTBTabPage();
    void updateCustomTabPage();
    void updateHistoryPage();

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

    int m_currentTBTabPage;
    int m_currentCustomTabPage;
    int m_currentHistoryPage;
    ColorFilterMode m_mode;
    ColorFilterMode m_previous_tab;
    ColorFilterButton m_currentTBTabButtonCheck;
    ColorFilterButton m_currentCustomTabButtonCheck;
    ColorFilterButton m_currentHistoryTabButtonCheck;
};

#endif // COLORFILTERCONTROL_H
