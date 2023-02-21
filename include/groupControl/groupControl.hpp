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
    bool operator==(const GroupControlButton &rhs) const
    {
        return text == rhs.text && title == rhs.title;
    }
};

class GroupControl : public PanelControlBase
{
    Q_OBJECT
    Q_PROPERTY(int currentGroupPage READ currentGroupPage WRITE setCurrentGroupPage NOTIFY currentGroupPageChanged)
    Q_PROPERTY(int currentHistoryPage READ currentHistoryPage WRITE setCurrentHistoryPage NOTIFY currentHistoryPageChanged)
    Q_PROPERTY(GroupControlButton CurrentGroupButton READ CurrentGroupButton WRITE SetCurrentGroupButton NOTIFY CurrentGroupButtonChanged)
    Q_PROPERTY(GroupControlButton CurrentHistoryButton READ CurrentHistoryButton WRITE SetCurrentHistoryButton NOTIFY CurrentHistoryButtonChanged)
    Q_PROPERTY(QString CurrentFooterButton READ CurrentFooterButton WRITE SetCurrentFooterButton NOTIFY CurrentFooterButtonChanged)

public:
    explicit GroupControl(QWidget* parent = nullptr);
    virtual void SetDispParamData(GROUP_DISP_PARAM *param);

    int currentGroupPage() const;
    void setCurrentGroupPage(int newCurrentGroupPage);

    int currentHistoryPage() const;
    void setCurrentHistoryPage(int newCurrentHistoryPage);

    const GroupControlButton &CurrentGroupButton() const;
    void SetCurrentGroupButton(const GroupControlButton &newCurrentGroupButton);

    const GroupControlButton &CurrentHistoryButton() const;
    void SetCurrentHistoryButton(const GroupControlButton &newCurrentHistoryButton);

    const QString &CurrentFooterButton() const;
    void SetCurrentFooterButton(const QString &newCurrentFooterButton);

signals:
    void currentGroupPageChanged();
    void currentHistoryPageChanged();
    void CurrentGroupButtonChanged();
    void CurrentHistoryButtonChanged();
    void ReturnButtonClicked();

    void CurrentFooterButtonChanged();

protected:
    int buttonsPerPage() const;
    virtual void updateGroupPage();
    virtual void updateHistoryPage();

    int maxGroupPages() const;
    int maxHistoryPages() const;

    virtual void addButtonToHistory(QSharedPointer<TitleSelectButton>& button);

protected slots:
    void onGroupButtonClicked();
    void onHistoryButtonClicked();

    void onTitleButonClicked(const bool check);
    void onRegisterButonClicked(const bool check);
    void onDeleteButonClicked(const bool check);

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

    int m_currentGroupPage;
    int m_currentHistoryPage;

    QSize m_buttons_grid_size;
    GroupControlButton m_CurrentGroupButton;
    GroupControlButton m_CurrentHistoryButton;
    QString m_CurrentFooterButton;
};


#endif // GROUPLIBCONTROL_H
