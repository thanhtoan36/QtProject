#ifndef TRACKCONTROL_H
#define TRACKCONTROL_H

#include "../baseComponent/panelControlBase.h"
#include "trackControl_datatypes.h"

#include "../baseComponent/selectButton.h"
#include "pantiltControl.h"
#include <QLabel>

class TrackControl : public PanelControlBase
{
    Q_OBJECT

    Q_PROPERTY(TrackMode mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(TrackValueMode valueMode READ valueMode WRITE setValueMode NOTIFY valueModeChanged)
    Q_PROPERTY(QVector<TRACK_PARAM_GROUP> trackPoints READ trackPoints WRITE setTrackPoints NOTIFY trackPointsChanged)

public:
    TrackControl(QWidget *parent = nullptr);
    void SetDispParamData(TRACK_DISP_PARAM *param);

    TrackMode mode() const;
    void setMode(TrackMode newMode);

    TrackValueMode valueMode() const;
    void setValueMode(TrackValueMode newValueMode);

    QVector<TRACK_PARAM_GROUP> trackPoints() const;
    void setTrackPoints(const QVector<TRACK_PARAM_GROUP> &newTrackPoints);

signals:
    void modeChanged();
    void valueModeChanged();
    void trackPointsChanged();

protected:
    QVector<TRACK_PARAM_GROUP> mapToScreen(const QVector<TRACK_PARAM_GROUP> &points);
    QVector<TRACK_PARAM_GROUP> mapToValue(const QVector<TRACK_PARAM_GROUP> &points);

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
  QVector<TRACK_PARAM_GROUP> m_trackPoints;
};

#endif // TRACKCONTROL_H
