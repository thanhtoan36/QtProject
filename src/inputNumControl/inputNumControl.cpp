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
    m_group_buttons_per_page = 4;

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
            emit InputNumButtonClicked(((CustomPushButton*)sender())->text());
        });

        m_input_num_buttons.append(button);
    }
    placeChildrenIntoPanel(m_input_num_buttons, IC_BUTTON_SIZE, IC_BUTTON_TOPLEFT, QSize(4, 4));

    connect(this, &InputNumControl::ModeChanged, this, &InputNumControl::OnModeChanged);
    connect(this, &InputNumControl::ValueModeChanged, this, &InputNumControl::OnValueModeChanged);
    connect(this, &InputNumControl::TypeChanged, this, &InputNumControl::OnTypeChanged);

    connect(&m_button_previous_tab, &QPushButton::clicked, this, [&](){
        SetCurrentGroupButtonsPage(CurrentGroupButtonsPage() - 1);
    });
    connect(&m_button_next_tab, &QPushButton::clicked, this, [&](){
        SetCurrentGroupButtonsPage(CurrentGroupButtonsPage() + 1);
    });
    connect(this, &InputNumControl::CurrentGroupButtonsPageChanged, this, &InputNumControl::SetupGroupButtonPages);
    connect(&m_button_mode_255, &QPushButton::clicked, this, [&](){
        SetMode(INPUT_NUM_MODE_255);
    });
    connect(&m_button_mode_percent, &QPushButton::clicked, this, [&](){
        SetMode(INPUT_NUM_MODE_PERCENT);
    });
    connect(&m_button_mode_angle, &QPushButton::clicked, this, [&](){
        SetMode(INPUT_NUM_MODE_ANGLE);
    });
    connect(&m_button_relative, &QPushButton::clicked, this, [&](){
        SetValueMode(INPUT_NUM_MODE_RELATIVE);
    });
    connect(&m_button_absolute, &QPushButton::clicked, this, [&](){
        SetValueMode(INPUT_NUM_MODE_ABSOLUTE);
    });
    connect(&m_return_button, &QPushButton::clicked, this, &InputNumControl::ReturnClicked);

    OnModeChanged();
    OnValueModeChanged();
}

void InputNumControl::SetDispParamData(INPUT_NUM_DISP_PARAM *param)
{
    Q_ASSERT(param);
    m_group_buttons.clear();
    QString current_mode;
    // type position has fixed button PAN and TILT
    if (param->type == INPUT_NUM_TYPE_POSITION)
    {
        m_button_mode_angle.setVisible(true);
        for (int i = 0; i< 2;i++)
        {
            auto button =  MakeSharedQObject<SelectButton>(this);
            button->setFixedSize(IC_MODE_SIZE);
            if (i == 0)
            {
                button->setText("PAN");
                button->setChecked(true);
                current_mode = "PAN";
            }
            else
            {
                button->setText("TILT");
                button->setChecked(false);
            }

            button->setVisible(false);
            button->setCheckMarkVisible(true);
            connect(button.get(),&QAbstractButton::clicked, this, &InputNumControl::OnGroupButtonClicked);
            m_group_buttons.push_back(button);
        }
    }
    else
    {
        m_button_mode_angle.setVisible(false);
        for (int i = 0; i< param->count;i++)
        {
            auto button =  MakeSharedQObject<SelectButton>(this);
            button->setFixedSize(IC_MODE_SIZE);
            button->setText(param->param[i].name);
            button->setChecked(param->param[i].select);
            if (param->param[i].select)
            {
                current_mode = param->param[i].name;
            }
            button->setVisible(false);
            button->setCheckMarkVisible(true);
            connect(button.get(),&QAbstractButton::clicked, this, &InputNumControl::OnGroupButtonClicked);
            m_group_buttons.push_back(button);
        }
    }


    placeChildrenIntoPanel(m_group_buttons, IC_MODE_SIZE, IC_MODE_PLACEMENT_START, QSize(MODE_COLUMN, 1) );
    SetType(param->type);
    SetMode(param->mode);

    SetCurrentGroupButtonsPage(0);
    SetupGroupButtonPages();
    OnTypeChanged();

    m_button_next_tab.setVisible(MaxGroupButtonPages() > 1);
    m_button_previous_tab.setVisible(MaxGroupButtonPages() > 1);
    SetCurrentModeButton(current_mode);
}

