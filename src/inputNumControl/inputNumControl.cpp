#include "inputNumControl/inputNumControl.hpp"
#include "inputNumControl/inputNumControl_define.hpp"
#include "utility.h"

#define BASE_BUTTON_WIDTH IC_7_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT IC_7_GEOMETRY.height()
#define MODE_ROW 1
#define MODE_COLUMN 4
#define MODE_POS_COLUMN 3

InputNumControl::InputNumControl(QWidget *parent)  : PanelControlBase(parent),
    m_grid(this),
    m_label_title(this),
    m_button_mode_percent(this),
    m_button_mode_255(this),
    m_button_mode_angle(this),
    m_button_relative(this),
    m_button_absolute(this),
    m_button_previous_tab(this),
    m_button_next_tab(this),
    m_return_button(this),
    m_mode()
{
    setFixedSize(IC_SCREEN_SIZE);
    setCurrentButtonModePage(0);
    m_return_button.setTextColor(Qt::yellow);
    m_button_mode_255.setCheckMarkVisible(true);
    m_button_mode_percent.setCheckMarkVisible(true);
    m_button_mode_percent.setChecked(true);
    m_return_button.setTextColor(Qt::yellow);

    m_grid.setGridSize(QSize(4, 6));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 32);

    m_label_title.setGeometry(IC_TITLE_GEOMETRY);
    m_label_title.setObjectName("title_label");
    m_label_title.setText("数値入力");

    m_button_mode_percent.setGeometry(IC_PERCENT_GEOMETRY);
    m_button_mode_percent.setText("%");
    m_button_mode_255.setGeometry(IC_255_GEOMETRY);
    m_button_mode_255.setText("255");

    m_button_mode_angle.setGeometry(IC_ANGEL_GEOMETRY);
    m_button_mode_angle.setText("°角度");
    m_button_mode_angle.setVisible(false);

    m_button_relative.setGeometry(IC_RELATIVE_GEOMETRY);
    m_button_relative.setText("相対");

    m_button_absolute.setGeometry(IC_ABSOLUTE_GEOMETRY);
    m_button_absolute.setText("絶対");

    m_button_previous_tab.setGeometry(IC_PREV_GEOMETRY);
    m_button_previous_tab.setText("◀");

    m_button_next_tab.setGeometry(IC_NEXT_GEOMETRY);
    m_button_next_tab.setText("▶");

    m_return_button.setGeometry(IC_RETURN_GEOMETRY);
    m_return_button.setText("戻す");

    QStringList input_num_model = {
        "7", "8", "9", "最大",
        "4", "5", "6", "最小",
        "1", "2", "3", "ENTER",
        "0", "ハーフ",
    };

    m_input_num_buttons.clear();
    for (const QString &b : input_num_model) {
        auto button = MakeSharedQObject<CustomPushButton>(this);
        button->setFixedSize(IC_BUTTON_SIZE);
        button->setVisible(true);
        button->setText(b);


        connect(button.get(), &QPushButton::clicked, this, [&]() {
            qDebug() << ((CustomPushButton*)sender())->text();
        });

        m_input_num_buttons.append(button);
    }
    placeChildrenIntoPanel(m_input_num_buttons, IC_BUTTON_SIZE, IC_BUTTON_TOPLEFT, QSize(4, 4));

    connect(this, &InputNumControl::modeChanged, this, &InputNumControl::onModeChanged);
    connect(this, &InputNumControl::typeChanged, this, &InputNumControl::onTypeChanged);
    connect(&m_button_previous_tab, &QPushButton::clicked, this, [&](){
        qDebug("previous");
        setCurrentButtonModePage(currentButtonModePage()-1);
    });
    connect(&m_button_next_tab, &QPushButton::clicked, this, [&](){
        qDebug("next");
        setCurrentButtonModePage(currentButtonModePage()+1);
    });
    connect(this, &InputNumControl::currentButtonModePageChanged, this, &InputNumControl::onCurrentButtonModePageChanged);
    connect(&m_button_mode_255, &QPushButton::clicked, this, &InputNumControl::onButtonMode255Clicked);
    connect(&m_button_mode_angle, &QPushButton::clicked, this, &InputNumControl::onButtonModeAngelClicked);
    connect(&m_button_mode_percent, &QPushButton::clicked, this, &InputNumControl::onButtonModePercentClicked);
    connect(&m_button_relative, &QPushButton::clicked, this, &InputNumControl::onButtonRelativeClicked);
    connect(&m_button_absolute, &QPushButton::clicked, this, &InputNumControl::onButtonAbsoluteClicked);
}

