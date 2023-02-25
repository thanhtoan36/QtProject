#include <QApplication>
#include "mainwindow.h"

int main( int argc, char *argv[] )
{
    QApplication::setAttribute( Qt::AA_EnableHighDpiScaling, true );
    QApplication a( argc, argv );

    MainWindow w;
    w.show();

    QFont font;
    font.setStyleHint( QFont::Monospace );
    font.setFamily( "monospace" );
    font.setPointSize( 9 );
    QApplication::setFont( font );

    return a.exec();
}
