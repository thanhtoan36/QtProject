#include "playbackControl/playbackControl.hpp"
#include "playbackControl/playbackControl_define.hpp"
#include "playbackControl/playbackRowDelegate.h"
#include "utility.h"

#include <QListWidgetItem>
#include <QPainter>

PlaybackControl::PlaybackControl(QWidget *parent)

    : PanelControlBase(parent),
      m_list_view(this),
      m_clicked_item(nullptr),
      m_double_click_stablize_timer(this),
      m_grid_overlay(this)
      // m_header_view(Qt::Horizontal, &m_list_view)
{
    m_column_width = PLC_COLUMN_WIDTH;
    setFixedSize(PLC_SCREENSIZE);
    m_list_view.setGeometry(PLC_LIST_GEOMETRY.adjusted(0, 48, 0, 0));
    m_list_view.setObjectName("playback_list");

    m_list_view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_list_view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_list_view.setAlternatingRowColors(true);

    // Use timer to prevent onItemClicked() from being miss fired before & after onItemDoubleClicked() event
    connect(&m_list_view, &QListWidget::itemClicked, this, [&](QListWidgetItem *item){
        if (!isMouseInsideMarkingColumn()) return;
        if (m_double_click_stablize_timer.isActive()) {
            m_double_click_stablize_timer.stop();
            return;
        }
        m_double_click_stablize_timer.start();
        m_clicked_item = item;
    });
    connect(&m_list_view, &QListWidget::itemDoubleClicked, this, [&](QListWidgetItem *item){
        if (!isMouseInsideMarkingColumn()) return;
        m_clicked_item = nullptr;
        onItemDoubleClicked(item);
    });
    connect(&m_double_click_stablize_timer, &QTimer::timeout, this, [&](){
        if (!m_clicked_item)
            return;
        onItemClicked(m_clicked_item);
        m_clicked_item = nullptr;
    });
    m_double_click_stablize_timer.setTimerType(Qt::PreciseTimer);
    m_double_click_stablize_timer.setSingleShot(true);
    m_double_click_stablize_timer.setInterval(200);

    m_grid_overlay.setGeometry(PLC_LIST_GEOMETRY);
    m_grid_overlay.setColumnsWidth(m_column_width);

    QStringList headers = {"", "キュー", "フェード", "「ディレイ", "ウェイト" };
    QRect cell(0, 0, 0, 48);
    for (int i = 0; i < m_column_width.length(); i++) {
        cell.setWidth(m_column_width[i]);
        auto label = MakeSharedQObject<QLabel>(this);
        label->setGeometry(cell);
        label->setText(headers[i]);
        label->setObjectName("playback_header");
        m_headers.append(label);
        cell.setX(cell.x() + cell.width());
    }
}

void PlaybackControl::SetupUiComponents()
{
    for (int i = 0; i < 20; ++i) {
#if 1
        auto item = new QListWidgetItem(&m_list_view, QListWidgetItem::ItemType::Type);
        item->setData(PlaybackRowDelegate::Roles::SelectedRole, i == 1);
        item->setData(PlaybackRowDelegate::Roles::MarkingColorRole, QColor(Qt::green).name());
        item->setData(PlaybackRowDelegate::Roles::MarkingRole, "");
        item->setData(PlaybackRowDelegate::Roles::QueueRole, "2");
        item->setData(PlaybackRowDelegate::Roles::FadeRole, "3");
        item->setData(PlaybackRowDelegate::Roles::DelayRole, "0/1.3");
        item->setData(PlaybackRowDelegate::Roles::WeightRole, "?");
        item->setData(PlaybackRowDelegate::Roles::TitleRole, "Title");
        m_list_view.addItem(item);
#endif
    }
    auto d = new PlaybackRowDelegate(&m_list_view);
    m_list_view.setItemDelegate(d);
}

void PlaybackControl::onItemClicked(QListWidgetItem *item)
{
    Q_ASSERT(item);
    item->setData(PlaybackRowDelegate::Roles::MarkingRole, "●");
}

void PlaybackControl::onItemDoubleClicked(QListWidgetItem *item)
{
    Q_ASSERT(item);
    item->setData(PlaybackRowDelegate::Roles::MarkingRole, " ");
}

bool PlaybackControl::isMouseInsideMarkingColumn() const
{
    int colSize = m_column_width[0];
    return m_list_view.mapFromGlobal(QCursor::pos()).x() <= colSize;
}

ListColumnSeperatorLineOverlay::ListColumnSeperatorLineOverlay(QWidget *parent)
    : QWidget(parent),
      m_columnsWidth()
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void ListColumnSeperatorLineOverlay::setColumnsWidth(const QVector<int> &columnsWidth)
{
    m_columnsWidth = columnsWidth;
}

void ListColumnSeperatorLineOverlay::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);

    p.setPen(Qt::darkGray);
    p.drawRect(QRect(QPoint(0, 0), size()));

    int x = 0;
    for (int i = 0; i < m_columnsWidth.length(); ++i) {
        x += m_columnsWidth[i];
        p.drawLine(x, 0, x, height());
    }
}