void InputNumControl::SetDispParamData(INPUT_NUM_DISP_PARAM *param)
{
    Q_ASSERT(param);
    m_menu_color_buttons.clear();
    m_menu_control_buttons.clear();
    m_menu_gobo_buttons.clear();
    m_menu_position_buttons.clear();
    m_menu_shutter_buttons.clear();
    setCurrentButtonModePage(0);
    switch (param->type) {
        case INPUT_NUM_TYPE_COLOR:
        {
            for (int i = 0; i< param->count;i++)
            {
                auto button =  MakeSharedQObject<SelectButton>(this);
                button->setFixedSize(IC_MODE_SIZE);
                button->setText(param->param[i].name);
                button->setChecked(param->param[i].select);
                button->setVisible(false);
                button->setCheckMarkVisible(true);
                connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
                    onButtonModeColorCheck(i,sender());
                });
                m_menu_color_buttons.push_back(button);
            }
            placeChildrenIntoPanel(m_menu_color_buttons, IC_MODE_SIZE, IC_MODE_PLACEMENT_START, QSize(MODE_COLUMN, 1) );
            break;
        }
        case INPUT_NUM_TYPE_GOBO:
        {
            for (int i = 0; i< param->count;i++)
            {
                auto button =  MakeSharedQObject<SelectButton>(this);
                button->setFixedSize(IC_MODE_SIZE);
                button->setText(param->param[i].name);
                button->setChecked(param->param[i].select);
                button->setVisible(false);
                button->setCheckMarkVisible(true);
                connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
                    onButtonModeGoboCheck(i,sender());
                });
                m_menu_gobo_buttons.push_back(button);
            }
            placeChildrenIntoPanel(m_menu_gobo_buttons, IC_MODE_SIZE, IC_MODE_PLACEMENT_START, QSize(MODE_COLUMN, 1));
            break;
        }
        case INPUT_NUM_TYPE_BEAM_SHUTTER:
        {
            for (int i = 0; i< param->count;i++)
            {
                auto button =  MakeSharedQObject<SelectButton>(this);
                button->setFixedSize(IC_MODE_SIZE);
                button->setText(param->param[i].name);
                button->setChecked(param->param[i].select);
                button->setVisible(false);
                button->setCheckMarkVisible(true);
                connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
                    onButtonModeShutterCheck(i,sender());
                });
                m_menu_shutter_buttons.push_back(button);
            }
            placeChildrenIntoPanel(m_menu_shutter_buttons, IC_MODE_SIZE, IC_MODE_PLACEMENT_START,  QSize(MODE_COLUMN, 1));
            break;
        }
        case INPUT_NUM_TYPE_POSITION:
        {
            for (int i = 0; i< param->count;i++)
            {
                auto button =  MakeSharedQObject<SelectButton>(this);
                button->setFixedSize(IC_MODE_SIZE);
                button->setText(param->param[i].name);
                button->setChecked(param->param[i].select);
                button->setVisible(false);
                connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
                    onButtonModePositionCheck(i,sender());
                });
                m_menu_position_buttons.push_back(button);
            }
            placeChildrenIntoPanel(m_menu_position_buttons, IC_MODE_SIZE, IC_MODE_PLACEMENT_START,  QSize(MODE_POS_COLUMN, 1));
            break;
        }
        case INPUT_NUM_TYPE_CONTROL:
        {
            for (int i = 0; i< param->count;i++)
            {
                auto button =  MakeSharedQObject<SelectButton>(this);
                button->setFixedSize(IC_MODE_SIZE);
                button->setText(param->param[i].name);
                button->setChecked(param->param[i].select);
                button->setVisible(false);
                connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
                    onButtonModeControlCheck(i,sender());
                });
                m_menu_control_buttons.push_back(button);
            }
            placeChildrenIntoPanel(m_menu_control_buttons, IC_MODE_SIZE, IC_MODE_PLACEMENT_START, QSize(MODE_COLUMN, 1));
            break;
        }
    }
    setType(param->type);
    setMode(param->mode);
    onTypeChanged();
    onCurrentButtonModePageChanged();
}

