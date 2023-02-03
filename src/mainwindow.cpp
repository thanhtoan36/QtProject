#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "baseComponent/panelWindow.h"
#include "colorFilterControl/colorFilterControl.hpp"

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
    static auto panel_window = new PanelWindow();
    panel_window->AttachPanelControl(new ColorFilterControl());
}

