#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colorPickerControl/colorPickerControlHorizon.h"
#include "colorPickerControl/colorPickerControl.hpp"
#include "trackControl/trackControl.hpp"
#include "trackControl/trackControlHorizon.h"
#include "intensityControl/intensityControl.hpp"
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

    m_color_filter_control= MakeSharedQObject<ColorFilterControl>();
    m_color_filter_control->PrepareUi();

    m_color_filter_control_horizon = MakeSharedQObject<ColorFilterControlHorizon>();
    m_color_filter_control_horizon->PrepareUi();

    m_input_num_control = MakeSharedQObject<InputNumControl>();
    m_input_num_control->PrepareUi();

    m_input_num_control_horizon = MakeSharedQObject<InputNumControlHorizon>();
    m_input_num_control_horizon->PrepareUi();
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


void MainWindow::on_ColorFilterControl_Fake_Open_clicked()
{
    COLOR_FILTER_DISP_PARAM param;
    param.tb.select = true;
    param.custom.select = false;
    param.history.select = false;
    param.tb.count = QRandomGenerator::global()->generate()%100;
    param.tb.color_filter = (COLOR_FILTER_PARAM*)malloc(param.tb.count*sizeof(COLOR_FILTER_PARAM));
    for (int i = 0; i< param.tb.count;i++)
    {
        qsrand(time(0));param.tb.color_filter[i].color = QColor( QRandomGenerator::global()->generate()%255,  QRandomGenerator::global()->generate()%255, QRandomGenerator::global()->generate()%255);
        strncpy(param.tb.color_filter[i].name, QString(QString("T")+QString::number(i)).toLocal8Bit().data(), COLOR_FILTER_NAME_SIZE);
    }
    param.custom.count = QRandomGenerator::global()->generate()%100;
    param.custom.color_filter = (COLOR_FILTER_PARAM*)malloc(param.custom.count*sizeof(COLOR_FILTER_PARAM));
    for (int i = 0; i< param.custom.count;i++)
    {
        qsrand(time(0));param.custom.color_filter[i].color = QColor( QRandomGenerator::global()->generate()%255,  QRandomGenerator::global()->generate()%255, QRandomGenerator::global()->generate()%255);
        strncpy(param.custom.color_filter[i].name, QString(QString("C")+QString::number(i)).toLocal8Bit().data(), COLOR_FILTER_NAME_SIZE);
    }
    param.history.count = QRandomGenerator::global()->generate()%100;
    param.history.color_filter = (COLOR_FILTER_PARAM*)malloc(param.history.count*sizeof(COLOR_FILTER_PARAM));
    for (int i = 0; i< param.history.count;i++)
    {
        qsrand(time(0));param.history.color_filter[i].color = QColor( QRandomGenerator::global()->generate()%255,  QRandomGenerator::global()->generate()%255, QRandomGenerator::global()->generate()%255);
        strncpy(param.history.color_filter[i].name, QString(QString("H")+QString::number(i)).toLocal8Bit().data(), COLOR_FILTER_NAME_SIZE);
    }

    if (!ui->checkBox_HorizontalLayout->isChecked()) {
        m_color_filter_control->setDispParamData(&param);
        m_panel_window->AttachPanelControl(m_color_filter_control);
    } else {
        m_color_filter_control_horizon->SetDispParamDataHorizon(&param);
        m_panel_window->AttachPanelControl(m_color_filter_control_horizon);
    }
    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_InputNumControl_Fake_Open_clicked()
{
    INPUT_NUM_DISP_PARAM param;
    QString start;
    if (ui->InputNumControl_Fake_Type->currentIndex() == 0)
    {
        param.type = INPUT_NUM_TYPE_COLOR;
        start = "Color";
    }
    else if(ui->InputNumControl_Fake_Type->currentIndex() == 1)
    {
        param.type = INPUT_NUM_TYPE_POSITION;
        start = "Pos";
    }
    else if(ui->InputNumControl_Fake_Type->currentIndex() == 2)
    {
        param.type = INPUT_NUM_TYPE_GOBO;
        start = "Gobo";
    }
    else if(ui->InputNumControl_Fake_Type->currentIndex() == 3)
    {
        param.type = INPUT_NUM_TYPE_BEAM_SHUTTER;
        start = "Shutter";
    }
    else if(ui->InputNumControl_Fake_Type->currentIndex() == 4)
    {
        param.type = INPUT_NUM_TYPE_CONTROL;
        start = "Control";
    }
    param.mode  = INPUT_NUM_MODE_255;
    param.count = QRandomGenerator::global()->generate()%10;
    param.param = (INPUT_NUM_PARAM*)malloc(param.count * sizeof(INPUT_NUM_PARAM));

    qDebug() << param.count ;

    for (int i=0 ; i< param.count ; i++)
    {
        param.param[i].select = false;
        strncpy(param.param[i].name, (start+QString::number(i)).toLocal8Bit().data(), INPUT_NUM_NAME_SIZE);
    }

    if (!ui->checkBox_HorizontalLayout->isChecked()) {
        m_input_num_control->SetDispParamData(&param);
        m_panel_window->AttachPanelControl(m_input_num_control);
    } else {
        m_input_num_control_horizon->SetDispParamDataHorizon(&param);
        m_panel_window->AttachPanelControl(m_input_num_control_horizon);
    }
    m_panel_window->show();
    m_panel_window->raise();
}

