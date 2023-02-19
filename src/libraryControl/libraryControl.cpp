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

    m_mode_buttons_grid_size = QSize(4, 2);
    m_lib_buttons_grid_size = QSize(4, 3);

    setLibStartPoint(LC_LIB_BUTTON_TOP_LEFT);
    setModeStartPoint(LC_MODE_TOP_LEFT);

    m_grid.setGridSize(QSize(4, 6));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 32);

    m_title_label.setGeometry(LC_TITLE_GEOMETRY);
    m_title_label.setObjectName("title_label");
    m_title_label.setText("ライブラリ");

    m_history_button.setGeometry(LC_HISTORY_GEOMETRY);
    m_history_button.setText("最近使った\nもの");

    m_up_button.setGeometry(LC_UP_GEOMETRY);
    m_up_button.setText("▲");
    m_up_button.setVisible(false);

    m_down_button.setGeometry(LC_DOWN_GEOMETRY);
    m_down_button.setText("▼");
    m_down_button.setVisible(false);

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

    connect(&m_up_button, &QPushButton::clicked, this, [&](){
        if (m_history_button.isChecked()) {
            setCurrentHistoryPage(currentHistoryPage() - 1);
        } else {
            setCurrentGroupPage(currentGroupPage() - 1);
        }
    });
    connect(&m_down_button, &QPushButton::clicked, this, [&](){
        if (m_history_button.isChecked()) {
            setCurrentHistoryPage(currentHistoryPage() + 1);
        } else {
            setCurrentGroupPage(currentGroupPage() + 1);
        }
    });

    connect(&m_history_button, &QPushButton::toggled, this, [&](){
        updateGroupTab();
        updateHistoryTab();
    });

    connect(this, &LibraryControl::currentGroupPageChanged, this, &LibraryControl::updateGroupTab);
    connect(this, &LibraryControl::currentHistoryPageChanged, this, &LibraryControl::updateHistoryTab);

    connect(&m_title_button, &QPushButton::clicked, this, &LibraryControl::onButtonTitleClicked);
    connect(&m_register_button, &QPushButton::clicked, this, &LibraryControl::onButtonRegisterClicked);
    connect(&m_delete_button, &QPushButton::clicked, this, &LibraryControl::onButtonDeleteClicked);
}

void LibraryControl::SetDispParamData(LIBRARY_DISP_PARAM *param)
{
    Q_ASSERT(param);

    m_group_lib_buttons.clear();
    m_history_lib_buttons.clear();
    m_group_mode_buttons.clear();
    m_history_mode_buttons.clear();

    setCurrentGroupPage(0);
    setCurrentHistoryPage(0);

    setSelectedGroupMode(QString());
    setSelectedHistoryMode(QString());

    m_history_button.setChecked(false);

    QStringList group_modes, history_modes;
    group_modes.append("ALL");
    history_modes.append("ALL");

    // group lib buttons
    for (int i = 0; i < param->group.count; ++i) {
        const auto data = param->group.library_param[i];

        LibraryButton button;
        button.mode = data.mode;
        button.widget = MakeSharedQObject<TitleSelectButton>(this);
        button.widget->setVisible(false);
        button.widget->setFixedSize(LC_BUTTON_SIZE);
        button.widget->setText(data.library_no);
        button.widget->setTitle(data.title);
        button.widget->setChecked(data.select);
        connect(button.widget.get(), &TitleSelectButton::clicked, this, &LibraryControl::onGroupLibButtonClicked);

        if (!group_modes.contains(data.mode)) {
            group_modes.append(data.mode);
        }

        m_group_lib_buttons.append(button);
    }

    // history lib buttons
    for (int i = 0; i < param->history.count; ++i) {
        const auto data = param->history.library_param[i];

        LibraryButton button;
        button.mode = data.mode;
        button.widget = MakeSharedQObject<TitleSelectButton>(this);
        button.widget->setVisible(false);
        button.widget->setFixedSize(LC_BUTTON_SIZE);
        button.widget->setText(data.library_no);
        button.widget->setTitle(data.title);
        button.widget->setChecked(data.select);
        connect(button.widget.get(), &TitleSelectButton::clicked, this, &LibraryControl::onHistoryLibButtonClicked);

        if (!history_modes.contains(data.mode)) {
            history_modes.append(data.mode);
        }

        m_history_lib_buttons.append(button);
    }

    // group modes
    for (const auto &mode : group_modes) {
        auto button = MakeSharedQObject<SelectButton>(this);
        button->setFixedSize(LC_BUTTON_SIZE);
        button->setText(mode);
        button->setVisible(false);
        button->setChecked(mode == "ALL");

        connect(button.get(), &SelectButton::clicked, this, &LibraryControl::onGroupModeButtonClicked);
        m_group_mode_buttons.append(button);
    }

    // history modes
    for (const auto &mode : history_modes) {
        auto button = MakeSharedQObject<SelectButton>(this);
        button->setFixedSize(LC_BUTTON_SIZE);
        button->setText(mode);
        button->setVisible(false);
        button->setChecked(mode == "ALL");

        connect(button.get(), &SelectButton::clicked, this, &LibraryControl::onHistoryModeButtonClicked);
        m_history_mode_buttons.append(button);
    }

    refilterGroupButtonsByMode();
    refilterHistoryButtonsByMode();

    updateGroupTab();
    updateHistoryTab();
}

