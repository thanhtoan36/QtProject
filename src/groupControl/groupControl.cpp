#include "groupControl/groupControl.hpp"
#include "groupControl/groupControl_define.hpp"
#include "utility.h"

#define BASE_BUTTON_WIDTH GC_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT GC_BUTTON1_GEOMETRY.height()

#define COLUMN 5
#define ROW 4
#define PAGE_SIZE (COLUMN*ROW)

GroupControl::GroupControl(QWidget *parent) : PanelControlBase(parent),
    m_grid(this),
    m_title_label(this),
    m_history_button(this),
    m_up_button(this),
    m_down_button(this),
    m_back_button(this),
    m_setting_label(this),
    m_title_button(this),
    m_empty_button(this),
    m_register_button(this),
    m_delete_button(this)
{
    setFixedSize(GC_SCREEN_SIZE);
    setCurrentGroupPage(0);
    setCurrentHistoryPage(0);
    m_back_button.setTextColor(Qt::yellow);
}

void GroupControl::SetDispParamData(GROUP_DISP_PARAM *param)
{
    Q_ASSERT(param);
    m_group_buttons.clear();
    m_history_buttons.clear();
    for (int i = 0; i< param->group.count;i++)
    {
        auto button =  MakeSharedQObject<TitleSelectButton>(this);
        button->setFixedSize(GC_MODE_SIZE);
        button->setTitle(param->group.group_param[i].title);
        button->setText(param->group.group_param[i].group_no);
        button->setChecked(param->group.group_param[i].select);
        connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
            onButtonGroupCheck(i,sender());
        });
        m_group_buttons.push_back(button);
    }
    placeChildrenIntoPanel(m_group_buttons, GC_MODE_SIZE, GC_MODE_PLACEMENT_START, ROW, COLUMN);
    updateGroupPage();
    m_up_button.setEnabled(currentGroupPage() > 0);
    m_down_button.setEnabled(currentGroupPage() < maxGroupPages() - 1);
    for (int i = 0; i< param->history.count;i++)
    {
        auto button =  MakeSharedQObject<TitleSelectButton>(this);
        button->setFixedSize(GC_MODE_SIZE);
        button->setTitle(param->history.group_param[i].title);
        button->setText(param->history.group_param[i].group_no);
        button->setChecked(param->history.group_param[i].select);
        button->setVisible(false);
        connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
            onButtonHistoryCheck(i,sender());
        });
        m_history_buttons.push_back(button);
    }
    placeChildrenIntoPanel(m_history_buttons, GC_MODE_SIZE, GC_MODE_PLACEMENT_START,ROW, COLUMN);
}

void GroupControl::SetupUiComponents()
{
    m_grid.setGridSize(QSize(4, 6));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 32);

    m_title_label.setGeometry(GC_TITLE_GEOMETRY);
    m_title_label.setObjectName("title_label");
    m_title_label.setText("グループ");

    m_history_button.setGeometry(GC_HISTORY_GEOMETRY);
    m_history_button.setText("最近使った\nもの");

    m_up_button.setGeometry(GC_UP_GEOMETRY);
    m_up_button.setText("▲");

    m_down_button.setGeometry(GC_DOWN_GEOMETRY);
    m_down_button.setText("▼");

    m_back_button.setGeometry(GC_RETURN_GEOMETRY);
    m_back_button.setText("戻す");

    m_setting_label.setGeometry(GC_SETTING_GEOMETRY);
    m_setting_label.setText("設定");

    m_title_button.setGeometry(GC_TITLE_BUTTON_GEOMETRY);
    m_title_button.setText("タイトル");

    m_empty_button.setGeometry(GC_EMPTY_GEOMETRY);
    m_empty_button.setText("");

    m_register_button.setGeometry(GC_REGISTER_BUTTON_GEOMETRY);
    m_register_button.setText("登録");

    m_delete_button.setGeometry(GC_DELETE_BUTTON_GEOMETRY);
    m_delete_button.setText("削除");
}

