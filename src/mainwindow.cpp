#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colorPickerControl/colorPickerControlHorizon.h"
#include "include/utility.h"
#include <QDebug>

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


    COLOR_PICKER_DISP_PARAM params;
    params.type = (ColorPickerType)ui->ColorPickerControl_Fake_Type->currentIndex();
    params.color = QColor::fromHsv(25,26,255);

    if (ui->checkBox_HorizontalLayout->isChecked())
    {
        auto color_picker_control = MakeSharedQObject<ColorPickerControlHorizon>();
        color_picker_control->SetDispParamData(&params);

        m_panel_window->AttachPanelControl(color_picker_control);
    }

    else{
        auto color_picker_control = MakeSharedQObject<ColorPickerControl>();
        color_picker_control->SetDispParamData(&params);

        m_panel_window->AttachPanelControl(color_picker_control);
    }


//    m_panel_window->move(1000, 1000);

    m_panel_window->show();
    m_panel_window->raise();
}

