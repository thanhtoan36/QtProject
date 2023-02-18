#include "libraryControl/libraryControl.hpp"
#include "libraryControl/libraryControl_define.h"
#include "utility.h"

#define BASE_BUTTON_WIDTH LC_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT LC_BUTTON1_GEOMETRY.height()

LibraryControl::LibraryControl(QWidget *parent) : PanelControlBase(parent),
    m_grid(this),
    m_title_label(this),
    m_history_button(this),
    m_up_button(this),
    m_down_button(this),
    m_return_button(this),
    m_setting_label(this),
    m_title_button(this),
    m_empty_button(this),
    m_register_button(this),
    m_delete_button(this)
{
    setFixedSize(LC_SCREEN_SIZE);
    m_return_button.setTextColor(Qt::yellow);
    setColumn(4);
    setLibRow(3);
    setModeRow(2);
    setLibStartPoint(LC_LIB_BUTTON_TOP_LEFT);
    setModeStartPoint(LC_MODE_TOP_LEFT);
}

void LibraryControl::SetDispParamData(LIBRARY_DISP_PARAM *param)
{
    Q_ASSERT(param);
    //library
    for (int i = 0; i< m_library_buttons_list.size() ; i ++)
    {
        m_library_buttons_list[i].clear();
    }
    m_library_buttons_list.clear();
    m_mode_buttons.clear();
    m_all_lib_buttons.clear();
    auto all_button = MakeSharedQObject<SelectButton>(this);
    all_button->setFixedSize(LC_BUTTON_SIZE);
    all_button->setText("ALL");
    all_button->setChecked(true);
    connect(all_button.get(),&QAbstractButton::clicked, this, [&](){
        onButtonModeClicked(0,sender());
    });
    m_mode_buttons.push_back(all_button);
    for (int i = 0 ; i < param->group.count; i++)
    {
        auto button_mode = MakeSharedQObject<SelectButton>(this);
        button_mode->setFixedSize(LC_BUTTON_SIZE);
        button_mode->setText(param->group.library_param[i].mode);

        bool is_contain = false;
        for (int j = 1; j < m_mode_buttons.size(); j++)
        {

            if (strcmp(param->group.library_param[i].mode,m_mode_buttons[j]->text().toLocal8Bit().data()) == 0)
            {
                is_contain = true;
                break;
            }
        }
        if (is_contain == false)
        {
            m_mode_buttons.push_back(button_mode);
            int mode_index = m_mode_buttons.size() -1;
            connect(button_mode.get(),&QAbstractButton::clicked, this, [&,mode_index](){
                onButtonModeClicked(mode_index,sender());
            });
        }

    }
    m_current_mode = 0;
    m_current_page_indexs = QVector<uint32_t>(m_mode_buttons.size(),0);
    m_library_buttons_list.resize(m_mode_buttons.size() - 1); // not for all;
    for (int i = 0 ; i < param->group.count; i++)
    {
        auto button_lib = MakeSharedQObject<TitleSelectButton>(this);
        button_lib->setFixedSize(LC_BUTTON_SIZE);
        button_lib->setText(param->group.library_param[i].library_no);
        button_lib->setTitle(param->group.library_param[i].title);
        connect(button_lib.get(),&QAbstractButton::clicked, this, [&,i](){
            onButtonLibraryClicked(i,sender());
        });
        m_all_lib_buttons.push_back(button_lib);
        //not contain all button
        for (int j = 1; j < m_mode_buttons.size(); j++)
        {
            if (m_mode_buttons[j]->text() == QString(param->group.library_param[i].mode))
            {
                m_library_buttons_list[j-1].push_back(button_lib);
                break;
            }
        }
    }

    //history
    for (int i = 0; i< m_history_buttons_list.size() ; i ++)
    {
        m_history_buttons_list[i].clear();
    }
    m_history_buttons_list.clear();
    m_history_mode_buttons.clear();
    m_all_historty_buttons.clear();
    auto all_button_history = MakeSharedQObject<SelectButton>(this);
    all_button_history->setFixedSize(LC_BUTTON_SIZE);
    all_button_history->setText("ALL");
    all_button_history->setVisible(false);
    all_button_history->setChecked(true);
    connect(all_button_history.get(),&QAbstractButton::clicked, this, [&](){
        onButtonModeHistoryClicked(0,sender());
    });
    m_history_mode_buttons.push_back(all_button_history);
    for (int i = 0 ; i < param->history.count; i++)
    {
        auto button_mode = MakeSharedQObject<SelectButton>(this);
        button_mode->setFixedSize(LC_BUTTON_SIZE);
        button_mode->setText(param->history.library_param[i].mode);
        button_mode->setVisible(false);

        bool is_contain = false;
        for (int j = 1; j < m_history_mode_buttons.size(); j++)
        {

            if (strcmp(param->history.library_param[i].mode,m_history_mode_buttons[j]->text().toLocal8Bit().data()) == 0)
            {
                is_contain = true;
                break;
            }
        }
        if (is_contain == false)
        {
            m_history_mode_buttons.push_back(button_mode);
            int mode_index = m_history_mode_buttons.size() -1;
            connect(button_mode.get(),&QAbstractButton::clicked, this, [&,mode_index](){
                onButtonModeHistoryClicked(mode_index,sender());
            });
        }

    }
    m_current_history_mode = 0;
    m_current_history_indexs = QVector<uint32_t>(m_history_mode_buttons.size(),0);
    m_history_buttons_list.resize(m_history_mode_buttons.size() - 1); // not for all;

    for (int i = 0 ; i < param->history.count; i++)
    {
        auto button_lib = MakeSharedQObject<TitleSelectButton>(this);
        button_lib->setFixedSize(LC_BUTTON_SIZE);
        button_lib->setText(param->history.library_param[i].library_no);
        button_lib->setTitle(param->history.library_param[i].title);
        button_lib->setVisible(false);
        connect(button_lib.get(),&QAbstractButton::clicked, this, [&,i](){
            onButtonHistoryLibraryClicked(i,sender());
        });
        m_all_historty_buttons.push_back(button_lib);
        //not contain all button
        for (int j = 1; j < m_history_mode_buttons.size(); j++)
        {
            if (m_history_mode_buttons[j]->text() == QString(param->history.library_param[i].mode))
            {
                m_history_buttons_list[j-1].push_back(button_lib);
                break;
            }
        }
    }

    placeChildrenIntoPanel(m_mode_buttons, LC_BUTTON_SIZE, modeStartPoint(), QSize(column(), modeRow()));
    updateChildrenVisibility(m_mode_buttons,0,modePageSize());

    placeChildrenIntoPanel(m_history_mode_buttons, LC_BUTTON_SIZE, modeStartPoint(), QSize(column(), modeRow()));
    onButtonHistoryClicked(m_history_button.isChecked());
}

