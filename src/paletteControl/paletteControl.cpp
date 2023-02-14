#include "paletteControl/paletteControl.hpp"
#include "paletteControl/paletteControl_define.hpp"
#include "utility.h"


#define BASE_BUTTON_WIDTH PC_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT PC_BUTTON1_GEOMETRY.height()

PaletteControl::PaletteControl(QWidget *parent) : PanelControlBase(parent),
    m_grid(this),
    m_title_label(this),
    m_prev_button(this),
    m_next_button(this),
    m_up_button(this),
    m_down_button(this),
    m_return_button(this)
{
    m_return_button.setTextColor(Qt::yellow);
    setFixedSize(PC_SCREEN_SIZE);
    setButtonColumn(4);
    setMenuColumn(4);
    setMenuRow(1);
    setButtonRow(3);
    setButtonStartPoint(PC_BUTTON_TOP_LEFT);
    setMenuStartPoint(PC_MENU_TOP_LEFT);
}

void PaletteControl::SetDispParamData(PALETTE_DISP_PARAM *param)
{
    Q_ASSERT(param);
    m_current_menu = 0;
    m_current_menu_page = 0;
    m_menu_buttons.clear();
    m_current_palette_page.clear();
    m_palette_buttons_list.clear();
    for (int i = 0; i < param->count; i++)
    {
        auto menu_button = MakeSharedQObject<SelectButton>(this);
        menu_button->setFixedSize(PC_BUTTON_SIZE);
        if (param->data[i].image.isNull())
        {
            menu_button->setText(param->data[i].name);
        }
        else
        {
                QPixmap pixels = QPixmap::fromImage(param->data[i].image);
                QIcon icon(pixels);
                menu_button->setIconSize(PC_BUTTON_SIZE - QSize(6, 6));
                menu_button->setIcon(icon);
        }

        connect(menu_button.get(),&QAbstractButton::clicked, this, [&,i](){
            onButtonMenuClicked(i,sender());
        });
        if (param->data[i].select)
        {
            m_current_menu = i;
        }
        m_menu_buttons.push_back(menu_button);
        m_current_palette_page.push_back(0);
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
                 QPixmap pixels = QPixmap::fromImage(param->data[i].palette[j].image);
                 QIcon icon(pixels);
                 palette_button->setIconSize(PC_BUTTON_SIZE - QSize(6, 6));
                 palette_button->setIcon(icon);
            }

            palette_button->setChecked(param->data[i].palette[j].select);
            palette_button->setVisible(false);
            connect(palette_button.get(),&QAbstractButton::clicked, this, [&,j](){
                onPaletteButtonClicked(j,sender());
            });
            palette_button_list.push_back(palette_button);
        }
        m_palette_buttons_list.push_back(palette_button_list);
        placeChildrenIntoPanel(palette_button_list, PC_BUTTON_SIZE, buttonStartPoint(), buttonColumn(), buttonRow());
    }
    m_menu_buttons[m_current_menu]->setChecked(true);

    onButtonMenuClicked(m_current_menu,nullptr);

    placeChildrenIntoPanel(m_menu_buttons, PC_BUTTON_SIZE, menuStartPoint(), menuColumn(), menuRow());
    updateChildrenVisibility(m_menu_buttons, m_current_menu_page, menuPageSize());
    m_prev_button.setEnabled(m_current_menu_page > 0);;
    m_next_button.setEnabled(m_current_menu_page + 1  < calulateNumberOfPages(m_menu_buttons.size(), menuPageSize()));

}

void PaletteControl::SetupUiComponents()
{
    m_grid.setGridSize(QSize(4, 6));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 32);

    m_title_label.setGeometry(PC_TITLE_GEOMETRY);
    m_title_label.setObjectName("title_label");
    m_title_label.setText("パレット");

    m_up_button.setGeometry(PC_UP_GEOMETRY);
    m_up_button.setText("▲");

    m_down_button.setGeometry(PC_DOWN_GEOMETRY);
    m_down_button.setText("▼");

    m_next_button.setGeometry(PC_NEXT_GEOMETRY);
    m_next_button.setText("▶");

    m_prev_button.setGeometry(PC_PREV_GEOMETRY);
    m_prev_button.setText("◀");

    m_return_button.setGeometry(PC_RETURN_GEOMETRY);

    m_return_button.setText("戻す");

}

void PaletteControl::SetupUiEvents()
{
    connect(&m_up_button, &QPushButton::clicked, this, &PaletteControl::scrollUp);
    connect(&m_down_button, &QPushButton::clicked, this, &PaletteControl::scrollDown);

    connect(&m_prev_button, &QPushButton::clicked, this, &PaletteControl::scrollPrev);
    connect(&m_next_button, &QPushButton::clicked, this, &PaletteControl::scrollNext);
}