void GroupControl::SetupUiEvents()
{
    connect(&m_up_button, &QPushButton::clicked, this, [&](){
        qDebug() << m_history_button.isChecked();
        if (m_history_button.isChecked())
        {
            setCurrentHistoryPage(currentHistoryPage()-1);
        }
        else
        {
            setCurrentGroupPage(currentGroupPage()-1);
        }
    });
    connect(&m_down_button, &QPushButton::clicked, this, [&](){
        qDebug() << m_history_button.isChecked();
        if (m_history_button.isChecked())
        {
            setCurrentHistoryPage(currentHistoryPage()+1);
        }
        else
        {
            setCurrentGroupPage(currentGroupPage()+1);
        }
    });

    connect(this, &GroupControl::currentGroupPageChanged, this, [&](){
        updateGroupPage();
        m_up_button.setEnabled(currentGroupPage() > 0);
        m_down_button.setEnabled(currentGroupPage() < maxGroupPages() - 1);
    });
    connect(this, &GroupControl::currentHistoryPageChanged, this, [&](){
        updateHistoryPage();
        m_up_button.setEnabled(currentHistoryPage() > 0);
        m_down_button.setEnabled(currentHistoryPage() < maxHistoryPages() - 1);
    });

    connect(&m_history_button, &QAbstractButton::toggled, this, [&]() {
        if (m_history_button.isChecked())
        {
            for (auto& btn: m_group_buttons)
            {
                btn->setVisible(false);
            }
            updateHistoryPage();
            m_up_button.setEnabled(currentHistoryPage() > 0);
            m_down_button.setEnabled(currentHistoryPage() < maxHistoryPages() - 1);
            m_title_label.setText("グループ (最近使ったもの)");
        }
        else
        {
            for (auto& btn: m_history_buttons)
            {
                btn->setVisible(false);
            }
            updateGroupPage();
            m_up_button.setEnabled(currentGroupPage() > 0);
            m_down_button.setEnabled(currentGroupPage() < maxGroupPages() - 1);
            m_title_label.setText("グループ");
        }
    });
}

int GroupControl::currentGroupPage() const
{
    return m_currentGroupPage;
}

void GroupControl::setCurrentGroupPage(int newCurrentGroupPage)
{
    if (m_currentGroupPage == newCurrentGroupPage)
        return;
    m_currentGroupPage = newCurrentGroupPage;
    emit currentGroupPageChanged();
}

int GroupControl::currentHistoryPage() const
{
    return m_currentHistoryPage;
}

void GroupControl::setCurrentHistoryPage(int newCurrentHistoryPage)
{
    if (m_currentHistoryPage == newCurrentHistoryPage)
        return;
    m_currentHistoryPage = newCurrentHistoryPage;
    emit currentHistoryPageChanged();
}

void GroupControl::updateGroupPage()
{
    updateChildrenVisibility(m_group_buttons,currentGroupPage(),PAGE_SIZE);
}

void GroupControl::updateHistoryPage()
{
    updateChildrenVisibility(m_history_buttons,currentHistoryPage(),PAGE_SIZE);
}

int GroupControl::maxGroupPages() const
{
    return calulateNumberOfPages(m_group_buttons.length(), PAGE_SIZE);
}

int GroupControl::maxHistoryPages() const
{
    return calulateNumberOfPages(m_history_buttons.length(), PAGE_SIZE);
}

void GroupControl::onButtonGroupCheck(const uint32_t index, QObject *sender)
{
    for (uint32_t i = 0; i < m_group_buttons.size(); i++)
    {
        if (i != index)
        {
            m_group_buttons[i]->setChecked(false);
        }
    }
}

void GroupControl::onButtonHistoryCheck(const uint32_t index, QObject *sender)
{
    for (uint32_t i = 0; i < m_history_buttons.size(); i++)
    {
        if (i != index)
        {
            m_history_buttons[i]->setChecked(false);
        }
    }
}
