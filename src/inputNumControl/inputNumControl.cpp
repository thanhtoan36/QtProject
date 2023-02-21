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

    connect(this, &InputNumControl::modeChanged, this, &InputNumControl::onModeChanged);
    connect(this, &InputNumControl::valueModeChanged, this, &InputNumControl::onValueModeChanged);
    connect(this, &InputNumControl::typeChanged, this, &InputNumControl::onTypeChanged);

    connect(&m_button_previous_tab, &QPushButton::clicked, this, [&](){
        setCurrentGroupButtonsPage(currentGroupButtonsPage() - 1);
    });
    connect(&m_button_next_tab, &QPushButton::clicked, this, [&](){
        setCurrentGroupButtonsPage(currentGroupButtonsPage() + 1);
    });
    connect(this, &InputNumControl::currentGroupButtonsPageChanged, this, &InputNumControl::setupGroupButtonPages);
    connect(&m_button_mode_255, &QPushButton::clicked, this, [&](){
        setMode(INPUT_NUM_MODE_255);
    });
    connect(&m_button_mode_percent, &QPushButton::clicked, this, [&](){
        setMode(INPUT_NUM_MODE_PERCENT);
    });
    connect(&m_button_mode_angle, &QPushButton::clicked, this, [&](){
        setMode(INPUT_NUM_MODE_ANGLE);
    });
    connect(&m_button_relative, &QPushButton::clicked, this, [&](){
        setValueMode(INPUT_NUM_MODE_RELATIVE);
    });
    connect(&m_button_absolute, &QPushButton::clicked, this, [&](){
        setValueMode(INPUT_NUM_MODE_ABSOLUTE);
    });
    connect(&m_return_button, &QPushButton::clicked, this, &InputNumControl::ReturnClicked);

    onModeChanged();
    onValueModeChanged();
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
            connect(button.get(),&QAbstractButton::clicked, this, &InputNumControl::onGroupButtonClicked);
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
            connect(button.get(),&QAbstractButton::clicked, this, &InputNumControl::onGroupButtonClicked);
            m_group_buttons.push_back(button);
        }
    }


    placeChildrenIntoPanel(m_group_buttons, IC_MODE_SIZE, IC_MODE_PLACEMENT_START, QSize(MODE_COLUMN, 1) );
    setType(param->type);
    setMode(param->mode);

    setCurrentGroupButtonsPage(0);
    setupGroupButtonPages();
    onTypeChanged();

    m_button_next_tab.setVisible(maxGroupButtonPages() > 1);
    m_button_previous_tab.setVisible(maxGroupButtonPages() > 1);
    SetCurrentModeButton(current_mode);
}

void InputNumControl::onModeChanged()
{
    m_button_mode_percent.setChecked(mode() == INPUT_NUM_MODE_PERCENT);
    m_button_mode_255.setChecked(mode() == INPUT_NUM_MODE_255);
    m_button_mode_angle.setChecked(mode() == INPUT_NUM_MODE_ANGLE);
}

void InputNumControl::onValueModeChanged()
{
    m_button_relative.setChecked(valueMode() == INPUT_NUM_MODE_RELATIVE);
    m_button_absolute.setChecked(valueMode() == INPUT_NUM_MODE_ABSOLUTE);
}

void InputNumControl::onTypeChanged()
{
    m_button_relative.setVisible(type() == INPUT_NUM_TYPE_POSITION);
    m_button_absolute.setVisible(type() == INPUT_NUM_TYPE_POSITION);
    placeChildrenIntoPanel(m_group_buttons, IC_MODE_SIZE, IC_MODE_PLACEMENT_START, QSize(groupButtonsPerPage(), 1) );
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

void InputNumControl::onGroupButtonClicked()
{
    for (const auto &button: qAsConst(m_group_buttons))
    {
        button->setChecked(button == sender());
    }
    SetCurrentModeButton(((SelectButton*)sender())->text());
}

InputNumValueMode InputNumControl::valueMode() const
{
    return m_valueMode;
}

void InputNumControl::setValueMode(const InputNumValueMode &newValueMode)
{
    if (m_valueMode == newValueMode)
        return;
    m_valueMode = newValueMode;
    emit valueModeChanged();
}

void InputNumControl::setupGroupButtonPages()
{
    m_button_previous_tab.setEnabled(currentGroupButtonsPage() > 0);
    m_button_next_tab.setEnabled(currentGroupButtonsPage() < maxGroupButtonPages() - 1);

    UpdateChildrenVisibility(m_group_buttons, currentGroupButtonsPage(), groupButtonsPerPage());
}

int InputNumControl::currentGroupButtonsPage() const
{
    return m_currentGroupButtonsPage;
}

void InputNumControl::setCurrentGroupButtonsPage(int newCurrentGroupButtonsPage)
{
    newCurrentGroupButtonsPage = qBound(newCurrentGroupButtonsPage, 0, maxGroupButtonPages() - 1);
    if (m_currentGroupButtonsPage == newCurrentGroupButtonsPage)
        return;
    m_currentGroupButtonsPage = newCurrentGroupButtonsPage;
    emit currentGroupButtonsPageChanged();
}

int InputNumControl::maxGroupButtonPages() const
{
    return calulateNumberOfPages(m_group_buttons.length(), groupButtonsPerPage());
}

int InputNumControl::groupButtonsPerPage() const
{
    if (type() == INPUT_NUM_TYPE_POSITION)
        return 3;
    return 4;
}

const QString &InputNumControl::CurrentModeButton() const
{
    return m_currentModeButton;
}

void InputNumControl::SetCurrentModeButton(const QString &newCurrentModeButton)
{
    if (m_currentModeButton == newCurrentModeButton)
        return;
    m_currentModeButton = newCurrentModeButton;
    emit CurrentModeButtonChanged();
}
