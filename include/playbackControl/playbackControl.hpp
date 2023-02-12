#ifndef PLAYBACKCONTROL_H
#define PLAYBACKCONTROL_H

#include "baseComponent/panelControlBase.h"
#include "baseComponent/selectButton.h"
#include "playbackControl_datatypes.h"

#include <QListWidget>
#include <QLabel>
#include <QTimer>


class ListColumnSeperatorLineOverlay : public QWidget
{
    Q_OBJECT
public:
    ListColumnSeperatorLineOverlay(QWidget *parent = nullptr);
    void setColumnsWidth(const QVector<int> &columnsWidth);
protected:
    virtual void paintEvent(QPaintEvent *e) override;
private:
    QVector<int> m_columnsWidth;
};

class PlaybackControl : public PanelControlBase
{
    Q_OBJECT

public:
    PlaybackControl(QWidget *parent = nullptr);
    virtual void SetupUiComponents() override;

protected:
    void onItemClicked(QListWidgetItem *item);
    void onItemDoubleClicked(QListWidgetItem *item);
    bool isMouseInsideMarkingColumn() const;

protected:
    QListWidget m_list_view;
    // QHeaderView m_header_view;
    QListWidgetItem *m_clicked_item;
    QTimer m_double_click_stablize_timer;
    QVector<int> m_column_width;
    QVector<QSharedPointer<QLabel>> m_headers;
    ListColumnSeperatorLineOverlay m_grid_overlay;
};

#endif // PLAYBACKCONTROL_H
