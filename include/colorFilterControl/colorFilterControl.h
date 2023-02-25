//--------------------------------------------------------------------------
// [ ファイル名 ] : colorFilterControl.h
// [ 概      要 ] : ColorFilterControl vertical widget
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
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
    bool operator==( const ColorFilterButton &rhs ) const
    {
        return text == rhs.text && color == rhs.color;
    }
};

class ColorFilterControl : public PanelControlBase
{
    Q_OBJECT
    Q_PROPERTY( int CurrentHeaderButtonsPage READ CurrentHeaderButtonsPage WRITE SetCurrentHeaderButtonsPage NOTIFY CurrentHeaderButtonsPageChanged )
    Q_PROPERTY( int CurrentTBTabPage READ CurrentTBTabPage WRITE SetCurrentTBTabPage NOTIFY CurrentTBTabPageChanged )
    Q_PROPERTY( int CurrentCustomTabPage READ CurrentCustomTabPage WRITE SetCurrentCustomTabPage NOTIFY CurrentCustomTabPageChanged )
    Q_PROPERTY( int CurrentHistoryPage READ CurrentHistoryPage WRITE SetCurrentHistoryPage NOTIFY CurrentHistoryPageChanged )
    Q_PROPERTY( ColorFilterDisplayMode Mode READ Mode WRITE SetMode NOTIFY ModeChanged )

    Q_PROPERTY( ColorFilterButton SelectedTbButton READ SelectedTbButton NOTIFY SelectedTbButtonChanged )
    Q_PROPERTY( ColorFilterButton SelectedCustomButton READ SelectedCustomButton NOTIFY SelectedCustomButtonChanged )
    Q_PROPERTY( ColorFilterButton SelectedHistoryButton READ SelectedHistoryButton NOTIFY SelectedHistoryButtonChanged )

    Q_PROPERTY( QString SelectedFooterButton READ SelectedFooterButton WRITE SetSelectedFooterButton NOTIFY SelectedFooterButtonChanged )

public:

    explicit ColorFilterControl( QWidget *parent = nullptr );

    virtual void setDispParamData( COLOR_FILTER_DISP_PARAM *param );

    ColorFilterDisplayMode Mode() const;
    void SetMode( ColorFilterDisplayMode value );

    const ColorFilterButton SelectedTbButton() const;
    const ColorFilterButton SelectedCustomButton() const;
    const ColorFilterButton SelectedHistoryButton() const;
    const QString &SelectedFooterButton() const;

signals:
    void CurrentTBTabPageChanged();
    void CurrentCustomTabPageChanged();
    void CurrentHistoryPageChanged();

    void ModeChanged();

    void CurrentHeaderButtonsPageChanged();

    void SelectedTbButtonChanged();
    void SelectedCustomButtonChanged();
    void SelectedHistoryButtonChanged();

    void ReturnButtonClicked();
    void NextButtonClicked();
    void PrevButtonClicked();

    void SelectedFooterButtonChanged();

protected:
    int CurrentTBTabPage() const;
    void SetCurrentTBTabPage( int value );

    int CurrentCustomTabPage() const;
    void SetCurrentCustomTabPage( int value );

    int CurrentHistoryPage() const;
    void SetCurrentHistoryPage( int value );

    void SetSelectedFooterButton( const QString &value );

    void ScrollUp();
    void ScrollDown();

    virtual void AddButtonToHistory( QSharedPointer<SelectButton> button );

    void OnModeChanged();
    void UpdateTBTabPage();
    void UpdateCustomTabPage();
    void UpdateHistoryPage();

    void AddHeaderButton( ColorFilterDisplayMode mode, const QString &text );
    QVector<QSharedPointer<SelectButton> > HeaderButtons() const;
    void SetupHeaderTabButtons();

    int MaxTBTabPages() const;
    int MaxCustomTabPages() const;
    int MaxHistoryPages() const;

    void OnTBTabButtonClicked();
    void OnCustomTabButtonClicked();
    void OnHistoryButtonClicked();

    int CurrentHeaderButtonsPage() const;
    void SetCurrentHeaderButtonsPage( int value );

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

    QVector<QWidget *> m_children_tb_tab;
    QVector<QWidget *> m_children_custom_tab;
    QVector<QWidget *> m_children_history;

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
    QString m_current_footer_button_active = "";
};

#endif // COLORFILTERCONTROL_H
