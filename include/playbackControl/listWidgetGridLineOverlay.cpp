#include "playbackControl/listWidgetGridLineOverlay.h"
#include <QPainter>

ListWidgetGridLineOverlay::ListWidgetGridLineOverlay(QWidget *parent)
    : QWidget(parent),
      m_columnsWidth()
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void ListWidgetGridLineOverlay::setColumnsWidth(const QVector<int> &columnsWidth)
{
    m_columnsWidth = columnsWidth;
}

void ListWidgetGridLineOverlay::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);

    p.setPen(Qt::darkGray);
    p.drawRect(QRect(QPoint(0, 0), size()));

    int x = 0;
    for (int i = 0; i < m_columnsWidth.length(); ++i) {
        x += m_columnsWidth[i];
        p.drawLine(x, 0, x, height());
    }
}
