#include "colorFilterControl/colorFilterControl.hpp"

#include "colorFilterControl/colorFilterControl_define.hpp"
#include <QFont>
#include <math.h>
#include "utility.h"


#define PAGE_ROW  4
#define PAGE_COLUMN  4
#define PAGE_SIZE (PAGE_ROW*PAGE_COLUMN)

#define BASE_BUTTON_X CFC_BUTTON1_GEOMETRY.x()
#define BASE_BUTTON_Y CFC_BUTTON1_GEOMETRY.y()

#define BASE_BUTTON_WIDTH CFC_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT CFC_BUTTON1_GEOMETRY.height()

ColorFilterControl::ColorFilterControl(QWidget* parent) : PanelControlBase(parent),
    m_grid(this),
    m_title_label(this),
    m_tb_tab_button(this),
    m_custom_tab_button(this),
    m_next_button(this),
    m_prev_button(this),
    m_history_button(this),
    m_up_button(this),
    m_down_button(this),
    m_back_button(this),
    m_setting_label(this),
    m_title_button(this),
    m_empty_button(this),
    m_register_button(this),
    m_delete_button(this),
    m_children_tb_tab{&m_tb_tab_button, &m_custom_tab_button},
    m_children_custom_tab{&m_tb_tab_button, &m_custom_tab_button, &m_setting_label, &m_title_button, &m_empty_button, &m_register_button, &m_delete_button}
{
    setFixedSize(CFC_SCREENSIZE);
    setCurrentTBTabPage(0);
    setCurrentCustomTabPage(0);
    setCurrentHistoryPage(0);
    m_up_button.setEnabled(false);
    m_back_button.setTextColor(Qt::yellow);
    m_tb_tab_button.setCheckMarkVisible(true);
    m_custom_tab_button.setCheckMarkVisible(true);
}

void ColorFilterControl::setDispParamData(COLOR_FILTER_DISP_PARAM *param)
{
    Q_ASSERT(param);
    m_tb_tab_buttons.clear();
    for (uint16_t i = 0; i < param->tb.count; i++)
    {
        auto button = MakeSharedQObject<SelectColorButton>(this);
        m_tb_tab_buttons.push_back(button);

        button->setFixedSize(CFC_BUTTON1_GEOMETRY.size());
        button->setText(param->tb.color_filter[i].name);

        button->setBackgroundColor(param->tb.color_filter[i].color);
        button->setSelectedBackgroundColor(button->backgroundColor());
        button->setCheckMarkVisible(true);
        button->setChecked(param->tb.color_filter[i].select);

        connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
            onTBTabButtonChecked(i,sender());
        });

    }
    placeChildrenIntoPanel(m_tb_tab_buttons, CFC_BUTTON1_GEOMETRY.size(), CFC_BUTTON1_GEOMETRY.topLeft(), 4,4);

    m_custom_tab_buttons.clear();
    for (uint16_t i = 0; i < param->custom.count; i++)
    {
        auto button = MakeSharedQObject<SelectColorButton>(this);
        m_custom_tab_buttons.push_back(button);
        button->setFixedSize(CFC_BUTTON1_GEOMETRY.size());
        button->setText(param->custom.color_filter[i].name);
        button->setBackgroundColor(param->custom.color_filter[i].color);
        button->setSelectedBackgroundColor(button->backgroundColor());
        button->setCheckMarkVisible(true);
        button->setChecked(param->custom.color_filter[i].select);
        connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
            onCustomTabButtonChecked(i,sender());
        });

    }
    placeChildrenIntoPanel(m_custom_tab_buttons, CFC_BUTTON1_GEOMETRY.size(), CFC_BUTTON1_GEOMETRY.topLeft(), 4,4);

    m_history_buttons.clear();
    for (uint16_t i = 0; i < param->history.count; i++)
    {
        auto button = MakeSharedQObject<SelectColorButton>(this);
        m_history_buttons.push_back(button);
        button->setText(param->history.color_filter[i].name);
        button->setBackgroundColor(param->history.color_filter[i].color);
        button->setSelectedBackgroundColor(button->backgroundColor());
        button->setFixedSize(CFC_BUTTON1_GEOMETRY.size());
        button->setCheckMarkVisible(true);
        button->setChecked(param->history.color_filter[i].select);
        connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
            onHistoryButtonChecked(i,sender());
        });
    }
    placeChildrenIntoPanel(m_history_buttons, CFC_BUTTON1_GEOMETRY.size(), CFC_BUTTON1_GEOMETRY.topLeft(), 4,4);

    if (param->tb.select == true)
    {
        setMode(COLOR_FILTER_MODE_TAB1);
    }

    if (param->custom.select == true)
    {
        setMode(COLOR_FILTER_MODE_TAB2);
    }

    if (param->history.select == true)
    {
        setMode(COLOR_FILTER_MODE_HISTORY);
    }
    onModeChanged();

}

