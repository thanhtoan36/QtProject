#include "inputNumControl/inputNumControlHorizon.h"
#include "inputNumControl/inputNumControlHorizon_define.h"
#include "utility.h"


#define BASE_BUTTON_WIDTH IC_HORIZON_BUTTON1_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT IC_HORIZON_BUTTON1_GEOMETRY.height()
#define MODE_ROW 1
#define MODE_COLUMN 5

InputNumControlHorizon::InputNumControlHorizon(QWidget *parent) :InputNumControl(parent),
    m_button_switch_panel_picker(this),
    m_button_switch_panel_encoder(this),
    m_button_switch_panel_input_num(this)
{
    setFixedSize(IC_HORIZON_SCREEN_SIZE);

    m_grid.setGridSize(QSize(6, 5));
    m_grid.setCellSize(QSize(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT));
    m_grid.move(0, 34);

    m_label_title.setGeometry(IC_HORIZON_TITLE_GEOMETRY);
    m_label_title.setObjectName("title_label_with_border");

    m_button_mode_percent.setGeometry(IC_HORIZON_PERCENT_GEOMETRY);
    m_button_mode_255.setGeometry(IC_HORIZON_255_GEOMETRY);
    m_button_mode_angle.setVisible(false);

    m_button_relative.setVisible(false);
    m_button_absolute.setVisible(false);

    m_button_switch_panel_encoder.setGeometry(IC_HORIZON_ENCODER_GEOMETRY);
    m_button_switch_panel_encoder.setText("エンコーダ");

    m_button_switch_panel_picker.setGeometry(IC_HORIZON_PICKER_GEOMETRY);
    m_button_switch_panel_picker.setText("ピッカー");

    m_button_switch_panel_input_num.setGeometry(IC_HORIZON_NUMBER_GEOMETRY);
    m_button_switch_panel_input_num.setChecked(true);
    m_button_switch_panel_input_num.setText("数値");

    m_button_previous_tab.setGeometry(IC_HORIZON_PREV_GEOMETRY);
    m_button_next_tab.setGeometry(IC_HORIZON_NEXT_GEOMETRY);
    m_return_button.setGeometry(IC_HORIZON_RETURN_GEOMETRY);

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
    placeChildrenIntoPanel(m_input_num_buttons, IC_HORIZON_BUTTON_SIZE, IC_HORIZON_BUTTON_TOPLEFT, QSize(4, 4));

    connect(&m_button_switch_panel_picker, &QAbstractButton::clicked, this, &InputNumControlHorizon::onPanelSwitchButtonClicked);
    connect(&m_button_switch_panel_encoder, &QAbstractButton::clicked, this, &InputNumControlHorizon::onPanelSwitchButtonClicked);
    connect(&m_button_switch_panel_input_num, &QAbstractButton::clicked, this, &InputNumControlHorizon::onPanelSwitchButtonClicked);
}

void InputNumControlHorizon::onPanelSwitchButtonClicked()
{
    m_button_switch_panel_picker.setChecked(false);
    m_button_switch_panel_encoder.setChecked(false);
    m_button_switch_panel_input_num.setChecked(false);
    ((QAbstractButton*)sender())->setChecked(true);
}

void InputNumControlHorizon::onTypeChanged()
{
    InputNumControl::onTypeChanged();
    placeChildrenIntoPanel(m_group_buttons, IC_HORIZON_MODE_SIZE, IC_HORIZON_MODE_PLACEMENT_START, QSize(groupButtonsPerPage(), 1) );
}

int InputNumControlHorizon::groupButtonsPerPage() const
{
    return 5;
}
