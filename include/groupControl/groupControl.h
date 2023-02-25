//--------------------------------------------------------------------------
// [ ファイル名 ] : groupControl.h
// [ 概      要 ] : グループコントロール垂直ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef GROUPLIBCONTROL_H
#define GROUPLIBCONTROL_H
#include "baseComponent/panelControlBase.h"
#include "groupControl_datatypes.h"
#include "baseComponent/titleSelectButton.h"
#include "baseComponent/customPushButton.h"
#include "baseComponent/gridBackground.h"

struct GroupControlButton
{
    QString text;
    QString title;
    bool operator==( const GroupControlButton &rhs ) const
    {
        return text == rhs.text && title == rhs.title;
    }
};

class GroupControl : public PanelControlBase
{
    Q_OBJECT
    Q_PROPERTY( int CurrentGroupPage READ CurrentGroupPage WRITE SetCurrentGroupPage NOTIFY CurrentGroupPageChanged )
    Q_PROPERTY( int CurrentHistoryPage READ CurrentHistoryPage WRITE SetCurrentHistoryPage NOTIFY CurrentHistoryPageChanged )
    Q_PROPERTY( GroupControlButton CurrentGroupButton READ CurrentGroupButton WRITE SetCurrentGroupButton NOTIFY CurrentGroupButtonChanged )
    Q_PROPERTY( GroupControlButton CurrentHistoryButton READ CurrentHistoryButton WRITE SetCurrentHistoryButton NOTIFY CurrentHistoryButtonChanged )
    Q_PROPERTY( QString CurrentFooterButton READ CurrentFooterButton WRITE SetCurrentFooterButton NOTIFY CurrentFooterButtonChanged )

public:
    explicit GroupControl( QWidget *parent = nullptr );
    virtual void SetDispParamData( GROUP_DISP_PARAM *param );

    int CurrentGroupPage() const;
    void SetCurrentGroupPage( int page );

    int CurrentHistoryPage() const;
    void SetCurrentHistoryPage( int page );

    const GroupControlButton &CurrentGroupButton() const;
    void SetCurrentGroupButton( const GroupControlButton &button );

    const GroupControlButton &CurrentHistoryButton() const;
    void SetCurrentHistoryButton( const GroupControlButton &button );

    const QString &CurrentFooterButton() const;
    void SetCurrentFooterButton( const QString &button );

signals:
    void CurrentGroupPageChanged();
    void CurrentHistoryPageChanged();
    void CurrentGroupButtonChanged();
    void CurrentHistoryButtonChanged();
    void ReturnButtonClicked();
    void CurrentFooterButtonChanged();

protected:
    int ButtonsPerPage() const;
    virtual void UpdateGroupPage();
    virtual void UpdateHistoryPage();

    int MaxGroupPages() const;
    int MaxHistoryPages() const;

    virtual void AddButtonToHistory( QSharedPointer<TitleSelectButton> &button );

protected slots:
    void OnGroupButtonClicked();
    void OnHistoryButtonClicked();

    void OnTitleButonClicked( const bool check );
    void OnRegisterButonClicked( const bool check );
    void OnDeleteButonClicked( const bool check );

protected:
    GridBackground m_grid;
    QLabel m_title_label;
    ToggleButton m_history_button;
    CustomPushButton m_up_button;
    CustomPushButton m_down_button;
    CustomPushButton m_back_button;
    QLabel m_setting_label;
    SelectButton m_title_button;
    CustomPushButton m_empty_button;
    SelectButton m_register_button;
    SelectButton m_delete_button;
    QVector<QSharedPointer<TitleSelectButton>> m_group_buttons;
    QVector<QSharedPointer<TitleSelectButton>> m_history_buttons;

    int m_current_group_page;
    int m_current_history_page;

    QSize m_buttons_grid_size;
    GroupControlButton m_current_group_button;
    GroupControlButton m_current_history_button;
    QString m_current_footer_button;
};


#endif // GROUPLIBCONTROL_H