void ColorFilterControl::ScrollUp()
{
    if (mode() == COLOR_FILTER_MODE_TAB1)
    {
        setCurrentTBTabPage(currentTBTabPage()-1);
    }
    else if(mode() == COLOR_FILTER_MODE_TAB2)
    {
        setCurrentCustomTabPage(currentCustomTabPage()-1);
    }
    else if(mode() == COLOR_FILTER_MODE_HISTORY)
    {
        setCurrentHistoryPage(currentHistoryPage()-1);
    }
}

void ColorFilterControl::ScrollDown()
{
    if (mode() == COLOR_FILTER_MODE_TAB1)
    {
        setCurrentTBTabPage(currentTBTabPage()+1);
    }
    else if(mode() == COLOR_FILTER_MODE_TAB2)
    {
        setCurrentCustomTabPage(currentCustomTabPage()+1);
    }
    else if(mode() == COLOR_FILTER_MODE_HISTORY)
    {
        setCurrentHistoryPage(currentHistoryPage()+1);
    }
}

void ColorFilterControl::SetupUiComponents()
{
    m_grid.setGridSize(QSize(6, 6));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 32);

    m_title_label.setGeometry(CFC_TITLE_GEOMETRY);
    m_title_label.setText("カラーフィルタ");
    m_title_label.setObjectName("title_label");

    m_tb_tab_button.setGeometry(CFC_TAB1_GEOMETRY);
    m_tb_tab_button.setText("TB標準");

    m_custom_tab_button.setGeometry(CFC_TAB2_GEOMETRY);
    m_custom_tab_button.setText("カスタム");

    m_next_button.setGeometry(CFC_NEXT_BUTTON_GEOMETRY);
    m_next_button.setText("▶");
    m_next_button.setVisible(false);

    m_prev_button.setGeometry(CFC_PREVIOUS_BUTTON_GEOMETRY);
    m_prev_button.setText("◀");
    m_prev_button.setVisible(false);

    m_history_button.setGeometry(CFC_HISTORY_GEOMETRY);
    m_history_button.setText("最近使った\nもの");

    m_up_button.setGeometry(CFC_UP_BUTTON_GEOMETRY);
    m_up_button.setText("▲");

    m_down_button.setGeometry(CFC_DOWN_BUTTON_GEOMETRY);
    m_down_button.setText("▼");

    m_title_button.setGeometry(CFC_TITLE_BUTTON_GEOMETRY);
    m_title_button.setText("タイトル");

    m_empty_button.setGeometry(CFC_EMPTY_GEOMETRY);
    m_empty_button.setText("");

    m_register_button.setGeometry(CFC_REGISTER_GEOMETRY);
    m_register_button.setText("登録");

    m_delete_button.setGeometry(CFC_DELETE_GEOMETRY);
    m_delete_button.setText("削除");

    m_back_button.setGeometry(CFC_BACK_BUTTON_GEOMETRY);
    m_back_button.setText("戻す");

    m_setting_label.setGeometry(CFC_SETTING_GEOMETRY);
    m_setting_label.setText("設定");
    m_setting_label.setObjectName("title_label");

}