void LibraryControl::SetupUiComponents()
{
    m_grid.setGridSize(QSize(4, 5));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 32);

    m_title_label.setGeometry(LC_TITLE_GEOMETRY);
    m_title_label.setObjectName("title_label");
    m_title_label.setText("ライブラリ");

    m_history_button.setGeometry(LC_HISTORY_GEOMETRY);
    m_history_button.setText("最近使った\nもの");

    m_up_button.setGeometry(LC_UP_GEOMETRY);
    m_up_button.setText("▲");

    m_down_button.setGeometry(LC_DOWN_GEOMETRY);
    m_down_button.setText("▼");

    m_return_button.setGeometry(LC_RETURN_GEOMETRY);
    m_return_button.setText("戻す");

    m_setting_label.setGeometry(LC_SETTING_LABEL_GEOMETRY);
    m_setting_label.setText("設定");

    m_title_button.setGeometry(LC_TITLE_BUTTON_GEOMETRY);
    m_title_button.setText("タイトル");


    m_register_button.setGeometry(LC_REGISTER_GEOMETRY);
    m_register_button.setText("登録");

    m_delete_button.setGeometry(LC_DELETE_GEOMETRY);
    m_delete_button.setText("削除");

    m_empty_button.setGeometry(LC_EMPTY2_GEOMETRY);
    m_empty_button.setText("");
    m_empty_button.setEnabled(false);
}

