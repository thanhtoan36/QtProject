//--------------------------------------------------------------------------
// [ ファイル名 ] : listWidgetGridLineOverlay.cpp
// [ 概      要 ] : Draw grid lines on the PlaybackControl's table
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "playbackControl/listWidgetGridLineOverlay.h"
#include <QPainter>

ListWidgetGridLineOverlay::ListWidgetGridLineOverlay(QWidget *parent)
    : QWidget(parent),
      m_columns_width()
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetColumnsWidth
//  [ 機　能 ] : Set the width for the columns
//  [ 引　数 ] : const QVector<int> &value : The width values
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
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
