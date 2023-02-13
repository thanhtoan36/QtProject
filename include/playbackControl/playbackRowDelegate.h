#ifndef PLAYBACKROWDELEGATE_H
#define PLAYBACKROWDELEGATE_H

#include <QStyledItemDelegate>

class PlaybackRowDelegate : public QStyledItemDelegate
{
public:
    enum Roles
    {
        QueueRole = Qt::UserRole + 1,
        LinkRole,
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

    void setColumnsWidth(const QVector<int> &columnsWidth);

private:
    QVector<int> m_columnsWidth;
};

#endif // PLAYBACKROWDELEGATE_H
