//--------------------------------------------------------------------------
// [ ファイル名 ] : libraryControl.cpp
// [ 概      要 ] : ライブラリコントロール垂直ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#include "libraryControl/libraryControl.h"
#include "libraryControl/libraryControl_define.h"
#include "utility.h"

#define BASE_BUTTON_WIDTH LC_FIRST_BUTTON_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT LC_FIRST_BUTTON_GEOMETRY.height()

LibraryControl::LibraryControl( QWidget *parent ) : PanelControlBase( parent ),
    m_grid( this ),
    m_title_label( this ),
    m_history_button( this ),
    m_up_button( this ),
    m_down_button( this ),
    m_return_button( this ),
    m_setting_label( this ),
    m_title_button( this ),
    m_empty_button( this ),
    m_register_button( this ),
    m_delete_button( this )
{
    setFixedSize( LC_SCREEN_SIZE );
    m_return_button.SetTextColor( Qt::yellow );

    m_mode_buttons_grid_size = QSize( 4, 2 );
    m_lib_buttons_grid_size = QSize( 4, 3 );

    SetLibraryStartPoint( LC_FIRST_BUTTON_GEOMETRY.topLeft() );
    SetModeStartPoint( LC_ALL_GEOMETRY.topLeft() );

    m_grid.SetGridSize( QSize( 4, 6 ) );
    m_grid.SetCellSize( QSize( BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT ) );
    m_grid.move( 0, 32 );

    m_title_label.setGeometry( LC_TITLE_GEOMETRY );
    m_title_label.setObjectName( "title_label" );
    m_title_label.setText( "ライブラリ" );

    m_history_button.setGeometry( LC_HISTORY_GEOMETRY );
    m_history_button.SetTextPixelSize( 14 );
    m_history_button.setText( "最近使った\nもの" );

    m_up_button.setGeometry( LC_UP_GEOMETRY );
    m_up_button.setText( "▲" );
    m_up_button.setVisible( false );

    m_down_button.setGeometry( LC_DOWN_GEOMETRY );
    m_down_button.setText( "▼" );
    m_down_button.setVisible( false );

    m_return_button.setGeometry( LC_RETURN_GEOMETRY );
    m_return_button.setText( "戻す" );

    m_setting_label.setGeometry( LC_SETTING_LABEL_GEOMETRY );
    m_setting_label.setText( "設定" );

    m_title_button.setGeometry( LC_TITLE_BUTTON_GEOMETRY );
    m_title_button.setText( "タイトル" );

    m_register_button.setGeometry( LC_REGISTER_GEOMETRY );
    m_register_button.setText( "登録" );

    m_delete_button.setGeometry( LC_DELETE_GEOMETRY );
    m_delete_button.setText( "削除" );

    m_empty_button.setGeometry( LC_EMPTY2_GEOMETRY );
    m_empty_button.setText( "" );
    m_empty_button.setEnabled( false );

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

    connect( &m_history_button, &QPushButton::toggled, this, [&]()
    {
        UpdateGroupTab();
        UpdateHistoryTab();

        if( m_history_button.isChecked() )
        {
            m_setting_label.setVisible( false );
            m_register_button.setVisible( false );
            m_title_button.setVisible( false );
            m_delete_button.setVisible( false );
            m_empty_button.setVisible( false );
            m_title_label.setText( "ライブラリ （最近使ったもの）" );
        }
        else
        {
            m_setting_label.setVisible( true );
            m_register_button.setVisible( true );
            m_title_button.setVisible( true );
            m_delete_button.setVisible( true );
            m_empty_button.setVisible( true );
            m_title_label.setText( "ライブラリ" );
        }
    } );

    connect( this, &LibraryControl::CurrentGroupPageChanged, this, &LibraryControl::UpdateGroupTab );
    connect( this, &LibraryControl::CurrentHistoryPageChanged, this, &LibraryControl::UpdateHistoryTab );

    connect( &m_title_button, &QPushButton::clicked, this, &LibraryControl::OnButtonTitleClicked );
    connect( &m_register_button, &QPushButton::clicked, this, &LibraryControl::OnButtonRegisterClicked );
    connect( &m_delete_button, &QPushButton::clicked, this, &LibraryControl::OnButtonDeleteClicked );
    connect( &m_return_button, &QPushButton::clicked, this, &LibraryControl::ReturnButtonClicked );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetDispParamData
//  [ 機　能   ] : コントロールに表示パラメータデータを設定する
//  [ 引　数   ] : LIBRARY_DISP_PARAM *param : the parameters
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void LibraryControl::SetDispParamData( LIBRARY_DISP_PARAM *param )
{
    Q_ASSERT( param );

    m_group_lib_buttons.clear();
    m_history_lib_buttons.clear();
    m_group_mode_buttons.clear();
    m_history_mode_buttons.clear();

    SetCurrentGroupPage( 0 );
    SetCurrentHistoryPage( 0 );

    SetSelectedGroupMode( QString() );
    SetSelectedHistoryMode( QString() );

    m_history_button.setChecked( false );

    QStringList group_modes, history_modes;
    group_modes.append( "ALL" );
    history_modes.append( "ALL" );

    LibraryControlButton current_library_button;
    LibraryControlButton current_history_button;

    // group lib buttons
    for( int i = 0; i < param->group.count; ++i )
    {
        const auto data = param->group.library_param[i];

        LibraryButton button;
        button.mode = data.mode;
        button.widget = MakeSharedQObject<TitleSelectButton>( this );
        button.widget->setVisible( false );
        button.widget->setFixedSize( LC_ALL_GEOMETRY.size() );
        button.widget->setText( data.library_no );
        button.widget->SetTitle( data.title );
        button.widget->setChecked( data.select );

        if( button.widget->isChecked() )
        {
            current_library_button.text = data.library_no;
            current_library_button.title = data.title;
        }

        connect( button.widget.get(), &TitleSelectButton::clicked, this, &LibraryControl::OnGroupLibButtonClicked );

        if( !group_modes.contains( data.mode ) )
        {
            group_modes.append( data.mode );
        }

        m_group_lib_buttons.append( button );
    }

    // history lib buttons
    for( int i = 0; i < param->history.count; ++i )
    {
        const auto data = param->history.library_param[i];

        LibraryButton button;
        button.mode = data.mode;
        button.widget = MakeSharedQObject<TitleSelectButton>( this );
        button.widget->setVisible( false );
        button.widget->setFixedSize( LC_ALL_GEOMETRY.size() );
        button.widget->setText( data.library_no );
        button.widget->SetTitle( data.title );
        button.widget->setChecked( data.select );

        if( button.widget->isChecked() )
        {
            current_library_button.text = data.library_no;
            current_library_button.title = data.title;
        }

        connect( button.widget.get(), &TitleSelectButton::clicked, this, &LibraryControl::OnHistoryLibButtonClicked );

        if( !history_modes.contains( data.mode ) )
        {
            history_modes.append( data.mode );
        }

        m_history_lib_buttons.append( button );
    }

    // group modes
    for( const auto &mode : group_modes )
    {
        auto button = MakeSharedQObject<SelectButton>( this );
        button->setFixedSize( LC_ALL_GEOMETRY.size() );
        button->setText( mode );
        button->setVisible( false );
        button->setChecked( mode == "ALL" );

        connect( button.get(), &SelectButton::clicked, this, &LibraryControl::OnGroupModeButtonClicked );
        m_group_mode_buttons.append( button );
    }

    // history modes
    for( const auto &mode : history_modes )
    {
        auto button = MakeSharedQObject<SelectButton>( this );
        button->setFixedSize( LC_ALL_GEOMETRY.size() );
        button->setText( mode );
        button->setVisible( false );
        button->setChecked( mode == "ALL" );

        connect( button.get(), &SelectButton::clicked, this, &LibraryControl::OnHistoryModeButtonClicked );
        m_history_mode_buttons.append( button );
    }

    RefilterGroupButtonsByMode();
    RefilterHistoryButtonsByMode();

    SetSelectedModeButton( "ALL" );
    SetSelectedHistoryModeButton( "ALL" );
    SetSelectedLibraryButton( current_library_button );
    SetSelectedHistoryButton( current_history_button );
    UpdateGroupTab();
    UpdateHistoryTab();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : AddButtonToHistory
//  [ 機　能   ] : 最近使ったものページにボタンを追加する
//  [ 引　数   ] : const LibraryControl::LibraryButton &button: 要追加のボタン
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void LibraryControl::AddButtonToHistory( const LibraryControl::LibraryButton &button )
{
    const auto mode = button.mode;

    auto widget = MakeSharedQObject<TitleSelectButton>( this );
    widget->setText( button.widget->text() );
    widget->SetCheckMarkVisible( true );
    widget->setFixedSize( LC_FIRST_BUTTON_GEOMETRY.size() );
    widget->setVisible( false );
    widget->SetBackgroundColor( button.widget->BackgroundColor() );
    widget->SetSelectedBackgroundColor( button.widget->BackgroundColor() );
    widget->SetTitle( button.widget->Title() );

    auto iter = std::find_if( m_history_mode_buttons.begin(), m_history_mode_buttons.end(), [mode]( const QSharedPointer<SelectButton> &b )
    {
        return b->text() == mode;
    } );

    // Add new mode if missing
    if( iter == m_history_mode_buttons.end() )
    {
        auto new_mode_button = MakeSharedQObject<SelectButton>( this );
        new_mode_button->setFixedSize( LC_ALL_GEOMETRY.size() );
        new_mode_button->setText( mode );
        new_mode_button->setVisible( false );

        connect( new_mode_button.get(), &SelectButton::clicked, this, &LibraryControl::OnHistoryModeButtonClicked );
        m_history_mode_buttons.append( new_mode_button );
    }

    connect( widget.get(), &TitleSelectButton::clicked, this, &LibraryControl::OnHistoryLibButtonClicked );

    m_history_lib_buttons.push_front( LibraryControl::LibraryButton{ mode, widget } );
    RefilterHistoryButtonsByMode();
    UpdateHistoryTab();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : OnButtonTitleClicked
//  [ 機　能   ] : タイトルボタンを処理するイベント
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void LibraryControl::OnButtonTitleClicked()
{
    m_register_button.setChecked( false );
    m_delete_button.setChecked( false );
    SetSelectedFooterButton( ( ( SelectButton * )sender() )->text() );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : OnButtonRegisterClicked
//  [ 機　能   ] : 登録ボタンを処理するイベント
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void LibraryControl::OnButtonRegisterClicked()
{
    m_title_button.setChecked( false );
    m_delete_button.setChecked( false );
    SetSelectedFooterButton( ( ( SelectButton * )sender() )->text() );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : OnButtonDeleteClicked
//  [ 機　能   ] : 削除ボタンを処理するイベント
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void LibraryControl::OnButtonDeleteClicked()
{
    m_register_button.setChecked( false );
    m_title_button.setChecked( false );
    SetSelectedFooterButton( ( ( SelectButton * )sender() )->text() );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : OnGroupModeButtonClicked
//  [ 機　能   ] : グループモードボタンを処理するイベント
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void LibraryControl::OnGroupModeButtonClicked()
{
    const auto modeButton = ( ( SelectButton * )sender() );

    for( const auto &b : qAsConst( m_group_mode_buttons ) )
    {
        b->setChecked( b == modeButton );
    }

    SetSelectedModeButton( ( ( SelectButton * )sender() )->text() );
    const auto mode = modeButton->text();

    if( mode == "ALL" )
    {
        SetSelectedGroupMode( QString() );
    }
    else
    {
        SetSelectedGroupMode( mode );
    }

    SetCurrentGroupPage( 0 );
    RefilterGroupButtonsByMode();

    UpdateGroupTab();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : OnHistoryModeButtonClicked
//  [ 機　能   ] : 最近使ったもののモードボタンを処理するイベント
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void LibraryControl::OnHistoryModeButtonClicked()
{
    const auto modeButton = ( ( SelectButton * )sender() );

    for( const auto &b : qAsConst( m_history_mode_buttons ) )
    {
        b->setChecked( b == modeButton );
    }

    SetSelectedHistoryModeButton( ( ( SelectButton * )sender() )->text() );
    const auto mode = modeButton->text();

    if( mode == "ALL" )
    {
        SetSelectedHistoryMode( QString() );
    }
    else
    {
        SetSelectedHistoryMode( mode );
    }

    SetCurrentHistoryPage( 0 );
    RefilterHistoryButtonsByMode();

    UpdateHistoryTab();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : OnGroupLibButtonClicked
//  [ 機　能   ] : グループライブラリボタンを処理するイベント
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void LibraryControl::OnGroupLibButtonClicked()
{
    const auto lib_button = ( ( TitleSelectButton * )sender() );

    for( const auto &b : qAsConst( m_group_lib_buttons ) )
    {
        if( b.widget == lib_button )
        {
            AddButtonToHistory( b );
            SetSelectedLibraryButton( {lib_button->text(), lib_button->Title()} );
            b.widget->setChecked( true );
        }
        else
        {
            b.widget->setChecked( false );
        }
    }
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : OnHistoryLibButtonClicked
//  [ 機　能   ] : グループの最近使ったもののボタンを処理するイベント
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void LibraryControl::OnHistoryLibButtonClicked()
{
    const auto lib_button = ( ( TitleSelectButton * )sender() );
    SetSelectedHistoryButton( {lib_button->text(), lib_button->Title()} );

    for( const auto &b : qAsConst( m_history_lib_buttons ) )
    {
        b.widget->setChecked( b.widget == lib_button );
    }
}

QPoint LibraryControl::ModeStartPoint() const
{
    return m_mode_start_point;
}

void LibraryControl::SetModeStartPoint( QPoint point )
{
    m_mode_start_point = point;
}

int LibraryControl::MaxGroupPages() const
{
    return CalulateNumberOfPages( m_current_group_lib_buttons.size(), LibraryButtonsPerPage() );
}

int LibraryControl::MaxHistoryPages() const
{
    return CalulateNumberOfPages( m_current_history_lib_buttons.size(), LibraryButtonsPerPage() );
}

int LibraryControl::ModeButtonsPerPage() const
{
    return m_mode_buttons_grid_size.width() * m_mode_buttons_grid_size.height();
}

int LibraryControl::LibraryButtonsPerPage() const
{
    return m_lib_buttons_grid_size.width() * m_lib_buttons_grid_size.height();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : RefilterGroupButtonsByMode
//  [ 機　能   ] : グループボタンをモードでフィルターする
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void LibraryControl::RefilterGroupButtonsByMode()
{
    m_current_group_lib_buttons = WidgetList( Filter( m_group_lib_buttons, SelectedGroupMode() ) );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : RefilterHistoryButtonsByMode
//  [ 機　能   ] : 最近使ったもののボタンをモードでフィルターする
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void LibraryControl::RefilterHistoryButtonsByMode()
{
    m_current_history_lib_buttons = WidgetList( Filter( m_history_lib_buttons, SelectedHistoryMode() ) );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : Filter
//  [ 機　能   ] : ボタンリストをモードで取得する
//  [ 引　数   ] : const QVector<LibraryControl::LibraryButton> &buttons: 全ボタン
//               const QString &mode: モードボタン
//  [ 戻り値    ] : QVector<LibraryControl::LibraryButton>: モードリストボタン
//--------------------------------------------------------------------------
QVector<LibraryControl::LibraryButton> LibraryControl::Filter( const QVector<LibraryControl::LibraryButton> &buttons, const QString &mode )
{
    if( mode.isEmpty() )
    {
        return buttons;
    }

    QVector<LibraryControl::LibraryButton> result;
    std::copy_if( buttons.begin(), buttons.end(), std::back_inserter( result ), [mode]( const LibraryControl::LibraryButton & b )
    {
        return b.mode == mode;
    } );
    return result;
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : WidgetList
//  [ 機　能   ] : ウィジェッボタントリストの取得
//  [ 引　数   ] : const QVector<LibraryButton> &buttons: 全ボタン
//  [ 戻り値    ] : QVector<QSharedPointer<TitleSelectButton> >: ウィジェッボタントリスト
//--------------------------------------------------------------------------
QVector<QSharedPointer<TitleSelectButton> > LibraryControl::WidgetList( const QVector<LibraryButton> &buttons )
{
    QVector<QSharedPointer<TitleSelectButton>> result;

    for( const auto &b : buttons )
    {
        result.append( b.widget );
    }

    return result;
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : UpdateGroupTab
//  [ 機　能   ] : 現在のグループボタンのジオメトリの可視性を更新する
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void LibraryControl::UpdateGroupTab()
{
    for( const auto &b : qAsConst( m_group_mode_buttons ) )
    {
        b->setVisible( !m_history_button.isChecked() );
    }

    for( const auto &b : qAsConst( m_group_lib_buttons ) )
    {
        b.widget->setVisible( false );
    }

    PlaceChildrenIntoPanel( m_group_mode_buttons, LC_ALL_GEOMETRY.size(), ModeStartPoint(), m_mode_buttons_grid_size );
    PlaceChildrenIntoPanel( m_current_group_lib_buttons, LC_ALL_GEOMETRY.size(), LibraryStartPoint(), m_lib_buttons_grid_size );

    if( !m_history_button.isChecked() )
    {
        UpdateChildrenVisibility( m_current_group_lib_buttons, CurrentGroupPage(), LibraryButtonsPerPage() );
        m_up_button.setVisible( MaxGroupPages() > 1 );
        m_down_button.setVisible( MaxGroupPages() > 1 );
        m_up_button.setEnabled( CurrentGroupPage() > 0 );
        m_down_button.setEnabled( CurrentGroupPage() < MaxGroupPages() - 1 );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : UpdateHistoryTab
//  [ 機　能   ] : 現在の最近使ったもののグループボタンのジオメトリの可視性を更新する
//  [ 引　数   ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void LibraryControl::UpdateHistoryTab()
{
    for( const auto &b : qAsConst( m_history_mode_buttons ) )
    {
        b->setVisible( m_history_button.isChecked() );
    }

    for( const auto &b : qAsConst( m_history_lib_buttons ) )
    {
        b.widget->setVisible( false );
    }

    PlaceChildrenIntoPanel( m_history_mode_buttons, LC_ALL_GEOMETRY.size(), ModeStartPoint(), m_mode_buttons_grid_size );
    PlaceChildrenIntoPanel( m_current_history_lib_buttons, LC_ALL_GEOMETRY.size(), LibraryStartPoint(), m_lib_buttons_grid_size );

    if( m_history_button.isChecked() )
    {
        UpdateChildrenVisibility( m_current_history_lib_buttons, CurrentHistoryPage(), LibraryButtonsPerPage() );
        m_up_button.setVisible( MaxHistoryPages() > 1 );
        m_down_button.setVisible( MaxHistoryPages() > 1 );
        m_up_button.setEnabled( CurrentHistoryPage() > 0 );
        m_down_button.setEnabled( CurrentHistoryPage() < MaxHistoryPages() - 1 );
    }
}

QPoint LibraryControl::LibraryStartPoint() const
{
    return m_library_start_point;
}

void LibraryControl::SetLibraryStartPoint( QPoint point )
{
    m_library_start_point = point;
}


int LibraryControl::CurrentGroupPage() const
{
    return m_current_group_page;
}

void LibraryControl::SetCurrentGroupPage( int page )
{
    page = qBound( 0, page, MaxGroupPages() );

    if( m_current_group_page == page )
    {
        return;
    }

    m_current_group_page = page;
    emit CurrentGroupPageChanged();
}

int LibraryControl::CurrentHistoryPage() const
{
    return m_current_history_page;
}

void LibraryControl::SetCurrentHistoryPage( int page )
{
    page = qBound( 0, page, MaxHistoryPages() );

    if( m_current_history_page == page )
    {
        return;
    }

    m_current_history_page = page;
    emit CurrentHistoryPageChanged();
}

QString LibraryControl::SelectedGroupMode() const
{
    return m_selected_group_mode;
}

void LibraryControl::SetSelectedGroupMode( const QString &mode )
{
    if( m_selected_group_mode == mode )
    {
        return;
    }

    m_selected_group_mode = mode;
    emit SelectedGroupModeChanged();
}

QString LibraryControl::SelectedHistoryMode() const
{
    return m_selected_history_mode;
}

void LibraryControl::SetSelectedHistoryMode( const QString &mode )
{
    if( m_selected_history_mode == mode )
    {
        return;
    }

    m_selected_history_mode = mode;
    emit SelectedHistoryModeChanged();
}


const LibraryControlButton &LibraryControl::SelectedLibraryButton() const
{
    return m_selected_library_button;
}

void LibraryControl::SetSelectedLibraryButton( const LibraryControlButton &button )
{
    if( m_selected_library_button == button )
    {
        return;
    }

    m_selected_library_button = button;
    emit SelectedLibraryButtonChanged();
}

const LibraryControlButton &LibraryControl::SelectedHistoryButton() const
{
    return m_selected_historybutton;
}

void LibraryControl::SetSelectedHistoryButton( const LibraryControlButton &button )
{
    if( m_selected_historybutton == button )
    {
        return;
    }

    m_selected_historybutton = button;
    emit SelectedHistoryButtonChanged();
}

const QString &LibraryControl::SelectedFooterButton() const
{
    return m_selected_footer_button;
}

void LibraryControl::SetSelectedFooterButton( const QString &button )
{
    if( m_selected_footer_button == button )
    {
        return;
    }

    m_selected_footer_button = button;
    emit SelectedFooterButtonChanged();
}

const QString &LibraryControl::SelectedModeButton() const
{
    return m_selected_mode_button;
}

void LibraryControl::SetSelectedModeButton( const QString &button )
{
    if( m_selected_mode_button == button )
    {
        return;
    }

    m_selected_mode_button = button;
    emit SelectedModeButtonChanged();
}

const QString &LibraryControl::SelectedHistoryModeButton() const
{
    return m_selected_history_mode_button;
}

void LibraryControl::SetSelectedHistoryModeButton( const QString &button )
{
    if( m_selected_history_mode_button == button )
    {
        return;
    }

    m_selected_history_mode_button = button;
    emit SelectedHistoryModeButtonChanged();
}
