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
    m_children_custom_tab{&m_setting_label, &m_title_button, &m_empty_button, &m_register_button, &m_delete_button},
    m_mode(COLOR_FILTER_MODE_TB),
    m_previous_tab(COLOR_FILTER_MODE_TB)
{
    m_header_buttons_per_page = 2;

    setFixedSize(CFC_SCREENSIZE);
    SetCurrentTBTabPage(0);
    SetCurrentCustomTabPage(0);
    SetCurrentHistoryPage(0);
    SetCurrentHeaderButtonsPage(0);

    m_button_next_filter_buttons_page.setEnabled(false);
    m_back_button.SetTextColor(Qt::yellow);

    m_grid.SetGridSize(QSize(6, 6));
    m_grid.SetCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
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

    AddHeaderButton(COLOR_FILTER_MODE_TB, "TB標準");
    AddHeaderButton(COLOR_FILTER_MODE_CUSTOM, "カスタム");

    PlaceChildrenIntoPanel(HeaderButtons(), CFC_TAB1_GEOMETRY.size(), CFC_TAB1_GEOMETRY.topLeft(), QSize(m_header_buttons_per_page, 1));
    m_button_next_header_buttons_page.setVisible(HeaderButtons().size() > m_header_buttons_per_page);
    m_button_previous_header_buttons_page.setVisible(HeaderButtons().size() > m_header_buttons_per_page);
    SetupHeaderTabButtons();

    connect(&m_button_previous_header_buttons_page, &QPushButton::clicked, this, [&](){
        SetCurrentHeaderButtonsPage(CurrentHeaderButtonsPage() - 1);
    });
    connect(&m_button_next_header_buttons_page, &QPushButton::clicked, this, [&](){
        SetCurrentHeaderButtonsPage(CurrentHeaderButtonsPage() + 1);
    });
    connect(this, &ColorFilterControl::CurrentHeaderButtonsPageChanged, this, &ColorFilterControl::SetupHeaderTabButtons);

    connect(&m_button_next_filter_buttons_page, &QAbstractButton::clicked, this, &ColorFilterControl::ScrollUp);
    connect(&m_button_previous_filter_buttons_page, &QAbstractButton::clicked, this, &ColorFilterControl::ScrollDown);
    connect(this, &ColorFilterControl::ModeChanged, this, &ColorFilterControl::OnModeChanged);
    connect(this, &ColorFilterControl::CurrentTBTabPageChanged, this, [&](){
        UpdateTBTabPage();
        m_button_next_filter_buttons_page.setEnabled(CurrentTBTabPage() > 0);
        m_button_previous_filter_buttons_page.setEnabled(CurrentTBTabPage() < MaxTBTabPages() - 1);
    });
    connect(this, &ColorFilterControl::CurrentCustomTabPageChanged, this, [&](){
        UpdateCustomTabPage();
        m_button_next_filter_buttons_page.setEnabled(CurrentCustomTabPage() > 0);
        m_button_previous_filter_buttons_page.setEnabled(CurrentCustomTabPage() < MaxCustomTabPages() - 1);
    });
    connect(this, &ColorFilterControl::CurrentHistoryPageChanged, this, [&](){
        UpdateHistoryPage();
        m_button_next_filter_buttons_page.setEnabled(CurrentHistoryPage() > 0);
        m_button_previous_filter_buttons_page.setEnabled(CurrentHistoryPage() < MaxHistoryPages() - 1);
    });

    connect(&m_history_button, &QAbstractButton::toggled, this, [&]() {
        if (m_history_button.isChecked())
        {
            SetMode(COLOR_FILTER_MODE_HISTORY);
            m_title_label.setText("カラーフィルタ (最近使ったもの)");
        }
        else
        {
            SetMode(m_previous_tab);
            m_title_label.setText("カラーフィルタ");
        }
    });

    connect(&m_title_button, &QAbstractButton::toggled, this, [&]() {
        if (m_title_button.isChecked())
        {
            SetCurrentFooterButtonActive("title");
            m_register_button.setChecked(false);
            m_delete_button.setChecked(false);
        }
    });
    connect(&m_register_button, &QAbstractButton::toggled, this, [&]() {
        if (m_register_button.isChecked())
        {
            SetCurrentFooterButtonActive("register");
            m_title_button.setChecked(false);
            m_delete_button.setChecked(false);
        }
    });
    connect(&m_delete_button, &QAbstractButton::toggled, this, [&]() {
        if (m_delete_button.isChecked())
        {
            SetCurrentFooterButtonActive("delete");
            m_register_button.setChecked(false);
            m_title_button.setChecked(false);
        }
    });
    connect(&m_back_button, &QAbstractButton::clicked, this, &ColorFilterControl::ReturnButtonClicked);
    connect(&m_button_next_header_buttons_page, &QAbstractButton::clicked, this, &ColorFilterControl::NextButtonClicked);
    connect(&m_button_previous_header_buttons_page, &QAbstractButton::clicked, this, &ColorFilterControl::PrevButtonClicked);
    SetupHeaderTabButtons();
    OnModeChanged();
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

        button->SetBackgroundColor(param->tb.color_filter[i].color);
        button->SetSelectedBackgroundColor(button->BackgroundColor());
        button->SetCheckMarkVisible(true);
        button->setChecked(param->tb.color_filter[i].select);

        connect(button.get(),&QAbstractButton::clicked, this, &ColorFilterControl::OnTBTabButtonClicked);

    }
    PlaceChildrenIntoPanel(m_tb_tab_buttons, CFC_BUTTON1_GEOMETRY.size(), CFC_BUTTON1_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE);

    m_custom_tab_buttons.clear();
    for (uint16_t i = 0; i < param->custom.count; i++)
    {
        auto button = MakeSharedQObject<SelectButton>(this);
        m_custom_tab_buttons.push_back(button);
        button->setFixedSize(CFC_BUTTON1_GEOMETRY.size());
        button->setText(param->custom.color_filter[i].name);
        button->SetBackgroundColor(param->custom.color_filter[i].color);
        button->SetSelectedBackgroundColor(button->BackgroundColor());
        button->SetCheckMarkVisible(true);
        button->setChecked(param->custom.color_filter[i].select);
        connect(button.get(),&QAbstractButton::clicked, this, &ColorFilterControl::OnCustomTabButtonClicked);
    }
    PlaceChildrenIntoPanel(m_custom_tab_buttons, CFC_BUTTON1_GEOMETRY.size(), CFC_BUTTON1_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE);

    m_history_buttons.clear();
    for (uint16_t i = 0; i < param->history.count; i++)
    {
        auto button = MakeSharedQObject<SelectButton>(this);
        m_history_buttons.push_back(button);
        button->setText(param->history.color_filter[i].name);
        button->SetBackgroundColor(param->history.color_filter[i].color);
        button->SetSelectedBackgroundColor(button->BackgroundColor());
        button->setFixedSize(CFC_BUTTON1_GEOMETRY.size());
        button->SetCheckMarkVisible(true);
        button->setChecked(param->history.color_filter[i].select);
        connect(button.get(),&QAbstractButton::clicked, this, &ColorFilterControl::OnHistoryButtonClicked);
    }
    PlaceChildrenIntoPanel(m_history_buttons, CFC_BUTTON1_GEOMETRY.size(), CFC_BUTTON1_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE);

    if (param->tb.select == true)
    {
        SetMode(COLOR_FILTER_MODE_TB);
    }

    if (param->custom.select == true)
    {
        SetMode(COLOR_FILTER_MODE_CUSTOM);
    }

    if (param->history.select == true)
    {
        SetMode(COLOR_FILTER_MODE_HISTORY);
    }
    OnModeChanged();
}

