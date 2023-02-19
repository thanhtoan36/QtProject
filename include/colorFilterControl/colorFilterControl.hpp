#ifndef COLORFILTERCONTROL_H
#define COLORFILTERCONTROL_H

#include "../baseComponent/panelControlBase.h"
#include "baseComponent/selectButton.h"
#include "baseComponent/customPushButton.h"
#include "baseComponent/gridBackground.h"
#include "colorFilterControl_datatypes.h"
#include <QLabel>

enum ColorFilterDisplayMode
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
    Q_PROPERTY(int currentHeaderButtonsPage READ currentHeaderButtonsPage WRITE setCurrentHeaderButtonsPage NOTIFY currentHeaderButtonsPageChanged)
    Q_PROPERTY(int currentTBTabPage READ currentTBTabPage WRITE setCurrentTBTabPage NOTIFY currentTBTabPageChanged)
    Q_PROPERTY(int currentCustomTabPage READ currentCustomTabPage WRITE setCurrentCustomTabPage NOTIFY currentCustomTabPageChanged)
    Q_PROPERTY(int currentHistoryPage READ currentHistoryPage WRITE setCurrentHistoryPage NOTIFY currentHistoryPageChanged)
    Q_PROPERTY(ColorFilterDisplayMode mode READ mode WRITE setMode NOTIFY modeChanged)
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

    ColorFilterDisplayMode mode() const;
    void setMode(ColorFilterDisplayMode newMode);

    int maxTBTabPages() const;
    int maxCustomTabPages() const;
    int maxHistoryPages() const;

    void onTBTabButtonClicked();
    void onCustomTabButtonClicked();
    void onHistoryButtonClicked();

    int currentHeaderButtonsPage() const;
    void setCurrentHeaderButtonsPage(int newCurrentHeaderButtonsPage);

signals:
    void currentTBTabPageChanged();
    void currentCustomTabPageChanged();
    void currentHistoryPageChanged();
    void modeChanged();
    void currentTBTabButtonCheckChanged();
    void currentCustomTabButtonCheckChanged();
    void currentHistoryTabButtonCheckChanged();
    void currentHeaderButtonsPageChanged();

protected:
    virtual void addButtonToHistory(QSharedPointer<SelectButton> button);
    void onModeChanged();
    void updateTBTabPage();
    void updateCustomTabPage();
    void updateHistoryPage();

    void addHeaderButton(ColorFilterDisplayMode mode, const QString &text);
    QVector<QSharedPointer<SelectButton> > headerButtons() const;
    void setupHeaderTabButtons();

protected slots:
    void onDisplayTabButtonClicked();

protected:
    struct DisplayTabButton
    {
        ColorFilterDisplayMode mode;
        QSharedPointer<SelectButton> button;
    };

    QVector<DisplayTabButton> m_header_buttons;
    int m_header_buttons_per_page;

    GridBackground m_grid;
    QLabel m_title_label;
    CustomPushButton m_button_next_header_buttons_page;
    CustomPushButton m_button_previous_header_buttons_page;
    ToggleButton m_history_button;
    CustomPushButton m_button_next_filter_buttons_page;
    CustomPushButton m_button_previous_filter_buttons_page;
    CustomPushButton m_back_button;
    QLabel m_setting_label;
    SelectButton m_title_button;
    CustomPushButton m_empty_button;
    SelectButton m_register_button;
    SelectButton m_delete_button;

    QVector<QWidget*> m_children_tb_tab;
    QVector<QWidget*> m_children_custom_tab;
    QVector<QWidget*> m_children_history;

    QVector<QSharedPointer<SelectButton>> m_tb_tab_buttons;
    QVector<QSharedPointer<SelectButton>> m_custom_tab_buttons;
    QVector<QSharedPointer<SelectButton>> m_history_buttons;

    uint32_t m_current_scroll_step = 0;

    int m_currentTBTabPage;
    int m_currentCustomTabPage;
    int m_currentHistoryPage;

    ColorFilterDisplayMode m_mode;
    ColorFilterDisplayMode m_previous_tab;
private:
    int m_currentHeaderButtonsPage;
};

#endif // COLORFILTERCONTROL_H
