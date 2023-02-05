#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colorPickerControl/colorPickerControl.hpp"
#include "include/utility.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_ColorPickerControl_Fake_Open_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ColorPickerControl_Fake_Open_clicked()
{
    auto color_picker_control = MakeSharedQObject<ColorPickerControl>();

    COLOR_PICKER_DISP_PARAM params;
    params.type = (ColorPickerType)ui->ColorPickerControl_Fake_Type->currentIndex();
    params.color = Qt::red;

    color_picker_control->SetDispParamData(&params);

    m_panel_window->AttachPanelControl(color_picker_control);
    m_panel_window->move(1000, 1000);
    m_panel_window->show();
    m_panel_window->raise();
}

