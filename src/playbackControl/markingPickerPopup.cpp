//--------------------------------------------------------------------------
// [ ファイル名 ] : markingPickerPopup.cpp
// [ 概      要 ] : A popup control to present the markings for users to select
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "playbackControl/markingPickerPopup.h"
#include "utility.h"

#include <QDebug>

#include <baseComponent/panelControlBase.h>

#define SCREEN_BACKGROUND_COLOR QColor(34, 43, 53) // 画面の背景色
#define PLC_PICKER_CELL_SIZE    QSize(78, 48)
#define PLC_PICKER_GRID_SIZE    QSize(2, 5)

MarkingPickerPopup::MarkingPickerPopup( QWidget *parent )
    : QWidget{parent}
{
    // Turn off window border and default buttons
    setWindowFlags( Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::Popup );

    QPalette palette {};
    palette.setColor( QPalette::Window, SCREEN_BACKGROUND_COLOR );
    palette.setColor( QPalette::Foreground, Qt::white );

    setFixedSize( PLC_PICKER_CELL_SIZE.width() * PLC_PICKER_GRID_SIZE.width(), PLC_PICKER_CELL_SIZE.height() * PLC_PICKER_GRID_SIZE.height() );

    QVector<Marking> markings =
    {
        {"●", QColor( Qt::red )},    {"●",  QColor( Qt::lightGray )},
        {"●", QColor( Qt::cyan )},   {"■",  QColor( Qt::lightGray )},
        {"●", QColor( Qt::yellow )}, {"★",  QColor( Qt::lightGray )},
        {"●", QColor( Qt::green )},  {"▲",  QColor( Qt::lightGray )},
        {"●", QColor( Qt::white )},  {"▼",  QColor( Qt::lightGray )},
    };

    for( const auto &m : markings )
    {
        const auto button = MakeSharedQObject<CustomPushButton>( this );
        button->setVisible( true );
        button->setText( m.marking );
        button->SetTextColor( m.color );
        button->setFixedSize( PLC_PICKER_CELL_SIZE );
        m_marking_buttons.append( button );

        connect( button.get(), &CustomPushButton::clicked, this, &MarkingPickerPopup::OnMarkingClicked );
    }

    PanelControlBase::PlaceChildrenIntoPanel( m_marking_buttons, PLC_PICKER_CELL_SIZE, QPoint( 0, 0 ), QSize( 2, 5 ) );
}

//--------------------------------------------------------------------------
//  [ 関数名 ] : OnMarkingClicked
//  [ 機　能 ] : Occurs when user click on a marking button
//  [ 引　数 ] : None
//  [ 戻り値 ] : void
//--------------------------------------------------------------------------
void MarkingPickerPopup::OnMarkingClicked()
{
    auto button = ( CustomPushButton * ) sender();
    Q_ASSERT( button );
    emit MarkingSelected( button->text(), button->TextColor() );
}
