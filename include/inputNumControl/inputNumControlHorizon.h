#ifndef INPUTNUMCONTROLHORIZON_H
#define INPUTNUMCONTROLHORIZON_H

#include "inputNumControl.hpp"
#include "inputNumControlHorizon_define.h"

class InputNumControlHorizon : public InputNumControl
{
public:
    explicit InputNumControlHorizon(QWidget* parent = nullptr);
    void SetDispParamDataHorizon(INPUT_NUM_DISP_PARAM *param);

protected slots:
    virtual void onModeChanged() override;
    virtual void onTypeChanged() override;
    virtual void onCurrentButtonModePageChanged() override;

    void onButtonPickerClicked(const bool check);
    void onButtonEncoderClicked(const bool check);
    void onButtonNumberClicked(const bool check);

private:
    SelectButton m_picker_button;
    SelectButton m_encoder_button;
    SelectButton m_number_button;
};

#endif // INPUTNUMCONTROLHORIZON_H