void ColorFilterControl::ScrollUp()
{
    if (Mode() == COLOR_FILTER_MODE_TB)
    {
        SetCurrentTBTabPage(CurrentTBTabPage()-1);
    }
    else if(Mode() == COLOR_FILTER_MODE_CUSTOM)
    {
        SetCurrentCustomTabPage(CurrentCustomTabPage()-1);
    }
    else if(Mode() == COLOR_FILTER_MODE_HISTORY)
    {
        SetCurrentHistoryPage(CurrentHistoryPage()-1);
    }
}

void ColorFilterControl::ScrollDown()
{
    if (Mode() == COLOR_FILTER_MODE_TB)
    {
        SetCurrentTBTabPage(CurrentTBTabPage()+1);
    }
    else if(Mode() == COLOR_FILTER_MODE_CUSTOM)
    {
        SetCurrentCustomTabPage(CurrentCustomTabPage()+1);
    }
    else if(Mode() == COLOR_FILTER_MODE_HISTORY)
    {
        SetCurrentHistoryPage(CurrentHistoryPage()+1);
    }
}

int ColorFilterControl::CurrentTBTabPage() const
{
    return m_current_tb_tab_page;
}

void ColorFilterControl::SetCurrentTBTabPage(int newCurrentTab1Page)
{
    if (m_current_tb_tab_page == newCurrentTab1Page)
        return;
    m_current_tb_tab_page = newCurrentTab1Page;
    emit CurrentTBTabPageChanged();
}

