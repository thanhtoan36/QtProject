//--------------------------------------------------------------------------
// [ ファイル名 ] : libraryControl.h
// [ 概      要 ] : ライブラリコントロール垂直ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef LIBRARYCONTROL_HPP
#define LIBRARYCONTROL_HPP

#include "baseComponent/panelControlBase.h"
#include "libraryControl_datatypes.h"
#include "baseComponent/titleSelectButton.h"
#include "baseComponent/customPushButton.h"
#include "baseComponent/gridBackground.h"
#include <QLabel>

struct LibraryControlButton
{
    QString text;
    QString title;
    bool operator==( const LibraryControlButton &rhs ) const
    {
        return text == rhs.text && title == rhs.title;
    }
};

class LibraryControl : public PanelControlBase
{
    Q_OBJECT
    Q_PROPERTY( int CurrentGroupPage READ CurrentGroupPage WRITE SetCurrentGroupPage NOTIFY CurrentGroupPageChanged )
    Q_PROPERTY( int CurrentHistoryPage READ CurrentHistoryPage WRITE SetCurrentHistoryPage NOTIFY CurrentHistoryPageChanged )
    Q_PROPERTY( QString SelectedGroupMode READ SelectedGroupMode WRITE SetSelectedGroupMode NOTIFY SelectedGroupModeChanged )
    Q_PROPERTY( QString SelectedHistoryMode READ SelectedHistoryMode WRITE SetSelectedHistoryMode NOTIFY SelectedHistoryModeChanged )
    Q_PROPERTY( QString SelectedModeButton READ SelectedModeButton WRITE SetSelectedModeButton NOTIFY SelectedModeButtonChanged )
    Q_PROPERTY( LibraryControlButton SelectedLibraryButton READ SelectedLibraryButton WRITE SetSelectedLibraryButton NOTIFY SelectedLibraryButtonChanged )
    Q_PROPERTY( QString SelectedHistoryModeButton READ SelectedHistoryModeButton WRITE SetSelectedHistoryModeButton NOTIFY SelectedHistoryModeButtonChanged )
    Q_PROPERTY( LibraryControlButton SelectedHistoryButton READ SelectedHistoryButton WRITE SetSelectedHistoryButton NOTIFY SelectedHistoryButtonChanged )
    Q_PROPERTY( QString SelectedFooterButton READ SelectedFooterButton WRITE SetSelectedFooterButton NOTIFY SelectedFooterButtonChanged )

public:
    struct LibraryButton
    {
        QString mode;
        QSharedPointer<TitleSelectButton> widget;
    };

    explicit LibraryControl( QWidget *parent = nullptr );
    virtual void SetDispParamData( LIBRARY_DISP_PARAM *param );

    QString SelectedGroupMode() const;
    QString SelectedHistoryMode() const;

    const LibraryControlButton &SelectedLibraryButton() const;
    const LibraryControlButton &SelectedHistoryButton() const;
    const QString &SelectedFooterButton() const;
    const QString &SelectedModeButton() const;
    const QString &SelectedHistoryModeButton() const;

signals:
    void CurrentGroupPageChanged();
    void CurrentHistoryPageChanged();
    void SelectedGroupModeChanged();
    void SelectedHistoryModeChanged();
    void SelectedModeButtonChanged();
    void SelectedLibraryButtonChanged();
    void SelectedHistoryModeButtonChanged();
    void SelectedHistoryButtonChanged();
    void SelectedFooterButtonChanged();
    void ReturnButtonClicked();

protected:
    void SetSelectedGroupMode( const QString &mode );
    void SetSelectedHistoryMode( const QString &mode );
    void SetSelectedLibraryButton( const LibraryControlButton &button );
    void SetSelectedHistoryButton( const LibraryControlButton &button );
    void SetSelectedFooterButton( const QString &button );
    void SetSelectedModeButton( const QString &button );
    void SetSelectedHistoryModeButton( const QString &button );

    int CurrentGroupPage() const;
    void SetCurrentGroupPage( int page );

    int CurrentHistoryPage() const;
    void SetCurrentHistoryPage( int page );

    QPoint LibraryStartPoint() const;
    void SetLibraryStartPoint( QPoint point );

    QPoint ModeStartPoint() const;
    void SetModeStartPoint( QPoint point );

    int MaxGroupPages() const;
    int MaxHistoryPages() const;

    int ModeButtonsPerPage() const;
    int LibraryButtonsPerPage() const;

    void RefilterGroupButtonsByMode();
    void RefilterHistoryButtonsByMode();

    static QVector<LibraryButton> Filter( const QVector<LibraryButton> &buttons, const QString &mode = QString() );
    static QVector<QSharedPointer<TitleSelectButton>> WidgetList( const QVector<LibraryButton> &buttons );

    void UpdateGroupTab();
    void UpdateHistoryTab();

protected:
    virtual void AddButtonToHistory( const LibraryButton &button );

    void OnButtonTitleClicked();
    void OnButtonRegisterClicked();
    void OnButtonDeleteClicked();

protected slots:
    void OnGroupModeButtonClicked();
    void OnHistoryModeButtonClicked();
    void OnGroupLibButtonClicked();
    void OnHistoryLibButtonClicked();

protected:
    GridBackground m_grid;
    QLabel m_title_label;
    ToggleButton m_history_button;
    CustomPushButton m_up_button;
    CustomButtonBase m_down_button;
    CustomPushButton m_return_button;
    QLabel m_setting_label;
    SelectButton m_title_button;
    CustomPushButton m_empty_button;
    SelectButton m_register_button;
    SelectButton m_delete_button;

    QVector<QSharedPointer<SelectButton>> m_group_mode_buttons;
    QVector<QSharedPointer<SelectButton>> m_history_mode_buttons;
    QVector<LibraryButton> m_group_lib_buttons;
    QVector<LibraryButton> m_history_lib_buttons;
    QVector<QSharedPointer<TitleSelectButton>> m_current_group_lib_buttons;
    QVector<QSharedPointer<TitleSelectButton>> m_current_history_lib_buttons;

    QPoint m_library_start_point;
    QPoint m_mode_start_point;

    QSize m_mode_buttons_grid_size;
    QSize m_lib_buttons_grid_size;

private:
    int m_current_group_page;
    int m_current_history_page;
    QString m_selected_group_mode;
    QString m_selected_history_mode;
    LibraryControlButton m_selected_library_button;
    LibraryControlButton m_selected_historybutton;
    QString m_selected_footer_button;
    QString m_selected_mode_button;
    QString m_selected_history_mode_button;
};

#endif // LIBRARYCONTROL_HPP
