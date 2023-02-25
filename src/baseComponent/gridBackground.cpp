//--------------------------------------------------------------------------
// [ ファイル名 ] : gridBackground.cpp
// [ 概      要 ] : グリッド線で背景を描画するウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "baseComponent/gridBackground.h"
#include <QPainter>
#include <QDebug>

GridBackground::GridBackground( QWidget *parent )
    : QWidget( parent ),
      m_gridSize( 0, 0 ),
      m_cellSize( 1, 1 ),
      m_backgroundColor( QColor::fromRgb( 22, 22, 22 ) ),
      m_gridLineColor( Qt::darkGray )
{
    connect( this, &GridBackground::GridSizeChanged, this, &GridBackground::UpdateGridSize );
    connect( this, &GridBackground::CellSizeChanged, this, &GridBackground::UpdateGridSize );
    connect( this, &GridBackground::GridLineColorChanged, this, &GridBackground::UpdateGridSize );
    connect( this, &GridBackground::BackgroundColorChanged, this, &GridBackground::UpdateGridSize );
    setAttribute( Qt::WA_TransparentForMouseEvents );
}

void GridBackground::paintEvent( QPaintEvent *e )
{
    Q_UNUSED( e );
    QPainter p( this );

    p.setPen( GridLineColor() );
    p.fillRect( QRect( 0, 0, width(), height() ), BackgroundColor() );

    for( int i = 0; i <= GridSize().width(); ++i )
    {
        int x = i * CellSize().width();

        if( i == GridSize().width() )
        {
            x -= 1;    // 最後の行を境界内に保つ
        }

        p.drawLine( x, 0, x, height() );
    }

    for( int i = 0; i <= GridSize().height(); ++i )
    {
        int y = i * CellSize().height();

        if( i == GridSize().height() )
        {
            y -= 1;    // 最後の行を境界内に保つ
        }

        p.drawLine( 0, y, width(), y );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : UpdateGridSize
//  [ 機　能 ] : 現在のグリッド サイズとセル サイズに基づいてウィジェット サイズを更新する
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void GridBackground::UpdateGridSize()
{
    setFixedSize( GridSize().width() * CellSize().width(), GridSize().height() * CellSize().height() );
    update();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : GridSize
//  [ 機　能 ] : グリッド サイズ取得
//  [ 引　数 ] : void
//  [ 戻り値 ] : QSize : グリッド サイズ
//--------------------------------------------------------------------------
QSize GridBackground::GridSize() const
{
    return m_gridSize;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetGridSize
//  [ 機　能 ] : グリッド サイズ設定
//  [ 引　数 ] : const QSize &value : 新しいサイズ
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void GridBackground::SetGridSize( const QSize &value )
{
    if( m_gridSize == value )
    {
        return;
    }

    m_gridSize = value;
    emit GridSizeChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : CellSize
//  [ 機　能 ] : セル サイズ取得
//  [ 引　数 ] : void
//  [ 戻り値 ] : QSize : セル サイズ
//--------------------------------------------------------------------------
QSize GridBackground::CellSize() const
{
    return m_cellSize;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetCellSize
//  [ 機　能 ] : セル サイズ設定
//  [ 引　数 ] : const QSize &value : 新しいセルサイズ
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void GridBackground::SetCellSize( const QSize &value )
{
    if( m_cellSize == value )
    {
        return;
    }

    m_cellSize = value;
    emit CellSizeChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : BackgroundColor
//  [ 機　能 ] : 背景色取得
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : 背景色
//--------------------------------------------------------------------------
QColor GridBackground::BackgroundColor() const
{
    return m_backgroundColor;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetBackgroundColor
//  [ 機　能 ] : 背景色設定
//  [ 引　数 ] : const QColor &value : 新しい背景色
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void GridBackground::SetBackgroundColor( const QColor &value )
{
    if( m_backgroundColor == value )
    {
        return;
    }

    m_backgroundColor = value;
    emit BackgroundColorChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : GridLineColor
//  [ 機　能 ] : グリッド線の色を取得する
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : グリッド線の色
//--------------------------------------------------------------------------
QColor GridBackground::GridLineColor() const
{
    return m_gridLineColor;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetGridLineColor
//  [ 機　能 ] : グリッド線の色を設定する
//  [ 引　数 ] : const QColor &value : 新しいグリッド線の色
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void GridBackground::SetGridLineColor( const QColor &value )
{
    if( m_gridLineColor == value )
    {
        return;
    }

    m_gridLineColor = value;
    emit GridLineColorChanged();
}
