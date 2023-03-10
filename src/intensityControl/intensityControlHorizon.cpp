//--------------------------------------------------------------------------
// [ ファイル名 ] : intensityControlHorizon.cpp
// [ 概      要 ] : インテンシティコントロール水平ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#include "intensityControl/intensityControlHorizon.h"
#include "intensityControl/intensityControl_define.h"
#include "utility.h"
#include <QDebug>

//--------------------------------------------------------------------------
//  [ 関数名   ] : IntensityControlHorizon
//  [ 機能名   ] : インテンシティコントロール水平のコンストラクター
//  [ 引数     ] : QWidget *parent: 親ウィジェット
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
IntensityControlHorizon::IntensityControlHorizon( QWidget *parent )
    : IntensityControl( parent )
{
    setFixedSize( ISC_SCREENSIZE_HORIZON );
    m_grid_background.SetGridSize( QSize( 6, 5 ) );
    m_grid_background.move( ISC_EMPTY_BUTON_GOEMETRY_HORIZON.topLeft() );

    m_label_title.setGeometry( ISC_TITLE_GOEMETRY_HORIZON );
    m_label_title.setObjectName( "title_label_with_border" );
    m_return_button.setGeometry( ISC_RETURN_GOEMETRY_HORIZON );

    QStringList intensity_model =
    {
        "FF", "+10", "+5", "+1",
        "00", "-10", "-5", "-1",
        "70", "80", "90", "",
        "40", "50", "60", "",
        "10", "20", "30", "",
    };

    m_intensity_buttons.clear();

    for( const QString &b : intensity_model )
    {
        auto button = MakeSharedQObject<CustomPushButton>( this );
        button->setFixedSize( ISC_FF_BUTON_GOEMETRY_HORIZON.size() );
        button->setVisible( true );
        button->setText( b );

        if( b.isEmpty() )
        {
            button->setEnabled( false );
        }

        connect( button.get(), &QPushButton::clicked, this, [&]()
        {
            emit IntensityButtonClicked( ( ( CustomPushButton * )sender() )->text() );
        } );

        m_intensity_buttons.append( button );
    }

    PlaceChildrenIntoPanel( m_intensity_buttons, ISC_FF_BUTON_GOEMETRY_HORIZON.size(), ISC_FF_BUTON_GOEMETRY_HORIZON.topLeft(), QSize( 4, 5 ) );

}
