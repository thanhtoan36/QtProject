#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "baseComponent/panelWidgetBase.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ColorPickerControl_Fake_Open_clicked()
{
    PanelWidgetBase* panel = new PanelWidgetBase(324,520);
    panel->show();
}