void PaletteControl::onButtonMenuClicked(const int index, QObject *sender)
{
    if (index >= m_menu_buttons.size())
    {
        return;
    }

    m_current_menu = index;

    for (int i = 0; i< m_menu_buttons.size(); i++)
    {
        if (i != index)
        {
            m_menu_buttons[i]->setChecked(false);
        }
    }
    for (int j = 0 ; j < m_palette_buttons_list.size(); j++)
    {
        if (j == index)
        {
            updateChildrenVisibility(m_palette_buttons_list[j],m_current_palette_page[m_current_menu],buttonPageSize());
            m_up_button.setEnabled(m_current_palette_page[m_current_menu] > 0);
            m_down_button.setEnabled(m_current_palette_page[m_current_menu] + 1  < calulateNumberOfPages(m_palette_buttons_list[j].size(), buttonPageSize()));
        }
        else
        {
            for (auto& btn : m_palette_buttons_list[j])
            {
                btn->setVisible(false);
            }
        }

    }

}

void PaletteControl::onPaletteButtonClicked(const int index, QObject *sender)
{
    for (int i = 0; i< m_palette_buttons_list[m_current_menu].size();i++)
    {
        if (i != index)
        {
            m_palette_buttons_list[m_current_menu][i]->setChecked(false);
        }
    }
}

void PaletteControl::scrollUp()
{
    if (m_current_menu >= m_palette_buttons_list.size())
    {
        return;
    }
    if(m_current_palette_page[m_current_menu] > 0)
    {
        m_current_palette_page[m_current_menu]-=1;
        updateChildrenVisibility(m_palette_buttons_list[m_current_menu],m_current_palette_page[m_current_menu],buttonPageSize());
        m_up_button.setEnabled(m_current_palette_page[m_current_menu] > 0);;
        m_down_button.setEnabled(m_current_palette_page[m_current_menu] + 1  < calulateNumberOfPages(m_palette_buttons_list[m_current_menu].size(), buttonPageSize()));
    }

}

void PaletteControl::scrollDown()
{
    if (m_current_menu >= m_palette_buttons_list.size())
    {
        return;
    }
    m_current_palette_page[m_current_menu]+=1;
    updateChildrenVisibility(m_palette_buttons_list[m_current_menu],m_current_palette_page[m_current_menu],buttonPageSize());
    m_up_button.setEnabled(m_current_palette_page[m_current_menu] > 0);;
    m_down_button.setEnabled(m_current_palette_page[m_current_menu] + 1  < calulateNumberOfPages(m_palette_buttons_list[m_current_menu].size(), buttonPageSize()));
}

void PaletteControl::scrollNext()
{
    if (m_current_menu_page >= m_menu_buttons.size())
    {
        return;
    }
    m_current_menu_page+=1;
    updateChildrenVisibility(m_menu_buttons,m_current_menu_page,menuPageSize());
    m_prev_button.setEnabled(m_current_menu_page > 0);;
    m_next_button.setEnabled(m_current_menu_page + 1  < calulateNumberOfPages(m_menu_buttons.size(), menuPageSize()));
}

void PaletteControl::scrollPrev()
{
    if (m_current_menu_page >= m_menu_buttons.size())
    {
        return;
    }
     if(m_current_menu_page > 0)
     {
         m_current_menu_page-=1;
         updateChildrenVisibility(m_menu_buttons,m_current_menu_page,menuPageSize());
         m_prev_button.setEnabled(m_current_menu_page > 0);;
         m_next_button.setEnabled(m_current_menu_page + 1  < calulateNumberOfPages(m_menu_buttons.size(), menuPageSize()));
     }
}

uint16_t PaletteControl::menuColumn() const
{
    return m_menuColumn;
}

void PaletteControl::setMenuColumn(uint16_t newMenuColumn)
{
    m_menuColumn = newMenuColumn;
}

QPoint PaletteControl::menuStartPoint() const
{
    return m_menuStartPoint;
}

void PaletteControl::setMenuStartPoint(QPoint newMenuStartPoint)
{
    m_menuStartPoint = newMenuStartPoint;
}

QPoint PaletteControl::buttonStartPoint() const
{
    return m_buttonStartPoint;
}

void PaletteControl::setButtonStartPoint(QPoint newButtonStartPoint)
{
    m_buttonStartPoint = newButtonStartPoint;
}

uint16_t PaletteControl::menuRow() const
{
    return m_menuRow;
}

void PaletteControl::setMenuRow(uint16_t newMenuRow)
{
    m_menuRow = newMenuRow;
}

uint16_t PaletteControl::menuPageSize() const
{
    return menuColumn()*menuRow();
}

uint16_t PaletteControl::buttonPageSize() const
{
    return buttonColumn()*buttonRow();
}

uint16_t PaletteControl::buttonRow() const
{
    return m_buttonRow;
}

void PaletteControl::setButtonRow(uint16_t newButtonRow)
{
    m_buttonRow = newButtonRow;
}

uint16_t PaletteControl::buttonColumn() const
{
    return m_buttonColumn;
}

void PaletteControl::setButtonColumn(uint16_t newColumn)
{
    m_buttonColumn = newColumn;
}
