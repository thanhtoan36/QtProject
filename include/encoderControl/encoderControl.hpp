#ifndef ENCODERCONTROL_H
#define ENCODERCONTROL_H

#include "../baseComponent/panelControlBase.h"
#include "encoderControl_datatypes.h"
#include "encoderSlider.h"
#include "../baseComponent/selectButton.h"

#include <QLabel>
#include <QVector>

class EncoderControl : public PanelControlBase
{
    Q_OBJECT
    Q_PROPERTY(int currentEncoderPage READ currentEncoderPage WRITE setCurrentEncoderPage NOTIFY currentEncoderPageChanged)
    Q_PROPERTY(QSize encoderMatrixSize READ encoderMatrixSize WRITE setEncoderMatrixSize NOTIFY encoderMatrixSizeChanged)
    Q_PROPERTY(EncoderMode mode READ mode WRITE setMode NOTIFY modeChanged)

public:
    EncoderControl(QWidget *parent = nullptr);
    void SetDispParamData(ENCODER_DISP_PARAM *param);

    int currentEncoderPage() const;
    void setCurrentEncoderPage(int newCurrentEncoderPage);

    int maxEncoderPages() const;

    EncoderMode mode() const;
    void setMode(EncoderMode newMode);

    QSize encoderMatrixSize() const;
    void setEncoderMatrixSize(const QSize &newEncoderMatrixSize);

signals:
    void currentEncoderPageChanged();
    void modeChanged();
    void encoderMatrixSizeChanged();

protected:
    virtual void SetupUiComponents() override;
    virtual void SetupUiEvents() override;
    virtual void setupEncoderPages();

protected slots:
    void onModeChanged();

protected:
  QLabel m_label_title;

  SelectButton m_button_mode_percent;
  SelectButton m_button_mode_255;
  SelectButton m_button_empty1;

  CustomPushButton m_button_previous_tab; // ◀
  CustomPushButton m_button_next_tab;     // ▶

  QVector<QSharedPointer<EncoderSlider>> m_encoders;
  int m_currentEncoderPage;
  EncoderMode m_mode;
  QSize m_encoderMatrixSize;
};

#endif // ENCODERCONTROL_H
