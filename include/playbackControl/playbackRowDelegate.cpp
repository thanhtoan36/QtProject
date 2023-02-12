#include "playbackRowDelegate.h"
#include "playbackControl/playbackControl_define.hpp"
#include <QPainter>
#include <QDebug>

PlaybackRowDelegate::PlaybackRowDelegate(QObject *parent)
    : QStyledItemDelegate(parent),
      m_orientation(Qt::Vertical)
{

}

void PlaybackRowDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPen textPen, borderPen;
    borderPen = QPen(Qt::darkGray);

    QVector<int> columnWidth = (m_orientation == Qt::Vertical) ? PLC_COLUMN_WIDTH : PLC_COLUMN_WIDTH_HORIZON;

    int x = 0;
    QVector<QRect> cells;
    for (int i = 0; i < columnWidth.length(); i++) {
        cells.append(QRect(option.rect.left() + x, option.rect.top(), columnWidth[i], option.rect.height()));
        x += columnWidth[i];
    }


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
    QString title = index.data(Roles::TitleRole).toString();

    QRect r = cells[0];
    auto font = painter->font();
    auto fontBackup = painter->font();
    font.setPixelSize(24);

    painter->setFont(font);
    painter->setPen(markingColor);
    painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, marking, &r);

    painter->setFont(fontBackup);
    painter->setPen(textPen);
    r = cells[1];
    painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, queue, &r);
    r = cells[2];
    painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, fade, &r);
    r = cells[3];
    painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, delay, &r);
    r = cells[4];
    painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, weight, &r);
    if (m_orientation == Qt::Horizontal) {
        r = cells[5];
        painter->drawText(r, Qt::AlignCenter | Qt::TextWordWrap, title, &r);
    }
}

QSize PlaybackRowDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (m_orientation == Qt::Vertical) {
        return QSize(312, 48);
    } else {
        return QSize(780, 48);
    }
}

void PlaybackRowDelegate::setOrientation(Qt::Orientation orientation)
{
    m_orientation = orientation;
}
