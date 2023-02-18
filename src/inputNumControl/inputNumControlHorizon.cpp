#include "inputNumControl/inputNumControlHorizon.h"
#include "utility.h"


#define BASE_BUTTON_WIDTH IC_HORIZON_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT IC_HORIZON_BUTTON1_GEOMETRY.height()
#define MODE_ROW 1
#define MODE_COLUMN 5

InputNumControlHorizon::InputNumControlHorizon(QWidget *parent) :InputNumControl(parent),
    m_picker_button(this),
    m_encoder_button(this),
    m_number_button(this)
{
    setCurrentButtonModePage(0);
    setFixedSize(IC_HORIZON_SCREEN_SIZE);
}

void InputNumControlHorizon::SetDispParamDataHorizon(INPUT_NUM_DISP_PARAM *param)
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
                button->setFixedSize(IC_HORIZON_MODE_SIZE);
                button->setText(param->param[i].name);
                button->setChecked(param->param[i].select);
                button->setVisible(false);
                connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
                    onButtonModeColorCheck(i,sender());
                });
                m_menu_color_buttons.push_back(button);
            }
            placeChildrenIntoPanel(m_menu_color_buttons, IC_HORIZON_MODE_SIZE, IC_HORIZON_MODE_PLACEMENT_START, MODE_COLUMN );
            break;
        }
        case INPUT_NUM_TYPE_GOBO:
        {
            for (int i = 0; i< param->count;i++)
            {
                auto button =  MakeSharedQObject<SelectButton>(this);
                button->setFixedSize(IC_HORIZON_MODE_SIZE);
                button->setText(param->param[i].name);
                button->setChecked(param->param[i].select);
                button->setVisible(false);
                connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
                    onButtonModeGoboCheck(i,sender());
                });
                m_menu_gobo_buttons.push_back(button);
            }
            placeChildrenIntoPanel(m_menu_gobo_buttons, IC_HORIZON_MODE_SIZE, IC_HORIZON_MODE_PLACEMENT_START, MODE_COLUMN);
            break;
        }
        case INPUT_NUM_TYPE_BEAM_SHUTTER:
        {
            for (int i = 0; i< param->count;i++)
            {
                auto button =  MakeSharedQObject<SelectButton>(this);
                button->setFixedSize(IC_HORIZON_MODE_SIZE);
                button->setText(param->param[i].name);
                button->setChecked(param->param[i].select);
                button->setVisible(false);
                connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
                    onButtonModeShutterCheck(i,sender());
                });
                m_menu_shutter_buttons.push_back(button);
            }
            placeChildrenIntoPanel(m_menu_shutter_buttons, IC_HORIZON_MODE_SIZE, IC_HORIZON_MODE_PLACEMENT_START,  MODE_COLUMN);
            break;
        }
        case INPUT_NUM_TYPE_POSITION:
        {
            for (int i = 0; i< param->count;i++)
            {
                auto button =  MakeSharedQObject<SelectButton>(this);
                button->setFixedSize(IC_HORIZON_MODE_SIZE);
                button->setText(param->param[i].name);
                button->setChecked(param->param[i].select);
                button->setVisible(false);
                connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
                    onButtonModePositionCheck(i,sender());
                });
                m_menu_position_buttons.push_back(button);
            }
            placeChildrenIntoPanel(m_menu_position_buttons, IC_HORIZON_MODE_SIZE, IC_HORIZON_MODE_PLACEMENT_START,  MODE_COLUMN);
            break;
        }
        case INPUT_NUM_TYPE_CONTROL:
        {
            for (int i = 0; i< param->count;i++)
            {
                auto button =  MakeSharedQObject<SelectButton>(this);
                button->setFixedSize(IC_HORIZON_MODE_SIZE);
                button->setText(param->param[i].name);
                button->setChecked(param->param[i].select);
                button->setVisible(false);
                connect(button.get(),&QAbstractButton::clicked, this, [&,i](){
                    onButtonModeControlCheck(i,sender());
                });
                m_menu_control_buttons.push_back(button);
            }
            placeChildrenIntoPanel(m_menu_control_buttons, IC_HORIZON_MODE_SIZE, IC_HORIZON_MODE_PLACEMENT_START, MODE_COLUMN);
            break;
        }
    }
    setType(param->type);
    setMode(param->mode);
    onTypeChanged();
    onCurrentButtonModePageChanged();
}

