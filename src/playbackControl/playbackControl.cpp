//--------------------------------------------------------------------------
// [ ファイル名 ] : playbackControl.cpp
// [ 概      要 ] : PlaybackControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "playbackControl/playbackControl.h"
#include "playbackControl/playbackControl_define.h"
#include "utility.h"

#include <QListWidgetItem>

//--------------------------------------------------------------------------
//  [ 関数名 ] : PlaybackControl
//  [ 機　能 ] : プレイバックコントロールのコンストラクター
//  [ 引　数 ] : QWidget *parent : 親ウィジェット
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
PlaybackControl::PlaybackControl( QWidget *parent )
    : PanelControlBase( parent ),
      m_list_view( this ),
      m_clicked_item( nullptr ),
      m_double_clicked( false ),
      m_double_click_stablize_timer( this ),
      m_grid_overlay( this ),
      m_row_delegate( &m_list_view ),
      m_marking_picker_popup()
{
    setFixedSize( PLC_SCREENSIZE );
    m_column_width = PLC_COLUMN_WIDTH;
    m_list_view.setGeometry( PLC_LIST_GEOMETRY.adjusted( 0, 36, 0, 0 ) );
    m_list_view.setObjectName( "playback_list" );

    m_list_view.setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    m_list_view.setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    m_list_view.setAlternatingRowColors( true );

    QStringList headers = {"", "キュー", "フェード", "ディレイ", "ウェイト", "リンク", "タイトル" };
    QRect cell( PLC_LIST_GEOMETRY.topLeft(), QSize( 0, 36 ) );

    for( int i = 0; i < m_column_width.length(); i++ )
    {
        cell.setWidth( m_column_width[i] );

        auto label = MakeSharedQObject<QLabel>( this );
        label->setGeometry( cell );
        label->setText( headers[i] );
        label->setObjectName( "playback_header" );

        m_headers.append( label );

        // 右に移動
        cell.moveLeft( cell.left() + cell.width() );
    }

    m_row_delegate.SetColumnsWidth( m_column_width );
    m_list_view.setItemDelegate( &m_row_delegate );

    m_grid_overlay.setGeometry( PLC_LIST_GEOMETRY );
    m_grid_overlay.SetColumnsWidth( m_column_width );
    m_grid_overlay.raise();

    // onItemDoubleClicked() イベントの前後に onItemClicked() が発生しないようにタイマーを使用する
    connect( &m_list_view, &QListWidget::itemClicked, this, [&]( QListWidgetItem * item )
    {
        if( !IsMouseInsideMarkingColumn() )
        {
            return;
        }

        if( m_double_click_stablize_timer.isActive() )
        {
            m_double_click_stablize_timer.stop();
            return;
        }

        m_double_click_stablize_timer.start();
        m_clicked_item = item;
        m_double_clicked = false;
    } );
    connect( &m_list_view, &QListWidget::itemDoubleClicked, this, [&]( QListWidgetItem * item )
    {
        if( !IsMouseInsideMarkingColumn() )
        {
            return;
        }

        // m_clicked_item = nullptr;
        m_double_clicked = true;
        OnItemDoubleClicked( item );
    } );
    connect( &m_double_click_stablize_timer, &QTimer::timeout, this, [&]()
    {
        if( m_double_clicked )
        {
            return;
        }

        OnItemClicked( m_clicked_item );
        // m_clicked_item = nullptr;
        m_double_clicked = false;
    } );
    connect( &m_marking_picker_popup, &MarkingPickerPopup::MarkingSelected, this, &PlaybackControl::OnMarkingSelected );

    m_double_click_stablize_timer.setTimerType( Qt::PreciseTimer );
    m_double_click_stablize_timer.setSingleShot( true );
    m_double_click_stablize_timer.setInterval( 200 );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetDispParamData
//  [ 機　能 ] : コントロールに表示パラメータデータを設定する
//  [ 引　数 ] : PLAYBACK_DISP_PARAM *param : the parameters
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PlaybackControl::SetDispParamData( PLAYBACK_DISP_PARAM *param )
{
    Q_ASSERT( param );
    m_double_clicked = false;
    m_clicked_item = nullptr;
    m_double_click_stablize_timer.stop();
    m_list_view.clear();

    for( int i = 0; i < param->count; ++i )
    {
        const auto &data = param->param[i];
        auto item = new QListWidgetItem( &m_list_view, QListWidgetItem::ItemType::Type );
        item->setData( PlaybackRowDelegate::Roles::SelectedRole, data.select );
        item->setData( PlaybackRowDelegate::Roles::MarkingColorRole, data.marking.color );
        item->setData( PlaybackRowDelegate::Roles::MarkingRole, QString::fromLocal8Bit( data.marking.marking ) );
        item->setData( PlaybackRowDelegate::Roles::QueueRole, QString::fromLocal8Bit( data.queue ) );
        item->setData( PlaybackRowDelegate::Roles::FadeRole,  QString::fromLocal8Bit( data.fade ) );
        item->setData( PlaybackRowDelegate::Roles::DelayRole, QString::fromLocal8Bit( data.delay ) );
        item->setData( PlaybackRowDelegate::Roles::WeightRole, QString::fromLocal8Bit( data.weight ) );
        item->setData( PlaybackRowDelegate::Roles::LinkRole,  QString::fromLocal8Bit( data.link ) );
        item->setData( PlaybackRowDelegate::Roles::TitleRole, QString::fromLocal8Bit( data.title ) );
        m_list_view.addItem( item );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : OnMarkingSelected
//  [ 機　能 ] : ユーザーがポップアップでマーキングを選択したときに発生する
//  [ 引　数 ] : const QString &marking : マーキング
//              const QColor &color : マーキングの色
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PlaybackControl::OnMarkingSelected( const QString &marking, const QColor &color )
{
    if( !m_clicked_item )
    {
        return;
    }

    m_clicked_item->setData( PlaybackRowDelegate::MarkingRole, marking );
    m_clicked_item->setData( PlaybackRowDelegate::MarkingColorRole, color );
    m_marking_picker_popup.hide();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : OnItemClicked
//  [ 機　能 ] : ユーザーが行をクリックしたときに発生する
//  [ 引　数 ] : QListWidgetItem *item : クリックされたアイテム
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PlaybackControl::OnItemClicked( QListWidgetItem *item )
{
    Q_ASSERT( item );
    item->setData( PlaybackRowDelegate::Roles::MarkingRole, "●" );
    item->setData( PlaybackRowDelegate::Roles::MarkingColorRole, QColor( Qt::lightGray ) );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : OnItemDoubleClicked
//  [ 機　能 ] : ユーザーが行をダブルクリックしたときに発生する
//  [ 引　数 ] : QListWidgetItem *item : クリックされたアイテム
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void PlaybackControl::OnItemDoubleClicked( QListWidgetItem *item )
{
    Q_ASSERT( item );

    m_marking_picker_popup.move( QCursor::pos() );
    m_marking_picker_popup.show();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : IsMouseInsideMarkingColumn
//  [ 機　能 ] : マウスがマーキング列内にあるかどうかを確認する
//  [ 引　数 ] : void
//  [ 戻り値 ] : bool : マウスがマーキング列内にある場合は true
//--------------------------------------------------------------------------
bool PlaybackControl::IsMouseInsideMarkingColumn() const
{
    int colSize = m_column_width[0];
    return m_list_view.mapFromGlobal( QCursor::pos() ).x() <= colSize;
}
