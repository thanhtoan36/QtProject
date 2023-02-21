#include "playbackControl/playbackControlHorizon.h"
#include "playbackControl/playbackControl_define.hpp"
#include "utility.h"

PlaybackControlHorizon::PlaybackControlHorizon(QWidget *parent)
    : PlaybackControl(parent)
{
    setFixedSize(PLC_SCREENSIZE_HORIZON);
    m_column_width = PLC_COLUMN_WIDTH_HORIZON;

    m_list_view.setGeometry(PLC_LIST_GEOMETRY_HORIZON.adjusted(0, 36, 0, 0));

    m_headers.clear();
    QStringList headers = {"", "キュー", "フェード", "ディレイ", "ウェイト", "リンク", "タイトル" };
    QRect cell(PLC_LIST_GEOMETRY_HORIZON.topLeft(), QSize(0, 36));
    for (int i = 0; i < m_column_width.length(); i++) {
        cell.setWidth(m_column_width[i]);

        auto label = MakeSharedQObject<QLabel>(this);
        label->setGeometry(cell);
        label->setText(headers[i]);
        label->setObjectName("playback_header");

        m_headers.append(label);

        // Move to the right
        cell.moveLeft(cell.left() + cell.width());
    }

    m_row_delegate.SetColumnsWidth(m_column_width);
    m_list_view.setItemDelegate(&m_row_delegate);

    m_grid_overlay.setGeometry(PLC_LIST_GEOMETRY_HORIZON);
    m_grid_overlay.setColumnsWidth(m_column_width);
    m_grid_overlay.raise();
}
