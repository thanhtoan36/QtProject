//--------------------------------------------------------------------------
// [ ファイル名 ] : groupControl.cpp
// [ 概      要 ] : グループコントロール垂直ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#include "groupControl/groupControl.h"
#include "groupControl/groupControl_define.h"
#include "utility.h"

//--------------------------------------------------------------------------
//  [ 関数名   ] : GroupControl
//  [ 機能名   ] : グループコントロールのコンストラクター
//  [ 引数     ] : QWidget *parent: 親ウィジェット
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
GroupControl::GroupControl( QWidget *parent ) : PanelControlBase( parent ),
    m_grid( this ),
    m_title_label( this ),
    m_history_button( this ),
    m_up_button( this ),
    m_down_button( this ),
    m_back_button( this ),
    m_setting_label( this ),
    m_title_button( this ),
    m_empty_button( this ),
    m_register_button( this ),
    m_delete_button( this ),
    m_current_group_page( 0 ),
    m_current_history_page( 0 )
{
    m_buttons_grid_size = QSize( 4, 5 );

    setFixedSize( GC_SCREEN_SIZE );
    m_back_button.SetTextColor( Qt::yellow );
    m_title_label.setObjectName( "title_label" );

    m_grid.SetGridSize( QSize( 4, 6 ) );
    m_grid.SetCellSize( GC_FIRST_BUTTON_GEOMETRY.size() );
    m_grid.move( 0, 32 );

    m_title_label.setGeometry( GC_TITLE_GEOMETRY );
    m_title_label.setText( "グループ" );

    m_history_button.setGeometry( GC_HISTORY_GEOMETRY );
    m_history_button.SetTextPixelSize( 14 );
    m_history_button.setText( "最近使った\nもの" );

    m_up_button.setGeometry( GC_UP_GEOMETRY );
    m_up_button.setText( "▲" );
    m_up_button.setVisible( false );

    m_down_button.setGeometry( GC_DOWN_GEOMETRY );
    m_down_button.setText( "▼" );
    m_down_button.setVisible( false );

    m_back_button.setGeometry( GC_RETURN_GEOMETRY );
    m_back_button.setText( "戻す" );

    m_setting_label.setGeometry( GC_SETTING_GEOMETRY );
    m_setting_label.setText( "設定" );

    m_title_button.setGeometry( GC_TITLE_BUTTON_GEOMETRY );
    m_title_button.setText( "タイトル" );

    m_empty_button.setGeometry( GC_EMPTY_GEOMETRY );
    m_empty_button.setText( "" );

    m_register_button.setGeometry( GC_REGISTER_BUTTON_GEOMETRY );
    m_register_button.setText( "登録" );

    m_delete_button.setGeometry( GC_DELETE_BUTTON_GEOMETRY );
    m_delete_button.setText( "削除" );

    connect( &m_up_button, &QPushButton::clicked, this, [&]()
    {
        if( m_history_button.isChecked() )
        {
            SetCurrentHistoryPage( CurrentHistoryPage() - 1 );
        }
        else
        {
            SetCurrentGroupPage( CurrentGroupPage() - 1 );
        }
    } );
    connect( &m_down_button, &QPushButton::clicked, this, [&]()
    {
        if( m_history_button.isChecked() )
        {
            SetCurrentHistoryPage( CurrentHistoryPage() + 1 );
        }
        else
        {
            SetCurrentGroupPage( CurrentGroupPage() + 1 );
        }
    } );

    connect( this, &GroupControl::CurrentGroupPageChanged, this, [&]()
    {
        UpdateGroupPage();
        m_up_button.setEnabled( CurrentGroupPage() > 0 );
        m_down_button.setEnabled( CurrentGroupPage() < MaxGroupPages() - 1 );
    } );
    connect( this, &GroupControl::CurrentHistoryPageChanged, this, [&]()
    {
        UpdateHistoryPage();
        m_up_button.setEnabled( CurrentHistoryPage() > 0 );
        m_down_button.setEnabled( CurrentHistoryPage() < MaxHistoryPages() - 1 );
    } );

    connect( &m_history_button, &QAbstractButton::toggled, this, [&]()
    {
        if( m_history_button.isChecked() )
        {
            for( auto &btn : m_group_buttons )
            {
                btn->setVisible( false );
            }

            UpdateHistoryPage();
            m_up_button.setVisible( MaxHistoryPages() > 1 );
            m_down_button.setVisible( MaxHistoryPages() > 1 );
            m_up_button.setEnabled( CurrentHistoryPage() > 0 );
            m_down_button.setEnabled( CurrentHistoryPage() < MaxHistoryPages() - 1 );
            m_title_label.setText( "グループ (最近使ったもの)" );
            m_title_button.setVisible( false );
            m_register_button.setVisible( false );
            m_delete_button.setVisible( false );
            m_empty_button.setVisible( false );
            m_setting_label.setVisible( false );
        }
        else
        {
            for( auto &btn : m_history_buttons )
            {
                btn->setVisible( false );
            }

            UpdateGroupPage();
            m_up_button.setVisible( MaxGroupPages() > 1 );
            m_down_button.setVisible( MaxGroupPages() > 1 );
            m_up_button.setEnabled( CurrentGroupPage() > 0 );
            m_down_button.setEnabled( CurrentGroupPage() < MaxGroupPages() - 1 );
            m_title_label.setText( "グループ" );
            m_title_button.setVisible( true );
            m_register_button.setVisible( true );
            m_delete_button.setVisible( true );
            m_setting_label.setVisible( true );
            m_empty_button.setVisible( true );
        }
    } );

    connect( &m_title_button, &QAbstractButton::toggled, this, &GroupControl::OnTitleButonClicked );
    connect( &m_register_button, &QAbstractButton::toggled, this, &GroupControl::OnRegisterButonClicked );
    connect( &m_delete_button, &QAbstractButton::toggled, this, &GroupControl::OnDeleteButonClicked );
    connect( &m_back_button, &QAbstractButton::clicked, this, &GroupControl::ReturnButtonClicked );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetDispParamData
//  [ 機　能   ] : コントロールに表示パラメータデータを設定する
//  [ 引　数   ] : GROUP_DISP_PARAM *param : the parameters
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControl::SetDispParamData( GROUP_DISP_PARAM *param )
{
    Q_ASSERT( param );
    m_group_buttons.clear();
    m_history_buttons.clear();

    SetCurrentGroupPage( 0 );
    SetCurrentHistoryPage( 0 );
    GroupControlButton current_group_button;
    GroupControlButton current_history_button;

    for( int i = 0; i < param->group.count; i++ )
    {
        auto button =  MakeSharedQObject<TitleSelectButton>( this );
        button->setFixedSize( GC_FIRST_BUTTON_GEOMETRY.size() );
        button->SetTitle( param->group.group_param[i].title );
        button->setText( param->group.group_param[i].group_no );
        button->setChecked( param->group.group_param[i].select );

        if( button->isChecked() )
        {
            current_group_button.text = button->text();
            current_group_button.title = button->Title();
        }

        connect( button.get(), &QAbstractButton::clicked, this, &GroupControl::OnGroupButtonClicked );
        m_group_buttons.push_back( button );
    }

    PlaceChildrenIntoPanel( m_group_buttons, GC_FIRST_BUTTON_GEOMETRY.size(), GC_FIRST_BUTTON_GEOMETRY.topLeft(), m_buttons_grid_size );
    UpdateGroupPage();

    m_up_button.setEnabled( CurrentGroupPage() > 0 );
    m_down_button.setEnabled( CurrentGroupPage() < MaxGroupPages() - 1 );

    for( int i = 0; i < param->history.count; i++ )
    {
        auto button =  MakeSharedQObject<TitleSelectButton>( this );
        button->setFixedSize( GC_FIRST_BUTTON_GEOMETRY.size() );
        button->SetTitle( param->history.group_param[i].title );
        button->setText( param->history.group_param[i].group_no );
        button->setChecked( param->history.group_param[i].select );
        button->setVisible( false );

        if( button->isChecked() )
        {
            current_history_button.text = button->text();
            current_history_button.title = button->Title();
        }

        connect( button.get(), &QAbstractButton::clicked, this, &GroupControl::OnHistoryButtonClicked );
        m_history_buttons.push_back( button );
    }

    PlaceChildrenIntoPanel( m_history_buttons, GC_FIRST_BUTTON_GEOMETRY.size(), GC_FIRST_BUTTON_GEOMETRY.topLeft(), m_buttons_grid_size );
    m_history_button.setChecked( false );

    m_up_button.setVisible( MaxGroupPages() > 1 );
    m_down_button.setVisible( MaxGroupPages() > 1 );
    SetCurrentGroupButton( current_group_button );
    SetCurrentHistoryButton( current_history_button );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : CurrentGroupPage
//  [ 機能名   ] : 現在のグループページを取得する
//  [ 引数     ] : void
//  [ 戻り値    ] : int: ページのインデックス
//--------------------------------------------------------------------------
int GroupControl::CurrentGroupPage() const
{
    return m_current_group_page;
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetCurrentGroupPage
//  [ 機能名   ] : 現在のグループ ージを設定する
//  [ 引数     ] : int page: 要設定のページ
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControl::SetCurrentGroupPage( int page )
{
    page = qBound( 0, page, MaxGroupPages() - 1 );

    if( m_current_group_page == page )
    {
        return;
    }

    m_current_group_page = page;
    emit CurrentGroupPageChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : CurrentHistoryPage
//  [ 機能名   ] : 現在の最近使ったもののページを取得する
//  [ 引数     ] : void
//  [ 戻り値    ] : int: ページのインデックス
//--------------------------------------------------------------------------
int GroupControl::CurrentHistoryPage() const
{
    return m_current_history_page;
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetCurrentHistoryPage
//  [ 機能名   ] : 現在の最近使ったもののページを設定する
//  [ 引数     ] : int page: 要設定のページ
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControl::SetCurrentHistoryPage( int page )
{
    page = qBound( 0, page, MaxHistoryPages() - 1 );

    if( m_current_history_page == page )
    {
        return;
    }

    m_current_history_page = page;
    emit CurrentHistoryPageChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : UpdateGroupPage
//  [ 機　能   ] : グループページの可視性を更新する·
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControl::UpdateGroupPage()
{
    UpdateChildrenVisibility( m_group_buttons, CurrentGroupPage(), ButtonsPerPage() );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : UpdateHistoryPage
//  [ 機　能   ] : 最近使ったものページの可視性を更新
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControl::UpdateHistoryPage()
{
    UpdateChildrenVisibility( m_history_buttons, CurrentHistoryPage(), ButtonsPerPage() );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : MaxGroupPages
//  [ 機能名   ] : グループページの最大数を取得する
//  [ 引数     ] : void
//  [ 戻り値    ] : int: ページ数
//--------------------------------------------------------------------------
int GroupControl::MaxGroupPages() const
{
    return CalulateNumberOfPages( m_group_buttons.length(), ButtonsPerPage() );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : MaxHistoryPages
//  [ 機能名   ] : 最近使ったもののページの最大数を取得する
//  [ 引数     ] : void
//  [ 戻り値    ] : int: ページ数
//--------------------------------------------------------------------------
int GroupControl::MaxHistoryPages() const
{
    return CalulateNumberOfPages( m_history_buttons.length(), ButtonsPerPage() );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : AddButtonToHistory
//  [ 機　能   ] : 最近使ったものページにボタンを追加する
//  [ 引　数   ] : QSharedPointer<TitleSelectButton> &button: 要追加のボタン
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControl::AddButtonToHistory( QSharedPointer<TitleSelectButton> &button )
{
    auto new_button = MakeSharedQObject<TitleSelectButton>( this );
    new_button->setText( button->text() );
    new_button->SetCheckMarkVisible( true );
    new_button->setFixedSize( GC_FIRST_BUTTON_GEOMETRY.size() );
    new_button->setVisible( false );
    new_button->SetBackgroundColor( button->BackgroundColor() );
    new_button->SetSelectedBackgroundColor( button->BackgroundColor() );
    new_button->SetTitle( button->Title() );

    connect( new_button.get(), &QAbstractButton::clicked, this, &GroupControl::OnHistoryButtonClicked );
    m_history_buttons.push_front( new_button );

    PlaceChildrenIntoPanel( m_history_buttons, GC_FIRST_BUTTON_GEOMETRY.size(), GC_FIRST_BUTTON_GEOMETRY.topLeft(), m_buttons_grid_size );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : OnGroupButtonClicked
//  [ 機　能   ] : グループボタンを処理するイベント
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControl::OnGroupButtonClicked()
{
    auto iter = std::find( m_group_buttons.begin(), m_group_buttons.end(), sender() );

    if( iter == m_group_buttons.end() )
    {
        return;
    }

    auto button = *iter;
    AddButtonToHistory( button );
    SetCurrentGroupButton( {button->text(), button->Title()} );

    for( const auto &b : qAsConst( m_group_buttons ) )
    {
        b->setChecked( b == button );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : OnHistoryButtonClicked
//  [ 関数名   ] : 最近使ったもののボタンを処理するイベント
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControl::OnHistoryButtonClicked()
{
    auto iter = std::find( m_history_buttons.begin(), m_history_buttons.end(), sender() );

    if( iter == m_history_buttons.end() )
    {
        return;
    }

    auto button = *iter;
    SetCurrentHistoryButton( {button->text(), button->Title()} );

    for( const auto &b : qAsConst( m_history_buttons ) )
    {
        b->setChecked( b == button );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : OnTitleButonClicked
//  [ 機　能   ] : タイトルボタンを処理するイベント
//  [ 引　数   ] : const bool check: ボタンのステータスをチェックする
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControl::OnTitleButonClicked( const bool check )
{
    if( check )
    {
        m_delete_button.setChecked( false );
        m_register_button.setChecked( false );
        SetCurrentFooterButton( m_title_button.text() );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : OnRegisterButonClicked
//  [ 機　能   ] : 登録ボタンを処理するイベント
//  [ 引　数   ] : const bool check: ボタンのステータスをチェックする
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControl::OnRegisterButonClicked( const bool check )
{
    if( check )
    {
        m_delete_button.setChecked( false );
        m_title_button.setChecked( false );
        SetCurrentFooterButton( m_register_button.text() );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : OnDeleteButonClicked
//  [ 機　能   ] : 削除ボタンを処理するイベント
//  [ 引　数   ] : const bool check: check status of button
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControl::OnDeleteButonClicked( const bool check )
{
    if( check )
    {
        m_title_button.setChecked( false );
        m_register_button.setChecked( false );
        SetCurrentFooterButton( m_delete_button.text() );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : ButtonsPerPage
//  [ 機能名   ] : ページごとに数字ボタンを取得する
//  [ 引数     ] : void
//  [ 戻り値    ] : int: ボタン数
//--------------------------------------------------------------------------
int GroupControl::ButtonsPerPage() const
{
    return m_buttons_grid_size.width() * m_buttons_grid_size.height();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : CurrentGroupButton
//  [ 機能名   ] : 現在のグループボタンを取得する
//  [ 引数     ] : void
//  [ 戻り値    ] : GroupControlButton: ボタンのテキストとタイトル
//--------------------------------------------------------------------------
const GroupControlButton &GroupControl::CurrentGroupButton() const
{
    return m_current_group_button;
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetCurrentGroupButton
//  [ 機能名   ] : 現在のグループボタンを設定する
//  [ 引数     ] : const GroupControlButton &button: 要設定のボタンのテキストとタイトル
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControl::SetCurrentGroupButton( const GroupControlButton &button )
{
    if( m_current_group_button == button )
    {
        return;
    }

    m_current_group_button = button;
    emit CurrentGroupButtonChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : CurrentHistoryButton
//  [ 機能名   ] : 現在の最近使ったもののボタンを取得する
//  [ 引数     ] : void
//  [ 戻り値    ] : GroupControlButton: ボタンのテキストとタイトル
//--------------------------------------------------------------------------
const GroupControlButton &GroupControl::CurrentHistoryButton() const
{
    return m_current_history_button;
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetCurrentHistoryButton
//  [ 機能名   ] : 現在の最近使ったもののボタンを設定する
//  [ 引数     ] : const GroupControlButton &button: 要設定のボタンのテキストとタイトル
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControl::SetCurrentHistoryButton( const GroupControlButton &button )
{
    if( m_current_history_button == button )
    {
        return;
    }

    m_current_history_button = button;
    emit CurrentHistoryButtonChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : CurrentFooterButton
//  [ 機能名   ] : 現在のフッターボタンを取得する
//  [ 引数     ] : void
//  [ 戻り値    ] : QString: ボタンのテキスト
//--------------------------------------------------------------------------
const QString &GroupControl::CurrentFooterButton() const
{
    return m_current_footer_button;
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetCurrentFooterButton
//  [ 機能名   ] : 現在のフッターボタンを設定する
//  [ 引数     ] : QString &button: 要設定のボタンのテキスト
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void GroupControl::SetCurrentFooterButton( const QString &button )
{
    if( m_current_footer_button == button )
    {
        return;
    }

    m_current_footer_button = button;
    emit CurrentFooterButtonChanged();
}
