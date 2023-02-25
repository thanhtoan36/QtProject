//--------------------------------------------------------------------------
// [ ファイル名 ] : gridBackground.h
// [ 概      要 ] : グリッド線で背景を描画するウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef GRIDBACKGROUND_H
#define GRIDBACKGROUND_H

#include <QWidget>

class GridBackground : public QWidget
{
    Q_OBJECT

    Q_PROPERTY( QSize GridSize READ GridSize WRITE SetGridSize NOTIFY GridSizeChanged )
    Q_PROPERTY( QSize CellSize READ CellSize WRITE SetCellSize NOTIFY CellSizeChanged )
    Q_PROPERTY( QColor BackgroundColor READ BackgroundColor WRITE SetBackgroundColor NOTIFY BackgroundColorChanged )
    Q_PROPERTY( QColor GridLineColor READ GridLineColor WRITE SetGridLineColor NOTIFY GridLineColorChanged )

public:
    GridBackground( QWidget *parent = nullptr );

    QSize GridSize() const;
    void SetGridSize( const QSize &value );

    QSize CellSize() const;
    void SetCellSize( const QSize &value );

    QColor BackgroundColor() const;
    void SetBackgroundColor( const QColor &value );

    QColor GridLineColor() const;
    void SetGridLineColor( const QColor &value );

signals:
    void GridSizeChanged();
    void CellSizeChanged();
    void BackgroundColorChanged();
    void GridLineColorChanged();

protected slots:
    void UpdateGridSize();

protected:
    virtual void paintEvent( QPaintEvent *e ) override;

private:
    QSize m_gridSize;
    QSize m_cellSize;
    QColor m_backgroundColor;
    QColor m_gridLineColor;
};


#endif // GRIDBACKGROUND_H
