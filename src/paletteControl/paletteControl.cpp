#include "paletteControl/paletteControl.hpp"
#include "paletteControl/paletteControl_define.hpp"
#include "utility.h"


#define BASE_BUTTON_WIDTH PC_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT PC_BUTTON1_GEOMETRY.height()

PaletteControl::PaletteControl(QWidget *parent) : PanelControlBase(parent),
    m_grid(this),
    m_title_label(this),
    m_button_previous_group_page(this),
    m_button_next_group_page(this),
    m_button_previous_palette_page(this),
    m_button_next_palette_page(this),
    m_return_button(this)
{
    setFixedSize(PC_SCREEN_SIZE);

    m_group_button_grid_size = QSize(4, 1);
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

    m_button_next_group_page.setGeometry(PC_NEXT_GEOMETRY);
    m_button_next_group_page.setText("▶");
    m_button_next_group_page.setVisible(false);

    m_button_previous_group_page.setGeometry(PC_PREV_GEOMETRY);
    m_button_previous_group_page.setText("◀");
    m_button_previous_group_page.setVisible(false);

    m_return_button.setGeometry(PC_RETURN_GEOMETRY);
    m_return_button.setText("戻す");

    connect(&m_button_previous_palette_page, &QPushButton::clicked, this, [&](){
        setCurrentPalettePage(currentPalettePage() - 1);
    });
    connect(&m_button_next_palette_page, &QPushButton::clicked, this, [&](){
        setCurrentPalettePage(currentPalettePage() + 1);
    });
    connect(&m_button_previous_group_page, &QPushButton::clicked, this, [&](){
        setCurrentGroupPage(currentGroupPage() - 1);
    });
    connect(&m_button_next_group_page, &QPushButton::clicked, this, [&](){
        setCurrentGroupPage(currentGroupPage() + 1);
    });

    connect(this, &PaletteControl::currentGroupPageChanged, this, &PaletteControl::updateGroupPages);
    connect(this, &PaletteControl::currentPalettePageChanged, this, &PaletteControl::updatePalettePages);
}

void PaletteControl::SetDispParamData(PALETTE_DISP_PARAM *param)
{
    Q_ASSERT(param);
    m_group_buttons.clear();
    m_palette_buttons.clear();

    for (int i = 0; i < param->count; i++)
    {
        auto menu_button = MakeSharedQObject<SelectButton>(this);
        menu_button->setFixedSize(PC_BUTTON_SIZE);
        menu_button->setChecked(param->data[i].select);

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

        connect(menu_button.get(),&QAbstractButton::clicked, this, &PaletteControl::onGroupButtonClicked);
        m_group_buttons.push_back(menu_button);

        QVector<QSharedPointer<SelectButton>> palette_button_list;
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
            palette_button->setVisible(false);

            connect(palette_button.get(),&QAbstractButton::clicked, this, &PaletteControl::onPaletteButtonClicked);
            palette_button_list.push_back(palette_button);
        }
        m_palette_buttons.push_back(palette_button_list);
    }

    setCurrentGroupPage(0);
    setCurrentPalettePage(0);
    updateGroupPages();
}

void PaletteControl::onGroupButtonClicked()
{
    for (auto &button: m_group_buttons) {
        button->setChecked(button == sender());
    }

    setCurrentPalettePage(0);
    updateGroupPages();
}

void PaletteControl::onPaletteButtonClicked()
{
    updatePalettePages();
    auto groupIndex = selectedGroupIndex();
    if (groupIndex == -1)
        return;

    auto &group = m_palette_buttons.at(groupIndex);
    for (auto &button : group) {
        button->setChecked(button == sender());
    }
}

void PaletteControl::updateGroupPages()
{
    updateChildrenVisibility(m_group_buttons, currentGroupPage(), groupButtonsPerPage());
    placeChildrenIntoPanel(m_group_buttons, PC_BUTTON_SIZE, groupStartPoint(), m_group_button_grid_size);

    m_button_previous_group_page.setVisible(maxGroupPages() > 1);
    m_button_next_group_page.setVisible(maxGroupPages() > 1);
    m_button_previous_group_page.setEnabled(currentGroupPage() > 0);
    m_button_next_group_page.setEnabled(currentGroupPage() < maxGroupPages() - 1);

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

    auto groupIndex = selectedGroupIndex();
    if (groupIndex == -1)
        return;

    m_button_previous_palette_page.setVisible(maxPalettePages() > 1);
    m_button_next_palette_page.setVisible(maxPalettePages() > 1);
    m_button_previous_palette_page.setEnabled(currentPalettePage() > 0);
    m_button_next_palette_page.setEnabled(currentPalettePage() < maxPalettePages() - 1);

    auto &group = m_palette_buttons.at(groupIndex);

    updateChildrenVisibility(group, currentPalettePage(), paletteButtonsPerPage());
    placeChildrenIntoPanel(group, PC_BUTTON_SIZE, buttonStartPoint(), m_palette_button_grid_size);
}
QPoint PaletteControl::groupStartPoint() const
{
    return m_menuStartPoint;
}

void PaletteControl::setMenuStartPoint(QPoint newMenuStartPoint)
{
    m_menuStartPoint = newMenuStartPoint;
}

int PaletteControl::maxGroupPages() const
{
    return calulateNumberOfPages(m_group_buttons.size(), groupButtonsPerPage());
}

int PaletteControl::maxPalettePages() const
{
    int groupIndex = selectedGroupIndex();
    if (groupIndex == -1)
        return 0;
    auto &group = m_palette_buttons.at(groupIndex);
    return calulateNumberOfPages(group.size(), paletteButtonsPerPage());
}

int PaletteControl::groupButtonsPerPage() const
{
    return m_group_button_grid_size.width() * m_group_button_grid_size.height();
}

int PaletteControl::paletteButtonsPerPage() const
{
    return m_palette_button_grid_size.width() * m_palette_button_grid_size.height();
}

int PaletteControl::selectedGroupIndex() const
{
    const auto iter = std::find_if(m_group_buttons.cbegin(), m_group_buttons.cend(), [](const QSharedPointer<SelectButton> &b) {
        return b->isChecked();
    });
    if (iter == m_group_buttons.cend()) {
        return -1;
    }
    return std::distance(m_group_buttons.cbegin(), iter);
}

QPoint PaletteControl::buttonStartPoint() const
{
    return m_buttonStartPoint;
}

void PaletteControl::setButtonStartPoint(QPoint newButtonStartPoint)
{
    m_buttonStartPoint = newButtonStartPoint;
}

int PaletteControl::currentGroupPage() const
{
    return m_currentGroupPage;
}

void PaletteControl::setCurrentGroupPage(int newCurrentGroupPage)
{
    newCurrentGroupPage = bounded(newCurrentGroupPage, 0, maxGroupPages() - 1);
    if (m_currentGroupPage == newCurrentGroupPage)
        return;
    m_currentGroupPage = newCurrentGroupPage;
    emit currentGroupPageChanged();
}

int PaletteControl::currentPalettePage() const
{
    return m_currentPalettePage;
}

void PaletteControl::setCurrentPalettePage(int newCurrentPalettePage)
{
    newCurrentPalettePage = bounded(newCurrentPalettePage, 0, maxPalettePages() - 1);
    if (m_currentPalettePage == newCurrentPalettePage)
        return;
    m_currentPalettePage = newCurrentPalettePage;
    emit currentPalettePageChanged();
}
