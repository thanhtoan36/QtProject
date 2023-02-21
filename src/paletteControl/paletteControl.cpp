#include "paletteControl/paletteControl.hpp"
#include "paletteControl/paletteControl_define.hpp"
#include "utility.h"

#define BUTTON_SIZE PC_BUTTON1_GEOMETRY.size()

PaletteControl::PaletteControl(QWidget *parent) : PanelControlBase(parent),
    m_grid(this),
    m_title_label(this),
    m_button_previous_mode_page(this),
    m_button_next_mode_page(this),
    m_button_previous_palette_page(this),
    m_button_next_palette_page(this),
    m_revert_button(this)
{
    setFixedSize(PC_SCREEN_SIZE);

    m_mode_button_grid_size = QSize(4, 1);
    m_palette_button_grid_size = QSize(4, 3);

    m_revert_button.setTextColor(Qt::yellow);

    SetButtonStartPoint(PC_BUTTON_TOP_LEFT);
    SetMenuStartPoint(PC_MENU_TOP_LEFT);

    m_grid.setGridSize(QSize(4, 6));
    m_grid.setCellSize(BUTTON_SIZE);
    m_grid.move(0, 32);

    m_title_label.setGeometry(PC_TITLE_GEOMETRY);
    m_title_label.setObjectName("title_label");
    m_title_label.setText("パレット");

    m_button_previous_palette_page.setGeometry(PC_UP_GEOMETRY);
    m_button_previous_palette_page.setText("▲");
    m_button_previous_palette_page.setVisible(false);

    m_button_next_palette_page.setGeometry(PC_DOWN_GEOMETRY);
    m_button_next_palette_page.setText("▼");
    m_button_next_palette_page.setVisible(false);

    m_button_next_mode_page.setGeometry(PC_NEXT_GEOMETRY);
    m_button_next_mode_page.setText("▶");
    m_button_next_mode_page.setVisible(false);

    m_button_previous_mode_page.setGeometry(PC_PREV_GEOMETRY);
    m_button_previous_mode_page.setText("◀");
    m_button_previous_mode_page.setVisible(false);

    m_revert_button.setGeometry(PC_RETURN_GEOMETRY);
    m_revert_button.setText("戻す");

    connect(&m_revert_button, &QPushButton::clicked, this, &PaletteControl::RevertButtonClicked);

    connect(&m_button_previous_palette_page, &QPushButton::clicked, this, [&](){
        SetCurrentPalettePage(CurrentPalettePage() - 1);
        emit PrevPalettePageClicked();
    });
    connect(&m_button_next_palette_page, &QPushButton::clicked, this, [&](){
        SetCurrentPalettePage(CurrentPalettePage() + 1);
        emit NextPalettePageClicked();
    });
    connect(&m_button_previous_mode_page, &QPushButton::clicked, this, [&](){
        SetCurrentModePage(CurrentModePage() - 1);
        emit PrevModePageClicked();
    });
    connect(&m_button_next_mode_page, &QPushButton::clicked, this, [&](){
        SetCurrentModePage(CurrentModePage() + 1);
        emit NextModePageClicked();
    });

    connect(this, &PaletteControl::CurrentModePageChanged, this, &PaletteControl::UpdateModePages);
    connect(this, &PaletteControl::CurrentPalettePageChanged, this, &PaletteControl::UpdatePalettePages);
    connect(this, &PaletteControl::TypeChanged, this, &PaletteControl::OnTypeChanged);
}

