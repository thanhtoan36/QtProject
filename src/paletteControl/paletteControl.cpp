#include "paletteControl/paletteControl.hpp"
#include "paletteControl/paletteControl_define.hpp"
#include "utility.h"


#define BASE_BUTTON_WIDTH PC_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT PC_BUTTON1_GEOMETRY.height()

PaletteControl::PaletteControl(QWidget *parent) : PanelControlBase(parent),
    m_grid(this),
    m_title_label(this),
    m_button_previous_mode_page(this),
    m_button_next_mode_page(this),
    m_button_previous_palette_page(this),
    m_button_next_palette_page(this),
    m_return_button(this)
{
    setFixedSize(PC_SCREEN_SIZE);

    m_mode_button_grid_size = QSize(4, 1);
    m_palette_button_grid_size = QSize(4, 3);

    m_return_button.setTextColor(Qt::yellow);

    setButtonStartPoint(PC_BUTTON_TOP_LEFT);
    setMenuStartPoint(PC_MENU_TOP_LEFT);

    m_grid.setGridSize(QSize(4, 6));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
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

    m_return_button.setGeometry(PC_RETURN_GEOMETRY);
    m_return_button.setText("戻す");

    connect(&m_button_previous_palette_page, &QPushButton::clicked, this, [&](){
        setCurrentPalettePage(currentPalettePage() - 1);
        emit PrevPalettePageClicked();
    });
    connect(&m_button_next_palette_page, &QPushButton::clicked, this, [&](){
        setCurrentPalettePage(currentPalettePage() + 1);
        emit NextPalettePageClicked();
    });
    connect(&m_button_previous_mode_page, &QPushButton::clicked, this, [&](){
        setCurrentModePage(currentModePage() - 1);
        emit PrevModePageClicked();
    });
    connect(&m_button_next_mode_page, &QPushButton::clicked, this, [&](){
        setCurrentModePage(currentModePage() + 1);
        emit NextModePageClicked();
    });

    connect(this, &PaletteControl::currentModePageChanged, this, &PaletteControl::updateModePages);
    connect(this, &PaletteControl::currentPalettePageChanged, this, &PaletteControl::updatePalettePages);
    connect(this, &PaletteControl::typeChanged, this, &PaletteControl::onTypeChanged);
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

        connect(menu_button.get(),&QAbstractButton::clicked, this, &PaletteControl::onModeButtonClicked);
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

            connect(palette_button.get(),&QAbstractButton::clicked, this, &PaletteControl::onPaletteButtonClicked);
            palette_button_list.push_back(palette_button);
            palette_name_list.push_back(param->data[i].palette[j].name);
        }
        m_palette_buttons.push_back(palette_button_list);
        m_palette_names.push_back(palette_name_list);
    }

    setType(param->type);
    setCurrentModePage(0);
    setCurrentPalettePage(0);
    updateModePages();

    setSelectedMode(selected_mode);
    setSelectedPalette(selected_palette);
}

void PaletteControl::onModeButtonClicked()
{
    for (auto &button: m_mode_buttons) {
        button->setChecked(button == sender());
    }

    int index = std::distance(m_mode_buttons.begin(), std::find(m_mode_buttons.begin(), m_mode_buttons.end(), sender()));
    setSelectedMode(m_mode_names.at(index));

    setCurrentPalettePage(0);
    updateModePages();
}

void PaletteControl::onPaletteButtonClicked()
{
    updatePalettePages();
    auto modeIndex = selectedModeIndex();
    if (modeIndex == -1)
        return;

    auto &group = m_palette_buttons.at(modeIndex);
    for (auto &button : group) {
        button->setChecked(button == sender());
    }

    int paletteIndex = std::distance(group.begin(), std::find(group.begin(), group.end(), sender()));
    setSelectedMode(m_mode_names.at(modeIndex));
    setSelectedPalette(m_palette_names.at(modeIndex).at(paletteIndex));
}

void PaletteControl::updateModePages()
{
    updateChildrenVisibility(m_mode_buttons, currentModePage(), modeButtonsPerPage());
    placeChildrenIntoPanel(m_mode_buttons, PC_BUTTON_SIZE, modeStartPoint(), m_mode_button_grid_size);

    m_button_previous_mode_page.setVisible(maxModePages() > 1);
    m_button_next_mode_page.setVisible(maxModePages() > 1);
    m_button_previous_mode_page.setEnabled(currentModePage() > 0);
    m_button_next_mode_page.setEnabled(currentModePage() < maxModePages() - 1);

    updatePalettePages();
}

