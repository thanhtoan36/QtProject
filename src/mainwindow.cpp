#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colorPickerControl/colorPickerControlHorizon.h"
#include "colorPickerControl/colorPickerControl.hpp"
#include "trackControl/trackControl.hpp"
#include "trackControl/trackControlHorizon.h"
#include "intensityControl/intensityControl.hpp"
#include "colorFilterControl/colorFilterControl.hpp"
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

    if (ui->checkBox_HorizontalLayout->isChecked()) {
        auto track_control = MakeSharedQObject<TrackControlHorizon>();
        track_control->PrepareUi();
        track_control->SetDispParamDataHorizon(&params);
        m_panel_window->AttachPanelControl(track_control);
    }
    else {
        auto track_control = MakeSharedQObject<TrackControl>();
        track_control->PrepareUi();
        track_control->SetDispParamData(&params);
        m_panel_window->AttachPanelControl(track_control);
    }

    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_IntensityControl_Fake_Open_clicked()
{
    auto intensity_control = MakeSharedQObject<IntensityControl>();
    intensity_control->PrepareUi();
    m_panel_window->AttachPanelControl(intensity_control);
    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_ColorFilterControl_Fake_Open_clicked()
{
    auto control = MakeSharedQObject<ColorFilterControl>();
    control->PrepareUi();
    COLOR_FILTER_DISP_PARAM param;
    param.tb.select = true;
    param.custom.select = false;
    param.history.select = false;
    param.tb.count = 50;
    param.tb.color_filter = (COLOR_FILTER_PARAM*)malloc(50*sizeof(COLOR_FILTER_PARAM));
    for (int i = 0; i< 50;i++)
    {
        qsrand(time(0));param.tb.color_filter[i].color = QColor( QRandomGenerator::global()->generate()%255,  QRandomGenerator::global()->generate()%255, QRandomGenerator::global()->generate()%255);
        strncpy(param.tb.color_filter[i].name, QString(QString("T")+QString::number(i)).toLocal8Bit().data(), COLOR_FILTER_NAME_SIZE);
    }
    param.custom.count = 0;
    param.history.count = 0;
    control->setDispParamData(&param);
    m_panel_window->AttachPanelControl(control);
    m_panel_window->show();
    m_panel_window->raise();
}

