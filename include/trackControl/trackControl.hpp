#ifndef TRACKCONTROL_H
#define TRACKCONTROL_H

#include "baseComponent/panelControlBase.h"
#include "trackControl_datatypes.h"

#include "baseComponent/selectButton.h"
#include "pantiltControl.h"
#include <QLabel>

class TrackControl : public PanelControlBase
{
    Q_OBJECT

    Q_PROPERTY(TrackMode mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(TrackValueMode valueMode READ valueMode WRITE setValueMode NOTIFY valueModeChanged)

public:
    TrackControl(QWidget *parent = nullptr);
    virtual void SetDispParamData(TRACK_DISP_PARAM *param);

    TrackMode mode() const;
    TrackValueMode valueMode() const;
    QVector<TRACK_PARAM_GROUP> trackPoints() const;

signals:
    void modeChanged();
    void valueModeChanged();
    void trackPointsChanged();

protected slots:
    void onModeChanged();
    void onValueModeChanged();

protected:
    void setMode(TrackMode newMode);
    void setValueMode(TrackValueMode newValueMode);

    QVector<PantiltControl::TrackPointFloatParamGroup> mapToScreen(const QVector<PantiltControl::TrackPointFloatParamGroup> &points) const;
    QVector<PantiltControl::TrackPointFloatParamGroup> mapToValue(const QVector<PantiltControl::TrackPointFloatParamGroup> &points) const;

    static QVector<PantiltControl::TrackPointFloatParamGroup> IntParam2FloatParam(const QVector<TRACK_PARAM_GROUP> int_param);
    static QVector<TRACK_PARAM_GROUP> FloatParam2IntParam(const QVector<PantiltControl::TrackPointFloatParamGroup> float_param);

protected:
  QLabel m_label_title;

  SelectButton m_button_mode_percent;
  SelectButton m_button_mode_255;
  SelectButton m_button_mode_angle;

  SelectButton m_button_value_mode_relative;
  SelectButton m_button_value_mode_absolute;
  SelectButton m_button_emply_field; // place holder

  PantiltControl m_pantilt_control;

private:
  TrackMode m_mode;
  TrackValueMode m_valueMode;
};

#endif // TRACKCONTROL_H
