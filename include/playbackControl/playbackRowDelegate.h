//--------------------------------------------------------------------------
// [ ファイル名 ] : playbackRowDelegate.h
// [ 概      要 ] : 行を描画するためのQListWidgetのデリゲートを表す
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef PLAYBACKROWDELEGATE_H
#define PLAYBACKROWDELEGATE_H

#include <QStyledItemDelegate>

class PlaybackRowDelegate : public QStyledItemDelegate
{
    Q_OBJECT
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
    PlaybackRowDelegate( QObject *parent = nullptr );

    void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const override;
    QSize sizeHint( const QStyleOptionViewItem &option, const QModelIndex &index ) const override;

    void SetColumnsWidth( const QVector<int> &value );

private:
    QVector<int> m_columns_width;
};

#endif // PLAYBACKROWDELEGATE_H
