#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colorFilterControl/colorFilterControl.hpp"
#include "include/utility.h"

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
    m_panel_window->AttachPanelControl( MakeSharedQObject<ColorFilterControl>() );
}

