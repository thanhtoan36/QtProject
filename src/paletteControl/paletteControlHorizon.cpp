#include "paletteControl/paletteControlHorizon.h"
#include "paletteControl/paletteControlHorizon_define.h"

#define BASE_BUTTON_WIDTH PC_HORIZON_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT PC_HORIZON_BUTTON1_GEOMETRY.height()

PaletteControlHorizon::PaletteControlHorizon(QWidget *parent) : PaletteControl(parent)
{
    setFixedSize(PC_HORIZON_SCREEN_SIZE);
    setButtonStartPoint(PC_HORIZON_BUTTON_TOP_LEFT);
    setMenuStartPoint(PC_HORIZON_MENU_TOP_LEFT);
    m_group_button_grid_size = QSize(1, 3);
    m_palette_button_grid_size = QSize(5, 4);
    m_title_label.setObjectName("title_label_with_border");
}

void PaletteControlHorizon::SetupUiComponents()
{
    m_grid.setGridSize(QSize(6, 5));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 34);

    m_title_label.setGeometry(PC_HORIZON_TITLE_GEOMETRY);
    m_title_label.setText("パレット");

    m_button_previous_palette_page.setGeometry(PC_HORIZON_UP_BUTTON_GEOMETRY);
    m_button_previous_palette_page.setText("▲");

    m_button_next_palette_page.setGeometry(PC_HORIZON_DOWN_BUTTON_GEOMETRY);
    m_button_next_palette_page.setText("▼");

    m_button_next_group_page.setGeometry(PC_HORIZON_DOWN_MODE_GEOMETRY);
    m_button_next_group_page.setText("▼");

    m_button_previous_group_page.setGeometry(PC_HORIZON_UP_MODE_GEOMETRY);
    m_button_previous_group_page.setText("▲");

    m_return_button.setGeometry(PC_HORIZON_RETURN_GEOMETRY);

    m_return_button.setText("戻す");
}