void InputNumControl::OnModeChanged()
{
    m_button_mode_percent.setChecked(Mode() == INPUT_NUM_MODE_PERCENT);
    m_button_mode_255.setChecked(Mode() == INPUT_NUM_MODE_255);
    m_button_mode_angle.setChecked(Mode() == INPUT_NUM_MODE_ANGLE);
}

void InputNumControl::OnValueModeChanged()
{
    m_button_relative.setChecked(ValueMode() == INPUT_NUM_MODE_RELATIVE);
    m_button_absolute.setChecked(ValueMode() == INPUT_NUM_MODE_ABSOLUTE);
}

void InputNumControl::OnTypeChanged()
{
    m_button_relative.setVisible(Type() == INPUT_NUM_TYPE_POSITION);
    m_button_absolute.setVisible(Type() == INPUT_NUM_TYPE_POSITION);
    placeChildrenIntoPanel(m_group_buttons, IC_MODE_SIZE, IC_MODE_PLACEMENT_START, QSize(GroupButtonsPerPage(), 1) );
}

InputNumMode InputNumControl::Mode() const
{
    return m_mode;
}

void InputNumControl::SetMode(InputNumMode newMode)
{
    if (m_mode == newMode)
        return;
    m_mode = newMode;
    emit ModeChanged();
}

InputNumType InputNumControl::Type() const
{
    return m_type;
}

void InputNumControl::SetType(InputNumType newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit TypeChanged();
}

void InputNumControl::OnGroupButtonClicked()
{
    for (const auto &button: qAsConst(m_group_buttons))
    {
        button->setChecked(button == sender());
    }
    SetCurrentModeButton(((SelectButton*)sender())->text());
}

InputNumValueMode InputNumControl::ValueMode() const
{
    return m_valueMode;
}

void InputNumControl::SetValueMode(const InputNumValueMode &mode)
{
    if (m_valueMode == mode)
        return;
    m_valueMode = mode;
    emit ValueModeChanged();
}

void InputNumControl::SetupGroupButtonPages()
{
    m_button_previous_tab.setEnabled(CurrentGroupButtonsPage() > 0);
    m_button_next_tab.setEnabled(CurrentGroupButtonsPage() < MaxGroupButtonPages() - 1);

    UpdateChildrenVisibility(m_group_buttons, CurrentGroupButtonsPage(), GroupButtonsPerPage());
}

int InputNumControl::CurrentGroupButtonsPage() const
{
    return m_current_group_buttons_page;
}

void InputNumControl::SetCurrentGroupButtonsPage(int page)
{
    page = qBound(page, 0, MaxGroupButtonPages() - 1);
    if (m_current_group_buttons_page == page)
        return;
    m_current_group_buttons_page = page;
    emit CurrentGroupButtonsPageChanged();
}

int InputNumControl::MaxGroupButtonPages() const
{
    return CalulateNumberOfPages(m_group_buttons.length(), GroupButtonsPerPage());
}

int InputNumControl::GroupButtonsPerPage() const
{
    if (Type() == INPUT_NUM_TYPE_POSITION)
        return 3;
    return 4;
}

const QString &InputNumControl::CurrentModeButton() const
{
    return m_current_mode_button;
}

void InputNumControl::SetCurrentModeButton(const QString &mode)
{
    if (m_current_mode_button == mode)
        return;
    m_current_mode_button = mode;
    emit CurrentModeButtonChanged();
}
