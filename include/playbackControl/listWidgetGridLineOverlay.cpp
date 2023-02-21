#include "playbackControl/listWidgetGridLineOverlay.h"
#include <QPainter>

ListWidgetGridLineOverlay::ListWidgetGridLineOverlay(QWidget *parent)
    : QWidget(parent),
      m_columns_width()
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void ListWidgetGridLineOverlay::SetColumnsWidth(const QVector<int> &value)
{
    m_columns_width = value;
}

void ListWidgetGridLineOverlay::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);

    p.setPen(Qt::darkGray);
    p.drawRect(QRect(QPoint(0, 0), size()));

    int x = 0;
    for (int i = 0; i < m_columns_width.length(); ++i) {
        x += m_columns_width[i];
        p.drawLine(x, 0, x, height());
    }
}