void PaletteControl::SetDispParamData(PALETTE_DISP_PARAM *param)
{
    Q_ASSERT(param);
    m_mode_buttons.clear();
    m_palette_buttons.clear();

    m_mode_names.clear();
    m_palette_names.clear();

    QString selected_mode = "";
    QString selected_palette = "";

    for (int i = 0; i < param->count; i++)
    {
        auto menu_button = MakeSharedQObject<SelectButton>(this);
        menu_button->setFixedSize(PC_BUTTON_SIZE);
        menu_button->setChecked(param->data[i].select);

        if (param->data[i].select)
        {
            selected_mode = param->data[i].name;
        }

        if (param->data[i].image.isNull())
        {
            menu_button->setText(param->data[i].name);
        }
        else
        {
            QIcon icon(QPixmap::fromImage(param->data[i].image));
            menu_button->setIconSize(PC_BUTTON_SIZE - QSize(6, 6));
            menu_button->setIcon(icon);
        }

        connect(menu_button.get(),&QAbstractButton::clicked, this, &PaletteControl::OnModeButtonClicked);
        m_mode_buttons.push_back(menu_button);
        m_mode_names.push_back(param->data[i].name);

        QVector<QSharedPointer<SelectButton>> palette_button_list;
        QStringList palette_name_list;
        for(int j = 0; j < param->data[i].count;j++)
        {
            auto palette_button = MakeSharedQObject<SelectButton>(this);
            palette_button->setFixedSize(PC_BUTTON_SIZE);

            if (param->data[i].palette[j].image.isNull())
            {
                 palette_button->setText(param->data[i].palette[j].name);
            }
            else
            {
                 QIcon icon(QPixmap::fromImage(param->data[i].palette[j].image));
                 palette_button->setIconSize(PC_BUTTON_SIZE - QSize(6, 6));
                 palette_button->setIcon(icon);
            }

            palette_button->setChecked(param->data[i].palette[j].select);
            if (param->data[i].palette[j].select)
            {
                selected_palette = param->data[i].palette[j].name;
            }
            palette_button->setVisible(false);

            connect(palette_button.get(),&QAbstractButton::clicked, this, &PaletteControl::OnPaletteButtonClicked);
            palette_button_list.push_back(palette_button);
            palette_name_list.push_back(param->data[i].palette[j].name);
        }
        m_palette_buttons.push_back(palette_button_list);
        m_palette_names.push_back(palette_name_list);
    }

    SetType(param->type);
    SetCurrentModePage(0);
    SetCurrentPalettePage(0);
    UpdateModePages();

    SetSelectedMode(selected_mode);
    SetSelectedPalette(selected_palette);
}

void PaletteControl::OnModeButtonClicked()
{
    for (auto &button: m_mode_buttons) {
        button->setChecked(button == sender());
    }

    int index = std::distance(m_mode_buttons.begin(), std::find(m_mode_buttons.begin(), m_mode_buttons.end(), sender()));
    SetSelectedMode(m_mode_names.at(index));

    SetCurrentPalettePage(0);
    UpdateModePages();
}

void PaletteControl::OnPaletteButtonClicked()
{
    UpdatePalettePages();
    auto mode_index = SelectedModeIndex();
    if (mode_index == -1)
        return;

    auto &group = m_palette_buttons.at(mode_index);
    for (auto &button : group) {
        button->setChecked(button == sender());
    }

    int palette_index = std::distance(group.begin(), std::find(group.begin(), group.end(), sender()));
    SetSelectedMode(m_mode_names.at(mode_index));
    SetSelectedPalette(m_palette_names.at(mode_index).at(palette_index));
}

void PaletteControl::UpdateModePages()
{
    UpdateChildrenVisibility(m_mode_buttons, CurrentModePage(), ModeButtonsPerPage());
    placeChildrenIntoPanel(m_mode_buttons, PC_BUTTON_SIZE, ModeStartPoint(), m_mode_button_grid_size);

    m_button_previous_mode_page.setVisible(MaxModePages() > 1);
    m_button_next_mode_page.setVisible(MaxModePages() > 1);
    m_button_previous_mode_page.setEnabled(CurrentModePage() > 0);
    m_button_next_mode_page.setEnabled(CurrentModePage() < MaxModePages() - 1);

    UpdatePalettePages();
}

void PaletteControl::UpdatePalettePages()
{
    m_button_next_palette_page.setVisible(false);
    m_button_previous_palette_page.setVisible(false);

    for (auto &group : m_palette_buttons)
    {
        for (auto &palette: group)
        {
            palette->setVisible(false);
        }
    }

    auto mode_index = SelectedModeIndex();
    if (mode_index == -1)
        return;

    m_button_previous_palette_page.setVisible(MaxPalettePages() > 1);
    m_button_next_palette_page.setVisible(MaxPalettePages() > 1);
    m_button_previous_palette_page.setEnabled(CurrentPalettePage() > 0);
    m_button_next_palette_page.setEnabled(CurrentPalettePage() < MaxPalettePages() - 1);

    auto &group = m_palette_buttons.at(mode_index);

    UpdateChildrenVisibility(group, CurrentPalettePage(), PaletteButtonsPerPage());
    placeChildrenIntoPanel(group, PC_BUTTON_SIZE, ButtonStartPoint(), m_palette_button_grid_size);
}

