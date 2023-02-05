#include <QApplication>
#include "mainwindow.h"
#include "loghandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, false);

    initLog();

    MainWindow w;
    w.show();

    return a.exec();
}
