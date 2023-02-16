#include <QApplication>
#include "mainwindow.h"
#include "loghandler.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QApplication::setStyle("fusion");
    QApplication a(argc, argv);

    initLog();

    MainWindow w;
    w.show();

    QFont font;
    font.setStyleHint(QFont::Monospace);
    font.setFamily("monospace");
    font.setPointSize(9);
    QApplication::setFont(font);

    return a.exec();
}