QPoint PaletteControl::ModeStartPoint() const
{
    return m_menu_start_point;
}

void PaletteControl::SetMenuStartPoint(QPoint newMenuStartPoint)
{
    m_menu_start_point = newMenuStartPoint;
}

int PaletteControl::MaxModePages() const
{
    return calulateNumberOfPages(m_mode_buttons.size(), ModeButtonsPerPage());
}

int PaletteControl::MaxPalettePages() const
{
    int modeIndex = SelectedModeIndex();
    if (modeIndex == -1)
        return 0;
    auto &group = m_palette_buttons.at(modeIndex);
    return calulateNumberOfPages(group.size(), PaletteButtonsPerPage());
}

int PaletteControl::ModeButtonsPerPage() const
{
    return m_mode_button_grid_size.width() * m_mode_button_grid_size.height();
}

int PaletteControl::PaletteButtonsPerPage() const
{
    return m_palette_button_grid_size.width() * m_palette_button_grid_size.height();
}

int PaletteControl::SelectedModeIndex() const
{
    const auto iter = std::find_if(m_mode_buttons.cbegin(), m_mode_buttons.cend(), [](const QSharedPointer<SelectButton> &b) {
        return b->isChecked();
    });
    if (iter == m_mode_buttons.cend())
    {
        return -1;
    }
    return std::distance(m_mode_buttons.cbegin(), iter);
}

void PaletteControl::OnTypeChanged()
{
    switch (Type()) {
        case PALETTE_TYPE_GOBO:
            m_title_label.setText("ゴボ");
            m_mode_button_grid_size = QSize(4, 1);
            m_palette_button_grid_size = QSize(4, 3);
            SetButtonStartPoint(PC_BUTTON_TOP_LEFT);
            break;
        case PALETTE_BEAM_SHUTTER:
            m_title_label.setText("モード");
            m_mode_button_grid_size = QSize(4, 1);
            m_palette_button_grid_size = QSize(4, 3);
            SetButtonStartPoint(PC_BUTTON_TOP_LEFT);
            break;
        case PALETTE_TYPE_CONTROL:
            m_title_label.setText("モード");
            m_mode_button_grid_size = QSize(4, 0);
            m_palette_button_grid_size = QSize(4, 4);
            SetButtonStartPoint(PC_MENU_TOP_LEFT);
            break;
        default:
            break;
    }
    UpdateModePages();
}

QPoint PaletteControl::ButtonStartPoint() const
{
    return m_button_start_point;
}

void PaletteControl::SetButtonStartPoint(QPoint newButtonStartPoint)
{
    m_button_start_point = newButtonStartPoint;
}

int PaletteControl::CurrentModePage() const
{
    return m_current_mode_page;
}

void PaletteControl::SetCurrentModePage(int value)
{
    value = qBound(value, 0, MaxModePages() - 1);
    if (m_current_mode_page == value)
        return;
    m_current_mode_page = value;
    emit CurrentModePageChanged();
}

int PaletteControl::CurrentPalettePage() const
{
    return m_current_palette_page;
}

void PaletteControl::SetCurrentPalettePage(int value)
{
    value = qBound(value, 0, MaxPalettePages() - 1);
    if (m_current_palette_page == value)
        return;
    m_current_palette_page = value;
    emit CurrentPalettePageChanged();
}

PaletteType PaletteControl::Type() const
{
    return m_type;
}

void PaletteControl::SetType(PaletteType value)
{
    if (m_type == value)
        return;
    m_type = value;
    emit TypeChanged();
}

QString PaletteControl::SelectedPalette() const
{
    return m_selected_palette;
}

void PaletteControl::SetSelectedPalette(const QString &value)
{
    if (m_selected_palette == value)
        return;
    m_selected_palette = value;
    emit SelectedPaletteChanged();
}

QString PaletteControl::SelectedMode() const
{
    return m_selected_mode;
}

void PaletteControl::SetSelectedMode(const QString &value)
{
    if (m_selected_mode == value)
        return;
    m_selected_mode = value;
    emit SelectedModeChanged();
}
