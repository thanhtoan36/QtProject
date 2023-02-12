#include "libraryControl/libraryControlHorizon.h"
#include "libraryControl/libraryControlHorizon_define.h"

#define BASE_BUTTON_WIDTH LC_HORIZON_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT LC_HORIZON_BUTTON1_GEOMETRY.height()

LibraryControlHorizon::LibraryControlHorizon(QWidget *parent) : LibraryControl(parent)
{
    setFixedSize(LC_HORIZON_SCREENSIZE);
    setColumn(10);
    setLibRow(3);
    setModeRow(1);

    setLibStartPoint(LC_HORIZON_LIB_BUTTON_TOP_LEFT);
    setModeStartPoint(LC_HORIZON_MODE_TOP_LEFT);
}

void LibraryControlHorizon::SetupUiComponents()
{
    m_grid.setGridSize(QSize(11, 5));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 34);

    m_title_label.setGeometry(LC_HORIZON_TITLE_GEOMETRY);
    m_title_label.setObjectName("title_label_horizon");
    m_title_label.setText("ライブラリ");

    m_history_button.setGeometry(LC_HORIZON_HISTORY_GEOMETRY);
    m_history_button.setText("最近使った\nもの");

    m_up_button.setGeometry(LC_HORIZON_UP_GEOMETRY);
    m_up_button.setText("▲");

    m_down_button.setGeometry(LC_HORIZON_DOWN_GEOMETRY);
    m_down_button.setText("▼");

    m_return_button.setGeometry(LC_HORIZON_RETURN_GEOMETRY);
    m_return_button.setText("戻す");

    m_setting_label.setVisible(false);

    m_title_button.setGeometry(LC_HORIZON_TITLE_BUTTON_GEOMETRY);
    m_title_button.setText("タイトル");


    m_register_button.setGeometry(LC_HORIZON_REGISTER_GEOMETRY);
    m_register_button.setText("登録");

    m_delete_button.setGeometry(LC_HORIZON_DELETE_GEOMETRY);
    m_delete_button.setText("削除");

    m_empty_button.setVisible(false);
}