int ColorFilterControl::CurrentCustomTabPage() const
{
    return m_current_custom_tab_page;
}

void ColorFilterControl::SetCurrentCustomTabPage(int newCurrentTab2Page)
{
    if (m_current_custom_tab_page == newCurrentTab2Page)
        return;
    m_current_custom_tab_page = newCurrentTab2Page;
    emit CurrentCustomTabPageChanged();
}

int ColorFilterControl::CurrentHistoryPage() const
{
    return m_current_history_page;
}

void ColorFilterControl::SetCurrentHistoryPage(int newCurrentHistoryPage)
{
    if (m_current_history_page == newCurrentHistoryPage)
        return;
    m_current_history_page = newCurrentHistoryPage;
    emit CurrentHistoryPageChanged();
}

ColorFilterDisplayMode ColorFilterControl::Mode() const
{
    return m_mode;
}

void ColorFilterControl::SetMode(ColorFilterDisplayMode newMode)
{
    if (m_mode == newMode)
        return;
    m_mode = newMode;
    emit ModeChanged();
}

void ColorFilterControl::OnModeChanged()
{
    for (const auto &button: qAsConst(m_header_buttons))
    {
        button.button->setChecked(button.mode == Mode());
    }

    SetupHeaderTabButtons();
    for(auto& btn : m_custom_tab_buttons)
    {
        btn->setVisible(Mode() == COLOR_FILTER_MODE_CUSTOM);
    }

    for(auto& btn : m_children_custom_tab)
    {
        btn->setVisible(Mode() == COLOR_FILTER_MODE_CUSTOM);
    }

    for(auto& btn : m_history_buttons)
    {
        btn->setVisible(Mode() == COLOR_FILTER_MODE_HISTORY);
    }

    for(auto& btn : m_tb_tab_buttons)
    {
        btn->setVisible(Mode() == COLOR_FILTER_MODE_TB);
    }
    for(auto& btn : m_children_tb_tab)
    {
        btn->setVisible(Mode() == COLOR_FILTER_MODE_TB);
    }

    if (Mode() == COLOR_FILTER_MODE_TB)
    {
        UpdateTBTabPage();
        m_history_button.setChecked(false);
        m_button_next_filter_buttons_page.setEnabled(CurrentTBTabPage() > 0);
        m_button_previous_filter_buttons_page.setEnabled(CurrentTBTabPage() < MaxTBTabPages() - 1);

        m_button_next_filter_buttons_page.setVisible(m_tb_tab_buttons.length() > BUTTONS_PER_PAGE);
        m_button_previous_filter_buttons_page.setVisible(m_tb_tab_buttons.length() > BUTTONS_PER_PAGE);
    }
    else if(Mode() == COLOR_FILTER_MODE_CUSTOM)
    {
        UpdateCustomTabPage();
        m_history_button.setChecked(false);
        m_button_next_filter_buttons_page.setEnabled(CurrentCustomTabPage() > 0);
        m_button_previous_filter_buttons_page.setEnabled(CurrentCustomTabPage() < MaxCustomTabPages() - 1);

        m_button_next_filter_buttons_page.setVisible(m_custom_tab_buttons.length() > BUTTONS_PER_PAGE);
        m_button_previous_filter_buttons_page.setVisible(m_custom_tab_buttons.length() > BUTTONS_PER_PAGE);
    }
    else if(Mode() == COLOR_FILTER_MODE_HISTORY)
    {
        m_history_button.setChecked(true);
        UpdateHistoryPage();

        m_button_next_filter_buttons_page.setEnabled(CurrentHistoryPage() > 0);
        m_button_previous_filter_buttons_page.setEnabled(CurrentHistoryPage() < MaxHistoryPages() - 1);

        m_button_next_filter_buttons_page.setVisible(m_history_buttons.length() > BUTTONS_PER_PAGE);
        m_button_previous_filter_buttons_page.setVisible(m_history_buttons.length() > BUTTONS_PER_PAGE);
    }
}