void LibraryControl::SetupUiEvents()
{
    connect(&m_up_button, &QPushButton::clicked, this, [&](){
        scrollUpLibraryPages();
    });
    connect(&m_down_button, &QPushButton::clicked, this, [&](){
        scrollDownLibraryPages();
    });

    connect(&m_history_button, &QPushButton::clicked, this, &LibraryControl::onButtonHistoryClicked);

}

void LibraryControl::scrollUpLibraryPages()
{
    if (m_history_button.isChecked())
    {
        if (m_current_history_indexs[m_current_history_mode] > 0)
        {
           m_current_history_indexs[m_current_history_mode] -= 1;
        }
        if (m_current_history_mode == 0)
        {
             updateChildrenVisibility(m_all_historty_buttons,m_current_history_indexs[m_current_history_mode],libPageSize());
             m_up_button.setEnabled(m_current_history_indexs[m_current_history_mode] > 0);;
             m_down_button.setEnabled(m_current_history_indexs[m_current_history_mode] + 1  < calulateNumberOfPages(m_all_historty_buttons.size(), libPageSize()));
        }
        else
        {
            updateChildrenVisibility(m_history_buttons_list[m_current_history_mode - 1],m_current_history_indexs[m_current_history_mode],libPageSize());
            m_up_button.setEnabled(m_current_history_indexs[m_current_history_mode] > 0);
            m_down_button.setEnabled(m_current_history_indexs[m_current_history_mode] + 1  < calulateNumberOfPages(m_history_buttons_list[m_current_history_mode - 1].size(), libPageSize()));

        }
    }
    else
    {
        if (m_current_page_indexs[m_current_mode] > 0)
        {
           m_current_page_indexs[m_current_mode] -= 1;
        }

        if (m_current_mode == 0)
        {
             updateChildrenVisibility(m_all_lib_buttons,m_current_page_indexs[m_current_mode],libPageSize());
             m_up_button.setEnabled(m_current_page_indexs[m_current_mode] > 0);;
             m_down_button.setEnabled(m_current_page_indexs[m_current_mode] + 1  < calulateNumberOfPages(m_all_lib_buttons.size(), libPageSize()));
        }
        else
        {
            updateChildrenVisibility(m_library_buttons_list[m_current_mode -1],m_current_page_indexs[m_current_mode],libPageSize());
            //set up down button enable
            m_up_button.setEnabled(m_current_page_indexs[m_current_mode] > 0);;
            m_down_button.setEnabled(m_current_page_indexs[m_current_mode] + 1 < calulateNumberOfPages(m_library_buttons_list[m_current_mode - 1].size(), libPageSize()));
        }
    }

}

