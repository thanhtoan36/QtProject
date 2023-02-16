#include "trackControl/pantiltControl.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include "utility.h"

#define TRACK_POINT_SIZE QSize(12, 12)
#define TRACK_UI_PADDING 10

TrackPoint::TrackPoint(QWidget *parent)
    : QWidget{parent},
      m_pressed(false)
{
    setFixedSize(TRACK_POINT_SIZE);
    setFocusPolicy(Qt::FocusPolicy::NoFocus);
}

QPoint TrackPoint::Coordinate()
{
    QPoint pos;
    pos.setX(geometry().x() + TRACK_POINT_SIZE.width() / 2);
    pos.setY(geometry().y() + TRACK_POINT_SIZE.height() / 2);
    return pos;
}

void TrackPoint::SetCoordinate(QPoint pos)
{
    pos.setX(pos.x() - TRACK_POINT_SIZE.width() / 2);
    pos.setY(pos.y() - TRACK_POINT_SIZE.height() / 2);
    move(pos);
}

void TrackPoint::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    if (m_pressed)
        p.setPen(Qt::yellow);
    p.setBrush(QBrush(Qt::yellow));
    p.drawEllipse(QRect(QPoint(0, 0), geometry().size()));
}

void TrackPoint::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;
    update();
    event->ignore();
}

void TrackPoint::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    update();
    event->ignore();
}

void TrackPoint::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_pressed)
        return;
    // emit moveRequested(event->pos());
    event->ignore();
}

PantiltControl::PantiltControl(QWidget *parent)
    : QWidget{parent},
      m_label_tilt(this), m_label_pan(this),
      m_track_points(),
      m_mode(), m_value_mode(),
      m_pressed(false),
      m_last_pos()
{
    m_label_tilt.setText("チルト");
    m_label_pan.setText("パン");

    m_label_tilt.setObjectName("graph_axis_label");
    m_label_pan.setObjectName("graph_axis_label");
}

void PantiltControl::setMode(TrackMode mode)
{
    if (mode == m_mode)
        return;
    float scale = mode == TRACK_MODE_255 ? (255.0 / 100.0) : (100.0 / 255.0);
}

void PantiltControl::SetTrackPoints(TrackMode mode, TrackValueMode value_mode, const QVector<TRACK_PARAM_GROUP> &points)
{
    m_mode = mode;
    m_value_mode = value_mode;

    m_track_points.clear();
    foreach (const TRACK_PARAM_GROUP &point, points) {
        TrackPointData data { point, MakeSharedQObject<TrackPoint>(this) };

        data.widget->SetCoordinate(ConvertValueToCoordinate(QPointF(data.param_group.pan.current, data.param_group.tilt.current)).toPoint());
        data.widget->raise();
        data.widget->setVisible(true);
        // connect(data.widget.get(), &TrackPoint::moveRequested, this, &PantiltControl::onTrackPointMoveRequested);

        m_track_points.push_back(data);
    }
}

QVector<TRACK_PARAM_GROUP> PantiltControl::trackPoints() const
{
    QVector<TRACK_PARAM_GROUP>  result;
    for (const auto &p : m_track_points) {
        result.append(p.param_group);
    }
    return result;
}

void PantiltControl::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);

    p.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    // Black background
    p.fillRect(QRect(QPoint(0, 0), geometry().size()), QBrush(Qt::black));
    p.setPen(QPen(Qt::darkGray));
    p.drawRect(QRect(QPoint(0, 0), geometry().size()));

    QSize bound = geometry().size();

    // Draw horizontal grid lines
    for (int i = 0; i <= 100; i += 20) {
        p.setPen(QPen(Qt::darkGray, (i % 50 == 0) ? 1 : 0.2));
        p.drawLine(0, i * bound.height() / 100.0, bound.width(), i * bound.height() / 100.0);
    }
    p.setPen(QPen(Qt::darkGray));
    p.drawLine(0, bound.height() / 2, bound.width(), bound.height() / 2);
    // Draw vertical grid lines
    for (int i = 0; i <= 100; i += 25) {
        p.setPen(QPen(Qt::darkGray, (i % 50 == 0) ? 1 : 0.2));
        p.drawLine(i * bound.width() / 100.0, 0, i * bound.width() / 100.0, bound.height());
    }
}

void PantiltControl::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    m_label_pan.setGeometry(QRect(geometry().width() - 50, geometry().height() / 2 - 22, 50, 22));
    m_label_tilt.setGeometry(QRect(geometry().width() / 2 + 10, 0, 50, 22));
}

void PantiltControl::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;
    m_last_pos = event->pos();

    if (m_value_mode == TRACK_MODE_ABSOLUTE) {
        for (auto &p : m_track_points) {
            MovePointWithConstraints(p, ConvertCoordinateToValue(event->pos()));
        }
        emit trackPointsUpdated();
    }
}

void PantiltControl::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
}

void PantiltControl::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_pressed)
        return;

    if (m_value_mode == TRACK_MODE_RELATIVE) {
        // Move all track point at the same time
        const QPoint diff = event->pos() - m_last_pos;

        for (auto &p : m_track_points) {
            const auto new_coordinate = p.widget->Coordinate() + diff;
            MovePointWithConstraints(p, ConvertCoordinateToValue(new_coordinate));
        }

        emit trackPointsUpdated();

        m_last_pos = event->pos();
    }
}

QPointF PantiltControl::ConvertValueToCoordinate(QPointF value)
{
    value.setY(TC_TRACK_RESOLUTION - value.y());

    QPointF coordinate(value.x() * geometry().width() / TC_TRACK_RESOLUTION,
                       value.y() * geometry().height() / TC_TRACK_RESOLUTION);

    return coordinate;
}

QPointF PantiltControl::ConvertCoordinateToValue(QPointF coordinate)
{
    QPointF value(coordinate.x() * TC_TRACK_RESOLUTION / geometry().width(),
                  coordinate.y() * TC_TRACK_RESOLUTION / geometry().height());

    value.setY(TC_TRACK_RESOLUTION - value.y());

    return value;
}

void PantiltControl::MovePointWithConstraints(TrackPointData &point, QPointF new_value)
{
    // Limit pan/tilt to max / min of this object
    if (new_value.x() < point.param_group.pan.min)
        new_value.setX(point.param_group.pan.min);
    if (new_value.x() > point.param_group.pan.max)
        new_value.setX(point.param_group.pan.max);

    if (new_value.y() < point.param_group.tilt.min)
        new_value.setY(point.param_group.tilt.min);
    if (new_value.y() > point.param_group.tilt.max)
        new_value.setY(point.param_group.tilt.max);

    QPointF new_pos = ConvertValueToCoordinate(new_value);
    point.widget->SetCoordinate(new_pos.toPoint());
    point.param_group.pan.current = new_value.x();
    point.param_group.tilt.current = new_value.y();
}

void PantiltControl::onTrackPointMoveRequested(QPoint new_pos)
{
    auto widget = static_cast<TrackPoint*>(QObject::sender());
    if (!widget)
        return;

    const QPoint diff = new_pos - widget->pos();

    for (TrackPointData &p : m_track_points) {
        auto new_value = ConvertCoordinateToValue(p.widget->pos() + diff);
        MovePointWithConstraints(p, new_value);
    }
}