void InputNumControlHorizon::SetupUiComponents()
{
    m_grid.setGridSize(QSize(6, 5));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 34);

    m_label_title.setGeometry(IC_HORIZON_TITLE_GEOMETRY);
    m_label_title.setObjectName("title_label_horizon");
    m_label_title.setText("数値入力");

    m_button_mode_percent.setGeometry(IC_HORIZON_PERCENT_GEOMETRY);
    m_button_mode_percent.setText("%");
    m_button_mode_255.setGeometry(IC_HORIZON_255_GEOMETRY);
    m_button_mode_255.setText("255");

    m_button_mode_angle.setText("角度");
    m_button_mode_angle.setVisible(false);

    m_button_relative.setText("相対");
    m_button_absolute.setText("絶対");
    m_button_relative.setVisible(false);
    m_button_absolute.setVisible(false);

    m_encoder_button.setGeometry(IC_HORIZON_ENCODER_GEOMETRY);
    m_encoder_button.setText("エンコーダ");

    m_picker_button.setGeometry(IC_HORIZON_PICKER_GEOMETRY);
    m_picker_button.setText("ピッカー");

    m_number_button.setGeometry(IC_HORIZON_NUMBER_GEOMETRY);
    m_number_button.setChecked(true);
    m_number_button.setText("数値");

    m_button_previous_tab.setGeometry(IC_HORIZON_PREV_GEOMETRY);
    m_button_previous_tab.setText("◀");

    m_button_next_tab.setGeometry(IC_HORIZON_NEXT_GEOMETRY);
    m_button_next_tab.setText("▶");

    m_return_button.setGeometry(IC_HORIZON_RETURN_GEOMETRY);
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
        button->setFixedSize(IC_HORIZON_BUTTON_SIZE);
        button->setVisible(true);
        button->setText(b);


        connect(button.get(), &QPushButton::clicked, this, [&]() {
            qDebug() << ((CustomPushButton*)sender())->text();
        });

        m_input_num_buttons.append(button);
    }
    placeChildrenIntoPanel(m_input_num_buttons, IC_HORIZON_BUTTON_SIZE, IC_HORIZON_BUTTON_TOPLEFT, 4, 5);
}

void InputNumControlHorizon::SetupUiEvents()
{
    InputNumControl::SetupUiEvents();
    connect(&m_picker_button, &QPushButton::clicked, this, &InputNumControlHorizon::onButtonPickerClicked);
    connect(&m_encoder_button, &QPushButton::clicked, this, &InputNumControlHorizon::onButtonEncoderClicked);
    connect(&m_number_button, &QPushButton::clicked, this, &InputNumControlHorizon::onButtonNumberClicked);
}

void InputNumControlHorizon::onModeChanged()
{
    m_button_mode_percent.setChecked(mode() == INPUT_NUM_MODE_PERCENT);
    m_button_mode_255.setChecked(mode() == INPUT_NUM_MODE_255);
}

void InputNumControlHorizon::onTypeChanged()
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
        updateChildrenVisibility(m_menu_position_buttons,0, MODE_COLUMN);
        qDebug() <<m_menu_position_buttons.size();
        bool more_than_4 = m_menu_position_buttons.size() > 4;
        m_button_previous_tab.setVisible(more_than_4);
        m_button_next_tab.setVisible(more_than_4);
    }

    if (type() == INPUT_NUM_TYPE_BEAM_SHUTTER)
    {
        updateChildrenVisibility(m_menu_shutter_buttons,0, MODE_COLUMN);
        bool more_than_4 = m_menu_shutter_buttons.size() > 4;
        m_button_previous_tab.setVisible(more_than_4);
        m_button_next_tab.setVisible(more_than_4);
    }
}

void InputNumControlHorizon::onCurrentButtonModePageChanged()
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
        updateChildrenVisibility(m_menu_position_buttons,currentButtonModePage(), MODE_COLUMN);
        m_button_previous_tab.setEnabled(currentButtonModePage() > 0);
        m_button_next_tab.setEnabled(currentButtonModePage() < calulateNumberOfPages(m_menu_position_buttons.length(), MODE_COLUMN) - 1);
    }
    if (type() == INPUT_NUM_TYPE_BEAM_SHUTTER)
    {
        updateChildrenVisibility(m_menu_shutter_buttons,currentButtonModePage(), MODE_COLUMN);
        m_button_previous_tab.setEnabled(currentButtonModePage() > 0);
        m_button_next_tab.setEnabled(currentButtonModePage() < calulateNumberOfPages(m_menu_shutter_buttons.length(), MODE_COLUMN) - 1);
    }
}

void InputNumControlHorizon::onButtonPickerClicked(const bool check)
{
    if (check)
    {
        m_encoder_button.setChecked(false);
        m_number_button.setChecked(false);
    }
}

void InputNumControlHorizon::onButtonEncoderClicked(const bool check)
{
    if (check)
    {
        m_picker_button.setChecked(false);
        m_number_button.setChecked(false);
    }
}

void InputNumControlHorizon::onButtonNumberClicked(const bool check)
{
    if (check)
    {
        m_picker_button.setChecked(false);
        m_encoder_button.setChecked(false);
    }
}
