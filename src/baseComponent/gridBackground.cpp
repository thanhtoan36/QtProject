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

void GridBackground::UpdateGridSize()
{
    setFixedSize( GridSize().width() * CellSize().width(), GridSize().height() * CellSize().height() );
    update();
}

QSize GridBackground::GridSize() const
{
    return m_gridSize;
}

void GridBackground::SetGridSize( const QSize &value )
{
    if( m_gridSize == value )
    {
        return;
    }

    m_gridSize = value;
    emit GridSizeChanged();
}

QSize GridBackground::CellSize() const
{
    return m_cellSize;
}

void GridBackground::SetCellSize( const QSize &value )
{
    if( m_cellSize == value )
    {
        return;
    }

    m_cellSize = value;
    emit CellSizeChanged();
}

QColor GridBackground::BackgroundColor() const
{
    return m_backgroundColor;
}

void GridBackground::SetBackgroundColor( const QColor &value )
{
    if( m_backgroundColor == value )
    {
        return;
    }

    m_backgroundColor = value;
    emit BackgroundColorChanged();
}

QColor GridBackground::GridLineColor() const
{
    return m_gridLineColor;
}

void GridBackground::SetGridLineColor( const QColor &value )
{
    if( m_gridLineColor == value )
    {
        return;
    }

    m_gridLineColor = value;
    emit GridLineColorChanged();
}