void LibraryControl::addButtonToHistory(const LibraryControl::LibraryButton &button)
{
    const auto mode = button.mode;

    auto widget = MakeSharedQObject<TitleSelectButton>(this);
    widget->setText(button.widget->text());
    widget->setCheckMarkVisible(true);
    widget->setFixedSize(LC_BUTTON1_GEOMETRY.size());
    widget->setVisible(false);
    widget->setBackgroundColor(button.widget->backgroundColor());
    widget->setSelectedBackgroundColor(button.widget->backgroundColor());
    widget->setTitle(button.widget->title());

    auto iter = std::find_if(m_history_mode_buttons.begin(), m_history_mode_buttons.end(), [mode](const QSharedPointer<SelectButton> &b) {
        return b->text() == mode;
    });

    // Add new mode if missing
    if (iter == m_history_mode_buttons.end()) {
        auto new_mode_button = MakeSharedQObject<SelectButton>(this);
        new_mode_button->setFixedSize(LC_BUTTON_SIZE);
        new_mode_button->setText(mode);
        new_mode_button->setVisible(false);

        connect(new_mode_button.get(), &SelectButton::clicked, this, &LibraryControl::onHistoryModeButtonClicked);
        m_history_mode_buttons.append(new_mode_button);
    }

    connect(widget.get(), &TitleSelectButton::clicked, this, &LibraryControl::onHistoryLibButtonClicked);

    m_history_lib_buttons.push_front(LibraryControl::LibraryButton{ mode, widget });
    refilterHistoryButtonsByMode();
    updateHistoryTab();
}

void LibraryControl::onButtonTitleClicked()
{
    m_register_button.setChecked(false);
    m_delete_button.setChecked(false);
}

void LibraryControl::onButtonRegisterClicked()
{
    m_title_button.setChecked(false);
    m_delete_button.setChecked(false);
}

void LibraryControl::onButtonDeleteClicked()
{
    m_register_button.setChecked(false);
    m_title_button.setChecked(false);
}

void LibraryControl::onGroupModeButtonClicked()
{
    const auto modeButton = ((SelectButton*)sender());
    for (const auto &b : qAsConst(m_group_mode_buttons)) {
        b->setChecked(b == modeButton);
    }

    const auto mode = modeButton->text();
    if (mode == "ALL") {
        setSelectedGroupMode(QString());
    } else {
        setSelectedGroupMode(mode);
    }

    setCurrentGroupPage(0);
    refilterGroupButtonsByMode();

    updateGroupTab();
}

void LibraryControl::onHistoryModeButtonClicked()
{
    const auto modeButton = ((SelectButton*)sender());
    for (const auto &b : qAsConst(m_history_mode_buttons)) {
        b->setChecked(b == modeButton);
    }

    const auto mode = modeButton->text();
    if (mode == "ALL") {
        setSelectedHistoryMode(QString());
    } else {
        setSelectedHistoryMode(mode);
    }

    setCurrentHistoryPage(0);
    refilterHistoryButtonsByMode();

    updateHistoryTab();
}

void LibraryControl::onGroupLibButtonClicked()
{
    const auto lib_button = ((TitleSelectButton*)sender());
    for (const auto &b : qAsConst(m_group_lib_buttons)) {
        if (b.widget == lib_button) {
            addButtonToHistory(b);
            b.widget->setChecked(true);
        } else {
            b.widget->setChecked(false);
        }
    }
}

