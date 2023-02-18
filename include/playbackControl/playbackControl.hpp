#ifndef PLAYBACKCONTROL_H
#define PLAYBACKCONTROL_H

#include "baseComponent/panelControlBase.h"
#include "baseComponent/selectButton.h"
#include "playbackControl_datatypes.h"

#include "playbackRowDelegate.h"
#include "listWidgetGridLineOverlay.h"
#include "markingPickerPopup.h"

#include <QListWidget>
#include <QLabel>
#include <QTimer>

class PlaybackControl : public PanelControlBase
{
    Q_OBJECT

public:
    PlaybackControl(QWidget *parent = nullptr);
    void setDispParamData(PLAYBACK_DISP_PARAM *param);

protected slots:
    void onMarkingSelected(const QString &marking, const QColor &color);

protected:
    void onItemClicked(QListWidgetItem *item);
    void onItemDoubleClicked(QListWidgetItem *item);
    bool isMouseInsideMarkingColumn() const;

protected:
    QListWidget m_list_view;

    QListWidgetItem *m_clicked_item;
    bool m_double_clicked;
    QTimer m_double_click_stablize_timer;

    QVector<int> m_column_width;
    QVector<QSharedPointer<QLabel>> m_headers;

    ListWidgetGridLineOverlay m_grid_overlay;
    PlaybackRowDelegate m_row_delegate;

    MarkingPickerPopup m_marking_picker_popup;
};

#endif // PLAYBACKCONTROL_H
