#include "trackControl/trackControl.hpp"
#include "trackControl/trackControl_define.hpp"
#include "utility.h"

TrackControl::TrackControl(QWidget *parent)
    : PanelControlBase(parent),
      m_label_title(this),

      m_button_mode_percent(this),
      m_button_mode_255(this),
      m_button_mode_angle(this),

      m_button_value_mode_relative(this),
      m_button_value_mode_absolute(this),
      m_button_emply_field(this),

      m_pantilt_control(this),
      m_mode(),
      m_valueMode()
{
    setFixedSize(TC_SCREENSIZE);
    qRegisterMetaType<TrackMode>("TrackMode");
    qRegisterMetaType<TrackValueMode>("TrackValueMode");
    qRegisterMetaType<QVector<TRACK_PARAM_GROUP>>("QVector<TRACK_PARAM_GROUP>");

    m_label_title.setObjectName("title_label");
    m_button_mode_255.setCheckMarkVisible(true);
    m_button_mode_percent.setCheckMarkVisible(true);
    m_button_mode_angle.setCheckMarkVisible(true);
    m_button_value_mode_absolute.setCheckMarkVisible(true);
    m_button_value_mode_relative.setCheckMarkVisible(true);

    m_label_title.setGeometry(TC_LABEL_TITLE_GEOMETRY);
    m_label_title.setText("トラック");
    setWindowTitle(m_label_title.text());

    m_button_mode_percent.setGeometry(TC_BUTTON_MODE_PERCENT_GEOMETRY);
    m_button_mode_percent.setText("%");

    m_button_mode_255.setGeometry(TC_BUTTON_MODE_255_GEOMETRY);
    m_button_mode_255.setText("255");

    m_button_mode_angle.setGeometry(TC_BUTTON_MODE_ANGLE_GEOMETRY);
    m_button_mode_angle.setText("°角度");
    m_button_mode_angle.setEnabled(false);

    m_button_value_mode_relative.setGeometry(TC_BUTTON_VALUEMODE_RELATIVE_GEOMETRY);
    m_button_value_mode_relative.setText("相対");

    m_button_value_mode_absolute.setGeometry(TC_BUTTON_VALUEMODE_ABSOLUTE_GEOMETRY);
    m_button_value_mode_absolute.setText("絶対");

    m_button_emply_field.setGeometry(TC_BUTTON_EMPTY_1_GEOMETRY);
    m_button_emply_field.setDisabled(true);

    m_pantilt_control.setGeometry(TC_PANTILTCONTROL_GEOMETRY);

    connect(&m_button_mode_percent, &SelectButton::toggled, this, [&](bool checked){
        if (!checked)
            return;
        setMode(TRACK_MODE_PERCENT);
        emit trackPointsChanged();
    });
    connect(&m_button_mode_255, &SelectButton::toggled, this, [&](bool checked){
        if (!checked)
            return;
        setMode(TRACK_MODE_255);
        emit trackPointsChanged();
    });
    // connect(&m_button_mode_angle, &SelectButton::clicked, this, [&](){
        // setMode(TRACK_MODE_ANGLE);
    // });
    connect(&m_button_value_mode_relative, &SelectButton::toggled, this, [&](bool checked){
        if (!checked)
            return;
        setValueMode(TRACK_MODE_RELATIVE);
        m_pantilt_control.setValueMode(valueMode());
    });
    connect(&m_button_value_mode_absolute, &SelectButton::toggled, this, [&](bool checked){
        if (!checked)
            return;
        setValueMode(TRACK_MODE_ABSOLUTE);
        auto trackPoints = m_pantilt_control.trackPoints();
        for (auto &p : trackPoints) {
            p.pan.current = 0;
            p.tilt.current = 0;
        }
        m_pantilt_control.setValueMode(valueMode());
        m_pantilt_control.SetTrackPoints(trackPoints);
        emit trackPointsChanged();
    });
    connect(&m_pantilt_control, &PantiltControl::trackPointsUpdated, this, [&](){
        emit trackPointsChanged();
    });
    connect(this, &TrackControl::modeChanged, this, &TrackControl::onModeChanged);
    connect(this, &TrackControl::valueModeChanged, this, &TrackControl::onValueModeChanged);
}

void TrackControl::SetDispParamData(TRACK_DISP_PARAM *param)
{
    Q_ASSERT(param);

    // NOTE: mode must be set prior to trackPoints
    setMode(param->mode);
    setValueMode(param->valueMode);

    QVector<TRACK_PARAM_GROUP> list;
    for (int i = 0; i < qBound(int(param->count), 0, 8); ++i) {
        list.push_back(param->data[i]);
    }
    m_pantilt_control.setValueMode(valueMode());
    m_pantilt_control.SetTrackPoints(mapToScreen(IntParam2FloatParam(list)));

    onModeChanged();
    onValueModeChanged();
}

