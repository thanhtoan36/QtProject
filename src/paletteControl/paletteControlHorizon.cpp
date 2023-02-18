#include "paletteControl/paletteControlHorizon.h"
#include "paletteControl/paletteControlHorizon_define.h"

#define BASE_BUTTON_WIDTH PC_HORIZON_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT PC_HORIZON_BUTTON1_GEOMETRY.height()

PaletteControlHorizon::PaletteControlHorizon(QWidget *parent) : PaletteControl(parent)
{
    setFixedSize(PC_HORIZON_SCREEN_SIZE);
    setMenuRow(3);
    setMenuColumn(1);
    setButtonRow(4);
    setButtonColumn(4);
    setButtonStartPoint(PC_HORIZON_BUTTON_TOP_LEFT);
    setMenuStartPoint(PC_HORIZON_MENU_TOP_LEFT);
    m_title_label.setObjectName("title_label_with_border");
}

void PaletteControlHorizon::SetupUiComponents()
{
    m_grid.setGridSize(QSize(6, 5));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 34);

    m_title_label.setGeometry(PC_HORIZON_TITLE_GEOMETRY);
    m_title_label.setText("パレット");

    m_up_button.setGeometry(PC_HORIZON_UP_BUTTON_GEOMETRY);
    m_up_button.setText("▲");

    m_down_button.setGeometry(PC_HORIZON_DOWN_BUTTON_GEOMETRY);
    m_down_button.setText("▼");

    m_next_button.setGeometry(PC_HORIZON_DOWN_MODE_GEOMETRY);
    m_next_button.setText("▼");

    m_prev_button.setGeometry(PC_HORIZON_UP_MODE_GEOMETRY);
    m_prev_button.setText("▲");

    m_return_button.setGeometry(PC_HORIZON_RETURN_GEOMETRY);

    m_return_button.setText("戻す");
}
