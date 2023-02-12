#ifndef GROUPLIBCONTROL_H
#define GROUPLIBCONTROL_H
#include "baseComponent/panelControlBase.h"
#include "groupControl_define.hpp"
#include "groupControl_datatypes.h"
#include "baseComponent/titleSelectButton.h"
#include "baseComponent/customPushButton.h"
#include "baseComponent/gridBackground.h"

class GroupControl : public PanelControlBase
{
    Q_OBJECT
    Q_PROPERTY(int currentGroupPage READ currentGroupPage WRITE setCurrentGroupPage NOTIFY currentGroupPageChanged)
    Q_PROPERTY(int currentHistoryPage READ currentHistoryPage WRITE setCurrentHistoryPage NOTIFY currentHistoryPageChanged)

public:
    explicit GroupControl(QWidget* parent = nullptr);
    void SetDispParamData(GROUP_DISP_PARAM *param);

    int currentGroupPage() const;
    void setCurrentGroupPage(int newCurrentGroupPage);

    int currentHistoryPage() const;
    void setCurrentHistoryPage(int newCurrentHistoryPage);



    void onButtonGroupCheck(const uint32_t index, QObject* sender);
    void onButtonHistoryCheck(const uint32_t index, QObject* sender);

signals:
    void currentGroupPageChanged();

    void currentHistoryPageChanged();

protected:
    virtual void SetupUiComponents() override;
    virtual void SetupUiEvents() override;

    virtual void updateGroupPage();
    virtual void updateHistoryPage();

    virtual int maxGroupPages() const;
    virtual int maxHistoryPages() const;

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
};


#endif // GROUPLIBCONTROL_H
