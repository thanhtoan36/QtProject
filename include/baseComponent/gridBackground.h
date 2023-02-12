#ifndef GRIDBACKGROUND_H
#define GRIDBACKGROUND_H

#include <QWidget>

class GridBackground : public QWidget {
    Q_OBJECT

    Q_PROPERTY(QSize gridSize READ gridSize WRITE setGridSize NOTIFY gridSizeChanged)
    Q_PROPERTY(QSize cellSize READ cellSize WRITE setCellSize NOTIFY cellSizeChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor gridLineColor READ gridLineColor WRITE setGridLineColor NOTIFY gridLineColorChanged)

public:
    GridBackground(QWidget *parent = nullptr);

    QSize gridSize() const;
    void setGridSize(const QSize &newGridSize);

    QSize cellSize() const;
    void setCellSize(const QSize &newCellSize);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &newBackgroundColor);

    QColor gridLineColor() const;
    void setGridLineColor(const QColor &newGridLineColor);

signals:
    void gridSizeChanged();
    void cellSizeChanged();
    void backgroundColorChanged();
    void gridLineColorChanged();

public slots:
    void updateGridSize();

protected:
    virtual void paintEvent(QPaintEvent *e) override;

private:
    QSize m_gridSize;
    QSize m_cellSize;
    QColor m_backgroundColor;
    QColor m_gridLineColor;
};


#endif // GRIDBACKGROUND_H
