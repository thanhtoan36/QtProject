#ifndef COLORFILTERCONTROL_H
#define COLORFILTERCONTROL_H

#include "baseComponent/panelControlBase.h"
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
    Q_PROPERTY(int CurrentHeaderButtonsPage READ CurrentHeaderButtonsPage WRITE SetCurrentHeaderButtonsPage NOTIFY CurrentHeaderButtonsPageChanged)
    Q_PROPERTY(int CurrentTBTabPage READ CurrentTBTabPage WRITE SetCurrentTBTabPage NOTIFY CurrentTBTabPageChanged)
    Q_PROPERTY(int CurrentCustomTabPage READ CurrentCustomTabPage WRITE SetCurrentCustomTabPage NOTIFY CurrentCustomTabPageChanged)
    Q_PROPERTY(int CurrentHistoryPage READ CurrentHistoryPage WRITE SetCurrentHistoryPage NOTIFY CurrentHistoryPageChanged)
    Q_PROPERTY(ColorFilterDisplayMode Mode READ Mode WRITE SetMode NOTIFY ModeChanged)

    Q_PROPERTY(ColorFilterButton CurrentTBTabButtonActive READ CurrentTBTabButtonActive WRITE SetCurrentTBTabButtonActive NOTIFY CurrentTBTabButtonActiveChanged)
    Q_PROPERTY(ColorFilterButton CurrentCustomTabButtonActive READ CurrentCustomTabButtonActive WRITE SetCurrentCustomTabButtonActive NOTIFY CurrentCustomTabButtonActiveChanged)
    Q_PROPERTY(ColorFilterButton CurrentHistoryButtonActive READ CurrentHistoryButtonActive WRITE SetCurrentHistoryButtonActive NOTIFY CurrentHistoryButtonActiveChanged)
public:

    explicit ColorFilterControl(QWidget* parent = nullptr);

    virtual void setDispParamData( COLOR_FILTER_DISP_PARAM *param);

    int CurrentTBTabPage() const;
    void SetCurrentTBTabPage(int newCurrentTab1Page);

    int CurrentCustomTabPage() const;
    void SetCurrentCustomTabPage(int newCurrentTab2Page);

    int CurrentHistoryPage() const;
    void SetCurrentHistoryPage(int newCurrentHistoryPage);

    ColorFilterDisplayMode Mode() const;
    void SetMode(ColorFilterDisplayMode newMode);

    const ColorFilterButton &CurrentTBTabButtonActive() const;
    void SetCurrentTBTabButtonActive(const ColorFilterButton &newCurrentTBTabButtonActive);

    const ColorFilterButton &CurrentCustomTabButtonActive() const;
    void SetCurrentCustomTabButtonActive(const ColorFilterButton &newCurrentCustomTabButtonActive);

    const ColorFilterButton &CurrentHistoryButtonActive() const;
    void SetCurrentHistoryButtonActive(const ColorFilterButton &newCurrentHistoryButtonActive);

    const QString &CurrentFooterButtonActive() const;
    void SetCurrentFooterButtonActive(const QString &newCurrentFooterButtonActive);

signals:
    void CurrentTBTabPageChanged();
    void CurrentCustomTabPageChanged();
    void CurrentHistoryPageChanged();
    void ModeChanged();
    void CurrentHeaderButtonsPageChanged();
    void CurrentTBTabButtonActiveChanged();
    void CurrentCustomTabButtonActiveChanged();
    void CurrentHistoryButtonActiveChanged();

    void ReturnButtonClicked();
    void NextButtonClicked();
    void PrevButtonClicked();

protected:
    void ScrollUp();
    void ScrollDown();

    virtual void AddButtonToHistory(QSharedPointer<SelectButton> button);

    void OnModeChanged();
    void UpdateTBTabPage();
    void UpdateCustomTabPage();
    void UpdateHistoryPage();

    void AddHeaderButton(ColorFilterDisplayMode mode, const QString &text);
    QVector<QSharedPointer<SelectButton> > HeaderButtons() const;
    void SetupHeaderTabButtons();

    int MaxTBTabPages() const;
    int MaxCustomTabPages() const;
    int MaxHistoryPages() const;

    void OnTBTabButtonClicked();
    void OnCustomTabButtonClicked();
    void OnHistoryButtonClicked();

    int CurrentHeaderButtonsPage() const;
    void SetCurrentHeaderButtonsPage(int newCurrentHeaderButtonsPage);

protected slots:
    void OnDisplayTabButtonClicked();

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

    int m_current_tb_tab_page;
    int m_current_custom_tab_page;
    int m_current_history_page;

    ColorFilterDisplayMode m_mode;
    ColorFilterDisplayMode m_previous_tab;

private:
    int m_current_header_buttons_page;
    ColorFilterButton m_current_tb_tab_button_active;
    ColorFilterButton m_current_custom_tab_button_active;
    ColorFilterButton m_current_history_button_active;
    QString m_current_footer_button_active = "";
};

#endif // COLORFILTERCONTROL_H
