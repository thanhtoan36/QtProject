#ifndef PLAYBACKROWDELEGATE_H
#define PLAYBACKROWDELEGATE_H

#include <QStyledItemDelegate>

class PlaybackRowDelegate : public QStyledItemDelegate
{
public:
    enum Roles
    {
        QueueRole = Qt::UserRole + 1,
        FadeRole,
        DelayRole,
        WeightRole,
        TitleRole,
        MarkingRole,
        MarkingColorRole,
        SelectedRole
    };
    PlaybackRowDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setOrientation(Qt::Orientation orientation);

private:
    Qt::Orientation m_orientation;
};

#endif // PLAYBACKROWDELEGATE_H
