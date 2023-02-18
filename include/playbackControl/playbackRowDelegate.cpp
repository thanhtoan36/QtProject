#include "playbackRowDelegate.h"
#include <QPainter>
#include <QDebug>

PlaybackRowDelegate::PlaybackRowDelegate(QObject *parent)
    : QStyledItemDelegate(parent),
      m_columnsWidth()
{

}

void PlaybackRowDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPen textPen, borderPen;
    borderPen = QPen(Qt::darkGray);

    int x = 0;
    QVector<QRect> cells;
    for (int i = 0; i < m_columnsWidth.length(); i++) {
        cells.append(QRect(option.rect.left() + x, option.rect.top(), m_columnsWidth[i], option.rect.height()));
        x += m_columnsWidth[i];
    }

    if (cells.isEmpty())
        return;

    bool selected = index.data(Roles::SelectedRole).toBool();
    if(selected) {
        borderPen = QColor::fromRgb(18, 110, 67);
        borderPen.setWidth(2);
        textPen = QColor::fromRgb(198, 89, 21);
    } else {
        borderPen = QPen(Qt::transparent);
        textPen = QColor::fromRgb(191, 191, 191);
    }

    painter->setPen(borderPen);
    painter->drawRect(option.rect.adjusted(0, 0, 0, -1));

    QColor markingColor = QColor(index.data(Roles::MarkingColorRole).toString());
    QString marking = index.data(Roles::MarkingRole).toString();
    QString queue = index.data(Roles::QueueRole).toString();
    QString fade = index.data(Roles::FadeRole).toString();
    QString delay = index.data(Roles::DelayRole).toString();
    QString weight = index.data(Roles::WeightRole).toString();
    QString link = index.data(Roles::LinkRole).toString();
    QString title = index.data(Roles::TitleRole).toString();

    QRect r = cells[0];
    painter->setPen(markingColor);
    painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, marking, &r);

    painter->setPen(textPen);
    r = cells[1];
    painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, queue, &r);
    r = cells[2];
    painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, fade, &r);
    r = cells[3];
    painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, delay, &r);
    r = cells[4];
    painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, weight, &r);

    if (cells.length() > 5) {
        r = cells[5];
        painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, link, &r);
        r = cells[6];
        painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, title, &r);
    }
}

QSize PlaybackRowDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(0, 36);
}

void PlaybackRowDelegate::setColumnsWidth(const QVector<int> &columnsWidth)
{
    m_columnsWidth = columnsWidth;
}