void ColorFilterControl::UpdateTBTabPage()
{
    qDebug() << CurrentTBTabPage();
    UpdateChildrenVisibility(m_tb_tab_buttons,CurrentTBTabPage(), BUTTONS_PER_PAGE);
}

void ColorFilterControl::UpdateCustomTabPage()
{
    UpdateChildrenVisibility(m_custom_tab_buttons,CurrentCustomTabPage(),BUTTONS_PER_PAGE);
}

void ColorFilterControl::UpdateHistoryPage()
{
    UpdateChildrenVisibility(m_history_buttons,CurrentHistoryPage(),BUTTONS_PER_PAGE);
}

void ColorFilterControl::AddHeaderButton(ColorFilterDisplayMode mode, const QString &text)
{
    auto button = MakeSharedQObject<SelectButton>(this);
    button->setText(text);
    button->setFixedSize(CFC_TAB1_GEOMETRY.size());

    m_header_buttons.append({mode, button});
    connect(button.get(), &QPushButton::clicked, this, &ColorFilterControl::OnDisplayTabButtonClicked);
}

QVector<QSharedPointer<SelectButton>> ColorFilterControl::HeaderButtons() const
{
    QVector<QSharedPointer<SelectButton>> buttons;
    for (const auto &button: qAsConst(m_header_buttons))
        buttons.append(button.button);
    return buttons;
}

void ColorFilterControl::SetupHeaderTabButtons()
{
    m_button_previous_header_buttons_page.setEnabled(CurrentHeaderButtonsPage() > 0);
    m_button_next_header_buttons_page.setEnabled(CurrentHeaderButtonsPage() < m_header_buttons_per_page - 1);

    if (Mode() == COLOR_FILTER_MODE_HISTORY) {
        for (const auto &button: qAsConst(m_header_buttons))
        {
            button.button->setVisible(false);
        }
        m_button_next_header_buttons_page.setVisible(false);
        m_button_previous_header_buttons_page.setVisible(false);
    } else {
        UpdateChildrenVisibility(HeaderButtons(), CurrentHeaderButtonsPage(), m_header_buttons_per_page);
        m_button_next_header_buttons_page.setVisible(HeaderButtons().size() > m_header_buttons_per_page);
        m_button_previous_header_buttons_page.setVisible(HeaderButtons().size() > m_header_buttons_per_page);
    }
}

void ColorFilterControl::OnDisplayTabButtonClicked()
{
    auto button = std::find_if(m_header_buttons.begin(), m_header_buttons.end(), [&](const DisplayTabButton &button) {
       return button.button.get() == sender();
    });
    if (button != m_header_buttons.end()) {
        SetMode(button->mode);
        m_previous_tab = Mode();
    }
}

const QString &ColorFilterControl::CurrentFooterButtonActive() const
{
    return m_current_footer_button_active;
}

void ColorFilterControl::SetCurrentFooterButtonActive(const QString &newCurrentFooterButtonActive)
{
    m_current_footer_button_active = newCurrentFooterButtonActive;
}

int ColorFilterControl::MaxTBTabPages() const
{
    return CalulateNumberOfPages(m_tb_tab_buttons.length(), BUTTONS_PER_PAGE);
}

int ColorFilterControl::MaxCustomTabPages() const
{
    return CalulateNumberOfPages(m_custom_tab_buttons.length(), BUTTONS_PER_PAGE);
}

int ColorFilterControl::MaxHistoryPages() const
{
    return CalulateNumberOfPages(m_history_buttons.length(), BUTTONS_PER_PAGE);
}

void ColorFilterControl::OnTBTabButtonClicked()
{
    auto iter = std::find(m_tb_tab_buttons.begin(), m_tb_tab_buttons.end(), sender());
    if (iter == m_tb_tab_buttons.end()) {
        return;
    }
    auto button = *iter;
    AddButtonToHistory(button);
    SetCurrentTBTabButtonActive({button->text(),button->BackgroundColor()});
    for (const auto &b : qAsConst(m_tb_tab_buttons))
    {
        b->setChecked(b == button);
    }
}

