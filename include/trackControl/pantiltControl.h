#ifndef PANTILTCONTROL_H
#define PANTILTCONTROL_H

#include <QLabel>
#include <QWidget>
#include "trackControl_datatypes.h"

#define TC_TRACK_RESOLUTION 1000

class TrackPoint : public QWidget
{
    Q_OBJECT

public:
    explicit TrackPoint(QWidget *parent = nullptr);
    void SetCoordinate(QPoint pos);
    QPoint Coordinate();

signals:
    void moveRequested(QPoint new_pos);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    bool m_pressed;
};


class PantiltControl : public QWidget
{
    Q_OBJECT
    struct TrackPointData {
        TRACK_PARAM_GROUP param_group;
        // range: 0..1000 (not 0..100 or 0..255)
        QSharedPointer<TrackPoint> widget;
    };

public:
    explicit PantiltControl(QWidget *parent = nullptr);

    void setMode(TrackMode mode);
    void SetTrackPoints(TrackMode mode, TrackValueMode value_mode, const QVector<TRACK_PARAM_GROUP> &points);
    QVector<TRACK_PARAM_GROUP> trackPoints() const;

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

    QPointF ConvertValueToCoordinate(QPointF value);
    QPointF ConvertCoordinateToValue(QPointF coordinate);

    void MovePointWithConstraints(TrackPointData &point, QPointF new_value);

signals:
    void trackPointsUpdated();

private slots:
    void onTrackPointMoveRequested(QPoint new_pos);

private:
    QLabel m_label_tilt, m_label_pan;
    QVector<TrackPointData> m_track_points;

    TrackMode m_mode;
    TrackValueMode m_value_mode;

    bool m_pressed;
    QPoint m_last_pos;
};

#endif // PANTILTCONTROL_H
