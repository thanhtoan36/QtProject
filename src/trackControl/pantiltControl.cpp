//--------------------------------------------------------------------------
// [ ファイル名 ] : pantiltControl.cpp
// [ 概      要 ] : PantiltControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "trackControl/pantiltControl.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include "utility.h"

#define TRACK_POINT_SIZE QSize(12, 12)  // トラック ポイントのサイズ

//--------------------------------------------------------------------------
//  [ 関数名 ] : TrackPoint
//  [ 機　能 ] : トラックポイントのコンストラクター
//  [ 引　数 ] : QWidget *parent : 親ウィジェット
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
TrackPoint::TrackPoint( QWidget *parent )
    : QWidget{parent}
{
    setFixedSize( TRACK_POINT_SIZE );
    setFocusPolicy( Qt::FocusPolicy::NoFocus );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : Coordinate
//  [ 機　能 ] : 現在の座標を取得する
//  [ 引　数 ] : void
//  [ 戻り値 ] : QPoint : 現在の座標
//--------------------------------------------------------------------------
QPoint TrackPoint::Coordinate()
{
    QPoint pos;
    pos.setX( geometry().x() + TRACK_POINT_SIZE.width() / 2 );
    pos.setY( geometry().y() + TRACK_POINT_SIZE.height() / 2 );
    return pos;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetCoordinate
//  [ 機　能 ] : 現在の座標を設定する
//  [ 引　数 ] : QPoint pos : 新しい座標
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void TrackPoint::SetCoordinate( QPoint pos )
{
    pos.setX( pos.x() - TRACK_POINT_SIZE.width() / 2 );
    pos.setY( pos.y() - TRACK_POINT_SIZE.height() / 2 );
    move( pos );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : paintEvent
//  [ 機　能 ] : ウィジェットをペイントする
//  [ 引　数 ] : QPaintEvent *event : ペイントイベントのデータ
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void TrackPoint::paintEvent( QPaintEvent *event )
{
    QPainter p( this );
    p.setRenderHints( QPainter::Antialiasing | QPainter::HighQualityAntialiasing );
    p.setBrush( QBrush( Qt::yellow ) );
    p.drawEllipse( QRect( QPoint( 0, 0 ), geometry().size() ) );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : PantiltControl
//  [ 機　能 ] : パンチルトコントロールのコンストラクター
//  [ 引　数 ] : QWidget *parent : 親ウィジェット
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
PantiltControl::PantiltControl( QWidget *parent )
    : QWidget{parent},
      m_label_tilt( this ), m_label_pan( this ),
      m_track_points(),
      m_value_mode(),
      m_pressed( false ),
      m_moved( false ),
      m_last_pos()
{
    m_label_tilt.setText( "チルト" );
    m_label_pan.setText( "パン" );

    m_label_tilt.setObjectName( "graph_axis_label" );
    m_label_pan.setObjectName( "graph_axis_label" );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetValueMode
//  [ 機　能 ] : 値モードの設定
//  [ 引　数 ] : TrackValueMode value_mode : 新しい値モード
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PantiltControl::SetValueMode( TrackValueMode value_mode )
{
    if( m_value_mode == value_mode )
    {
        return;
    }

    m_value_mode = value_mode;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetTrackPoints
//  [ 機　能 ] : ペイントへトラック ポイントを設定する
//  [ 引　数 ] : const QVector<PantiltControl::TrackPointFloatParamGroup> &points : 各新しいポイント
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PantiltControl::SetTrackPoints( const QVector<PantiltControl::TrackPointFloatParamGroup> &points )
{
    m_track_points.clear();

    foreach( const auto &point, points )
    {
        TrackPointData data;
        data.param = point;
        data.widget = MakeSharedQObject<TrackPoint>( this );

        data.widget->SetCoordinate( ConvertValueToCoordinate( QPointF( data.param.pan.current, data.param.tilt.current ) ).toPoint() );
        data.widget->raise();
        data.widget->setVisible( true );
        // connect(data.widget.get(), &TrackPoint::moveRequested, this, &PantiltControl::onTrackPointMoveRequested);

        m_track_points.push_back( data );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : TrackPoints
//  [ 機　能 ] : 現在のトラック ポイントを取得する
//  [ 引　数 ] : void
//  [ 戻り値 ] : QVector<PantiltControl::TrackPointFloatParamGroup> :各トラック ポイント
//--------------------------------------------------------------------------
QVector<PantiltControl::TrackPointFloatParamGroup> PantiltControl::TrackPoints() const
{
    QVector<PantiltControl::TrackPointFloatParamGroup>  result;

    for( const auto &p : m_track_points )
    {
        result.append( p.param );
    }

    return result;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : paintEvent
//  [ 機　能 ] : ウィジェットをペイントする
//  [ 引　数 ] : QPaintEvent *event : ペイントイベントのデータ
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PantiltControl::paintEvent( QPaintEvent *event )
{
    Q_UNUSED( event );
    QPainter p( this );

    p.setRenderHints( QPainter::Antialiasing | QPainter::HighQualityAntialiasing );
    // 黒の背景
    p.fillRect( QRect( QPoint( 0, 0 ), geometry().size() ), QBrush( Qt::black ) );
    p.setPen( QPen( Qt::darkGray ) );
    p.drawRect( QRect( QPoint( 0, 0 ), geometry().size() ) );

    QSize bound = geometry().size();

    // 水平グリッド線を描画する
    for( int i = 0; i <= 100; i += 20 )
    {
        p.setPen( QPen( Qt::darkGray, ( i % 50 == 0 ) ? 1 : 0.2 ) );
        p.drawLine( 0, i * bound.height() / 100.0, bound.width(), i * bound.height() / 100.0 );
    }

    p.setPen( QPen( Qt::darkGray ) );
    p.drawLine( 0, bound.height() / 2, bound.width(), bound.height() / 2 );

    // 垂直のグリッド線を引く
    for( int i = 0; i <= 100; i += 25 )
    {
        p.setPen( QPen( Qt::darkGray, ( i % 50 == 0 ) ? 1 : 0.2 ) );
        p.drawLine( i * bound.width() / 100.0, 0, i * bound.width() / 100.0, bound.height() );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : resizeEvent
//  [ 機　能 ] : リサイズ時のイベント
//  [ 引　数 ] : QResizeEvent *event: リサイズイベントのデータ
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PantiltControl::resizeEvent( QResizeEvent *event )
{
    QWidget::resizeEvent( event );
    m_label_pan.setGeometry( QRect( geometry().width() - 50, geometry().height() / 2 - 22, 50, 22 ) );
    m_label_tilt.setGeometry( QRect( geometry().width() / 2 + 10, 0, 50, 22 ) );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : mousePressEvent
//  [ 機　能 ] : 押したときのイベント
//  [ 引　数 ] : QMouseEvent *event: マウスイベントのデータ
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PantiltControl::mousePressEvent( QMouseEvent *event )
{
    m_pressed = true;
    m_moved = false;
    m_last_pos = event->pos();

    if( m_value_mode == TRACK_MODE_ABSOLUTE )
    {
        for( auto &p : m_track_points )
        {
            MovePointWithConstraints( p, ConvertCoordinateToValue( event->pos() ) );
        }

        emit TrackPointsUpdated();
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : mouseReleaseEvent
//  [ 機　能 ] : マウスを離したときのイベント
//  [ 引　数 ] : QMouseEvent *event: マウスイベントのデータ
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PantiltControl::mouseReleaseEvent( QMouseEvent *event )
{
    m_pressed = false;

    if( m_value_mode == TRACK_MODE_RELATIVE && m_moved )
    {
        emit TrackPointsUpdated();
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : mouseMoveEvent
//  [ 機　能 ] : マウス移動時のイベント
//  [ 引　数 ] : QMouseEvent *event: マウスイベントのデータ
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PantiltControl::mouseMoveEvent( QMouseEvent *event )
{
    if( !m_pressed )
    {
        return;
    }

    if( m_value_mode == TRACK_MODE_RELATIVE )
    {
        m_moved = true;
        // すべてのトラックポイントを同時に移動させる·
        const QPoint diff = event->pos() - m_last_pos;

        for( auto &p : m_track_points )
        {
            const auto new_coordinate = p.widget->Coordinate() + diff;
            MovePointWithConstraints( p, ConvertCoordinateToValue( new_coordinate ) );
        }

        m_last_pos = event->pos();
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : ConvertValueToCoordinate
//  [ 機　能 ] : トラックポイント値をスクリーン座標に変換する
//  [ 引　数 ] : QPointF value : トラックポイント値
//  [ 戻り値 ] : QPointF : スクリーン座標
//--------------------------------------------------------------------------
QPointF PantiltControl::ConvertValueToCoordinate( QPointF value )
{
    value.setY( TC_TRACK_RESOLUTION - value.y() );

    QPointF coordinate( value.x() * geometry().width() / TC_TRACK_RESOLUTION,
                        value.y() * geometry().height() / TC_TRACK_RESOLUTION );

    return coordinate;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : ConvertCoordinateToValue
//  [ 機　能 ] : スクリーン座標をトラックポイント値に変換する
//  [ 引　数 ] : QPointF coordinate : スクリーン座標
//  [ 戻り値 ] : QPointF : トラックポイント値
//--------------------------------------------------------------------------
QPointF PantiltControl::ConvertCoordinateToValue( QPointF coordinate )
{
    QPointF value( coordinate.x() * TC_TRACK_RESOLUTION / geometry().width(),
                   coordinate.y() * TC_TRACK_RESOLUTION / geometry().height() );

    value.setY( TC_TRACK_RESOLUTION - value.y() );

    return value;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : MovePointWithContrains
//  [ 機　能 ] : 最小/最大の制約内でポイントを移動する
//  [ 引　数 ] : TrackPointData &point : 移動するポイントウィジェット
//              QPointF new_value : 各新しい値
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PantiltControl::MovePointWithConstraints( TrackPointData &point, QPointF new_value )
{
    // パン/チルトをこのトラックポイントの最小/最大に制限する
    new_value.setX( qBound( point.param.pan.min, float( new_value.x() ), point.param.pan.max ) );
    new_value.setY( qBound( point.param.tilt.min, float( new_value.y() ), point.param.tilt.max ) );

    QPointF new_pos = ConvertValueToCoordinate( new_value );
    point.widget->SetCoordinate( new_pos.toPoint() );
    point.param.pan.current = new_value.x();
    point.param.tilt.current = new_value.y();
}