void ColorFilterControl::SetupUiEvents()
{
    connect(&m_up_button, &QAbstractButton::clicked, this, [&]() {
        ScrollUp();
    });
    connect(&m_down_button, &QAbstractButton::clicked, this, [&]() {
        ScrollDown();
    });
    connect(this, &ColorFilterControl::modeChanged, this, [&]() {
       onModeChanged();
    });
    connect(this, &ColorFilterControl::currentTBTabPageChanged, this, [&](){
        updateTBTabPage();
        m_up_button.setEnabled(currentTBTabPage() > 0);
        m_down_button.setEnabled(currentTBTabPage() < maxTBTabPages() - 1);
    });
    connect(this, &ColorFilterControl::currentCustomTabPageChanged, this, [&](){
        updateCustomTabPage();
        m_up_button.setEnabled(currentCustomTabPage() > 0);
        m_down_button.setEnabled(currentCustomTabPage() < maxCustomTabPages() - 1);
    });
    connect(this, &ColorFilterControl::currentHistoryPageChanged, this, [&](){
        updateHistoryPage();
        m_up_button.setEnabled(currentHistoryPage() > 0);
        m_down_button.setEnabled(currentHistoryPage() < maxHistoryPages() - 1);
    });
    connect(&m_tb_tab_button, &QAbstractButton::toggled, this, [&]() {
        if (m_tb_tab_button.isChecked())
        {
            m_previous_tab = COLOR_FILTER_MODE_TAB1;
            setMode(COLOR_FILTER_MODE_TAB1);
        }
    });
    connect(&m_custom_tab_button, &QAbstractButton::toggled, this, [&]() {
        if (m_custom_tab_button.isChecked())
        {
            m_previous_tab = COLOR_FILTER_MODE_TAB2;
            setMode(COLOR_FILTER_MODE_TAB2);
        }
    });
    connect(&m_history_button, &QAbstractButton::toggled, this, [&]() {
        if (m_history_button.isChecked())
        {
            setMode(COLOR_FILTER_MODE_HISTORY);
            m_title_label.setText("カラーフィルタ (最近使ったもの)");
        }
        else
        {
            setMode(m_previous_tab);
            m_title_label.setText("カラーフィルタ");
        }
    });

    connect(&m_title_button, &QAbstractButton::toggled, this, [&]() {
        if (m_title_button.isChecked())
        {
            m_register_button.setChecked(false);
            m_delete_button.setChecked(false);
        }
    });
    connect(&m_register_button, &QAbstractButton::toggled, this, [&]() {
        if (m_register_button.isChecked())
        {
            m_title_button.setChecked(false);
            m_delete_button.setChecked(false);
        }
    });
    connect(&m_delete_button, &QAbstractButton::toggled, this, [&]() {
        if (m_delete_button.isChecked())
        {
            m_register_button.setChecked(false);
            m_title_button.setChecked(false);
        }
    });
}

int ColorFilterControl::currentTBTabPage() const
{
    return m_currentTBTabPage;
}

void ColorFilterControl::setCurrentTBTabPage(int newCurrentTab1Page)
{
    if (m_currentTBTabPage == newCurrentTab1Page)
        return;
    m_currentTBTabPage = newCurrentTab1Page;
    emit currentTBTabPageChanged();
}

int ColorFilterControl::currentCustomTabPage() const
{
    return m_currentCustomTabPage;
}

void ColorFilterControl::setCurrentCustomTabPage(int newCurrentTab2Page)
{
    if (m_currentCustomTabPage == newCurrentTab2Page)
        return;
    m_currentCustomTabPage = newCurrentTab2Page;
    emit currentCustomTabPageChanged();
}

int ColorFilterControl::currentHistoryPage() const
{
    return m_currentHistoryPage;
}

void ColorFilterControl::setCurrentHistoryPage(int newCurrentHistoryPage)
{
    if (m_currentHistoryPage == newCurrentHistoryPage)
        return;
    m_currentHistoryPage = newCurrentHistoryPage;
    emit currentHistoryPageChanged();
}

COLOR_FILTER_MODE ColorFilterControl::mode() const
{
    return m_mode;
}

void ColorFilterControl::setMode(COLOR_FILTER_MODE newMode)
{
    if (m_mode == newMode)
        return;
    m_mode = newMode;
    emit modeChanged();
}

