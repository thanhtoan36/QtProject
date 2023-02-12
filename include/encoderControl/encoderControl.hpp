#ifndef ENCODERCONTROL_H
#define ENCODERCONTROL_H

#include "../baseComponent/panelControlBase.h"
#include "encoderControl_datatypes.h"
#include "customEncoder.h"
#include "../baseComponent/selectButton.h"
#include "../baseComponent/gridBackground.h"

#include <QLabel>
#include <QVector>

class EncoderControl : public PanelControlBase
{
    Q_OBJECT
    Q_PROPERTY(int currentEncoderPage READ currentEncoderPage WRITE setCurrentEncoderPage NOTIFY currentEncoderPageChanged)
    Q_PROPERTY(QSize encoderMatrixSize READ encoderMatrixSize WRITE setEncoderMatrixSize NOTIFY encoderMatrixSizeChanged)
    Q_PROPERTY(EncoderMode mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(EncoderType type READ type WRITE setType NOTIFY typeChanged)

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

    EncoderType type() const;
    void setType(EncoderType newType);

signals:
    void currentEncoderPageChanged();
    void modeChanged();
    void encoderMatrixSizeChanged();
    void typeChanged();

protected:
    virtual void SetupUiComponents() override;
    virtual void SetupUiEvents() override;
    virtual void setupEncoderPages();

protected slots:
    void onModeChanged();
    void onTypeChanged();
    void updateEncoderLabelValue(int index);
    void onEncoderValueChanged(int index, int value);

protected:
    struct EncoderParamFloat
    {
        QString name;
        float level, maxLevel;

        EncoderParamFloat() {}
        EncoderParamFloat(const ENCODER_PARAM &paramInt) : name(paramInt.name), level(paramInt.level), maxLevel(paramInt.maxLevel) { }
    };
    GridBackground m_encoder_background;
    GridBackground m_button_background;

    QLabel m_label_title;

    SelectButton m_button_mode_percent;
    SelectButton m_button_mode_255;
    SelectButton m_button_empty1;

    CustomPushButton m_button_previous_tab; // ◀
    CustomPushButton m_button_next_tab;     // ▶

    QVector<EncoderParamFloat> m_params;
    QVector<QSharedPointer<QLabel>> m_encoder_labels;
    QVector<QSharedPointer<CustomEncoder>> m_encoders;
    int m_currentEncoderPage;
    QSize m_encoderMatrixSize;

    EncoderType m_type;
    EncoderMode m_mode;
private:
};

#endif // ENCODERCONTROL_H
