//--------------------------------------------------------------------------
// [ ファイル名 ] : pantiltControl.h
// [ 概      要 ] : PantiltControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

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
    explicit TrackPoint( QWidget *parent = nullptr );
    void SetCoordinate( QPoint pos );
    QPoint Coordinate();

protected:
    virtual void paintEvent( QPaintEvent *event ) override;
};


class PantiltControl : public QWidget
{
    Q_OBJECT
public:
    struct TrackPointFloatParam
    {
        float min, max, current;
    };
    struct TrackPointFloatParamGroup
    {
        TrackPointFloatParam pan, tilt;
    };

    struct TrackPointData
    {
        // range: 0..1000 (not 0..100 or 0..255)
        TrackPointFloatParamGroup param;
        QSharedPointer<TrackPoint> widget;
    };

    explicit PantiltControl( QWidget *parent = nullptr );

    void SetValueMode( TrackValueMode value_mode );
    void SetTrackPoints( const QVector<TrackPointFloatParamGroup> &points );
    QVector<TrackPointFloatParamGroup> TrackPoints() const;

protected:
    virtual void paintEvent( QPaintEvent *event ) override;
    virtual void resizeEvent( QResizeEvent *event ) override;
    virtual void mousePressEvent( QMouseEvent *event ) override;
    virtual void mouseReleaseEvent( QMouseEvent *event ) override;
    virtual void mouseMoveEvent( QMouseEvent *event ) override;

    QPointF ConvertValueToCoordinate( QPointF value );
    QPointF ConvertCoordinateToValue( QPointF coordinate );

    void MovePointWithConstraints( TrackPointData &point, QPointF new_value );

signals:
    void TrackPointsUpdated();

private:
    QLabel m_label_tilt, m_label_pan;
    QVector<TrackPointData> m_track_points;

    TrackValueMode m_value_mode;

    bool m_pressed;
    bool m_moved;
    QPoint m_last_pos;
};

#endif // PANTILTCONTROL_H
