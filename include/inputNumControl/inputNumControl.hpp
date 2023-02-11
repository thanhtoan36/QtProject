#ifndef INPUTNUMCONTROL_H
#define INPUTNUMCONTROL_H

#include "baseComponent/panelControlBase.h"
#include "baseComponent/customPushButton.h"
#include "baseComponent/selectButton.h"
#include "inputNumControl_datatypes.h"
#include "baseComponent/gridBackground.h"
#include <QLabel>

class InputNumControl : public PanelControlBase
{
    Q_OBJECT
    Q_PROPERTY(InputNumMode mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(InputNumType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(int currentButtonModePage READ currentButtonModePage WRITE setCurrentButtonModePage NOTIFY currentButtonModePageChanged)

public:
    explicit InputNumControl(QWidget* parent = nullptr);
    void SetDispParamData(INPUT_NUM_DISP_PARAM *param);

    InputNumMode mode() const;
    void setMode(InputNumMode newMode);

    InputNumType type() const;
    void setType(InputNumType newType);

    int currentButtonModePage() const;
    void setCurrentButtonModePage(int newCurrentButtonModePage);

signals:
    void modeChanged();

    void typeChanged();

    void currentButtonModePageChanged();

protected:
    virtual void SetupUiComponents() override;
    virtual void SetupUiEvents() override;

    void onButtonModeColorCheck(const int index, QObject* sender);
    void onButtonModePositionCheck(const int index, QObject* sender);
    void onButtonModeGoboCheck(const int index, QObject* sender);
    void onButtonModeShutterCheck(const int index, QObject* sender);
    void onButtonModeControlCheck(const int index, QObject* sender);

protected slots:
    virtual void onModeChanged();
    virtual void onTypeChanged();
    virtual void onCurrentButtonModePageChanged();
    void onButtonMode255Clicked(const bool check);
    void onButtonModeAngelClicked(const bool check);
    void onButtonModePercentClicked(const bool check);
    void onButtonRelativeClicked(const bool check);
    void onButtonAbsoluteClicked(const bool check);

protected:
    GridBackground m_grid;
    QLabel m_label_title;
    SelectButton m_button_mode_percent;
    SelectButton m_button_mode_255;
    SelectButton m_button_mode_angel;
    SelectButton m_button_relative;
    SelectButton m_button_absolute;

    CustomPushButton m_button_previous_tab;
    CustomPushButton m_button_next_tab;



    QVector<QSharedPointer<SelectButton>> m_menu_color_buttons;
    QVector<QSharedPointer<SelectButton>> m_menu_position_buttons;
    QVector<QSharedPointer<SelectButton>> m_menu_gobo_buttons;
    QVector<QSharedPointer<SelectButton>> m_menu_shutter_buttons;
    QVector<QSharedPointer<SelectButton>> m_menu_control_buttons;
    QVector<QSharedPointer<CustomPushButton>> m_input_num_buttons;
    CustomPushButton m_return_button;

    InputNumMode m_mode;
    InputNumType m_type;
    int m_currentButtonModePage;

};


#endif // INPUTNUMCONTROL_H
