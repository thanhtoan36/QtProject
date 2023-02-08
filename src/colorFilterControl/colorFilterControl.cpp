#include "colorFilterControl/colorFilterControl.hpp"

#include "colorFilterControl/colorFilterControl_define.hpp"
#include <QFont>
#include <math.h>

ColorFilterControl::ColorFilterControl(QWidget* parent) : PanelControlBase(parent),
    m_title_label(this),
    m_tab1_button(this),
    m_tab2_button(this),
    m_next_button(this),
    m_prev_button(this),
    m_history_button(this),
    m_up_button(this),
    m_down_button(this),
    m_back_button(this),
    m_setting_label(this),
    m_title_button(this),
    m_empty_button(this),
    m_register_button(this),
    m_delete_button(this)
{
    setFixedSize(CFC_SCREENSIZE);
}

void ColorFilterControl::setDispParamData(COLOR_FILTER_DISP_PARAM *param)
{
    Q_ASSERT(param);
    for (uint16_t i = 0; i < param->tb.count; i++)
    {
        auto button = MakeSharedQObject<SelectColorButton>(this);
        m_tab1_buttons.push_back(button);
        QRect a(78*(i %4) +0, 80 + (i % 16 /4)*48	,78	,48);
        button->setText(param->tb.color_filter[i].name);
        button->SetBackgroundColor(param->tb.color_filter[i].color);
        button->setGeometry(a);
        if (i > 15)
        {
            button->setVisible(false);
        }
    }
    for (uint16_t i = 0; i < param->custom.count; i++)
    {
        auto button = MakeSharedQObject<SelectColorButton>(this);
        m_tab2_buttons.push_back(button);
        QRect a(78*(i %4) +0, 80 + (i/4)*48	,78	,48);
        button->setText(param->custom.color_filter[i].name);
        button->SetBackgroundColor(param->custom.color_filter[i].color);
        button->setGeometry(a);
        button->setVisible(false);
    }
    for (uint16_t i = 0; i < param->history.count; i++)
    {
        auto button = MakeSharedQObject<SelectColorButton>(this);
        m_history_buttons.push_back(button);
        button->setText(param->history.color_filter[i].name);
        button->SetBackgroundColor(param->history.color_filter[i].color);
        QRect a(78*(i %4) +0, 80 + (i/4)*48	,78	,48);
        button->setGeometry(a);
        button->setVisible(false);
    }
}

void ColorFilterControl::ScrollUp()
{
    if (m_current_scroll_step == 0)
    {
        return;
    }
    m_current_scroll_step--;
    if (m_tab1_buttons.size() > 16)
    {
        for(uint32_t i = 0;i < m_tab1_buttons.size();i++)
        {
            if ((i >= 16*(m_current_scroll_step+1)) || i < (16*(m_current_scroll_step)))
            {
                m_tab1_buttons[i]->setVisible(false);
            }
            else
            {
                m_tab1_buttons[i]->setVisible(true);
            }
        }
    }
}

void ColorFilterControl::ScrollDown()
{
    uint32_t step_size = std::ceil((float)m_tab1_buttons.size()/16);

    if (m_current_scroll_step >= (step_size-1))
    {
        return;
    }
    m_current_scroll_step++;
    if (m_tab1_buttons.size() > 16)
    {
        for(uint32_t i = 0;i < m_tab1_buttons.size();i++)
        {
            if ((i >= 16*(m_current_scroll_step+1)) || i < (16*(m_current_scroll_step)))
            {
                m_tab1_buttons[i]->setVisible(false);
            }
            else
            {
                m_tab1_buttons[i]->setVisible(true);
            }
        }
    }
}

void ColorFilterControl::SetupUiComponents()
{
    m_title_label.setGeometry(CFC_TITLE_GEOMETRY);
    m_title_label.setText("カラーフィルタ");
    m_title_label.setObjectName("title_label");

    m_tab1_button.setGeometry(CFC_TAB1_GEOMETRY);
    m_tab1_button.setText("TB標準");

    m_tab2_button.setGeometry(CFC_TAB2_GEOMETRY);
    m_tab2_button.setText("カスタム");

    m_next_button.setGeometry(CFC_NEXT_BUTTON_GEOMETRY);
    m_next_button.setText("▶");
    m_next_button.setVisible(false);

    m_prev_button.setGeometry(CFC_PREVIOUS_BUTTON_GEOMETRY);
    m_prev_button.setText("◀");
    m_prev_button.setVisible(false);

    m_history_button.setGeometry(CFC_HISTORY_GEOMETRY);
    m_history_button.setText("最近使った\nもの");
    m_history_button.setIsCheckMarkEnable(false);

    m_up_button.setGeometry(CFC_UP_BUTTON_GEOMETRY);
    m_up_button.setText("▲");

    m_down_button.setGeometry(CFC_DOWN_BUTTON_GEOMETRY);
    m_down_button.setText("▼");

    m_title_button.setGeometry(CFC_TITLE_BUTTON_GEOMETRY);
    m_title_button.setText("タイトル");

    m_empty_button.setGeometry(CFC_EMPTY_GEOMETRY);
    m_empty_button.setText("");

    m_register_button.setGeometry(CFC_REGISTER_GEOMETRY);
    m_register_button.setText("登録");

    m_delete_button.setGeometry(CFC_DELETE_GEOMETRY);
    m_delete_button.setText("削除");

    m_back_button.setGeometry(CFC_BACK_BUTTON_GEOMETRY);
    m_back_button.setText("戻す");

    m_setting_label.setGeometry(CFC_SETTING_GEOMETRY);
    m_setting_label.setText("設定");
    m_setting_label.setObjectName("title_label");

}

void ColorFilterControl::SetupUiEvents()
{
    connect(&m_up_button, &QAbstractButton::clicked, this, [&]() {
        ScrollUp();
    });
    connect(&m_down_button, &QAbstractButton::clicked, this, [&]() {
        ScrollDown();
    });
}
