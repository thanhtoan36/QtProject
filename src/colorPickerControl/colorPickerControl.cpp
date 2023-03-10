//--------------------------------------------------------------------------
// [ ファイル名 ] : colorPickerControl.cpp
// [ 概      要 ] : カラーピッカーコントロール垂直ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#include "colorPickerControl/colorPickerControl.h"
#include "colorPickerControl/colorPickerControl_define.h"
#include "utility.h"

#include <QDebug>
#include <QColorDialog>

//--------------------------------------------------------------------------
//  [ 関数名   ] : ColorPickerControl
//  [ 機能名   ] : カラーピッカーコントロールのコンストラクター
//  [ 引数     ] : QWidget *parent: 親ウィジェット
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
ColorPickerControl::ColorPickerControl( QWidget *parent )
    : PanelControlBase( parent ),
      m_menu_background( this ),
      m_slider_background( this ),
      m_label_title( this ),
      m_button_previous_menu_page( this ),
      m_button_next_menu_page( this ),
      m_label_setting( this ),
      m_picker_xy( this ),
      m_label_title_x( this ),
      m_label_value_x( this ),
      m_slider_x( this ),
      m_label_title_y( this ),
      m_label_value_y( this ),
      m_slider_y( this ),
      m_picker_rgb( this ),
      m_label_title_h( this ),
      m_label_value_h( this ),
      m_slider_h( this ),
      m_label_title_s( this ),
      m_label_value_s( this ),
      m_slider_s( this ),
      m_label_title_v( this ),
      m_label_value_v( this ),
      m_slider_v( this ),
      m_children_xy{&m_picker_xy, &m_label_value_x, &m_label_value_y, &m_label_title_x, &m_label_title_y, &m_slider_x, &m_slider_y},
      m_children_rgb{&m_picker_rgb, &m_label_value_h, &m_label_title_h, &m_slider_h, &m_label_value_s, &m_label_title_s, &m_slider_s, &m_label_value_v, &m_label_title_v, &m_slider_v},
      m_picker_type( COLOR_PICKER_TYPE_XY ), m_picker_color( Qt::white ),
      m_header_buttons_per_page( 2 ),
      m_current_header_buttons_page( 0 )
{
    setFixedSize( CPC_SCREENSIZE );

    m_slider_x.setRange( 0, 1000 );
    m_slider_y.setRange( 0, 1000 );
    m_slider_h.setRange( 0, 359 );
    m_slider_s.setRange( 0, 255 );
    m_slider_v.setRange( 0, 255 );

    m_label_title.setObjectName( "title_label" );
    m_label_setting.setObjectName( "title_label_with_border" );

    m_slider_background.SetGridSize( QSize( 1, 1 ) );
    m_slider_background.SetBackgroundColor( QColor::fromRgb( 89, 89, 89 ) );
    m_slider_background.SetGridLineColor( Qt::transparent );
    m_slider_background.move( 0, CPC_LABEL_SETTING_GEOMETRY.bottom() );
    m_slider_background.SetCellSize( QSize( width(), height() - CPC_LABEL_SETTING_GEOMETRY.bottom() ) );

    m_menu_background.SetGridSize( QSize( 4, 1 ) );
    m_menu_background.SetCellSize( CPC_BUTTON_XY_GEOMETRY.size() );
    m_menu_background.move( CPC_BUTTON_XY_GEOMETRY.topLeft() );

    m_label_title.setGeometry( CPC_TITLE_GEOMETRY );

    m_button_previous_menu_page.setGeometry( CPC_BUTTON_PREVIOUS_TAB_GEOMETRY );
    m_button_previous_menu_page.setText( "◀" );

    m_button_next_menu_page.setGeometry( CPC_BUTTON_NEXT_TAB_GEOMETRY );
    m_button_next_menu_page.setText( "▶" );

    m_label_setting.setGeometry( CPC_LABEL_SETTING_GEOMETRY );
    m_label_setting.setText( "設定" );

    m_picker_xy.setGeometry( CPC_PICKER_XY_GEOMETRY );
    m_picker_rgb.setGeometry( CPC_PICKER_RGB_GEOMETRY );

    m_label_title_x.setGeometry( CPC_LABEL_TITLE_X_GEOMETRY );
    m_label_title_x.setText( "x" );

    m_label_value_x.setGeometry( CPC_LABEL_VALUE_X_GEOMETRY );

    m_slider_x.setGeometry( CPC_SLIDER_X_GEOMETRY );
    m_slider_x.setOrientation( Qt::Horizontal );

    m_label_title_y.setGeometry( CPC_LABEL_TITLE_Y_GEOMETRY );
    m_label_title_y.setText( "y" );

    m_label_value_y.setGeometry( CPC_LABEL_VALUE_Y_GEOMETRY );

    m_slider_y.setGeometry( CPC_SLIDER_Y_GEOMETRY );
    m_slider_y.setOrientation( Qt::Horizontal );

    // RGB Tab
    m_label_title_h.setGeometry( CPC_LABEL_TITLE_H_GEOMETRY );
    m_label_title_h.setText( "H" );

    m_label_value_h.setGeometry( CPC_LABEL_VALUE_H_GEOMETRY );

    m_slider_h.setGeometry( CPC_SLIDER_X_GEOMETRY );
    m_slider_h.setOrientation( Qt::Horizontal );

    m_label_title_s.setGeometry( CPC_LABEL_TITLE_S_GEOMETRY );
    m_label_title_s.setText( "S" );

    m_label_value_s.setGeometry( CPC_LABEL_VALUE_S_GEOMETRY );

    m_slider_s.setGeometry( CPC_SLIDER_S_GEOMETRY );
    m_slider_s.setOrientation( Qt::Horizontal );

    m_label_title_v.setGeometry( CPC_LABEL_TITLE_V_GEOMETRY );
    m_label_title_v.setText( "V" );

    m_label_value_v.setGeometry( CPC_LABEL_VALUE_V_GEOMETRY );

    m_slider_v.setGeometry( CPC_SLIDER_V_GEOMETRY );
    m_slider_v.setOrientation( Qt::Horizontal );

    // セットアップメニューボタン
    AddHeaderButton( COLOR_PICKER_TYPE_XY, "xy" );
    AddHeaderButton( COLOR_PICKER_TYPE_RGB, "RGB" );

    PlaceChildrenIntoPanel( HeaderButtons(), CPC_BUTTON_XY_GEOMETRY.size(), CPC_BUTTON_XY_GEOMETRY.topLeft(), QSize( m_header_buttons_per_page, 1 ) );
    m_button_previous_menu_page.setVisible( HeaderButtons().size() > m_header_buttons_per_page );
    m_button_next_menu_page.setVisible( HeaderButtons().size() > m_header_buttons_per_page );
    SetupHeaderButtonPages();

    OnPickerTypeChanged();

    m_picker_xy.SetColor( Qt::gray );
    m_picker_rgb.SetColor( Qt::gray );

    auto xy = m_picker_xy.Xy();
    m_slider_x.setValue( xy.x() * 1000 );
    m_slider_y.setValue( xy.y() * 1000 );
    m_label_value_x.setText( QString::asprintf( "%.03f", xy.x() ) );
    m_label_value_y.setText( QString::asprintf( "%.03f", xy.y() ) );

    auto hsv = m_picker_rgb.HSV();
    m_slider_h.setValue( hsv.h );
    m_slider_s.setValue( hsv.s );
    m_slider_v.setValue( hsv.v );
    m_label_value_h.setText( QString::number( hsv.h ) );
    m_label_value_s.setText( QString::number( hsv.s ) );
    m_label_value_v.setText( QString::number( hsv.v ) );

    connect( &m_button_previous_menu_page, &QPushButton::clicked, this, [&]()
    {
        SetCurrentHeaderButtonsPage( CurrentHeaderButtonsPage() - 1 );
    } );
    connect( &m_button_next_menu_page, &QPushButton::clicked, this, [&]()
    {
        SetCurrentHeaderButtonsPage( CurrentHeaderButtonsPage() + 1 );
    } );
    connect( this, &ColorPickerControl::CurrentHeaderButtonsPageChanged, this, &ColorPickerControl::SetupHeaderButtonPages );

    connect( this, &ColorPickerControl::PickerTypeChanged, this, &ColorPickerControl::OnPickerTypeChanged );
    //xy picker
    connect( &m_picker_xy, &CustomColorPickerXY::XyChanged, this, [&]( QPointF xy )
    {
        m_label_value_x.setText( QString::asprintf( "%.03f", xy.x() ) );
        m_label_value_y.setText( QString::asprintf( "%.03f", xy.y() ) );
    } );
    connect( &m_picker_xy, &CustomColorPickerXY::Picked, this, [&]()
    {
        PauseSliderEvents();

        SetPickerColor( m_picker_xy.Color() );
        auto xy = m_picker_xy.Xy();
        m_slider_x.setValue( xy.x() * 1000 );
        m_slider_y.setValue( xy.y() * 1000 );

        ResumeSliderEvents();
    } );

    connect( &m_slider_x, &QSlider::valueChanged, this, [&]( int )
    {
        m_picker_xy.SetXy( QPointF( m_slider_x.value() / 1000.0, m_slider_y.value() / 1000.0 ) );
        SetPickerColor( m_picker_xy.Color() );
        // m_picker_rgb.SetColor(pickerColor());
    } );
    connect( &m_slider_y, &QSlider::valueChanged, this, [&]( int )
    {
        m_picker_xy.SetXy( QPointF( m_slider_x.value() / 1000.0, m_slider_y.value() / 1000.0 ) );
        SetPickerColor( m_picker_xy.Color() );
        // m_picker_rgb.SetColor(pickerColor());
    } );

    //rgb picker event
    connect( &m_picker_rgb, &CustomColorPickerRGB::HSVChanged, this, [&]( hsv_t hsv )
    {
        m_label_value_h.setText( QString::number( hsv.h ) );
        m_label_value_s.setText( QString::number( hsv.s ) );
        m_label_value_v.setText( QString::number( hsv.v ) );
    } );
    connect( &m_picker_rgb, &CustomColorPickerRGB::Picked, this, [&]()
    {
        PauseSliderEvents();

        SetPickerColor( m_picker_rgb.Color() );
        // m_picker_xy.SetColor(pickerColor());
        auto hsv = m_picker_rgb.HSV();
        m_slider_h.setValue( hsv.h );
        m_slider_s.setValue( hsv.s );
        m_slider_v.setValue( hsv.v );

        ResumeSliderEvents();
    } );

    connect( &m_slider_h, &QSlider::valueChanged, this, [&]( int )
    {
        m_picker_rgb.SetHSV( m_slider_h.value(), m_slider_s.value(), m_slider_v.value() );
        SetPickerColor( m_picker_rgb.Color() );
        // m_picker_xy.SetColor(pickerColor());
    } );
    connect( &m_slider_s, &QSlider::valueChanged, this, [&]( int )
    {
        m_picker_rgb.SetHSV( m_slider_h.value(), m_slider_s.value(), m_slider_v.value() );
        SetPickerColor( m_picker_rgb.Color() );
        // m_picker_xy.SetColor(pickerColor());
    } );
    connect( &m_slider_v, &QSlider::valueChanged, this, [&]( int )
    {
        m_picker_rgb.SetHSV( m_slider_h.value(), m_slider_s.value(), m_slider_v.value() );
        SetPickerColor( m_picker_rgb.Color() );
        // m_picker_xy.SetColor(pickerColor());
    } );

    connect( &m_button_next_menu_page, &QAbstractButton::clicked, this, &ColorPickerControl::NextButtonClicked );
    connect( &m_button_previous_menu_page, &QAbstractButton::clicked, this, &ColorPickerControl::PrevButtonClicked );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetDispParamData
//  [ 機能名   ] : 色とスライダーの値を設定する
//  [ 引数     ] : COLOR_PICKER_DISP_PARAM *param: 表示パラメータ
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void ColorPickerControl::SetDispParamData( COLOR_PICKER_DISP_PARAM *param )
{
    Q_ASSERT( param );
    SetPickerType( param->type );
    SetPickerColor( param->color );

    m_picker_xy.SetColor( PickerColor() );
    m_picker_rgb.SetColor( PickerColor() );

    PauseSliderEvents();
    auto xy = m_picker_xy.Xy();
    m_slider_x.setValue( xy.x() * 1000 );
    m_slider_y.setValue( xy.y() * 1000 );

    auto hsv = m_picker_rgb.HSV();
    m_slider_h.setValue( hsv.h );
    m_slider_s.setValue( hsv.s );
    m_slider_v.setValue( hsv.v );
    ResumeSliderEvents();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : PauseSliderEvents
//  [ 機能名   ] : シグナルスロットを無効にする
//  [ 引数          ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void ColorPickerControl::PauseSliderEvents()
{
    m_slider_x.blockSignals( true );
    m_slider_y.blockSignals( true );
    m_slider_h.blockSignals( true );
    m_slider_s.blockSignals( true );
    m_slider_v.blockSignals( true );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : ResumeSliderEvents
//  [ 機能名   ] : シグナルスロットを有効にする
//  [ 引数          ] : void
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void ColorPickerControl::ResumeSliderEvents()
{
    m_slider_x.blockSignals( false );
    m_slider_y.blockSignals( false );
    m_slider_h.blockSignals( false );
    m_slider_s.blockSignals( false );
    m_slider_v.blockSignals( false );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : AddHeaderButton
//  [ 機能名   ] : ヘッダーボタンを追加する
//  [ 引数          ] : ColorPickerType type: ボタンタイプ がxy または rgb
//                const QString &text: ボタン文字
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void ColorPickerControl::AddHeaderButton( ColorPickerType type, const QString &text )
{
    auto button = MakeSharedQObject<SelectButton>( this );
    button->setText( text );
    button->setFixedSize( CPC_BUTTON_XY_GEOMETRY.size() );

    m_header_buttons.append( {type, button} );
    connect( button.get(), &QPushButton::clicked, this, &ColorPickerControl::OnPickerTypeButtonClicked );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : HeaderButtons
//  [ 機能名   ] : ヘッダーボタンリストを取得する
//  [ 引数          ] : void
//  [ 戻り値    ] : QVector<QSharedPointer<SelectButton>> : SelectButtonのリスト
//--------------------------------------------------------------------------
QVector<QSharedPointer<SelectButton>> ColorPickerControl::HeaderButtons() const
{
    QVector<QSharedPointer<SelectButton>> buttons;

    for( const auto &button : qAsConst( m_header_buttons ) )
    {
        buttons.append( button.button );
    }

    return buttons;
}


//--------------------------------------------------------------------------
//  [ 関数名   ] : PickerType
//  [ 機能名   ] : ピッカータイプ取得
//  [ 引数     ] : void
//  [ 戻り値    ] : ColorPickerType: xyタイプ、または、rgbタイプ
//--------------------------------------------------------------------------
ColorPickerType ColorPickerControl::PickerType() const
{
    return m_picker_type;
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetPickerType
//  [ 機能名   ] : ピッカータイプ設定
//  [ 引数     ] : ColorPickerType type: 要設定のピッカータイプ
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void ColorPickerControl::SetPickerType( ColorPickerType type )
{
    if( m_picker_type == type )
    {
        return;
    }

    m_picker_type = type;
    emit PickerTypeChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : PickerColor
//  [ 機能名   ] : 選んだ色の取得
//  [ 引数     ] : void
//  [ 戻り値    ] : QColor: 選んだ色
//--------------------------------------------------------------------------
QColor ColorPickerControl::PickerColor() const
{
    return m_picker_color;
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetPickerColor
//  [ 機能名   ] : 選んだ色を設定する
//  [ 引数     ] : const QColor &color: 要設定の色
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void ColorPickerControl::SetPickerColor( const QColor &color )
{
    if( m_picker_color == color )
    {
        return;
    }

    m_picker_color = color;
    emit PickerColorChanged();
}

//--------------------------------------------------------------------------
//  [ 関数名  ] : OnPickerTypeChanged
//  [ 機能名  ] : ピッカーのタイプが変更されたイベントを処理する
//  [ 引数         ] : void
//  [ 戻り値   ] : void
//--------------------------------------------------------------------------
void ColorPickerControl::OnPickerTypeChanged()
{
    auto button = std::find_if( m_header_buttons.begin(), m_header_buttons.end(), [&]( const PickerButton & button )
    {
        return button.type == PickerType();
    } );

    if( button != m_header_buttons.end() )
    {
        m_label_title.setText( QString( "ピッカー %1" ).arg( button->button->text() ) );
    }

    for( const auto &button : qAsConst( m_header_buttons ) )
    {
        button.button->setChecked( button.type == PickerType() );
    }

    if( PickerType() == COLOR_PICKER_TYPE_XY )
    {
        foreach( auto &child, m_children_xy )
        {
            child->setVisible( true );
        }

        foreach( auto &child, m_children_rgb )
        {
            child->setVisible( false );
        }
    }

    if( PickerType() == COLOR_PICKER_TYPE_RGB )
    {
        foreach( auto &child, m_children_xy )
        {
            child->setVisible( false );
        }

        foreach( auto &child, m_children_rgb )
        {
            child->setVisible( true );
        }
    }
}

//--------------------------------------------------------------------------
//  [ 関数名  ] : OnPickerTypeButtonClicked
//  [ 機能名  ] : ヘッダーボタンのクリックイベントを処理する
//  [ 引数    ] : void
//  [ 戻り値   ] : void
//--------------------------------------------------------------------------
void ColorPickerControl::OnPickerTypeButtonClicked()
{
    auto button = std::find_if( m_header_buttons.begin(), m_header_buttons.end(), [&]( const PickerButton & button )
    {
        return button.button.get() == sender();
    } );

    if( button != m_header_buttons.end() )
    {
        SetPickerType( button->type );
    }
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : SetupHeaderButtonPages
//  [ 機能名 ] : ヘッダーボタンをスクロールする
//  [ 引数   ] : void
//  [ 戻り値  ] : void
//--------------------------------------------------------------------------
void ColorPickerControl::SetupHeaderButtonPages()
{
    m_button_previous_menu_page.setEnabled( CurrentHeaderButtonsPage() > 0 );
    m_button_next_menu_page.setEnabled( CurrentHeaderButtonsPage() < m_header_buttons_per_page - 1 );

    UpdateChildrenVisibility( HeaderButtons(), CurrentHeaderButtonsPage(), m_header_buttons_per_page );
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : CurrentHeaderButtonsPage
//  [ 機能名   ] : 現在のヘッダーボタンを取得する
//  [ 引数     ] : void
//  [ 戻り値    ] : int: 現在のページ
//--------------------------------------------------------------------------
int ColorPickerControl::CurrentHeaderButtonsPage() const
{
    return m_current_header_buttons_page;
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetCurrentHeaderButtonsPage
//  [ 機能名   ] : 現在のヘッダーボタンを設定する
//  [ 引数     ] : int new_button_page: ボタンのインデックス
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void ColorPickerControl::SetCurrentHeaderButtonsPage( int new_button_page )
{
    new_button_page = qBound( 0, new_button_page, CalulateNumberOfPages( m_header_buttons.length(), m_header_buttons_per_page ) - 1 );

    if( m_current_header_buttons_page == new_button_page )
    {
        return;
    }

    m_current_header_buttons_page = new_button_page;
    emit CurrentHeaderButtonsPageChanged();
}