void LibraryControl::scrollDownLibraryPages()
{
    if (m_history_button.isChecked())
    {
        m_current_history_indexs[m_current_history_mode] += 1;
        if (m_current_history_mode == 0)
        {
             updateChildrenVisibility(m_all_historty_buttons,m_current_history_indexs[m_current_history_mode],libPageSize());
             m_up_button.setEnabled(m_current_history_indexs[m_current_history_mode] > 0);;
             m_down_button.setEnabled(m_current_history_indexs[m_current_history_mode] + 1  < calulateNumberOfPages(m_all_historty_buttons.size(), libPageSize()));
        }
        else
        {
            updateChildrenVisibility(m_history_buttons_list[m_current_history_mode - 1],m_current_history_indexs[m_current_history_mode],libPageSize());
            m_up_button.setEnabled(m_current_history_indexs[m_current_history_mode] > 0);
            m_down_button.setEnabled(m_current_history_indexs[m_current_history_mode] + 1  < calulateNumberOfPages(m_history_buttons_list[m_current_history_mode - 1].size(), libPageSize()));

        }
    }
    else
    {
        m_current_page_indexs[m_current_mode] += 1;
        if (m_current_mode == 0)
        {
             updateChildrenVisibility(m_all_lib_buttons,m_current_page_indexs[m_current_mode],libPageSize());
             m_up_button.setEnabled(m_current_page_indexs[m_current_mode] > 0);;
             m_down_button.setEnabled(m_current_page_indexs[m_current_mode] + 1  < calulateNumberOfPages(m_all_lib_buttons.size(), libPageSize()));
        }
        else
        {
            updateChildrenVisibility(m_library_buttons_list[m_current_mode - 1],m_current_page_indexs[m_current_mode],libPageSize());
            m_up_button.setEnabled(m_current_page_indexs[m_current_mode] > 0);;
            m_down_button.setEnabled(m_current_page_indexs[m_current_mode] + 1  < calulateNumberOfPages(m_library_buttons_list[m_current_mode - 1].size(), libPageSize()));
        }
    }
}

void LibraryControl::onButtonModeClicked(const int index, QObject *sender)
{
    //m_mode_buttons more than m_library_buttons_list 1
    if (index >= m_mode_buttons.size() || index >= m_library_buttons_list.size() +1)
    {
        return;
    }
    m_current_mode = index;
    for (int i = 0; i< m_mode_buttons.size(); i++)
    {
        if (i != index)
        {
            m_mode_buttons[i]->setChecked(false);
        }
    }
    //for ALL button
    if (index == 0)
    {
        placeChildrenIntoPanel(m_all_lib_buttons, LC_BUTTON_SIZE, libStartPoint(), QSize(column(), libRow()));
        updateChildrenVisibility(m_all_lib_buttons,m_current_page_indexs[m_current_mode],libPageSize());
        m_up_button.setEnabled(m_current_page_indexs[m_current_mode] > 0);;
        m_down_button.setEnabled(m_current_page_indexs[m_current_mode] + 1  < calulateNumberOfPages(m_all_lib_buttons.size(), libPageSize()));
        return;
    }

    for (int j = 0 ; j < m_library_buttons_list.size(); j++)
    {
        if (j == index -1)
        {
            placeChildrenIntoPanel(m_library_buttons_list[j], LC_BUTTON_SIZE, libStartPoint(), QSize(column(), libRow()));
            updateChildrenVisibility(m_library_buttons_list[j],m_current_page_indexs[m_current_mode],libPageSize());
            m_up_button.setEnabled(m_current_page_indexs[m_current_mode] > 0);;
            m_down_button.setEnabled(m_current_page_indexs[m_current_mode] + 1  < calulateNumberOfPages(m_library_buttons_list[j].size(), libPageSize()));
        }
        else
        {
            for (auto& btn : m_library_buttons_list[j])
            {
                btn->setVisible(false);
            }
        }

    }
}

void LibraryControl::onButtonLibraryClicked(const int index, QObject *sender)
{
    for (int i = 0; i< m_all_lib_buttons.size(); i++)
    {
        if (i != index)
        {
            m_all_lib_buttons[i]->setChecked(false);
        }
    }
}

void LibraryControl::onButtonHistoryLibraryClicked(const int index, QObject *sender)
{
    for (int i = 0; i< m_all_historty_buttons.size(); i++)
    {
        if (i != index)
        {
            m_all_historty_buttons[i]->setChecked(false);
        }
    }
}

