//--------------------------------------------------------------------------
// [ ファイル名 ] : trackControl.h
// [ 概      要 ] : TrackControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

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

    Q_PROPERTY(TrackMode Mode READ Mode WRITE SetMode NOTIFY ModeChanged)
    Q_PROPERTY(TrackValueMode ValueMode READ ValueMode WRITE SetValueMode NOTIFY ValueModeChanged)

public:
    TrackControl(QWidget *parent = nullptr);
    virtual void SetDispParamData(TRACK_DISP_PARAM *param);

    TrackMode Mode() const;
    TrackValueMode ValueMode() const;
    QVector<TRACK_PARAM_GROUP> TrackPoints() const;

signals:
    void ModeChanged();
    void ValueModeChanged();
    void TrackPointsChanged();

protected slots:
    void OnModeChanged();
    void OnValueModeChanged();

protected:
    void SetMode(TrackMode value);
    void SetValueMode(TrackValueMode value);

    QVector<PantiltControl::TrackPointFloatParamGroup> MapToScreen(const QVector<PantiltControl::TrackPointFloatParamGroup> &points) const;
    QVector<PantiltControl::TrackPointFloatParamGroup> MapToValue(const QVector<PantiltControl::TrackPointFloatParamGroup> &points) const;

    static QVector<PantiltControl::TrackPointFloatParamGroup> IntParam2FloatParam(const QVector<TRACK_PARAM_GROUP> &int_param);
    static QVector<TRACK_PARAM_GROUP> FloatParam2IntParam(const QVector<PantiltControl::TrackPointFloatParamGroup> &float_param);

protected:
  QLabel m_label_title;

  SelectButton m_button_mode_percent;
  SelectButton m_button_mode_255;
  SelectButton m_button_mode_angle;

  SelectButton m_button_value_mode_relative;
  SelectButton m_button_value_mode_absolute;
  SelectButton m_button_emply_field;

  PantiltControl m_pantilt_control;

  TrackMode m_mode;
  TrackValueMode m_value_mode;
};

#endif // TRACKCONTROL_H
