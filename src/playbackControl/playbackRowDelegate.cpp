//--------------------------------------------------------------------------
// [ ファイル名 ] : playbackRowDelegate.cpp
// [ 概      要 ] : Represent a delegate for QListWidget to paint the rows
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "playbackControl/playbackRowDelegate.h"
#include <QPainter>
#include <QDebug>

PlaybackRowDelegate::PlaybackRowDelegate( QObject *parent )
    : QStyledItemDelegate( parent ),
      m_columns_width()
{

}

void PlaybackRowDelegate::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QPen text_pen, border_pen;
    border_pen = QPen( Qt::darkGray );

    int x = 0;
    QVector<QRect> cells;

    for( int i = 0; i < m_columns_width.length(); i++ )
    {
        cells.append( QRect( option.rect.left() + x, option.rect.top(), m_columns_width[i], option.rect.height() ) );
        x += m_columns_width[i];
    }

    if( cells.isEmpty() )
    {
        return;
    }

    bool selected = index.data( Roles::SelectedRole ).toBool();

    if( selected )
    {
        border_pen = QColor::fromRgb( 18, 110, 67 );
        border_pen.setWidth( 2 );
        text_pen = QColor::fromRgb( 198, 89, 21 );
    }
    else
    {
        border_pen = QPen( Qt::transparent );
        text_pen = QColor::fromRgb( 191, 191, 191 );
    }

    painter->setPen( border_pen );
    painter->drawRect( option.rect.adjusted( 0, 0, 0, -1 ) );

    QColor marking_color = QColor( index.data( Roles::MarkingColorRole ).toString() );
    QString marking = index.data( Roles::MarkingRole ).toString();
    QString queue = index.data( Roles::QueueRole ).toString();
    QString fade = index.data( Roles::FadeRole ).toString();
    QString delay = index.data( Roles::DelayRole ).toString();
    QString weight = index.data( Roles::WeightRole ).toString();
    QString link = index.data( Roles::LinkRole ).toString();
    QString title = index.data( Roles::TitleRole ).toString();

    QRect r = cells[0];
    painter->setPen( marking_color );
    painter->drawText( r, Qt::AlignCenter | Qt::TextWordWrap, marking, &r );

    painter->setPen( text_pen );
    r = cells[1];
    painter->drawText( r, Qt::AlignCenter | Qt::TextWordWrap, queue, &r );
    r = cells[2];
    painter->drawText( r, Qt::AlignCenter | Qt::TextWordWrap, fade, &r );
    r = cells[3];
    painter->drawText( r, Qt::AlignCenter | Qt::TextWordWrap, delay, &r );
    r = cells[4];
    painter->drawText( r, Qt::AlignCenter | Qt::TextWordWrap, weight, &r );

    if( cells.length() > 5 )
    {
        r = cells[5];
        painter->drawText( r, Qt::AlignCenter | Qt::TextWordWrap, link, &r );
        r = cells[6];
        painter->drawText( r, Qt::AlignCenter | Qt::TextWordWrap, title, &r );
    }
}

QSize PlaybackRowDelegate::sizeHint( const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    return QSize( 0, 36 );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetColumnsWidth
//  [ 機　能 ] : Set the widths for each columns
//  [ 引　数 ] : const QVector<int> &value : the list of width values
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PlaybackRowDelegate::SetColumnsWidth( const QVector<int> &value )
{
    m_columns_width = value;
}
