#ifndef ENCODERCONTROL_H
#define ENCODERCONTROL_H

#include "../baseComponent/panelControlBase.h"
#include "encoderControl_datatypes.h"
#include "encoderSlider.h"
#include "../baseComponent/selectButton.h"

#include <QLabel>
#include <QVector>

class EncoderPanelControl : public PanelControlBase
{
    Q_OBJECT

public:
    EncoderPanelControl(QWidget *parent = nullptr);
    void SetDispParamData(ENCODER_DISP_PARAM *param);

protected:
    virtual void SetupUiComponents() override;
    virtual void SetupUiEvents() override;

private:
  QLabel m_label_title;

  SelectButton m_button_mode_percent;
  SelectButton m_button_mode_255;
  SelectButton m_button_empty1;

  Encoder m_test_encoder;
};

#endif // ENCODERCONTROL_H
