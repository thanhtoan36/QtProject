#ifndef INPUTNUMCONTROL_H
#define INPUTNUMCONTROL_H

#include "baseComponent/panelControlBase.h"
#include "baseComponent/customPushButton.h"
#include "baseComponent/selectButton.h"
#include "inputNumControl_datatypes.h"
#include "baseComponent/gridBackground.h"
#include <QLabel>

enum InputNumValueMode
{
    INPUT_NUM_MODE_RELATIVE,
    INPUT_NUM_MODE_ABSOLUTE,
};

class InputNumControl : public PanelControlBase
{
    Q_OBJECT
    Q_PROPERTY(InputNumMode mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(InputNumValueMode valueMode READ valueMode WRITE setValueMode NOTIFY valueModeChanged)
    Q_PROPERTY(InputNumType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(int currentGroupButtonsPage READ currentGroupButtonsPage WRITE setCurrentGroupButtonsPage NOTIFY currentGroupButtonsPageChanged)

public:
    explicit InputNumControl(QWidget* parent = nullptr);
    void SetDispParamData(INPUT_NUM_DISP_PARAM *param);

    InputNumMode mode() const;
    void setMode(InputNumMode newMode);

    InputNumType type() const;
    void setType(InputNumType newType);

    InputNumValueMode valueMode() const;
    void setValueMode(const InputNumValueMode &newValueMode);

    int currentGroupButtonsPage() const;
    void setCurrentGroupButtonsPage(int newCurrentGroupButtonsPage);

signals:
    void modeChanged();
    void typeChanged();
    void currentButtonModePageChanged();
    void valueModeChanged();
    void currentGroupButtonsPageChanged();

protected:
    int maxGroupButtonPages() const;
    virtual int groupButtonsPerPage() const;
    virtual void setupGroupButtonPages();
    void onGroupButtonClicked();

protected slots:
    void onModeChanged();
    void onValueModeChanged();
    virtual void onTypeChanged();

protected:
    GridBackground m_grid;
    QLabel m_label_title;
    SelectButton m_button_mode_percent;
    SelectButton m_button_mode_255;
    SelectButton m_button_mode_angle;
    SelectButton m_button_relative;
    SelectButton m_button_absolute;

    CustomPushButton m_button_previous_tab;
    CustomPushButton m_button_next_tab;

    QVector<QSharedPointer<SelectButton>> m_group_buttons;
    QVector<QSharedPointer<CustomPushButton>> m_input_num_buttons;
    CustomPushButton m_return_button;

    InputNumMode m_mode;
    InputNumValueMode m_valueMode;
    InputNumType m_type;
    int m_currentGroupButtonsPage;
    int m_group_buttons_per_page;
};


#endif // INPUTNUMCONTROL_H