TrackMode TrackControl::mode() const
{
    return m_mode;
}

void TrackControl::setMode(TrackMode newMode)
{
    if (m_mode == newMode)
        return;
    m_mode = newMode;
    emit modeChanged();
}

TrackValueMode TrackControl::valueMode() const
{
    return m_valueMode;
}

void TrackControl::setValueMode(TrackValueMode newValueMode)
{
    if (m_valueMode == newValueMode)
        return;
    m_valueMode = newValueMode;
    emit valueModeChanged();
}

QVector<TRACK_PARAM_GROUP> TrackControl::trackPoints() const
{
    return FloatParam2IntParam(mapToValue(m_pantilt_control.trackPoints()));
}

QVector<PantiltControl::TrackPointFloatParamGroup> TrackControl::mapToScreen(const QVector<PantiltControl::TrackPointFloatParamGroup> &points) const {
    float scale = mode() == TRACK_MODE_PERCENT
            ? (TC_TRACK_RESOLUTION / 100.0)  // map from 0..100% to 0..TC_TRACK_RESOLUTION
            : (TC_TRACK_RESOLUTION / 255.0); // map from 0..255 to 0..TC_TRACK_RESOLUTION
    QVector<PantiltControl::TrackPointFloatParamGroup> result;
    for (auto p : points) {
        p.pan.current *= scale;
        p.pan.min *= scale;
        p.pan.max *= scale;
        p.tilt.current *= scale;
        p.tilt.min *= scale;
        p.tilt.max *= scale;
        result.append(p);
    }
    return result;
}

QVector<PantiltControl::TrackPointFloatParamGroup> TrackControl::mapToValue(const QVector<PantiltControl::TrackPointFloatParamGroup> &points) const
{
    float scale = mode() == TRACK_MODE_PERCENT
            ? (TC_TRACK_RESOLUTION / 100.0)  // map from 0..TC_TRACK_RESOLUTION to 0..100
            : (TC_TRACK_RESOLUTION / 255.0); // map from 0..TC_TRACK_RESOLUTION to 0..100
    QVector<PantiltControl::TrackPointFloatParamGroup> result;
    for (auto p : points) {
        p.pan.current /= scale;
        p.pan.min /= scale;
        p.pan.max /= scale;
        p.tilt.current /= scale;
        p.tilt.min /= scale;
        p.tilt.max /= scale;
        result.append(p);
    }
    return result;
}

QVector<PantiltControl::TrackPointFloatParamGroup> TrackControl::IntParam2FloatParam(const QVector<TRACK_PARAM_GROUP> int_param)
{
    QVector<PantiltControl::TrackPointFloatParamGroup> result;
    for (const auto &param : int_param)
    {
        PantiltControl::TrackPointFloatParamGroup t;
        t.pan.current = param.pan.current;
        t.pan.max = param.pan.max;
        t.pan.min = param.pan.min;
        t.tilt.current = param.tilt.current;
        t.tilt.max = param.tilt.max;
        t.tilt.min = param.tilt.min;
        result.append(t);
    }
    return result;
}

QVector<TRACK_PARAM_GROUP> TrackControl::FloatParam2IntParam(const QVector<PantiltControl::TrackPointFloatParamGroup> float_param)
{
    QVector<TRACK_PARAM_GROUP> result;
    for (const auto &param : float_param)
    {
        TRACK_PARAM_GROUP t;
        t.pan.current = qRound(param.pan.current);
        t.pan.max = qRound(param.pan.max);
        t.pan.min = qRound(param.pan.min);
        t.tilt.current = qRound(param.tilt.current);
        t.tilt.max = qRound(param.tilt.max);
        t.tilt.min = qRound(param.tilt.min);
        result.append(t);
    }
    return result;
}


void TrackControl::onModeChanged()
{
    m_button_mode_percent.setChecked(mode() == TRACK_MODE_PERCENT);
    m_button_mode_255.setChecked(mode() == TRACK_MODE_255);
    m_button_mode_angle.setChecked(mode() == TRACK_MODE_ANGLE);
}

void TrackControl::onValueModeChanged()
{
    m_button_value_mode_relative.setChecked(valueMode() == TRACK_MODE_RELATIVE);
    m_button_value_mode_absolute.setChecked(valueMode() == TRACK_MODE_ABSOLUTE);
}
