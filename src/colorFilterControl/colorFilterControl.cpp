#include "colorFilterControl/colorFilterControl.hpp"

#include "colorFilterControl/colorFilterControl_define.hpp"
#include <QFont>
#include <math.h>
#include "utility.h"


#define BUTTONS_GRID_SIZE QSize(4, 4)
#define BUTTONS_PER_PAGE (BUTTONS_GRID_SIZE.width() * BUTTONS_GRID_SIZE.height())

#define BASE_BUTTON_X CFC_BUTTON1_GEOMETRY.x()
#define BASE_BUTTON_Y CFC_BUTTON1_GEOMETRY.y()

#define BASE_BUTTON_WIDTH CFC_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT CFC_BUTTON1_GEOMETRY.height()

ColorFilterControl::ColorFilterControl(QWidget* parent) : PanelControlBase(parent),
    m_grid(this),
    m_title_label(this),
    m_button_next_header_buttons_page(this),
    m_button_previous_header_buttons_page(this),
    m_history_button(this),
    m_button_next_filter_buttons_page(this),
    m_button_previous_filter_buttons_page(this),
    m_back_button(this),
    m_setting_label(this),
    m_title_button(this),
    m_empty_button(this),
    m_register_button(this),
    m_delete_button(this),
    m_children_tb_tab{},
    m_children_custom_tab{&m_setting_label, &m_title_button, &m_empty_button, &m_register_button, &m_delete_button}
{
    m_header_buttons_per_page = 2;

    setFixedSize(CFC_SCREENSIZE);
    setCurrentTBTabPage(0);
    setCurrentCustomTabPage(0);
    setCurrentHistoryPage(0);
    setCurrentHeaderButtonsPage(0);

    m_button_next_filter_buttons_page.setEnabled(false);
    m_back_button.setTextColor(Qt::yellow);

    m_grid.setGridSize(QSize(6, 6));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 32);

    m_title_label.setGeometry(CFC_TITLE_GEOMETRY);
    m_title_label.setText("カラーフィルタ");
    m_title_label.setObjectName("title_label");

    m_button_next_header_buttons_page.setGeometry(CFC_NEXT_BUTTON_GEOMETRY);
    m_button_next_header_buttons_page.setText("▶");
    m_button_next_header_buttons_page.setVisible(false);

    m_button_previous_header_buttons_page.setGeometry(CFC_PREVIOUS_BUTTON_GEOMETRY);
    m_button_previous_header_buttons_page.setText("◀");
    m_button_previous_header_buttons_page.setVisible(false);

    m_history_button.setGeometry(CFC_HISTORY_GEOMETRY);
    m_history_button.setText("最近使った\nもの");

    m_button_next_filter_buttons_page.setGeometry(CFC_UP_BUTTON_GEOMETRY);
    m_button_next_filter_buttons_page.setText("▲");

    m_button_previous_filter_buttons_page.setGeometry(CFC_DOWN_BUTTON_GEOMETRY);
    m_button_previous_filter_buttons_page.setText("▼");

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

    addHeaderButton(COLOR_FILTER_MODE_TB, "TB標準");
    addHeaderButton(COLOR_FILTER_MODE_CUSTOM, "カスタム");

    placeChildrenIntoPanel(headerButtons(), CFC_TAB1_GEOMETRY.size(), CFC_TAB1_GEOMETRY.topLeft(), QSize(m_header_buttons_per_page, 1));
    m_button_next_header_buttons_page.setVisible(headerButtons().size() > m_header_buttons_per_page);
    m_button_previous_header_buttons_page.setVisible(headerButtons().size() > m_header_buttons_per_page);
    setupHeaderTabButtons();

    connect(&m_button_previous_header_buttons_page, &QPushButton::clicked, this, [&](){
        setCurrentHeaderButtonsPage(currentHeaderButtonsPage() - 1);
    });
    connect(&m_button_next_header_buttons_page, &QPushButton::clicked, this, [&](){
        setCurrentHeaderButtonsPage(currentHeaderButtonsPage() + 1);
    });
    connect(this, &ColorFilterControl::currentHeaderButtonsPageChanged, this, &ColorFilterControl::setupHeaderTabButtons);

    connect(&m_button_next_filter_buttons_page, &QAbstractButton::clicked, this, &ColorFilterControl::ScrollUp);
    connect(&m_button_previous_filter_buttons_page, &QAbstractButton::clicked, this, &ColorFilterControl::ScrollDown);
    connect(this, &ColorFilterControl::modeChanged, this, &ColorFilterControl::onModeChanged);
    connect(this, &ColorFilterControl::currentTBTabPageChanged, this, [&](){
        updateTBTabPage();
        m_button_next_filter_buttons_page.setEnabled(currentTBTabPage() > 0);
        m_button_previous_filter_buttons_page.setEnabled(currentTBTabPage() < maxTBTabPages() - 1);
    });
    connect(this, &ColorFilterControl::currentCustomTabPageChanged, this, [&](){
        updateCustomTabPage();
        m_button_next_filter_buttons_page.setEnabled(currentCustomTabPage() > 0);
        m_button_previous_filter_buttons_page.setEnabled(currentCustomTabPage() < maxCustomTabPages() - 1);
    });
    connect(this, &ColorFilterControl::currentHistoryPageChanged, this, [&](){
        updateHistoryPage();
        m_button_next_filter_buttons_page.setEnabled(currentHistoryPage() > 0);
        m_button_previous_filter_buttons_page.setEnabled(currentHistoryPage() < maxHistoryPages() - 1);
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
    setupHeaderTabButtons();
    onModeChanged();
}

void ColorFilterControl::setDispParamData(COLOR_FILTER_DISP_PARAM *param)
{
    Q_ASSERT(param);
    m_tb_tab_buttons.clear();
    for (uint16_t i = 0; i < param->tb.count; i++)
    {
        auto button = MakeSharedQObject<SelectButton>(this);
        m_tb_tab_buttons.push_back(button);

        button->setFixedSize(CFC_BUTTON1_GEOMETRY.size());
        button->setText(param->tb.color_filter[i].name);

        button->setBackgroundColor(param->tb.color_filter[i].color);
        button->setSelectedBackgroundColor(button->backgroundColor());
        button->setCheckMarkVisible(true);
        button->setChecked(param->tb.color_filter[i].select);

        connect(button.get(),&QAbstractButton::clicked, this, &ColorFilterControl::onTBTabButtonClicked);

    }
    placeChildrenIntoPanel(m_tb_tab_buttons, CFC_BUTTON1_GEOMETRY.size(), CFC_BUTTON1_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE);

    m_custom_tab_buttons.clear();
    for (uint16_t i = 0; i < param->custom.count; i++)
    {
        auto button = MakeSharedQObject<SelectButton>(this);
        m_custom_tab_buttons.push_back(button);
        button->setFixedSize(CFC_BUTTON1_GEOMETRY.size());
        button->setText(param->custom.color_filter[i].name);
        button->setBackgroundColor(param->custom.color_filter[i].color);
        button->setSelectedBackgroundColor(button->backgroundColor());
        button->setCheckMarkVisible(true);
        button->setChecked(param->custom.color_filter[i].select);
        connect(button.get(),&QAbstractButton::clicked, this, &ColorFilterControl::onCustomTabButtonClicked);
    }
    placeChildrenIntoPanel(m_custom_tab_buttons, CFC_BUTTON1_GEOMETRY.size(), CFC_BUTTON1_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE);

    m_history_buttons.clear();
    for (uint16_t i = 0; i < param->history.count; i++)
    {
        auto button = MakeSharedQObject<SelectButton>(this);
        m_history_buttons.push_back(button);
        button->setText(param->history.color_filter[i].name);
        button->setBackgroundColor(param->history.color_filter[i].color);
        button->setSelectedBackgroundColor(button->backgroundColor());
        button->setFixedSize(CFC_BUTTON1_GEOMETRY.size());
        button->setCheckMarkVisible(true);
        button->setChecked(param->history.color_filter[i].select);
        connect(button.get(),&QAbstractButton::clicked, this, &ColorFilterControl::onHistoryButtonClicked);
    }
    placeChildrenIntoPanel(m_history_buttons, CFC_BUTTON1_GEOMETRY.size(), CFC_BUTTON1_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE);

    if (param->tb.select == true)
    {
        setMode(COLOR_FILTER_MODE_TB);
    }

    if (param->custom.select == true)
    {
        setMode(COLOR_FILTER_MODE_CUSTOM);
    }

    if (param->history.select == true)
    {
        setMode(COLOR_FILTER_MODE_HISTORY);
    }
    onModeChanged();
}

void ColorFilterControl::ScrollUp()
{
    if (mode() == COLOR_FILTER_MODE_TB)
    {
        setCurrentTBTabPage(currentTBTabPage()-1);
    }
    else if(mode() == COLOR_FILTER_MODE_CUSTOM)
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
    if (mode() == COLOR_FILTER_MODE_TB)
    {
        setCurrentTBTabPage(currentTBTabPage()+1);
    }
    else if(mode() == COLOR_FILTER_MODE_CUSTOM)
    {
        setCurrentCustomTabPage(currentCustomTabPage()+1);
    }
    else if(mode() == COLOR_FILTER_MODE_HISTORY)
    {
        setCurrentHistoryPage(currentHistoryPage()+1);
    }
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

ColorFilterDisplayMode ColorFilterControl::mode() const
{
    return m_mode;
}

void ColorFilterControl::setMode(ColorFilterDisplayMode newMode)
{
    if (m_mode == newMode)
        return;
    m_mode = newMode;
    emit modeChanged();
}

void ColorFilterControl::onModeChanged()
{
    for (const auto &button: qAsConst(m_header_buttons))
    {
        button.button->setChecked(button.mode == mode());
    }

    setupHeaderTabButtons();
    for(auto& btn : m_custom_tab_buttons)
    {
        btn->setVisible(mode() == COLOR_FILTER_MODE_CUSTOM);
    }

    for(auto& btn : m_children_custom_tab)
    {
        btn->setVisible(mode() == COLOR_FILTER_MODE_CUSTOM);
    }

    for(auto& btn : m_history_buttons)
    {
        btn->setVisible(mode() == COLOR_FILTER_MODE_HISTORY);
    }

    for(auto& btn : m_tb_tab_buttons)
    {
        btn->setVisible(mode() == COLOR_FILTER_MODE_TB);
    }
    for(auto& btn : m_children_tb_tab)
    {
        btn->setVisible(mode() == COLOR_FILTER_MODE_TB);
    }

    if (mode() == COLOR_FILTER_MODE_TB)
    {
        updateTBTabPage();
        m_history_button.setChecked(false);
        m_button_next_filter_buttons_page.setEnabled(currentTBTabPage() > 0);
        m_button_previous_filter_buttons_page.setEnabled(currentTBTabPage() < maxTBTabPages() - 1);

        m_button_next_filter_buttons_page.setVisible(m_tb_tab_buttons.length() > BUTTONS_PER_PAGE);
        m_button_previous_filter_buttons_page.setVisible(m_tb_tab_buttons.length() > BUTTONS_PER_PAGE);
    }
    else if(mode() == COLOR_FILTER_MODE_CUSTOM)
    {
        updateCustomTabPage();
        m_history_button.setChecked(false);
        m_button_next_filter_buttons_page.setEnabled(currentCustomTabPage() > 0);
        m_button_previous_filter_buttons_page.setEnabled(currentCustomTabPage() < maxCustomTabPages() - 1);

        m_button_next_filter_buttons_page.setVisible(m_custom_tab_buttons.length() > BUTTONS_PER_PAGE);
        m_button_previous_filter_buttons_page.setVisible(m_custom_tab_buttons.length() > BUTTONS_PER_PAGE);
    }
    else if(mode() == COLOR_FILTER_MODE_HISTORY)
    {
        m_history_button.setChecked(true);
        updateHistoryPage();

        m_button_next_filter_buttons_page.setEnabled(currentHistoryPage() > 0);
        m_button_previous_filter_buttons_page.setEnabled(currentHistoryPage() < maxHistoryPages() - 1);

        m_button_next_filter_buttons_page.setVisible(m_history_buttons.length() > BUTTONS_PER_PAGE);
        m_button_previous_filter_buttons_page.setVisible(m_history_buttons.length() > BUTTONS_PER_PAGE);
    }
}

void ColorFilterControl::updateTBTabPage()
{
    qDebug() << currentTBTabPage();
    updateChildrenVisibility(m_tb_tab_buttons,currentTBTabPage(), BUTTONS_PER_PAGE);
}

void ColorFilterControl::updateCustomTabPage()
{
    updateChildrenVisibility(m_custom_tab_buttons,currentCustomTabPage(),BUTTONS_PER_PAGE);
}

void ColorFilterControl::updateHistoryPage()
{
    updateChildrenVisibility(m_history_buttons,currentHistoryPage(),BUTTONS_PER_PAGE);
}

void ColorFilterControl::addHeaderButton(ColorFilterDisplayMode mode, const QString &text)
{
    auto button = MakeSharedQObject<SelectButton>(this);
    button->setText(text);
    button->setFixedSize(CFC_TAB1_GEOMETRY.size());

    m_header_buttons.append({mode, button});
    connect(button.get(), &QPushButton::clicked, this, &ColorFilterControl::onDisplayTabButtonClicked);
}

QVector<QSharedPointer<SelectButton>> ColorFilterControl::headerButtons() const
{
    QVector<QSharedPointer<SelectButton>> buttons;
    for (const auto &button: qAsConst(m_header_buttons))
        buttons.append(button.button);
    return buttons;
}

void ColorFilterControl::setupHeaderTabButtons()
{
    m_button_previous_header_buttons_page.setEnabled(currentHeaderButtonsPage() > 0);
    m_button_next_header_buttons_page.setEnabled(currentHeaderButtonsPage() < m_header_buttons_per_page - 1);

    if (mode() == COLOR_FILTER_MODE_HISTORY) {
        for (const auto &button: qAsConst(m_header_buttons))
        {
            button.button->setVisible(false);
        }
        m_button_next_header_buttons_page.setVisible(false);
        m_button_previous_header_buttons_page.setVisible(false);
    } else {
        updateChildrenVisibility(headerButtons(), currentHeaderButtonsPage(), m_header_buttons_per_page);
        m_button_next_header_buttons_page.setVisible(headerButtons().size() > m_header_buttons_per_page);
        m_button_previous_header_buttons_page.setVisible(headerButtons().size() > m_header_buttons_per_page);
    }
}

void ColorFilterControl::onDisplayTabButtonClicked()
{
    auto button = std::find_if(m_header_buttons.begin(), m_header_buttons.end(), [&](const DisplayTabButton &button) {
       return button.button.get() == sender();
    });
    if (button != m_header_buttons.end()) {
        setMode(button->mode);
        m_previous_tab = mode();
    }
}

int ColorFilterControl::maxTBTabPages() const
{
    return calulateNumberOfPages(m_tb_tab_buttons.length(), BUTTONS_PER_PAGE);
}

int ColorFilterControl::maxCustomTabPages() const
{
    return calulateNumberOfPages(m_custom_tab_buttons.length(), BUTTONS_PER_PAGE);
}

int ColorFilterControl::maxHistoryPages() const
{
    return calulateNumberOfPages(m_history_buttons.length(), BUTTONS_PER_PAGE);
}

void ColorFilterControl::onTBTabButtonClicked()
{
    auto iter = std::find(m_tb_tab_buttons.begin(), m_tb_tab_buttons.end(), sender());
    if (iter == m_tb_tab_buttons.end()) {
        return;
    }
    auto button = *iter;
    addButtonToHistory(button);

    for (const auto &b : qAsConst(m_tb_tab_buttons))
    {
        b->setChecked(b == button);
    }
}

void ColorFilterControl::onCustomTabButtonClicked()
{
    auto iter = std::find(m_custom_tab_buttons.begin(), m_custom_tab_buttons.end(), sender());
    if (iter == m_custom_tab_buttons.end()) {
        return;
    }
    auto button = *iter;
    addButtonToHistory(button);

    for (const auto &b : qAsConst(m_custom_tab_buttons))
    {
        b->setChecked(b == button);
    }
}

void ColorFilterControl::onHistoryButtonClicked()
{
    auto iter = std::find(m_history_buttons.begin(), m_history_buttons.end(), sender());
    if (iter == m_history_buttons.end()) {
        return;
    }
    auto button = *iter;

    for (const auto &b : qAsConst(m_history_buttons))
    {
        b->setChecked(b == button);
    }
}

void ColorFilterControl::addButtonToHistory(QSharedPointer<SelectButton> button)
{
    auto new_button = MakeSharedQObject<SelectButton>(this);
    new_button->setText(button->text());
    new_button->setCheckMarkVisible(true);
    new_button->setFixedSize(CFC_BUTTON1_GEOMETRY.size());
    new_button->setVisible(false);
    new_button->setBackgroundColor(button->backgroundColor());
    new_button->setSelectedBackgroundColor(button->backgroundColor());
    connect(new_button.get(),&QAbstractButton::clicked, this, &ColorFilterControl::onHistoryButtonClicked);
    m_history_buttons.push_front(new_button);
    placeChildrenIntoPanel(m_history_buttons, CFC_BUTTON1_GEOMETRY.size(), CFC_BUTTON1_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE);

    for (const auto &b : qAsConst(m_history_buttons))
    {
        b->setChecked(b == new_button);
    }
}

int ColorFilterControl::currentHeaderButtonsPage() const
{
    return m_currentHeaderButtonsPage;
}

void ColorFilterControl::setCurrentHeaderButtonsPage(int newCurrentHeaderButtonsPage)
{
    newCurrentHeaderButtonsPage = bounded(newCurrentHeaderButtonsPage, 0, calulateNumberOfPages(m_header_buttons.length(), m_header_buttons_per_page) - 1);
    if (m_currentHeaderButtonsPage == newCurrentHeaderButtonsPage)
        return;
    m_currentHeaderButtonsPage = newCurrentHeaderButtonsPage;
    emit currentHeaderButtonsPageChanged();
}
