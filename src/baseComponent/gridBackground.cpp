#include "baseComponent/gridBackground.h"
#include <QPainter>
#include <QDebug>

GridBackground::GridBackground(QWidget *parent)
    : QWidget(parent),
      m_gridSize(0, 0),
      m_cellSize(1, 1),
      m_backgroundColor(QColor::fromRgb(22, 22, 22)),
      m_gridLineColor(Qt::darkGray)
{
    connect(this, &GridBackground::gridSizeChanged, this, &GridBackground::updateGridSize);
    connect(this, &GridBackground::cellSizeChanged, this, &GridBackground::updateGridSize);
    connect(this, &GridBackground::gridLineColorChanged, this, &GridBackground::updateGridSize);
    connect(this, &GridBackground::backgroundColorChanged, this, &GridBackground::updateGridSize);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void GridBackground::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);

    p.setPen(gridLineColor());
    p.fillRect(QRect(0, 0, width(), height()), backgroundColor());

    for (int i = 0; i <= gridSize().width(); ++i) {
        int x = i * cellSize().width();
        if (i == gridSize().width()) x -= 1; // keep the last line inside boundary
        p.drawLine(x, 0, x, height());
    }
    for (int i = 0; i <= gridSize().height(); ++i) {
        int y = i * cellSize().height();
        if (i == gridSize().height()) y -= 1; // keep the last line inside boundary
        p.drawLine(0, y, width(), y);
    }
}

void GridBackground::updateGridSize()
{
    setFixedSize(gridSize().width() * cellSize().width(), gridSize().height() * cellSize().height());
    update();
}

QSize GridBackground::gridSize() const
{
    return m_gridSize;
}

void GridBackground::setGridSize(const QSize &newGridSize)
{
    if (m_gridSize == newGridSize)
        return;
    m_gridSize = newGridSize;
    emit gridSizeChanged();
}

QSize GridBackground::cellSize() const
{
    return m_cellSize;
}

void GridBackground::setCellSize(const QSize &newCellSize)
{
    if (m_cellSize == newCellSize)
        return;
    m_cellSize = newCellSize;
    emit cellSizeChanged();
}

QColor GridBackground::backgroundColor() const
{
    return m_backgroundColor;
}

void GridBackground::setBackgroundColor(const QColor &newBackgroundColor)
{
    if (m_backgroundColor == newBackgroundColor)
        return;
    m_backgroundColor = newBackgroundColor;
    emit backgroundColorChanged();
}

QColor GridBackground::gridLineColor() const
{
    return m_gridLineColor;
}

void GridBackground::setGridLineColor(const QColor &newGridLineColor)
{
    if (m_gridLineColor == newGridLineColor)
        return;
    m_gridLineColor = newGridLineColor;
    emit gridLineColorChanged();
}