void LibraryControl::onHistoryLibButtonClicked()
{
    const auto lib_button = ((TitleSelectButton*)sender());
    for (const auto &b : qAsConst(m_history_lib_buttons)) {
        b.widget->setChecked(b.widget == lib_button);
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

int LibraryControl::maxGroupPages() const
{
    return calulateNumberOfPages(m_current_group_lib_buttons.size(), libraryButtonsPerPage());
}

int LibraryControl::maxHistoryPages() const
{
    return calulateNumberOfPages(m_current_history_lib_buttons.size(), libraryButtonsPerPage());
}

int LibraryControl::modeButtonsPerPage() const
{
    return m_mode_buttons_grid_size.width() * m_mode_buttons_grid_size.height();
}

int LibraryControl::libraryButtonsPerPage() const
{
    return m_lib_buttons_grid_size.width() * m_lib_buttons_grid_size.height();
}

void LibraryControl::refilterGroupButtonsByMode()
{
    m_current_group_lib_buttons = widgetList(filter(m_group_lib_buttons, selectedGroupMode()));
}

void LibraryControl::refilterHistoryButtonsByMode()
{
    m_current_history_lib_buttons = widgetList(filter(m_history_lib_buttons, selectedHistoryMode()));
}

QVector<LibraryControl::LibraryButton> LibraryControl::filter(const QVector<LibraryControl::LibraryButton> &buttons, const QString &mode)
{
    if (mode.isEmpty())
        return buttons;
    QVector<LibraryControl::LibraryButton> result;
    std::copy_if(buttons.begin(), buttons.end(), std::back_inserter(result), [mode](const LibraryControl::LibraryButton &b) {
        return b.mode == mode;
    });
    return result;
}

QVector<QSharedPointer<TitleSelectButton> > LibraryControl::widgetList(const QVector<LibraryButton> &buttons)
{
    QVector<QSharedPointer<TitleSelectButton>> result;
    for (const auto &b : buttons) {
        result.append(b.widget);
    }
    return result;
}

void LibraryControl::updateGroupTab()
{
    for (const auto &b : qAsConst(m_group_mode_buttons))
    {
        b->setVisible(!m_history_button.isChecked());
    }
    for (const auto &b : qAsConst(m_group_lib_buttons))
    {
        b.widget->setVisible(false);
    }

    placeChildrenIntoPanel(m_group_mode_buttons, LC_BUTTON_SIZE, modeStartPoint(), m_mode_buttons_grid_size);
    placeChildrenIntoPanel(m_current_group_lib_buttons, LC_BUTTON_SIZE, libStartPoint(), m_lib_buttons_grid_size);

    if (!m_history_button.isChecked()) {
        updateChildrenVisibility(m_current_group_lib_buttons, currentGroupPage(), libraryButtonsPerPage());
        m_up_button.setVisible(maxGroupPages() > 1);
        m_down_button.setVisible(maxGroupPages() > 1);
        m_up_button.setEnabled(currentGroupPage() > 0);
        m_down_button.setEnabled(currentGroupPage() < maxGroupPages() - 1);
    }
}

void LibraryControl::updateHistoryTab()
{
    for (const auto &b : qAsConst(m_history_mode_buttons))
    {
        b->setVisible(m_history_button.isChecked());
    }
    for (const auto &b : qAsConst(m_history_lib_buttons))
    {
        b.widget->setVisible(false);
    }

    placeChildrenIntoPanel(m_history_mode_buttons, LC_BUTTON_SIZE, modeStartPoint(), m_mode_buttons_grid_size);
    placeChildrenIntoPanel(m_current_history_lib_buttons, LC_BUTTON_SIZE, libStartPoint(), m_lib_buttons_grid_size);
    if (m_history_button.isChecked()) {
        updateChildrenVisibility(m_current_history_lib_buttons, currentHistoryPage(), libraryButtonsPerPage());
        m_up_button.setVisible(maxHistoryPages() > 1);
        m_down_button.setVisible(maxHistoryPages() > 1);
        m_up_button.setEnabled(currentHistoryPage() > 0);
        m_down_button.setEnabled(currentHistoryPage() < maxHistoryPages() - 1);
    }
}

QPoint LibraryControl::libStartPoint() const
{
    return m_libStartPoint;
}

void LibraryControl::setLibStartPoint(QPoint newLibStartPoint)
{
    m_libStartPoint = newLibStartPoint;
}


int LibraryControl::currentGroupPage() const
{
    return m_currentGroupPage;
}

void LibraryControl::setCurrentGroupPage(int newCurrentGroupPage)
{
    newCurrentGroupPage = qBound(newCurrentGroupPage, 0, maxGroupPages());
    if (m_currentGroupPage == newCurrentGroupPage)
        return;
    m_currentGroupPage = newCurrentGroupPage;
    emit currentGroupPageChanged();
}

int LibraryControl::currentHistoryPage() const
{
    return m_currentHistoryPage;
}

void LibraryControl::setCurrentHistoryPage(int newCurrentHistoryPage)
{
    newCurrentHistoryPage = qBound(newCurrentHistoryPage, 0, maxHistoryPages());
    if (m_currentHistoryPage == newCurrentHistoryPage)
        return;
    m_currentHistoryPage = newCurrentHistoryPage;
    emit currentHistoryPageChanged();
}

QString LibraryControl::selectedGroupMode() const
{
    return m_selectedGroupMode;
}

void LibraryControl::setSelectedGroupMode(const QString &newSelectedGroupMode)
{
    if (m_selectedGroupMode == newSelectedGroupMode)
        return;
    m_selectedGroupMode = newSelectedGroupMode;
    emit selectedGroupModeChanged();
}

QString LibraryControl::selectedHistoryMode() const
{
    return m_selectedHistoryMode;
}

void LibraryControl::setSelectedHistoryMode(const QString &newSelectedHistoryMode)
{
    if (m_selectedHistoryMode == newSelectedHistoryMode)
        return;
    m_selectedHistoryMode = newSelectedHistoryMode;
    emit selectedHistoryModeChanged();
}
