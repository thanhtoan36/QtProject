#include <QApplication>
#include "mainwindow.h"
#include "loghandler.h"
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QApplication::setStyle("fusion");

    initLog();

    MainWindow w;
    w.show();

    QFont font("Monospace");
    font.setStyleHint(QFont::Monospace);
    font.setPixelSize(16);

    QApplication::setFont(font);

    return a.exec();
}