void ColorFilterControl::onModeChanged()
{
    qDebug()<< mode();
    if (mode() == COLOR_FILTER_MODE_TAB1)
    {
        for(auto& btn : m_custom_tab_buttons)
        {
            btn->setVisible(false);
        }

        for(auto& btn : m_children_custom_tab)
        {
            btn->setVisible(false);
        }

        for(auto& btn : m_history_buttons)
        {
            btn->setVisible(false);
        }

        for(auto& btn : m_children_tb_tab)
        {
            btn->setVisible(true);
        }

        updateTBTabPage();
        m_tb_tab_button.setChecked(true);
        m_custom_tab_button.setChecked(false);
        m_history_button.setChecked(false);
        m_up_button.setEnabled(currentTBTabPage() > 0);
        m_down_button.setEnabled(currentTBTabPage() < maxTBTabPages() - 1);
    }
    else if(mode() == COLOR_FILTER_MODE_TAB2)
    {
        for(auto& btn : m_tb_tab_buttons)
        {
            btn->setVisible(false);
        }
        for(auto& btn : m_children_tb_tab)
        {
            btn->setVisible(false);
        }
        for(auto& btn : m_history_buttons)
        {
            btn->setVisible(false);
        }
        for(auto& btn : m_children_custom_tab)
        {
            btn->setVisible(true);
        }

        updateCustomTabPage();
        m_tb_tab_button.setChecked(false);
        m_custom_tab_button.setChecked(true);
        m_history_button.setChecked(false);
        m_up_button.setEnabled(currentCustomTabPage() > 0);
        m_down_button.setEnabled(currentCustomTabPage() < maxCustomTabPages() - 1);
    }
    else if(mode() == COLOR_FILTER_MODE_HISTORY)
    {
        m_history_button.setChecked(true);
        for(auto& btn : m_tb_tab_buttons)
        {
            btn->setVisible(false);
        }
        for(auto& btn : m_custom_tab_buttons)
        {
            btn->setVisible(false);
        }
        for(auto& btn : m_children_tb_tab)
        {
            btn->setVisible(false);
        }

        for(auto& btn : m_children_custom_tab)
        {
            btn->setVisible(false);
        }

        for(auto& btn : m_children_history)
        {
            btn->setVisible(true);
        }

        updateHistoryPage();
        m_tb_tab_button.setChecked(false);
        m_custom_tab_button.setChecked(false);
        m_up_button.setEnabled(currentHistoryPage() > 0);
        m_down_button.setEnabled(currentHistoryPage() < maxHistoryPages() - 1);
    }
}

void ColorFilterControl::updateTBTabPage()
{
    qDebug() << currentTBTabPage();
    updateChildrenVisibility(m_tb_tab_buttons,currentTBTabPage(),PAGE_SIZE);
}

void ColorFilterControl::updateCustomTabPage()
{
    updateChildrenVisibility(m_custom_tab_buttons,currentCustomTabPage(),PAGE_SIZE);
}

void ColorFilterControl::updateHistoryPage()
{
    updateChildrenVisibility(m_history_buttons,currentHistoryPage(),PAGE_SIZE);
}

int ColorFilterControl::maxTBTabPages() const
{
    return calulateNumberOfPages(m_tb_tab_buttons.length(), PAGE_SIZE);
}

int ColorFilterControl::maxCustomTabPages() const
{
    return calulateNumberOfPages(m_custom_tab_buttons.length(), PAGE_SIZE);
}

int ColorFilterControl::maxHistoryPages() const
{
    return calulateNumberOfPages(m_history_buttons.length(), PAGE_SIZE);
}

void ColorFilterControl::onTBTabButtonChecked(const int index, QObject *sender)
{
    if (index < m_tb_tab_buttons.size())
    {
        for (int i = 0; i < m_tb_tab_buttons.size(); i++)
        {
            m_tb_tab_buttons[i]->setChecked( i == index);
        }
        addButtonToHistory(m_tb_tab_buttons[index]);
    }
    SelectButton* button = static_cast<SelectButton*>(sender);
    if (button != nullptr)
    {
        qDebug() << index;
        qDebug() << button->backgroundColor();
        setCurrentTBTabButtonCheck({button->text(),button->backgroundColor()});
    }
}