void LibraryControl::onButtonModeHistoryClicked(const int index, QObject *sender)
{
    //m_mode_buttons more than m_library_buttons_list 1
    if (index >= m_history_mode_buttons.size() || index >= m_history_buttons_list.size() +1)
    {
        return;
    }
    m_current_history_mode = index;
    for (int i = 0; i< m_history_mode_buttons.size(); i++)
    {
        if (i != index)
        {
            m_history_mode_buttons[i]->setChecked(false);
        }
    }
    //for ALL button
    if (index == 0)
    {
        placeChildrenIntoPanel(m_all_historty_buttons, LC_BUTTON_SIZE, libStartPoint(), QSize(column(), libRow()));
        updateChildrenVisibility(m_all_historty_buttons,m_current_page_indexs[m_current_history_mode],libPageSize());
        m_up_button.setEnabled(m_current_history_indexs[m_current_history_mode] > 0);;
        m_down_button.setEnabled(m_current_history_indexs[m_current_history_mode] + 1  < calulateNumberOfPages(m_all_lib_buttons.size(), libPageSize()));
        return;
    }

    for (int j = 0 ; j < m_history_buttons_list.size(); j++)
    {
        if (j == index -1)
        {
            placeChildrenIntoPanel(m_history_buttons_list[j], LC_BUTTON_SIZE, libStartPoint(), QSize(column(), libRow()));
            updateChildrenVisibility(m_history_buttons_list[j],m_current_history_indexs[m_current_history_mode],libPageSize());
            m_up_button.setEnabled(m_current_history_indexs[m_current_history_mode] > 0);;
            m_down_button.setEnabled(m_current_history_indexs[m_current_history_mode] + 1  < calulateNumberOfPages(m_history_buttons_list[j].size(), libPageSize()));
        }
        else
        {
            for (auto& btn : m_history_buttons_list[j])
            {
                btn->setVisible(false);
            }
        }

    }
}

void LibraryControl::onButtonHistoryClicked(const bool check)
{
    if (check)
    {
        for (auto& btn : m_mode_buttons)
        {
            btn->setVisible(false);
        }
        for (auto& btn : m_all_lib_buttons)
        {
            btn->setVisible(false);
        }
        updateChildrenVisibility(m_history_mode_buttons,0,modePageSize());
        onButtonModeHistoryClicked(m_current_history_mode,nullptr);
        m_title_label.setText("ライブラリ (最近使ったもの)");

    }
    else
    {
        for (auto& btn : m_history_mode_buttons)
        {
            btn->setVisible(false);
        }
        for (auto& btn : m_all_historty_buttons)
        {
            btn->setVisible(false);
        }
        updateChildrenVisibility(m_mode_buttons,0,modePageSize());
        onButtonModeClicked(m_current_mode, nullptr);
        m_title_label.setText("ライブラリ");
    }
}

QPoint LibraryControl::modeStartPoint() const
{
    return m_modeStartPoint;
}

void LibraryControl::setModeStartPoint(QPoint newModeStartPoint)
{
    m_modeStartPoint = newModeStartPoint;
}

QPoint LibraryControl::libStartPoint() const
{
    return m_libStartPoint;
}

void LibraryControl::setLibStartPoint(QPoint newLibStartPoint)
{
    m_libStartPoint = newLibStartPoint;
}

uint16_t LibraryControl::modeRow() const
{
    return m_modeRow;
}

void LibraryControl::setModeRow(uint16_t newModeRow)
{
    m_modeRow = newModeRow;
}

uint16_t LibraryControl::libPageSize() const
{
    return column()*libRow();
}

uint16_t LibraryControl::modePageSize() const
{
    return column()*modeRow();
}

uint16_t LibraryControl::libRow() const
{
    return m_libRow;
}

void LibraryControl::setLibRow(uint16_t newLibRow)
{
    m_libRow = newLibRow;
}

uint16_t LibraryControl::column() const
{
    return m_column;
}

void LibraryControl::setColumn(uint16_t newColumn)
{
    m_column = newColumn;
}


