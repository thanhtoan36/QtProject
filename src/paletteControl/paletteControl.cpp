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
    setColumn(4);
    setMenuRow(1);
    setButtonRow(3);
    setButtonStartPoint(PC_BUTTON_TOP_LEFT);
    setMenuStartPoint(PC_MENU_TOP_LEFT);
}

void PaletteControl::SetDispParamData(PALETTE_DISP_PARAM *param)
{
    Q_ASSERT(param);
    m_memu_buttons.clear();
    m_palette_buttons_list.clear();
    for (int i = 0; i < param->count; i++)
    {
        auto menu_button = MakeSharedQObject<SelectButton>(this);
        menu_button->setText(param->data[i].name);
        m_memu_buttons.push_back(menu_button);
        QVector<QSharedPointer<SelectButton>> palette_button_list;
        for(int j = 0; j < param->data[i].count;j++)
        {
            auto palette_button = MakeSharedQObject<SelectButton>(this);
            palette_button->setText(param->data[i].palette[j].name);
            palette_button_list.push_back(palette_button);
        }
        m_palette_buttons_list.push_back(palette_button_list);
    }
}

void PaletteControl::SetupUiComponents()
{
    m_grid.setGridSize(QSize(4, 6));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 32);

    m_title_label.setGeometry(PC_TITLE_GEOMETRY);
    m_title_label.setObjectName("title_label");
    m_title_label.setText("ライブラリ");

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

}

void PaletteControl::scrollUp()
{

}

void PaletteControl::scrollDown()
{

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
    return column()*menuRow();
}

uint16_t PaletteControl::buttonPageSize() const
{
    return column()*buttonRow();
}

uint16_t PaletteControl::buttonRow() const
{
    return m_buttonRow;
}

void PaletteControl::setButtonRow(uint16_t newButtonRow)
{
    m_buttonRow = newButtonRow;
}

uint16_t PaletteControl::column() const
{
    return m_column;
}

void PaletteControl::setColumn(uint16_t newColumn)
{
    m_column = newColumn;
}
