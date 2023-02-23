//--------------------------------------------------------------------------
// [ ファイル名 ] : gridBackground.cpp
// [ 概      要 ] : Widget to draw background with grid lines
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
            x -= 1;    // keep the last line inside boundary
        }

        p.drawLine( x, 0, x, height() );
    }

    for( int i = 0; i <= GridSize().height(); ++i )
    {
        int y = i * CellSize().height();

        if( i == GridSize().height() )
        {
            y -= 1;    // keep the last line inside boundary
        }

        p.drawLine( 0, y, width(), y );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : UpdateGridSize
//  [ 機　能 ] : Update widget size base on the current grid size and cell size
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
//  [ 機　能 ] : Get the grid size
//  [ 引　数 ] : void
//  [ 戻り値 ] : QSize : Grid size
//--------------------------------------------------------------------------
QSize GridBackground::GridSize() const
{
    return m_gridSize;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetGridSize
//  [ 機　能 ] : Set the grid size
//  [ 引　数 ] : const QSize &value : new size
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
//  [ 機　能 ] : Get the cell size
//  [ 引　数 ] : void
//  [ 戻り値 ] : QSize : cell size
//--------------------------------------------------------------------------
QSize GridBackground::CellSize() const
{
    return m_cellSize;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetCellSize
//  [ 機　能 ] : Set the cell size
//  [ 引　数 ] : const QSize &value : new cell size
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
//  [ 機　能 ] : Get the background color
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : background color
//--------------------------------------------------------------------------
QColor GridBackground::BackgroundColor() const
{
    return m_backgroundColor;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetBackgroundColor
//  [ 機　能 ] : Set the background color
//  [ 引　数 ] : const QColor &value : new background color
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
//  [ 機　能 ] : Get the grid line color
//  [ 引　数 ] : void
//  [ 戻り値 ] : QColor : grid line color
//--------------------------------------------------------------------------
QColor GridBackground::GridLineColor() const
{
    return m_gridLineColor;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetGridLineColor
//  [ 機　能 ] : Set the grid line color
//  [ 引　数 ] : const QColor &value : new grid line color
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