void ColorFilterControl::OnCustomTabButtonClicked()
{
    auto iter = std::find(m_custom_tab_buttons.begin(), m_custom_tab_buttons.end(), sender());
    if (iter == m_custom_tab_buttons.end()) {
        return;
    }
    auto button = *iter;
    AddButtonToHistory(button);
    SetCurrentCustomTabButtonActive({button->text(),button->BackgroundColor()});
    for (const auto &b : qAsConst(m_custom_tab_buttons))
    {
        b->setChecked(b == button);
    }
}

void ColorFilterControl::OnHistoryButtonClicked()
{
    auto iter = std::find(m_history_buttons.begin(), m_history_buttons.end(), sender());
    if (iter == m_history_buttons.end()) {
        return;
    }
    auto button = *iter;
    SetCurrentHistoryButtonActive({button->text(),button->BackgroundColor()});
    for (const auto &b : qAsConst(m_history_buttons))
    {
        b->setChecked(b == button);
    }
}

void ColorFilterControl::AddButtonToHistory(QSharedPointer<SelectButton> button)
{
    auto new_button = MakeSharedQObject<SelectButton>(this);
    new_button->setText(button->text());
    new_button->SetCheckMarkVisible(true);
    new_button->setFixedSize(CFC_BUTTON1_GEOMETRY.size());
    new_button->setVisible(false);
    new_button->SetBackgroundColor(button->BackgroundColor());
    new_button->SetSelectedBackgroundColor(button->BackgroundColor());
    connect(new_button.get(),&QAbstractButton::clicked, this, &ColorFilterControl::OnHistoryButtonClicked);
    m_history_buttons.push_front(new_button);
    PlaceChildrenIntoPanel(m_history_buttons, CFC_BUTTON1_GEOMETRY.size(), CFC_BUTTON1_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE);

    for (const auto &b : qAsConst(m_history_buttons))
    {
        b->setChecked(b == new_button);
    }
}

int ColorFilterControl::CurrentHeaderButtonsPage() const
{
    return m_current_header_buttons_page;
}

void ColorFilterControl::SetCurrentHeaderButtonsPage(int newCurrentHeaderButtonsPage)
{
    newCurrentHeaderButtonsPage = qBound(newCurrentHeaderButtonsPage, 0, CalulateNumberOfPages(m_header_buttons.length(), m_header_buttons_per_page) - 1);
    if (m_current_header_buttons_page == newCurrentHeaderButtonsPage)
        return;
    m_current_header_buttons_page = newCurrentHeaderButtonsPage;
    emit CurrentHeaderButtonsPageChanged();
}

const ColorFilterButton &ColorFilterControl::CurrentTBTabButtonActive() const
{
    return m_current_tb_tab_button_active;
}

void ColorFilterControl::SetCurrentTBTabButtonActive(const ColorFilterButton &newCurrentTBTabButtonActive)
{
    if (m_current_tb_tab_button_active == newCurrentTBTabButtonActive)
        return;
    m_current_tb_tab_button_active = newCurrentTBTabButtonActive;
    emit CurrentTBTabButtonActiveChanged();
}

const ColorFilterButton &ColorFilterControl::CurrentCustomTabButtonActive() const
{
    return m_current_custom_tab_button_active;
}

void ColorFilterControl::SetCurrentCustomTabButtonActive(const ColorFilterButton &newCurrentCustomTabButtonActive)
{
    if (m_current_custom_tab_button_active == newCurrentCustomTabButtonActive)
        return;
    m_current_custom_tab_button_active = newCurrentCustomTabButtonActive;
    emit CurrentCustomTabButtonActiveChanged();
}

const ColorFilterButton &ColorFilterControl::CurrentHistoryButtonActive() const
{
    return m_current_history_button_active;
}

void ColorFilterControl::SetCurrentHistoryButtonActive(const ColorFilterButton &newCurrentHistoryButtonActive)
{
    if (m_current_history_button_active == newCurrentHistoryButtonActive)
        return;
    m_current_history_button_active = newCurrentHistoryButtonActive;
    emit CurrentHistoryButtonActiveChanged();
}