void ColorFilterControl::onCustomTabButtonChecked(const int index, QObject *sender)
{
    if (index < m_custom_tab_buttons.size())
    {
        for (int i = 0; i < m_custom_tab_buttons.size(); i++)
        {
            m_custom_tab_buttons[i]->setChecked( i == index);
        }
        addButtonToHistory(m_custom_tab_buttons[index]);
    }
    SelectButton* button = static_cast<SelectButton*>(sender);
    if (button != nullptr)
    {
        qDebug() << index;
        qDebug() << button->backgroundColor();
        setCurrentCustomTabButtonCheck({button->text(),button->backgroundColor()});
    }
}

void ColorFilterControl::onHistoryButtonChecked(const int index, QObject *sender)
{
    if (index < m_history_buttons.size())
    {
        for (int i = 0; i < m_history_buttons.size(); i++)
        {
            m_history_buttons[i]->setChecked( i == index);
        }
    }
    SelectButton* button = static_cast<SelectButton*>(sender);
    if (button != nullptr)
    {
        qDebug() << index;
        qDebug() << button->backgroundColor();
        setCurrentHistoryTabButtonCheck({button->text(),button->backgroundColor()});
    }
}


const COLOR_FILTER_BUTTON_DATA ColorFilterControl::currentTBTabButtonCheck() const
{
    return m_currentTBTabButtonCheck;
}

void ColorFilterControl::setCurrentTBTabButtonCheck(const COLOR_FILTER_BUTTON_DATA& newCurrentTBTabButtonCheck)
{
    if (m_currentTBTabButtonCheck == newCurrentTBTabButtonCheck)
        return;
    m_currentTBTabButtonCheck = newCurrentTBTabButtonCheck;
    emit currentTBTabButtonCheckChanged();
}

const COLOR_FILTER_BUTTON_DATA ColorFilterControl::currentCustomTabButtonCheck() const
{
    return m_currentCustomTabButtonCheck;
}

void ColorFilterControl::setCurrentCustomTabButtonCheck(const COLOR_FILTER_BUTTON_DATA& newCurrentCustomTabButtonCheck)
{
    if (m_currentCustomTabButtonCheck == newCurrentCustomTabButtonCheck)
        return;
    m_currentCustomTabButtonCheck = newCurrentCustomTabButtonCheck;
    emit currentCustomTabButtonCheckChanged();
}

const COLOR_FILTER_BUTTON_DATA ColorFilterControl::currentHistoryTabButtonCheck() const
{
    return m_currentHistoryTabButtonCheck;
}

void ColorFilterControl::setCurrentHistoryTabButtonCheck(const COLOR_FILTER_BUTTON_DATA& newCurrentHistoryTabButtonCheck)
{
    if (m_currentHistoryTabButtonCheck == newCurrentHistoryTabButtonCheck)
        return;
    m_currentHistoryTabButtonCheck = newCurrentHistoryTabButtonCheck;
    emit currentHistoryTabButtonCheckChanged();
}

void ColorFilterControl::addButtonToHistory(QSharedPointer<SelectColorButton> &button)
{
    auto new_button = MakeSharedQObject<SelectColorButton>(this);
    new_button->setText(button->text());
    new_button->setCheckMarkVisible(true);
    new_button->setFixedSize(CFC_BUTTON1_GEOMETRY.size());
    new_button->setVisible(false);
    new_button->setBackgroundColor(button->backgroundColor());
    new_button->setSelectedBackgroundColor(button->backgroundColor());
    int index = m_history_buttons.size();
    connect(new_button.get(),&QAbstractButton::clicked, this, [&,index](){
        onHistoryButtonChecked(index,sender());
    });
    m_history_buttons.push_back(new_button);
    placeChildrenIntoPanel(m_history_buttons, CFC_BUTTON1_GEOMETRY.size(), CFC_BUTTON1_GEOMETRY.topLeft(), 4,4);
}
