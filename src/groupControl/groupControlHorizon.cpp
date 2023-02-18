#include "groupControl/groupControlHorizon.h"
#include "utility.h"

#define BASE_BUTTON_WIDTH GC_HORIZON_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT GC_HORIZON_BUTTON1_GEOMETRY.height()

#define COLUMN 4
#define ROW 10
#define PAGE_SIZE (COLUMN*ROW)

GroupControlHorizon::GroupControlHorizon(QWidget *parent) : GroupControl(parent)
{
    setFixedSize(GC_HORIZON_SCREEN_SIZE);
    m_title_label.setObjectName("title_label_with_border");
}

void GroupControlHorizon::SetDispParamDataHorizon(GROUP_DISP_PARAM *param)
{
    Q_ASSERT(param);
    m_group_buttons.clear();
    m_history_buttons.clear();
    setCurrentGroupPage(0);
    for (int i = 0; i< param->group.count;i++)
    {
        auto button =  MakeSharedQObject<TitleSelectButton>(this);
        button->setFixedSize(GC_HORIZON_MODE_SIZE);
        button->setTitle(param->group.group_param[i].title);
        button->setText(param->group.group_param[i].group_no);
        button->setChecked(param->group.group_param[i].select);
        connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
            onButtonGroupCheck(i,sender());
        });
        m_group_buttons.push_back(button);
    }
    placeChildrenIntoPanel(m_group_buttons, GC_HORIZON_MODE_SIZE, GC_HORIZON_MODE_PLACEMENT_START, QSize(ROW, COLUMN));
    updateGroupPage();
    m_up_button.setEnabled(currentGroupPage() > 0);
    m_down_button.setEnabled(currentGroupPage() < maxGroupPages() - 1);
    for (int i = 0; i< param->history.count;i++)
    {
        auto button =  MakeSharedQObject<TitleSelectButton>(this);
        button->setFixedSize(GC_HORIZON_MODE_SIZE);
        button->setTitle(param->history.group_param[i].title);
        button->setText(param->history.group_param[i].group_no);
        button->setChecked(param->history.group_param[i].select);
        button->setVisible(false);
        connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
            onButtonHistoryCheck(i,sender());
        });
        m_history_buttons.push_back(button);
    }
    placeChildrenIntoPanel(m_history_buttons, GC_HORIZON_MODE_SIZE, GC_HORIZON_MODE_PLACEMENT_START, QSize(ROW, COLUMN));
}

void GroupControlHorizon::SetupUiComponents()
{
    m_grid.setGridSize(QSize(11, 5));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 34);

    m_title_label.setGeometry(GC_HORIZON_TITLE_GEOMETRY);
    m_title_label.setText("グループ");

    m_history_button.setGeometry(GC_HORIZON_HISTORY_GEOMETRY);
    m_history_button.setText("最近使った\nもの");

    m_up_button.setGeometry(GC_HORIZON_UP_GEOMETRY);
    m_up_button.setText("▲");

    m_down_button.setGeometry(GC_HORIZON_DOWN_GEOMETRY);
    m_down_button.setText("▼");

    m_back_button.setGeometry(GC_HORIZON_RETURN_GEOMETRY);
    m_back_button.setText("戻す");
    m_setting_label.setVisible(false);

    m_title_button.setGeometry(GC_HORIZON_TITLE_BUTTON_GEOMETRY);
    m_title_button.setText("タイトル");
    m_empty_button.setVisible(false);

    m_register_button.setGeometry(GC_HORIZON_REGISTER_GEOMETRY);
    m_register_button.setText("登録");

    m_delete_button.setGeometry(GC_HORIZON_DELETE_GEOMETRY);
    m_delete_button.setText("削除");
}

void GroupControlHorizon::updateGroupPage()
{
    updateChildrenVisibility(m_group_buttons,currentGroupPage(),PAGE_SIZE);
}

void GroupControlHorizon::updateHistoryPage()
{
    updateChildrenVisibility(m_history_buttons,currentHistoryPage(),PAGE_SIZE);
}

int GroupControlHorizon::maxGroupPages() const
{
    return calulateNumberOfPages(m_group_buttons.length(), PAGE_SIZE);
}

int GroupControlHorizon::maxHistoryPages() const
{
    return calulateNumberOfPages(m_history_buttons.length(), PAGE_SIZE);
}
