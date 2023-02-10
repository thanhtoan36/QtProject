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
    Q_PROPERTY(int currentEncoderPage READ currentEncoderPage WRITE setCurrentEncoderPage NOTIFY currentEncoderPageChanged)
    Q_PROPERTY(int maxEncoderPages READ maxEncoderPages WRITE setMaxEncoderPages NOTIFY maxEncoderPagesChanged)
    Q_PROPERTY(int encodersPerPage READ encodersPerPage WRITE setEncodersPerPage NOTIFY encodersPerPageChanged)
    Q_PROPERTY(EncoderMode mode READ mode WRITE setMode NOTIFY modeChanged)

public:
    EncoderPanelControl(QWidget *parent = nullptr);
    void SetDispParamData(ENCODER_DISP_PARAM *param);

    int currentEncoderPage() const;
    void setCurrentEncoderPage(int newCurrentEncoderPage);

    int maxEncoderPages() const;
    void setMaxEncoderPages(int newMaxEncoderPages);

    int encodersPerPage() const;
    void setEncodersPerPage(int newEncodersPerPage);

    EncoderMode mode() const;
    void setMode(EncoderMode newMode);

signals:
    void currentEncoderPageChanged();
    void maxEncoderPagesChanged();
    void encodersPerPageChanged();

    void modeChanged();

protected:
    virtual void SetupUiComponents() override;
    virtual void SetupUiEvents() override;
    void updateEncoders();

private:
  QLabel m_label_title;

  SelectButton m_button_mode_percent;
  SelectButton m_button_mode_255;
  SelectButton m_button_empty1;

  CustomPushButton m_button_previous_tab; // ◀
  CustomPushButton m_button_next_tab;     // ▶

  QVector<QSharedPointer<EncoderSlider>> m_encoders;
  int m_currentEncoderPage;
  int m_maxEncoderPages;
  int m_encodersPerPage;
  EncoderMode m_mode;
};

#endif // ENCODERCONTROL_H
