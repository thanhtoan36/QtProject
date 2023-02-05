#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colorPickerControl/colorPickerControlHorizon.h"
#include "colorPickerControl/colorPickerControl.hpp"
#include "trackControl/trackControl.hpp"
#include "utility.h"

#include <QDebug>
#include <QRandomGenerator>

QRandomGenerator gRandom;

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
    params.color = QColor::fromHsv(25, 26, 255);

    if (ui->checkBox_HorizontalLayout->isChecked())
    {
        auto color_picker_control = MakeSharedQObject<ColorPickerControlHorizon>();
        color_picker_control->PrepareUi();
        color_picker_control->SetDispParamData(&params);

        m_panel_window->AttachPanelControl(color_picker_control);
    }

    else{
        auto color_picker_control = MakeSharedQObject<ColorPickerControl>();
        color_picker_control->PrepareUi();
        color_picker_control->SetDispParamData(&params);

        m_panel_window->AttachPanelControl(color_picker_control);
    }

    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_TrackControl_Fake_Open_clicked()
{
    auto track_control = MakeSharedQObject<TrackControl>();
    track_control->PrepareUi();

    TRACK_DISP_PARAM params;
    params.mode = (TrackMode)ui->TrackControl_Fake_Mode->currentIndex();
    params.valueMode = (TrackValueMode)ui->TrackControl_Fake_ValueMode->currentIndex();

    QVector<TRACK_PARAM_GROUP> points{};

    // Generate random points
    int point_count = ui->TrackControl_Fake_PointCount->text().toInt();
    for (int i = 0; i < point_count; i++) {
        TRACK_PARAM_GROUP point;

        const int max_value = params.mode == TrackMode::TRACK_MODE_PERCENT ? 100 : 255;

        point.pan.current = gRandom.bounded(0, max_value);
        point.pan.min = 0;
        point.pan.max = max_value;

        point.tilt.current = gRandom.bounded(0, max_value);
        point.tilt.min = 0;
        point.tilt.max = max_value;

        points.push_back(point);
    }

    params.count = points.size();
    params.data = points.data();

    track_control->SetDispParamData(&params);

    m_panel_window->AttachPanelControl(track_control);
    m_panel_window->show();
    m_panel_window->raise();
}

