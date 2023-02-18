#include "trackControl/trackControl.hpp"
#include "trackControl/trackControl_define.hpp"

TrackControl::TrackControl(QWidget *parent)
    : m_label_title(this),

      m_button_mode_percent(this),
      m_button_mode_255(this),
      m_button_mode_angle(this),

      m_button_value_mode_relative(this),
      m_button_value_mode_absolute(this),
      m_button_emply_field(this),

      m_pantilt_control(this),
      m_mode(),
      m_valueMode(),
      m_trackPoints()
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

    connect(&m_button_mode_percent, &SelectButton::clicked, this, [&](){
        setMode(TRACK_MODE_PERCENT);
        // m_pantilt_control.SetTrackPoints(mode(), valueMode(), mapToScreen(m_trackPoints));
    });
    connect(&m_button_mode_255, &SelectButton::clicked, this, [&](){
        setMode(TRACK_MODE_255);
        // m_pantilt_control.SetTrackPoints(mode(), valueMode(), mapToScreen(m_trackPoints));
    });
    // connect(&m_button_mode_angle, &SelectButton::clicked, this, [&](){
        // setMode(TRACK_MODE_ANGLE);
    // });
    connect(&m_button_value_mode_relative, &SelectButton::clicked, this, [&](){
        setValueMode(TRACK_MODE_RELATIVE);
        m_pantilt_control.SetTrackPoints(mode(), valueMode(), mapToScreen(m_trackPoints));
    });
    connect(&m_button_value_mode_absolute, &SelectButton::clicked, this, [&](){
        setValueMode(TRACK_MODE_ABSOLUTE);
        for (auto &p : m_trackPoints) {
            p.pan.current = 0;
            p.tilt.current = 0;
        }
        setTrackPoints(m_trackPoints);
    });
    connect(&m_pantilt_control, &PantiltControl::trackPointsUpdated, this, [&](){
        m_trackPoints = mapToValue(m_pantilt_control.trackPoints());
    });
}

void TrackControl::SetDispParamData(TRACK_DISP_PARAM *param)
{
    Q_ASSERT(param);

    // NOTE: mode must be set prior to trackPoints
    setMode(param->mode);
    setValueMode(param->valueMode);

    QVector<TRACK_PARAM_GROUP> data;
    for (int i = 0; i < std::min(8, (int)param->count); ++i) {
        data.push_back(param->data[i]);
    }
    setTrackPoints(data);
}

TrackMode TrackControl::mode() const
{
    return m_mode;
}

void TrackControl::setMode(TrackMode newMode)
{
    m_button_mode_percent.setChecked(newMode == TRACK_MODE_PERCENT);
    m_button_mode_255.setChecked(newMode == TRACK_MODE_255);
    m_button_mode_angle.setChecked(newMode == TRACK_MODE_ANGLE);

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
    m_button_value_mode_relative.setChecked(newValueMode == TRACK_MODE_RELATIVE);
    m_button_value_mode_absolute.setChecked(newValueMode == TRACK_MODE_ABSOLUTE);

    if (m_valueMode == newValueMode)
        return;
    m_valueMode = newValueMode;
    emit valueModeChanged();
}

QVector<TRACK_PARAM_GROUP> TrackControl::trackPoints() const
{
    return m_trackPoints;
}

QVector<TRACK_PARAM_GROUP> TrackControl::mapToScreen(const QVector<TRACK_PARAM_GROUP> &points) {
    float scale = mode() == TRACK_MODE_PERCENT
            ? (TC_TRACK_RESOLUTION / 100.0)  // map from 0..100% to 0..TC_TRACK_RESOLUTION
            : (TC_TRACK_RESOLUTION / 255.0); // map from 0..255 to 0..TC_TRACK_RESOLUTION
    QVector<TRACK_PARAM_GROUP> result;
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

QVector<TRACK_PARAM_GROUP> TrackControl::mapToValue(const QVector<TRACK_PARAM_GROUP> &points)
{
    float scale = mode() == TRACK_MODE_PERCENT
            ? (TC_TRACK_RESOLUTION / 100.0)  // map from 0..TC_TRACK_RESOLUTION to 0..100
            : (TC_TRACK_RESOLUTION / 255.0); // map from 0..TC_TRACK_RESOLUTION to 0..100
    QVector<TRACK_PARAM_GROUP> result;
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


void TrackControl::setTrackPoints(const QVector<TRACK_PARAM_GROUP> &newTrackPoints)
{
    m_trackPoints = newTrackPoints;
    m_pantilt_control.SetTrackPoints(mode(), valueMode(), mapToScreen(newTrackPoints));
    emit trackPointsChanged();
}