void InputNumControl::onButtonModeColorCheck(const int index, QObject *sender)
{
    if (index < m_menu_color_buttons.size())
    {
        for (int i = 0; i < m_menu_color_buttons.size(); i++)
        {
            if (i != index)
            {
                m_menu_color_buttons[i]->setChecked(false);
            }

        }
    }
}

void InputNumControl::onButtonModePositionCheck(const int index, QObject *sender)
{
    if (index < m_menu_position_buttons.size())
    {
        for (int i = 0; i < m_menu_position_buttons.size(); i++)
        {
            if (i != index)
            {
                m_menu_position_buttons[i]->setChecked(false);
            }

        }
    }
}

void InputNumControl::onButtonModeGoboCheck(const int index, QObject *sender)
{
    if (index < m_menu_gobo_buttons.size())
    {
        for (int i = 0; i < m_menu_gobo_buttons.size(); i++)
        {
            if (i != index)
            {
                m_menu_gobo_buttons[i]->setChecked(false);
            }

        }
    }
}

void InputNumControl::onButtonModeShutterCheck(const int index, QObject *sender)
{
    if (index < m_menu_shutter_buttons.size())
    {
        for (int i = 0; i < m_menu_shutter_buttons.size(); i++)
        {
            if (i != index)
            {
                m_menu_shutter_buttons[i]->setChecked(false);
            }

        }
    }
}

void InputNumControl::onButtonModeControlCheck(const int index, QObject *sender)
{
    if (index < m_menu_control_buttons.size())
    {
        for (int i = 0; i < m_menu_control_buttons.size(); i++)
        {
            if (i != index)
            {
                m_menu_control_buttons[i]->setChecked(false);
            }

        }
    }
}

void InputNumControl::onModeChanged()
{
    m_button_mode_percent.setChecked(mode() == INPUT_NUM_MODE_PERCENT);
    m_button_mode_255.setChecked(mode() == INPUT_NUM_MODE_255);
    m_button_mode_angle.setChecked(mode() == INPUT_NUM_MODE_ANGLE);
}

void InputNumControl::onTypeChanged()
{
    if (type() == INPUT_NUM_TYPE_COLOR)
    {
        updateChildrenVisibility(m_menu_color_buttons,0, MODE_COLUMN);
        bool more_than_4 = m_menu_color_buttons.size() > 4;
        m_button_previous_tab.setVisible(more_than_4);
        m_button_next_tab.setVisible(more_than_4);
    }
    if (type() == INPUT_NUM_TYPE_CONTROL)
    {
        updateChildrenVisibility(m_menu_control_buttons,0, MODE_COLUMN);
        bool more_than_4 = m_menu_control_buttons.size() > 4;
        m_button_previous_tab.setVisible(more_than_4);
        m_button_next_tab.setVisible(more_than_4);
    }
    if (type() == INPUT_NUM_TYPE_GOBO)
    {
        updateChildrenVisibility(m_menu_gobo_buttons,0, MODE_COLUMN);
        bool more_than_4 = m_menu_gobo_buttons.size() > 4;
        m_button_previous_tab.setVisible(more_than_4);
        m_button_next_tab.setVisible(more_than_4);
    }
    if (type() == INPUT_NUM_TYPE_POSITION)
    {
        updateChildrenVisibility(m_menu_position_buttons,0, MODE_POS_COLUMN);
        qDebug() <<m_menu_position_buttons.size();
        bool more_than_4 = m_menu_position_buttons.size() > 3;
        m_button_previous_tab.setVisible(more_than_4);
        m_button_next_tab.setVisible(more_than_4);
        m_button_relative.setVisible(true);
        m_button_absolute.setVisible(true);
        m_button_mode_angle.setVisible(true);
    }
    else
    {
        m_button_relative.setVisible(false);
        m_button_absolute.setVisible(false);
        m_button_mode_angle.setVisible(false);
    }
    if (type() == INPUT_NUM_TYPE_BEAM_SHUTTER)
    {
        updateChildrenVisibility(m_menu_shutter_buttons,0, MODE_COLUMN);
        bool more_than_4 = m_menu_shutter_buttons.size() > 4;
        m_button_previous_tab.setVisible(more_than_4);
        m_button_next_tab.setVisible(more_than_4);
    }
}

