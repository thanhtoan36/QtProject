//--------------------------------------------------------------------------
// [ ファイル名 ] : customColorPickerXY.cpp
// [ 概   要 ] : カラーピッカーXYウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#include "colorPickerControl/customColorPickerXY.h"
#include "colorPickerControl/colorPickerControl_define.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <math.h>


//Inverse sRGB gamma correction, transforms R' to R
#define INV_GAMMA_CORRECTION(t)                                                \
    (((t) <= 0.0404482362771076) ? ((t) / 12.92)                               \
     : pow(((t) + 0.055) / 1.055, 2.4))

//--------------------------------------------------------------------------
//  [ 関数名   ] : CustomColorPickerXY
//  [ 機能名   ] : カスタムカラーピッカーXYのコンストラクター
//  [ 引数     ] : QWidget *parent: 親ウィジェット
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
CustomColorPickerXY::CustomColorPickerXY( QWidget *parent ) : QWidget( parent ),
    m_plot_area( QRectF( 36, 0, CPC_PICKER_XY_GEOMETRY.height(), CPC_PICKER_XY_GEOMETRY.height() ) )
{
    QImage img( ":/resources/cie_img.png" );
    m_img = img.scaled( CPC_PICKER_XY_GEOMETRY.height(), CPC_PICKER_XY_GEOMETRY.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation );
    SetColor( Qt::white );
    m_white_xy = m_valid_xy;
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetColor
//  [ 機能名   ] : 色を設定し、x y値に変換する
//  [ 引数          ] : const QColor &color : 要設定の色
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void CustomColorPickerXY::SetColor( const QColor &color )
{
    float x, y, z;
    RBG2XY( color.red(), color.green(), color.blue(), x, y, z );
    SetXy( QPointF( x, y ) );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetXy
//  [ 機能名   ] : x yの値を設定する
//  [ 引数          ] : const QPointF &xy : xy座標
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void CustomColorPickerXY::SetXy( const QPointF &xy )
{
    QPointF nearest = FindNearestXy( xy );
    m_pointer = MapToPosition( nearest );
    m_pointer_visible = true;
    update();

    if( nearest != m_valid_xy )
    {
        m_valid_xy = nearest;
        emit XyChanged( nearest );
        emit ColorChanged( Color() );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : Xy
//  [ 機能名   ] : 有効なxy値を取得する
//  [ 引数     ] : void
//  [ 戻り値    ] : QPointF: xyリザルト
//--------------------------------------------------------------------------
QPointF CustomColorPickerXY::Xy() const
{
    return m_valid_xy;
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : Color
//  [ 機能名   ] : xyからカラーを取得する
//  [ 引数     ] : void
//  [ 戻り値    ] : QColor: 有効なカラー
//--------------------------------------------------------------------------
QColor CustomColorPickerXY::Color() const
{
    return GetColor( m_valid_xy );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : GetColor
//  [ 機能名   ] : xyからカラーを取得する
//  [ 引数     ] : QPointF xy: xy値
//  [ 戻り値    ] : QColor: 有効なカラー
//--------------------------------------------------------------------------
QColor CustomColorPickerXY::GetColor( QPointF xy ) const
{
    return m_cie_maker.GetColor( xy );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : paintEvent
//  [ 機能名   ] : ペイントイベントを上書きして、ウィジェットを描画する
//  [ 引数          ] : QPaintEvent *
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void CustomColorPickerXY::paintEvent( QPaintEvent * )
{
    QPainter p( this );
    p.setRenderHints( QPainter::Antialiasing | QPainter::HighQualityAntialiasing );

    // Black background
    p.fillRect( QRect( QPoint( 0, 0 ), geometry().size() ), QBrush( Qt::black ) );

    p.setPen( QPen( Qt::gray, 1 ) );
    p.drawLine( m_plot_area.bottomLeft(), m_plot_area.topLeft() );
    p.drawLine( m_plot_area.bottomLeft(), m_plot_area.bottomRight() );

    for( int i = 1; i <= 10; i++ )
    {
        p.setPen( QPen( Qt::lightGray, 0.5 ) );
        p.drawLine( QPointF( m_plot_area.bottomLeft().rx() + 24 * i, m_plot_area.bottomLeft().ry() ), QPointF( m_plot_area.topLeft().rx() + 24 * i, m_plot_area.topLeft().ry() ) );
        p.drawLine( QPointF( m_plot_area.topLeft().rx(), m_plot_area.topLeft().ry() + 24 * ( i - 1 ) ), QPointF( m_plot_area.topRight().rx(), m_plot_area.topRight().ry() + 24 * ( i - 1 ) ) );
    }

    p.drawImage( m_plot_area, m_img );

    if( m_pointer_visible )
    {
        p.setPen( QPen( Qt::white, 1 ) );
        p.drawEllipse( m_pointer, 5, 5 );
        p.setPen( QPen( Qt::gray, 1 ) );
        p.drawEllipse( m_pointer, 6, 6 );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : mousePressEvent
//  [ 機能名   ] : 押下イベントを処理して、色とxyを選択する
//  [ 引数          ] : QMouseEvent *event : 押下イベント
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void CustomColorPickerXY::mousePressEvent( QMouseEvent *event )
{
    if( m_plot_area.contains( event->pos() ) )
    {
        QPointF p = MapToValue( event->pos() );
        CPointF curP( p.x(), p.y() );

        if( m_cie_maker.IsPointInsideBound( curP ) )
        {
            SetXy( p );
            emit Picked();
        }
    }
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : MapToPosition
//  [ 機能名   ] : CIE xyの値をウィジェットの座標に変換する
//  [ 引数          ] : const QPointF &p : xy座標
//  [ 戻り値    ] : QPointF
//--------------------------------------------------------------------------
QPointF CustomColorPickerXY::MapToPosition( const QPointF &p )
{
    return QPointF( m_plot_area.x() + m_plot_area.width() * p.x(),
                    m_offset.height() + m_plot_area.height() * ( 1 - p.y() ) );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : MapToValue
//  [ 機能名   ] : マウスプレスポイントをCIE xyに変換する
//  [ 引数          ] : const QPointF &p : xy座標
//  [ 戻り値    ] : QPointF
//--------------------------------------------------------------------------
QPointF CustomColorPickerXY::MapToValue( const QPoint &p )
{
    return QPointF( 1.0f * ( p.x() - m_plot_area.x() ) / m_plot_area.width(),
                    1.0f * ( m_plot_area.y() + m_plot_area.height() - p.y() ) / m_plot_area.height() );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : RBG2XY
//  [ 機能名   ] : RGBの色をxyzに変換する
//  [ 引数          ] : float R : 赤値
//                float G : グリーンバリュー
//                float B : ブルーバリュー
//                float &x : x値
//                float &y : y値
//                float &z : z値
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void CustomColorPickerXY::RBG2XY( float R, float G, float B, float &x, float &y, float &z )
{
    R = INV_GAMMA_CORRECTION( R );
    G = INV_GAMMA_CORRECTION( G );
    B = INV_GAMMA_CORRECTION( B );

    float X, Y, Z;
    X = ( float )( 0.4123955889674142161 * R + 0.3575834307637148171 * G + 0.1804926473817015735 * B );
    Y = ( float )( 0.2125862307855955516 * R + 0.7151703037034108499 * G + 0.07220049864333622685 * B );
    Z = ( float )( 0.01929721549174694484 * R + 0.1191838645808485318 * G + 0.9504971251315797660 * B );

    x = X / ( X + Y + Z );
    y = Y / ( X + Y + Z );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : FindNearestXy
//  [ 機能名   ] : 座標内から外れた場合、最も近いxyを探す
//  [ 引数      ] : QPointF target : ターゲット座標
//  [ 戻り値    ] : QPointF: 最も近いxy
//--------------------------------------------------------------------------
QPointF CustomColorPickerXY::FindNearestXy( QPointF target )
{
    if( m_cie_maker.IsPointInsideBound( CPointF( target.x(), target.y() ) ) )
    {
        return target;
    }

    // find nearest valid point from white center point
    QPointF nearest = m_white_xy;
    auto diff = target - nearest;

    for( auto i = nearest; m_cie_maker.IsPointInsideBound( CPointF( i.x(), i.y() ) ); i += diff * 0.001 )
    {
        nearest = i;
    }

    return nearest;
}

