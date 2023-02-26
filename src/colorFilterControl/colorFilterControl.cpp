//--------------------------------------------------------------------------
// [ ファイル名 ] : colorFilterControl.cpp
// [ 概      要 ] : カラーフィルターコントロール垂直ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#include "colorFilterControl/colorFilterControl.h"
#include "colorFilterControl/colorFilterControl_define.h"
#include <QFont>
#include <math.h>
#include "utility.h"


#define BUTTONS_GRID_SIZE QSize(4, 4)
#define BUTTONS_PER_PAGE (BUTTONS_GRID_SIZE.width() * BUTTONS_GRID_SIZE.height())

#define BASE_BUTTON_X CFC_FIRST_BUTTON_GEOMETRY.x()
#define BASE_BUTTON_Y CFC_FIRST_BUTTON_GEOMETRY.y()

#define BASE_BUTTON_WIDTH CFC_FIRST_BUTTON_GEOMETRY.width()
#define BASE_BUTTON_HEIGHT CFC_FIRST_BUTTON_GEOMETRY.height()

ColorFilterControl::ColorFilterControl( QWidget *parent ) : PanelControlBase( parent ),
    m_grid( this ),
    m_title_label( this ),
    m_button_next_header_buttons_page( this ),
    m_button_previous_header_buttons_page( this ),
    m_history_button( this ),
    m_button_next_filter_buttons_page( this ),
    m_button_previous_filter_buttons_page( this ),
    m_back_button( this ),
    m_setting_label( this ),
    m_title_button( this ),
    m_empty_button( this ),
    m_register_button( this ),
    m_delete_button( this ),
    m_children_tb_tab{},
    m_children_custom_tab{&m_setting_label, &m_title_button, &m_empty_button, &m_register_button, &m_delete_button},
    m_mode( COLOR_FILTER_MODE_TB ),
    m_previous_tab( COLOR_FILTER_MODE_TB )
{
    m_header_buttons_per_page = 2;

    setFixedSize( CFC_SCREENSIZE );
    SetCurrentTBTabPage( 0 );
    SetCurrentCustomTabPage( 0 );
    SetCurrentHistoryPage( 0 );
    SetCurrentHeaderButtonsPage( 0 );

    m_button_next_filter_buttons_page.setEnabled( false );
    m_back_button.SetTextColor( Qt::yellow );

    m_grid.SetGridSize( QSize( 6, 6 ) );
    m_grid.SetCellSize( QSize( BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT ) );
    m_grid.move( 0, 32 );

    m_title_label.setGeometry( CFC_TITLE_GEOMETRY );
    m_title_label.setText( "カラーフィルタ" );
    m_title_label.setObjectName( "title_label" );

    m_button_next_header_buttons_page.setGeometry( CFC_NEXT_BUTTON_GEOMETRY );
    m_button_next_header_buttons_page.setText( "▶" );
    m_button_next_header_buttons_page.setVisible( false );

    m_button_previous_header_buttons_page.setGeometry( CFC_PREVIOUS_BUTTON_GEOMETRY );
    m_button_previous_header_buttons_page.setText( "◀" );
    m_button_previous_header_buttons_page.setVisible( false );

    m_history_button.setGeometry( CFC_HISTORY_GEOMETRY );
    m_history_button.setText( "最近使った\nもの" );

    m_button_next_filter_buttons_page.setGeometry( CFC_UP_BUTTON_GEOMETRY );
    m_button_next_filter_buttons_page.setText( "▲" );

    m_button_previous_filter_buttons_page.setGeometry( CFC_DOWN_BUTTON_GEOMETRY );
    m_button_previous_filter_buttons_page.setText( "▼" );

    m_title_button.setGeometry( CFC_TITLE_BUTTON_GEOMETRY );
    m_title_button.setText( "タイトル" );

    m_empty_button.setGeometry( CFC_EMPTY_GEOMETRY );
    m_empty_button.setText( "" );

    m_register_button.setGeometry( CFC_REGISTER_GEOMETRY );
    m_register_button.setText( "登録" );

    m_delete_button.setGeometry( CFC_DELETE_GEOMETRY );
    m_delete_button.setText( "削除" );

    m_back_button.setGeometry( CFC_BACK_BUTTON_GEOMETRY );
    m_back_button.setText( "戻す" );

    m_setting_label.setGeometry( CFC_SETTING_GEOMETRY );
    m_setting_label.setText( "設定" );
    m_setting_label.setObjectName( "title_label" );

    AddHeaderButton( COLOR_FILTER_MODE_TB, "TB標準" );
    AddHeaderButton( COLOR_FILTER_MODE_CUSTOM, "カスタム" );

    PlaceChildrenIntoPanel( HeaderButtons(), CFC_FIRST_TAB_GEOMETRY.size(), CFC_FIRST_TAB_GEOMETRY.topLeft(), QSize( m_header_buttons_per_page, 1 ) );
    m_button_next_header_buttons_page.setVisible( HeaderButtons().size() > m_header_buttons_per_page );
    m_button_previous_header_buttons_page.setVisible( HeaderButtons().size() > m_header_buttons_per_page );
    SetupHeaderTabButtons();

    connect( &m_button_previous_header_buttons_page, &QPushButton::clicked, this, [&]()
    {
        SetCurrentHeaderButtonsPage( CurrentHeaderButtonsPage() - 1 );
    } );
    connect( &m_button_next_header_buttons_page, &QPushButton::clicked, this, [&]()
    {
        SetCurrentHeaderButtonsPage( CurrentHeaderButtonsPage() + 1 );
    } );
    connect( this, &ColorFilterControl::CurrentHeaderButtonsPageChanged, this, &ColorFilterControl::SetupHeaderTabButtons );

    connect( &m_button_next_filter_buttons_page, &QAbstractButton::clicked, this, &ColorFilterControl::ScrollUp );
    connect( &m_button_previous_filter_buttons_page, &QAbstractButton::clicked, this, &ColorFilterControl::ScrollDown );
    connect( this, &ColorFilterControl::ModeChanged, this, &ColorFilterControl::OnModeChanged );
    connect( this, &ColorFilterControl::CurrentTBTabPageChanged, this, [&]()
    {
        UpdateTBTabPage();
        m_button_next_filter_buttons_page.setEnabled( CurrentTBTabPage() > 0 );
        m_button_previous_filter_buttons_page.setEnabled( CurrentTBTabPage() < MaxTBTabPages() - 1 );
    } );
    connect( this, &ColorFilterControl::CurrentCustomTabPageChanged, this, [&]()
    {
        UpdateCustomTabPage();
        m_button_next_filter_buttons_page.setEnabled( CurrentCustomTabPage() > 0 );
        m_button_previous_filter_buttons_page.setEnabled( CurrentCustomTabPage() < MaxCustomTabPages() - 1 );
    } );
    connect( this, &ColorFilterControl::CurrentHistoryPageChanged, this, [&]()
    {
        UpdateHistoryPage();
        m_button_next_filter_buttons_page.setEnabled( CurrentHistoryPage() > 0 );
        m_button_previous_filter_buttons_page.setEnabled( CurrentHistoryPage() < MaxHistoryPages() - 1 );
    } );

    connect( &m_history_button, &QAbstractButton::toggled, this, [&]()
    {
        if( m_history_button.isChecked() )
        {
            SetMode( COLOR_FILTER_MODE_HISTORY );
            m_title_label.setText( "カラーフィルタ (最近使ったもの)" );
        }
        else
        {
            SetMode( m_previous_tab );
            m_title_label.setText( "カラーフィルタ" );
        }
    } );

    connect( &m_title_button, &QAbstractButton::toggled, this, [&]()
    {
        if( m_title_button.isChecked() )
        {
            SetSelectedFooterButton( m_title_button.text() );
            m_register_button.setChecked( false );
            m_delete_button.setChecked( false );
        }
    } );
    connect( &m_register_button, &QAbstractButton::toggled, this, [&]()
    {
        if( m_register_button.isChecked() )
        {
            SetSelectedFooterButton( m_register_button.text() );
            m_title_button.setChecked( false );
            m_delete_button.setChecked( false );
        }
    } );
    connect( &m_delete_button, &QAbstractButton::toggled, this, [&]()
    {
        if( m_delete_button.isChecked() )
        {
            SetSelectedFooterButton( m_delete_button.text() );
            m_register_button.setChecked( false );
            m_title_button.setChecked( false );
        }
    } );
    connect( &m_back_button, &QAbstractButton::clicked, this, &ColorFilterControl::ReturnButtonClicked );
    connect( &m_button_next_header_buttons_page, &QAbstractButton::clicked, this, &ColorFilterControl::NextButtonClicked );
    connect( &m_button_previous_header_buttons_page, &QAbstractButton::clicked, this, &ColorFilterControl::PrevButtonClicked );
    SetupHeaderTabButtons();
    OnModeChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetDispParamData
//  [ 機　能   ] : コントロールの表示パラメータデータを設する·
//  [ 引　数   ] : COLOR_FILTER_DISP_PARAM *param : 各パラメータ
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void ColorFilterControl::setDispParamData( COLOR_FILTER_DISP_PARAM *param )
{
    Q_ASSERT( param );
    m_tb_tab_buttons.clear();

    for( uint16_t i = 0; i < param->tb.count; i++ )
    {
        auto button = MakeSharedQObject<SelectButton>( this );
        m_tb_tab_buttons.push_back( button );

        button->setFixedSize( CFC_FIRST_BUTTON_GEOMETRY.size() );
        button->setText( param->tb.color_filter[i].name );

        button->SetBackgroundColor( param->tb.color_filter[i].color );
        button->SetSelectedBackgroundColor( button->BackgroundColor() );
        button->SetCheckMarkVisible( true );
        button->setChecked( param->tb.color_filter[i].select );

        connect( button.get(), &QAbstractButton::clicked, this, &ColorFilterControl::OnTBTabButtonClicked );

    }

    PlaceChildrenIntoPanel( m_tb_tab_buttons, CFC_FIRST_BUTTON_GEOMETRY.size(), CFC_FIRST_BUTTON_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE );

    m_custom_tab_buttons.clear();

    for( uint16_t i = 0; i < param->custom.count; i++ )
    {
        auto button = MakeSharedQObject<SelectButton>( this );
        m_custom_tab_buttons.push_back( button );
        button->setFixedSize( CFC_FIRST_BUTTON_GEOMETRY.size() );
        button->setText( param->custom.color_filter[i].name );
        button->SetBackgroundColor( param->custom.color_filter[i].color );
        button->SetSelectedBackgroundColor( button->BackgroundColor() );
        button->SetCheckMarkVisible( true );
        button->setChecked( param->custom.color_filter[i].select );

        connect( button.get(), &QAbstractButton::clicked, this, &ColorFilterControl::OnCustomTabButtonClicked );
    }

    PlaceChildrenIntoPanel( m_custom_tab_buttons, CFC_FIRST_BUTTON_GEOMETRY.size(), CFC_FIRST_BUTTON_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE );

    m_history_buttons.clear();

    for( uint16_t i = 0; i < param->history.count; i++ )
    {
        auto button = MakeSharedQObject<SelectButton>( this );
        m_history_buttons.push_back( button );
        button->setText( param->history.color_filter[i].name );
        button->SetBackgroundColor( param->history.color_filter[i].color );
        button->SetSelectedBackgroundColor( button->BackgroundColor() );
        button->setFixedSize( CFC_FIRST_BUTTON_GEOMETRY.size() );
        button->SetCheckMarkVisible( true );
        button->setChecked( param->history.color_filter[i].select );

        connect( button.get(), &QAbstractButton::clicked, this, &ColorFilterControl::OnHistoryButtonClicked );
    }

    PlaceChildrenIntoPanel( m_history_buttons, CFC_FIRST_BUTTON_GEOMETRY.size(), CFC_FIRST_BUTTON_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE );

    if( param->tb.select == true )
    {
        SetMode( COLOR_FILTER_MODE_TB );
    }

    if( param->custom.select == true )
    {
        SetMode( COLOR_FILTER_MODE_CUSTOM );
    }

    if( param->history.select == true )
    {
        SetMode( COLOR_FILTER_MODE_HISTORY );
    }

    OnModeChanged();

    emit SelectedTbButtonChanged();
    emit SelectedCustomButtonChanged();
    emit SelectedHistoryButtonChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : ScrollUp
//  [ 機　能 ] : グループボタンを上にスクロールする
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControl::ScrollUp()
{
    if( Mode() == COLOR_FILTER_MODE_TB )
    {
        SetCurrentTBTabPage( CurrentTBTabPage() - 1 );
    }
    else if( Mode() == COLOR_FILTER_MODE_CUSTOM )
    {
        SetCurrentCustomTabPage( CurrentCustomTabPage() - 1 );
    }
    else if( Mode() == COLOR_FILTER_MODE_HISTORY )
    {
        SetCurrentHistoryPage( CurrentHistoryPage() - 1 );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : ScrollDown
//  [ 機　能 ] : グループボタンを下にスクロールする
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControl::ScrollDown()
{
    if( Mode() == COLOR_FILTER_MODE_TB )
    {
        SetCurrentTBTabPage( CurrentTBTabPage() + 1 );
    }
    else if( Mode() == COLOR_FILTER_MODE_CUSTOM )
    {
        SetCurrentCustomTabPage( CurrentCustomTabPage() + 1 );
    }
    else if( Mode() == COLOR_FILTER_MODE_HISTORY )
    {
        SetCurrentHistoryPage( CurrentHistoryPage() + 1 );
    }
}

int ColorFilterControl::CurrentTBTabPage() const
{
    return m_current_tb_tab_page;
}

void ColorFilterControl::SetCurrentTBTabPage( int value )
{
    if( m_current_tb_tab_page == value )
    {
        return;
    }

    m_current_tb_tab_page = value;
    emit CurrentTBTabPageChanged();
}

int ColorFilterControl::CurrentCustomTabPage() const
{
    return m_current_custom_tab_page;
}

void ColorFilterControl::SetCurrentCustomTabPage( int value )
{
    if( m_current_custom_tab_page == value )
    {
        return;
    }

    m_current_custom_tab_page = value;
    emit CurrentCustomTabPageChanged();
}

int ColorFilterControl::CurrentHistoryPage() const
{
    return m_current_history_page;
}

void ColorFilterControl::SetCurrentHistoryPage( int value )
{
    if( m_current_history_page == value )
    {
        return;
    }

    m_current_history_page = value;
    emit CurrentHistoryPageChanged();
}

ColorFilterDisplayMode ColorFilterControl::Mode() const
{
    return m_mode;
}

void ColorFilterControl::SetMode( ColorFilterDisplayMode value )
{
    if( m_mode == value )
    {
        return;
    }

    m_mode = value;
    emit ModeChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : OnModeChanged
//  [ 機　能 ] : モード変更を処理するイベント
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControl::OnModeChanged()
{
    for( const auto &button : qAsConst( m_header_buttons ) )
    {
        button.button->setChecked( button.mode == Mode() );
    }

    SetupHeaderTabButtons();

    for( auto &btn : m_custom_tab_buttons )
    {
        btn->setVisible( Mode() == COLOR_FILTER_MODE_CUSTOM );
    }

    for( auto &btn : m_children_custom_tab )
    {
        btn->setVisible( Mode() == COLOR_FILTER_MODE_CUSTOM );
    }

    for( auto &btn : m_history_buttons )
    {
        btn->setVisible( Mode() == COLOR_FILTER_MODE_HISTORY );
    }

    for( auto &btn : m_tb_tab_buttons )
    {
        btn->setVisible( Mode() == COLOR_FILTER_MODE_TB );
    }

    for( auto &btn : m_children_tb_tab )
    {
        btn->setVisible( Mode() == COLOR_FILTER_MODE_TB );
    }

    if( Mode() == COLOR_FILTER_MODE_TB )
    {
        UpdateTBTabPage();
        m_history_button.setChecked( false );
        m_button_next_filter_buttons_page.setEnabled( CurrentTBTabPage() > 0 );
        m_button_previous_filter_buttons_page.setEnabled( CurrentTBTabPage() < MaxTBTabPages() - 1 );

        m_button_next_filter_buttons_page.setVisible( m_tb_tab_buttons.length() > BUTTONS_PER_PAGE );
        m_button_previous_filter_buttons_page.setVisible( m_tb_tab_buttons.length() > BUTTONS_PER_PAGE );
    }
    else if( Mode() == COLOR_FILTER_MODE_CUSTOM )
    {
        UpdateCustomTabPage();
        m_history_button.setChecked( false );
        m_button_next_filter_buttons_page.setEnabled( CurrentCustomTabPage() > 0 );
        m_button_previous_filter_buttons_page.setEnabled( CurrentCustomTabPage() < MaxCustomTabPages() - 1 );

        m_button_next_filter_buttons_page.setVisible( m_custom_tab_buttons.length() > BUTTONS_PER_PAGE );
        m_button_previous_filter_buttons_page.setVisible( m_custom_tab_buttons.length() > BUTTONS_PER_PAGE );
    }
    else if( Mode() == COLOR_FILTER_MODE_HISTORY )
    {
        m_history_button.setChecked( true );
        UpdateHistoryPage();

        m_button_next_filter_buttons_page.setEnabled( CurrentHistoryPage() > 0 );
        m_button_previous_filter_buttons_page.setEnabled( CurrentHistoryPage() < MaxHistoryPages() - 1 );

        m_button_next_filter_buttons_page.setVisible( m_history_buttons.length() > BUTTONS_PER_PAGE );
        m_button_previous_filter_buttons_page.setVisible( m_history_buttons.length() > BUTTONS_PER_PAGE );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : UpdateTBTabPage
//  [ 機　能 ] : TBタブボタンの可視性を更新する
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControl::UpdateTBTabPage()
{
    UpdateChildrenVisibility( m_tb_tab_buttons, CurrentTBTabPage(), BUTTONS_PER_PAGE );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : UpdateCustomTabPage
//  [ 機　能 ] : カスタムタブボタンの可視性を更新する
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControl::UpdateCustomTabPage()
{
    UpdateChildrenVisibility( m_custom_tab_buttons, CurrentCustomTabPage(), BUTTONS_PER_PAGE );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : UpdateHistoryPage
//  [ 機　能 ] : 最近使ったものタブボタンの可視性を更新する
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControl::UpdateHistoryPage()
{
    UpdateChildrenVisibility( m_history_buttons, CurrentHistoryPage(), BUTTONS_PER_PAGE );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : AddHeaderButton
//  [ 機　能 ] : ヘッダーボタンを追加する
//  [ 引　数 ] : ColorFilterDisplayMode mode: TBタブ、Custom or History
//             const QString &text: 次へボタン
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControl::AddHeaderButton( ColorFilterDisplayMode mode, const QString &text )
{
    auto button = MakeSharedQObject<SelectButton>( this );
    button->setText( text );
    button->setFixedSize( CFC_FIRST_TAB_GEOMETRY.size() );

    m_header_buttons.append( {mode, button} );
    connect( button.get(), &QPushButton::clicked, this, &ColorFilterControl::OnDisplayTabButtonClicked );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : HeaderButtons
//  [ 機　能 ] : ヘッダーボタンを取得する
//  [ 引　数 ] : void
//  [ 戻り値 ] : QVector<QSharedPointer<SelectButton>>: ボタンリスト
//--------------------------------------------------------------------------
QVector<QSharedPointer<SelectButton>> ColorFilterControl::HeaderButtons() const
{
    QVector<QSharedPointer<SelectButton>> buttons;

    for( const auto &button : qAsConst( m_header_buttons ) )
    {
        buttons.append( button.button );
    }

    return buttons;
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetupHeaderTabButtons
//  [ 機　能 ] : ヘッダーボタンの可視性を設定、更新する
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControl::SetupHeaderTabButtons()
{
    m_button_previous_header_buttons_page.setEnabled( CurrentHeaderButtonsPage() > 0 );
    m_button_next_header_buttons_page.setEnabled( CurrentHeaderButtonsPage() < m_header_buttons_per_page - 1 );

    if( Mode() == COLOR_FILTER_MODE_HISTORY )
    {
        for( const auto &button : qAsConst( m_header_buttons ) )
        {
            button.button->setVisible( false );
        }

        m_button_next_header_buttons_page.setVisible( false );
        m_button_previous_header_buttons_page.setVisible( false );
    }
    else
    {
        UpdateChildrenVisibility( HeaderButtons(), CurrentHeaderButtonsPage(), m_header_buttons_per_page );
        m_button_next_header_buttons_page.setVisible( HeaderButtons().size() > m_header_buttons_per_page );
        m_button_previous_header_buttons_page.setVisible( HeaderButtons().size() > m_header_buttons_per_page );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : OnDisplayTabButtonClicked
//  [ 機　能 ] : タブボタンをクリックするイベントを処理する
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControl::OnDisplayTabButtonClicked()
{
    auto button = std::find_if( m_header_buttons.begin(), m_header_buttons.end(), [&]( const DisplayTabButton & button )
    {
        return button.button.get() == sender();
    } );

    if( button != m_header_buttons.end() )
    {
        SetMode( button->mode );
        m_previous_tab = Mode();
    }
}

const QString &ColorFilterControl::SelectedFooterButton() const
{
    return m_current_footer_button_active;
}

void ColorFilterControl::SetSelectedFooterButton( const QString &value )
{
    if( m_current_footer_button_active == value )
    {
        return;
    }

    m_current_footer_button_active = value;
    emit SelectedFooterButtonChanged();
}

int ColorFilterControl::MaxTBTabPages() const
{
    return CalulateNumberOfPages( m_tb_tab_buttons.length(), BUTTONS_PER_PAGE );
}

int ColorFilterControl::MaxCustomTabPages() const
{
    return CalulateNumberOfPages( m_custom_tab_buttons.length(), BUTTONS_PER_PAGE );
}

int ColorFilterControl::MaxHistoryPages() const
{
    return CalulateNumberOfPages( m_history_buttons.length(), BUTTONS_PER_PAGE );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : OnTBTabButtonClicked
//  [ 機　能 ] : TBタブボタンをクリックするイベントを処理する
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControl::OnTBTabButtonClicked()
{
    auto iter = std::find( m_tb_tab_buttons.begin(), m_tb_tab_buttons.end(), sender() );

    if( iter == m_tb_tab_buttons.end() )
    {
        return;
    }

    auto button = *iter;
    AddButtonToHistory( button );

    for( const auto &b : qAsConst( m_tb_tab_buttons ) )
    {
        b->setChecked( b == button );
    }

    emit SelectedTbButtonChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : OnCustomTabButtonClicked
//  [ 機　能 ] : カスタムタブボタンをクリックするイベントを処理する
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControl::OnCustomTabButtonClicked()
{
    auto iter = std::find( m_custom_tab_buttons.begin(), m_custom_tab_buttons.end(), sender() );

    if( iter == m_custom_tab_buttons.end() )
    {
        return;
    }

    auto button = *iter;
    AddButtonToHistory( button );

    for( const auto &b : qAsConst( m_custom_tab_buttons ) )
    {
        b->setChecked( b == button );
    }

    emit SelectedCustomButtonChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : OnHistoryButtonClicked
//  [ 機　能 ] : 最近使ったものボタンをクリックするイベントを処理する
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControl::OnHistoryButtonClicked()
{
    auto iter = std::find( m_history_buttons.begin(), m_history_buttons.end(), sender() );

    if( iter == m_history_buttons.end() )
    {
        return;
    }

    auto button = *iter;

    for( const auto &b : qAsConst( m_history_buttons ) )
    {
        b->setChecked( b == button );
    }

    emit SelectedHistoryButtonChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : AddButtonToHistory
//  [ 機　能 ] : ボタンを最近使ったものリストに追加する
//  [ 引　数 ] : QSharedPointer<SelectButton> button: 要追加のボタン
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void ColorFilterControl::AddButtonToHistory( QSharedPointer<SelectButton> button )
{
    auto new_button = MakeSharedQObject<SelectButton>( this );
    new_button->setText( button->text() );
    new_button->SetCheckMarkVisible( true );
    new_button->setFixedSize( CFC_FIRST_BUTTON_GEOMETRY.size() );
    new_button->setVisible( false );
    new_button->SetBackgroundColor( button->BackgroundColor() );
    new_button->SetSelectedBackgroundColor( button->BackgroundColor() );
    connect( new_button.get(), &QAbstractButton::clicked, this, &ColorFilterControl::OnHistoryButtonClicked );
    m_history_buttons.push_front( new_button );
    PlaceChildrenIntoPanel( m_history_buttons, CFC_FIRST_BUTTON_GEOMETRY.size(), CFC_FIRST_BUTTON_GEOMETRY.topLeft(), BUTTONS_GRID_SIZE );

    for( const auto &b : qAsConst( m_history_buttons ) )
    {
        b->setChecked( b == new_button );
    }
}

int ColorFilterControl::CurrentHeaderButtonsPage() const
{
    return m_current_header_buttons_page;
}

void ColorFilterControl::SetCurrentHeaderButtonsPage( int value )
{
    value = qBound( 0, value, CalulateNumberOfPages( m_header_buttons.length(), m_header_buttons_per_page ) - 1 );

    if( m_current_header_buttons_page == value )
    {
        return;
    }

    m_current_header_buttons_page = value;
    emit CurrentHeaderButtonsPageChanged();
}
//--------------------------------------------------------------------------
//  [ 関数名 ] : SelectedTbButton
//  [ 機　能 ] : TBタブの現在選択されているボタン
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
const ColorFilterButton ColorFilterControl::SelectedTbButton() const
{
    auto iter = std::find_if( m_tb_tab_buttons.begin(), m_tb_tab_buttons.end(), []( const QSharedPointer<SelectButton> &b )
    {
        return b->isChecked();
    } );

    if( iter == m_tb_tab_buttons.end() )
    {
        return ColorFilterButton {};
    }

    return ColorFilterButton { ( *iter )->text(), ( *iter )->BackgroundColor() };
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SelectedCustomButton
//  [ 機　能 ] : カスタムタブの現在選択されているボタン
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
const ColorFilterButton ColorFilterControl::SelectedCustomButton() const
{
    auto iter = std::find_if( m_custom_tab_buttons.begin(), m_custom_tab_buttons.end(), []( const QSharedPointer<SelectButton> &b )
    {
        return b->isChecked();
    } );

    if( iter == m_custom_tab_buttons.end() )
    {
        return ColorFilterButton {};
    }

    return ColorFilterButton { ( *iter )->text(), ( *iter )->BackgroundColor() };
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SelectedHistoryButton
//  [ 機　能 ] : 最近使ったものタブの現在選択されているボタン
//  [ 引　数 ] : void
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
const ColorFilterButton ColorFilterControl::SelectedHistoryButton() const
{
    auto iter = std::find_if( m_history_buttons.begin(), m_history_buttons.end(), []( const QSharedPointer<SelectButton> &b )
    {
        return b->isChecked();
    } );

    if( iter == m_history_buttons.end() )
    {
        return ColorFilterButton {};
    }

    return ColorFilterButton { ( *iter )->text(), ( *iter )->BackgroundColor() };
}