void InputNumControl::onCurrentButtonModePageChanged()
{
    if (type() == INPUT_NUM_TYPE_COLOR)
    {
        qDebug() << currentButtonModePage();
        updateChildrenVisibility(m_menu_color_buttons,currentButtonModePage(), MODE_COLUMN);
        m_button_previous_tab.setEnabled(currentButtonModePage() > 0);
        m_button_next_tab.setEnabled(currentButtonModePage() < calulateNumberOfPages(m_menu_color_buttons.length(), MODE_COLUMN) - 1);
    }
    if (type() == INPUT_NUM_TYPE_CONTROL)
    {
        updateChildrenVisibility(m_menu_control_buttons,currentButtonModePage(), MODE_COLUMN);
        m_button_previous_tab.setEnabled(currentButtonModePage() > 0);
        m_button_next_tab.setEnabled(currentButtonModePage() < calulateNumberOfPages(m_menu_control_buttons.length(), MODE_COLUMN) - 1);
    }
    if (type() == INPUT_NUM_TYPE_GOBO)
    {
        qDebug() << currentButtonModePage();
        updateChildrenVisibility(m_menu_gobo_buttons,currentButtonModePage(), MODE_COLUMN);
        m_button_previous_tab.setEnabled(currentButtonModePage() > 0);
        m_button_next_tab.setEnabled(currentButtonModePage() < calulateNumberOfPages(m_menu_gobo_buttons.length(), MODE_COLUMN) - 1);
    }
    if (type() == INPUT_NUM_TYPE_POSITION)
    {
        updateChildrenVisibility(m_menu_position_buttons,currentButtonModePage(), MODE_POS_COLUMN);
        m_button_previous_tab.setEnabled(currentButtonModePage() > 0);
        m_button_next_tab.setEnabled(currentButtonModePage() < calulateNumberOfPages(m_menu_position_buttons.length(), MODE_POS_COLUMN) - 1);
    }
    if (type() == INPUT_NUM_TYPE_BEAM_SHUTTER)
    {
        updateChildrenVisibility(m_menu_shutter_buttons,currentButtonModePage(), MODE_COLUMN);
        m_button_previous_tab.setEnabled(currentButtonModePage() > 0);
        m_button_next_tab.setEnabled(currentButtonModePage() < calulateNumberOfPages(m_menu_shutter_buttons.length(), MODE_COLUMN) - 1);
    }
}

void InputNumControl::onButtonMode255Clicked(const bool check)
{
    if (check)
    {
        setMode(INPUT_NUM_MODE_255);
    }
}

void InputNumControl::onButtonModeAngelClicked(const bool check)
{
    if (check)
    {
        setMode(INPUT_NUM_MODE_ANGLE);
    }
}

void InputNumControl::onButtonModePercentClicked(const bool check)
{
    if (check)
    {
        setMode(INPUT_NUM_MODE_PERCENT);
    }
}

void InputNumControl::onButtonRelativeClicked(const bool check)
{
    if (check)
    {
        m_button_absolute.setChecked(false);
    }
}

void InputNumControl::onButtonAbsoluteClicked(const bool check)
{
    if (check)
    {
        m_button_relative.setChecked(false);
    }
}

InputNumMode InputNumControl::mode() const
{
    return m_mode;
}

void InputNumControl::setMode(InputNumMode newMode)
{
    if (m_mode == newMode)
        return;
    m_mode = newMode;
    emit modeChanged();
}

InputNumType InputNumControl::type() const
{
    return m_type;
}

void InputNumControl::setType(InputNumType newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

int InputNumControl::currentButtonModePage() const
{
    return m_currentButtonModePage;
}

void InputNumControl::setCurrentButtonModePage(int newCurrentButtonModePage)
{
    if (m_currentButtonModePage == newCurrentButtonModePage)
        return;
    m_currentButtonModePage = newCurrentButtonModePage;
    emit currentButtonModePageChanged();
}