void PaletteControl::updatePalettePages()
{
    m_button_next_palette_page.setVisible(false);
    m_button_previous_palette_page.setVisible(false);

    for (auto &group : m_palette_buttons) {
        for (auto &palette: group) {
            palette->setVisible(false);
        }
    }

    auto modeIndex = selectedModeIndex();
    if (modeIndex == -1)
        return;

    m_button_previous_palette_page.setVisible(maxPalettePages() > 1);
    m_button_next_palette_page.setVisible(maxPalettePages() > 1);
    m_button_previous_palette_page.setEnabled(currentPalettePage() > 0);
    m_button_next_palette_page.setEnabled(currentPalettePage() < maxPalettePages() - 1);

    auto &group = m_palette_buttons.at(modeIndex);

    updateChildrenVisibility(group, currentPalettePage(), paletteButtonsPerPage());
    placeChildrenIntoPanel(group, PC_BUTTON_SIZE, buttonStartPoint(), m_palette_button_grid_size);
}

QPoint PaletteControl::modeStartPoint() const
{
    return m_menuStartPoint;
}

void PaletteControl::setMenuStartPoint(QPoint newMenuStartPoint)
{
    m_menuStartPoint = newMenuStartPoint;
}

int PaletteControl::maxModePages() const
{
    return calulateNumberOfPages(m_mode_buttons.size(), modeButtonsPerPage());
}

int PaletteControl::maxPalettePages() const
{
    int modeIndex = selectedModeIndex();
    if (modeIndex == -1)
        return 0;
    auto &group = m_palette_buttons.at(modeIndex);
    return calulateNumberOfPages(group.size(), paletteButtonsPerPage());
}

int PaletteControl::modeButtonsPerPage() const
{
    return m_mode_button_grid_size.width() * m_mode_button_grid_size.height();
}

int PaletteControl::paletteButtonsPerPage() const
{
    return m_palette_button_grid_size.width() * m_palette_button_grid_size.height();
}

int PaletteControl::selectedModeIndex() const
{
    const auto iter = std::find_if(m_mode_buttons.cbegin(), m_mode_buttons.cend(), [](const QSharedPointer<SelectButton> &b) {
        return b->isChecked();
    });
    if (iter == m_mode_buttons.cend()) {
        return -1;
    }
    return std::distance(m_mode_buttons.cbegin(), iter);
}

void PaletteControl::onTypeChanged()
{
    switch (type()) {
        case PALETTE_TYPE_GOBO:
            m_title_label.setText("ゴボ");
            m_mode_button_grid_size = QSize(4, 1);
            m_palette_button_grid_size = QSize(4, 3);
            setButtonStartPoint(PC_BUTTON_TOP_LEFT);
            break;
        case PALETTE_BEAM_SHUTTER:
            m_title_label.setText("モード");
            m_mode_button_grid_size = QSize(4, 1);
            m_palette_button_grid_size = QSize(4, 3);
            setButtonStartPoint(PC_BUTTON_TOP_LEFT);
            break;
        case PALETTE_TYPE_CONTROL:
            m_title_label.setText("モード");
            m_mode_button_grid_size = QSize(4, 0);
            m_palette_button_grid_size = QSize(4, 4);
            setButtonStartPoint(PC_MENU_TOP_LEFT);
            break;
        default:
            break;
    }
    updateModePages();
}

QPoint PaletteControl::buttonStartPoint() const
{
    return m_buttonStartPoint;
}

void PaletteControl::setButtonStartPoint(QPoint newButtonStartPoint)
{
    m_buttonStartPoint = newButtonStartPoint;
}

int PaletteControl::currentModePage() const
{
    return m_currentModePage;
}

void PaletteControl::setCurrentModePage(int newCurrentModePage)
{
    newCurrentModePage = qBound(newCurrentModePage, 0, maxModePages() - 1);
    if (m_currentModePage == newCurrentModePage)
        return;
    m_currentModePage = newCurrentModePage;
    emit currentModePageChanged();
}

int PaletteControl::currentPalettePage() const
{
    return m_currentPalettePage;
}

void PaletteControl::setCurrentPalettePage(int newCurrentPalettePage)
{
    newCurrentPalettePage = qBound(newCurrentPalettePage, 0, maxPalettePages() - 1);
    if (m_currentPalettePage == newCurrentPalettePage)
        return;
    m_currentPalettePage = newCurrentPalettePage;
    emit currentPalettePageChanged();
}

PaletteType PaletteControl::type() const
{
    return m_type;
}

void PaletteControl::setType(PaletteType newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

QString PaletteControl::selectedPalette() const
{
    return m_selectedPalette;
}

void PaletteControl::setSelectedPalette(const QString &newSelectedPalette)
{
    if (m_selectedPalette == newSelectedPalette)
        return;
    m_selectedPalette = newSelectedPalette;
    emit selectedPaletteChanged();
}

QString PaletteControl::selectedMode() const
{
    return m_selectedMode;
}

void PaletteControl::setSelectedMode(const QString &newSelectedMode)
{
    if (m_selectedMode == newSelectedMode)
        return;
    m_selectedMode = newSelectedMode;
    emit selectedModeChanged();
}
