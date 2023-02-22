#include "baseComponent/toggleButton.h"
#include "baseComponent/designPolicyDefine.h"
#include <QDebug>
#include <QTimer>

ToggleButton::ToggleButton( QWidget *parent )
    : CustomToggleButtonBase( parent ),
      m_check_label( this )
{
    m_check_label.setText( "✓" );
    m_check_label.setStyleSheet( "QLabel { background-color: transparent; color : white; }" );
    m_check_label.setGeometry( 3, 3, 12, 12 );

    connect( this, &QAbstractButton::toggled, this, [&]( bool )
    {
        m_check_label.setVisible( isChecked() && CheckMarkVisible() );
    } );
    connect( this, &ToggleButton::CheckMarkVisibleChanged, this, [&]()
    {
        m_check_label.setVisible( isChecked() && CheckMarkVisible() );
    } );

    SetCheckMarkVisible( false );
    m_check_label.setVisible( isChecked() && CheckMarkVisible() );
}

bool ToggleButton::CheckMarkVisible() const
{
    return m_check_mark_vsible;
}

void ToggleButton::SetCheckMarkVisible( bool value )
{
    if( m_check_mark_vsible == value )
    {
        return;
    }

    m_check_mark_vsible = value;
    emit CheckMarkVisibleChanged();
}
