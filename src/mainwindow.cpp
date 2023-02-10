#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utility.h"

#include <cstring>
#include <cmath>
#include <QDebug>
#include <QRandomGenerator>

QRandomGenerator gRandom;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_color_picker_control = MakeSharedQObject<ColorPickerControl>();
    m_color_picker_control->PrepareUi();

    m_color_picker_control_horizon = MakeSharedQObject<ColorPickerControlHorizon>();
    m_color_picker_control_horizon->PrepareUi();

    m_track_control = MakeSharedQObject<TrackControl>();
    m_track_control->PrepareUi();

    m_track_control_horizon = MakeSharedQObject<TrackControlHorizon>();
    m_track_control_horizon->PrepareUi();

    m_intensity_control = MakeSharedQObject<IntensityControl>();
    m_intensity_control->PrepareUi();

    m_intensity_control_horizon = MakeSharedQObject<IntensityControlHorizon>();
    m_intensity_control_horizon->PrepareUi();

    m_encoder_control = MakeSharedQObject<EncoderControl>();
    m_encoder_control->PrepareUi();

    m_encoder_control_horizon = MakeSharedQObject<EncoderControlHorizon>();
    m_encoder_control_horizon->PrepareUi();
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
        m_color_picker_control_horizon->SetDispParamDataHorizon(&params);
        m_panel_window->AttachPanelControl(m_color_picker_control_horizon);
    } else {
        m_color_picker_control->SetDispParamData(&params);
        m_panel_window->AttachPanelControl(m_color_picker_control);
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
        m_track_control_horizon->SetDispParamDataHorizon(&params);
        m_panel_window->AttachPanelControl(m_track_control_horizon);
    }
    else {
        m_track_control->PrepareUi();
        m_track_control->SetDispParamData(&params);
        m_panel_window->AttachPanelControl(m_track_control);
    }

    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_IntensityControl_Fake_Open_clicked()
{
    if (ui->checkBox_HorizontalLayout->isChecked()) {
        m_panel_window->AttachPanelControl(m_intensity_control_horizon);
    } else {
        m_panel_window->AttachPanelControl(m_intensity_control);
    }
    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_EncoderControl_Fake_Open_clicked()
{
    ENCODER_DISP_PARAM params;
    params.type = (EncoderType)ui->EncoderControl_Fake_Type->currentIndex();
    params.mode = (EncoderMode)ui->EncoderControl_Fake_Mode->currentIndex();
    params.count = gRandom.bounded(0, 10);
    QVector<ENCODER_PARAM> data;
    for (int i = 0; i < params.count; ++i) {
        ENCODER_PARAM p;
        p.maxLevel = gRandom.bounded(100, 255);
        p.level = gRandom.bounded(0, p.maxLevel);
        QString randomName = QString("Test%1").arg(gRandom.bounded(1, 50));
        std::strncpy(p.name, (const char*)randomName.toLocal8Bit().data(), sizeof(p.name) - 1);
        data.push_back(p);
    }
    params.param = data.data();

    if (ui->checkBox_HorizontalLayout->isChecked()) {
        m_encoder_control_horizon->SetDispParamData(&params);
        m_panel_window->AttachPanelControl(m_encoder_control_horizon);
    } else {
        m_encoder_control->SetDispParamData(&params);
        m_panel_window->AttachPanelControl(m_encoder_control);
    }
    m_panel_window->show();
    m_panel_window->raise();
}

