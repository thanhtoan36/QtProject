#include "colorFilterControl/colorFilterControlHorizon.h"
#include "colorFilterControl/colorFilterControlHorizon_define.h"

#define PAGE_ROW  4
#define PAGE_COLUMN  4
#define PAGE_SIZE (PAGE_ROW*PAGE_COLUMN)

#define BASE_BUTTON_X CFC_HORIZON_BUTTON1_GEOMETRY.x()
#define BASE_BUTTON_Y CFC_HORIZON_BUTTON1_GEOMETRY.y()

#define BASE_BUTTON_WIDTH CFC_HORIZON_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT CFC_HORIZON_BUTTON1_GEOMETRY.height()

ColorFilterControlHorizon::ColorFilterControlHorizon(QWidget *parent) : ColorFilterControl(parent),
     m_empty1_button(this),
     m_up_tab_button(this),
     m_down_tab_button(this)
{
    setFixedSize(CFC_HORIZON_SCREENSIZE);
    m_children_history.append(&m_tb_tab_button);
    m_children_history.append(&m_custom_tab_button);
}

void ColorFilterControlHorizon::SetDispParamDataHorizon(COLOR_FILTER_DISP_PARAM *param)
{
    Q_ASSERT(param);
    m_tb_tab_buttons.clear();
    for (uint16_t i = 0; i < param->tb.count; i++)
    {
        auto button = MakeSharedQObject<SelectColorButton>(this);
        m_tb_tab_buttons.push_back(button);
        QRect a(BASE_BUTTON_WIDTH*(i % PAGE_COLUMN) +BASE_BUTTON_X, BASE_BUTTON_Y + (i % PAGE_SIZE /PAGE_ROW)*BASE_BUTTON_HEIGHT,BASE_BUTTON_WIDTH	,BASE_BUTTON_HEIGHT);
        button->setText(param->tb.color_filter[i].name);
        button->SetBackgroundColor(param->tb.color_filter[i].color);
        button->setGeometry(a);
        if (i > PAGE_SIZE - 1)
        {
            button->setVisible(false);
        }
        connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
            onTBTabButtonChecked(i,sender());
        });

    }
    m_custom_tab_buttons.clear();
    for (uint16_t i = 0; i < param->custom.count; i++)
    {
        auto button = MakeSharedQObject<SelectColorButton>(this);
        m_custom_tab_buttons.push_back(button);
        QRect a(BASE_BUTTON_WIDTH*(i % PAGE_COLUMN) +BASE_BUTTON_X, BASE_BUTTON_Y + (i % PAGE_SIZE /PAGE_ROW)*BASE_BUTTON_HEIGHT,BASE_BUTTON_WIDTH	,BASE_BUTTON_HEIGHT);
        button->setText(param->custom.color_filter[i].name);
        button->SetBackgroundColor(param->custom.color_filter[i].color);
        button->setGeometry(a);
        if (i > PAGE_SIZE - 1)
        {
            button->setVisible(false);
        }
        connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
            onCustomTabButtonChecked(i,sender());
        });

    }
    m_history_buttons.clear();
    for (uint16_t i = 0; i < param->history.count; i++)
    {
        auto button = MakeSharedQObject<SelectColorButton>(this);
        m_history_buttons.push_back(button);
        button->setText(param->history.color_filter[i].name);
        button->SetBackgroundColor(param->history.color_filter[i].color);
        QRect a(BASE_BUTTON_WIDTH*(i % PAGE_COLUMN) +BASE_BUTTON_X, BASE_BUTTON_Y + (i % PAGE_SIZE /PAGE_ROW)*BASE_BUTTON_HEIGHT,BASE_BUTTON_WIDTH	,BASE_BUTTON_HEIGHT);
        button->setGeometry(a);
        if (i > PAGE_SIZE - 1)
        {
            button->setVisible(false);
        }
        connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
            onHistoryButtonChecked(i,sender());
        });
    }

    if (param->tb.select == true)
    {
        setMode(COLOR_FILTER_MODE_TAB1);
    }
    else if (param->custom.select == true)
    {
        setMode(COLOR_FILTER_MODE_TAB2);
    }
    else if (param->history.select == true)
    {
        setMode(COLOR_FILTER_MODE_TAB2);
    }
    m_grid.setGridSize(QSize(7, 5));
    m_grid.setCellSize(QSize(78, 48));
    m_grid.move(0, 34);
}

void ColorFilterControlHorizon::SetupUiComponents()
{
    m_title_label.setGeometry(CFC_HORIZON_TITLE_GEOMETRY);
    m_title_label.setText("カラーフィルタ");
    m_title_label.setObjectName("title_label");
    m_title_label.setObjectName("title_label_horizon");

    m_tb_tab_button.setGeometry(CFC_HORIZON_TB_TAB_GEOMETRY);
    m_tb_tab_button.setText("TB標準");

    m_custom_tab_button.setGeometry(CFC_HORIZON_CUSTOM_TAB_GEOMETRY);
    m_custom_tab_button.setText("カスタム");


    m_history_button.setGeometry(CFC_HORIZON_HISTORY_BUTTON_GEOMETRY);
    m_history_button.setText("最近使った\nもの");
    m_history_button.setIsCheckMarkEnable(false);

    m_up_tab_button.setGeometry(CFC_HORIZON_UP_BUTTON_GEOMETRY);
    m_up_tab_button.setText("▲");

    m_down_tab_button.setGeometry(CFC_HORIZON_DOWN_BUTTON_GEOMETRY);
    m_down_tab_button.setText("▼");

    m_up_button.setGeometry(CFC_HORIZON_UP2_BUTTON_GEOMETRY);
    m_up_button.setText("▲");

    m_down_button.setGeometry(CFC_HORIZON_DOWN2_BUTTON_GEOMETRY);
    m_down_button.setText("▼");

    m_title_button.setGeometry(CFC_HORIZON_TITLE_BUTTON_GEOMETRY);
    m_title_button.setText("タイトル");

    m_empty_button.setGeometry(CFC_HORIZON_EMPTY2_GEOMETRY);
    m_empty_button.setText("");

    m_empty1_button.setGeometry(CFC_HORIZON_EMPTY1_GEOMETRY);
    m_empty1_button.setText("");

    m_register_button.setGeometry(CFC_HORIZON_REGISTER_BUTTON_GEOMETRY);
    m_register_button.setText("登録");

    m_delete_button.setGeometry(CFC_HORIZON_DELETE_BUTTON_GEOMETRY);
    m_delete_button.setText("削除");

    m_back_button.setGeometry(CFC_HORIZON_BACK_BUTTON_GEOMETRY);
    m_back_button.setText("戻す");

    m_setting_label.setVisible(false);
    m_next_button.setVisible(false);
    m_prev_button.setVisible(false);
}

void ColorFilterControlHorizon::SetupUiEvents()
{
    ColorFilterControl::SetupUiEvents();
}
