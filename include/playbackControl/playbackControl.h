//--------------------------------------------------------------------------
// [ ファイル名 ] : playbackControl.h
// [ 概      要 ] : PlaybackControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef PLAYBACKCONTROL_H
#define PLAYBACKCONTROL_H

#include "baseComponent/panelControlBase.h"
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
    virtual void SetDispParamData(PLAYBACK_DISP_PARAM *param);

protected slots:
    void OnMarkingSelected(const QString &marking, const QColor &color);

protected:
    void OnItemClicked(QListWidgetItem *item);
    void OnItemDoubleClicked(QListWidgetItem *item);
    bool IsMouseInsideMarkingColumn() const;

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
