#include "groupControl/groupControlHorizon.h"
#include "groupControl/groupControlHorizon_define.h"

#define BASE_BUTTON_WIDTH GC_HORIZON_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT GC_HORIZON_BUTTON1_GEOMETRY.height()

GroupControlHorizon::GroupControlHorizon(QWidget *parent) : GroupControl(parent)
{
    setFixedSize(GC_HORIZON_SCREEN_SIZE);
    m_buttons_grid_size = QSize(10, 4);
    m_title_label.setObjectName("title_label_with_border");

    m_grid.setGridSize(QSize(11, 5));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 34);

    m_title_label.setGeometry(GC_HORIZON_TITLE_GEOMETRY);

    m_history_button.setGeometry(GC_HORIZON_HISTORY_GEOMETRY);

    m_up_button.setGeometry(GC_HORIZON_UP_GEOMETRY);
    m_down_button.setGeometry(GC_HORIZON_DOWN_GEOMETRY);

    m_back_button.setGeometry(GC_HORIZON_RETURN_GEOMETRY);
    m_setting_label.setVisible(false);

    m_title_button.setGeometry(GC_HORIZON_TITLE_BUTTON_GEOMETRY);
    m_empty_button.setVisible(false);

    m_register_button.setGeometry(GC_HORIZON_REGISTER_GEOMETRY);
    m_delete_button.setGeometry(GC_HORIZON_DELETE_GEOMETRY);
}

void GroupControlHorizon::SetDispParamData(GROUP_DISP_PARAM *param)
{
    Q_ASSERT(param);
    GroupControl::SetDispParamData(param);
    placeChildrenIntoPanel(m_group_buttons, GC_HORIZON_BUTTON1_GEOMETRY.size(), GC_HORIZON_BUTTON1_GEOMETRY.topLeft(), m_buttons_grid_size);
    placeChildrenIntoPanel(m_history_buttons, GC_HORIZON_BUTTON1_GEOMETRY.size(), GC_HORIZON_BUTTON1_GEOMETRY.topLeft(), m_buttons_grid_size);
}

void GroupControlHorizon::addButtonToHistory(QSharedPointer<TitleSelectButton> &button)
{
    GroupControl::addButtonToHistory(button);
    placeChildrenIntoPanel(m_history_buttons, GC_HORIZON_BUTTON1_GEOMETRY.size(), GC_HORIZON_BUTTON1_GEOMETRY.topLeft(), m_buttons_grid_size);
}
