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

#include "testDataParser.h"
#include <QDateTime>

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

    m_group_control = MakeSharedQObject<GroupControl>();
    m_group_control->PrepareUi();

    m_group_control_horizon = MakeSharedQObject<GroupControlHorizon>();
    m_group_control_horizon->PrepareUi();

    m_library_control = MakeSharedQObject<LibraryControl>();
    m_library_control->PrepareUi();

    m_library_control_horizon = MakeSharedQObject<LibraryControlHorizon>();
    m_library_control_horizon->PrepareUi();

    m_playback_control = MakeSharedQObject<PlaybackControl>();
    m_playback_control->PrepareUi();

    m_palette_control = MakeSharedQObject<PaletteControl>();
    m_palette_control->PrepareUi();

    connect(m_color_picker_control.get(), &ColorPickerControl::pickerColorChanged, this, &MainWindow::CPC_OnColorChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::logEvent(const QString &log)
{
    const QString TIME_FORMAT = "HH:mm:ss.zzz";
    const auto time = QTime::currentTime().toString(TIME_FORMAT);
    ui->EventOutput->appendPlainText(QString("[%1] %2").arg(time).arg(log));
}

void MainWindow::on_ColorPickerControl_Fake_Open_clicked()
{
    if (ui->checkBox_HorizontalLayout->isChecked())
    {
        m_panel_window->AttachPanelControl(m_color_picker_control_horizon);
    } else {
        m_panel_window->AttachPanelControl(m_color_picker_control);
    }

    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_TrackControl_Fake_Open_clicked()
{
    if (ui->checkBox_HorizontalLayout->isChecked()) {
        m_panel_window->AttachPanelControl(m_track_control_horizon);
    } else {
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
    if (ui->checkBox_HorizontalLayout->isChecked()) {
        m_panel_window->AttachPanelControl(m_encoder_control_horizon);
    } else {
        m_panel_window->AttachPanelControl(m_encoder_control);
    }
    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_ColorFilterControl_Fake_Open_clicked()
{
    if (ui->checkBox_HorizontalLayout->isChecked()) {
        m_panel_window->AttachPanelControl(m_color_filter_control_horizon);
    } else {
        m_panel_window->AttachPanelControl(m_color_filter_control);
    }
    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_InputNumControl_Fake_Open_clicked()
{
    if (ui->checkBox_HorizontalLayout->isChecked()) {
        m_panel_window->AttachPanelControl(m_input_num_control_horizon);
    } else {
        m_panel_window->AttachPanelControl(m_input_num_control);
    }
    m_panel_window->show();
    m_panel_window->raise();
}

void MainWindow::on_PlaybackControl_Fake_Open_clicked()
{
    if (ui->checkBox_HorizontalLayout->isChecked()) {
    } else {
        m_panel_window->AttachPanelControl(m_playback_control);
    }
    m_panel_window->show();
    m_panel_window->raise();
}

void MainWindow::on_GroupPanelControl_Fake_Open_clicked()
{
    GROUP_DISP_PARAM param;
    param.group.count = QRandomGenerator::global()->generate()%100;
    param.history.count = QRandomGenerator::global()->generate()%100;
    param.group.group_param = (GROUP_PARAM*)malloc(param.group.count*sizeof(GROUP_PARAM));
    param.history.group_param = (GROUP_PARAM*)malloc(param.history.count*sizeof(GROUP_PARAM));
    qDebug() << param.group.count;
    for (int i=0;i< param.group.count;i++)
    {
        param.group.group_param[i].select = false;
        strncpy(param.group.group_param[i].title, ("tG"+QString::number(i)).toLocal8Bit().data(), GROUP_NO_SIZE);
        strncpy(param.group.group_param[i].group_no, ("G"+QString::number(i)).toLocal8Bit().data(), GROUP_NO_SIZE);
    }
    for (int i=0;i< param.history.count;i++)
    {
        param.history.group_param[i].select = false;
        strncpy(param.history.group_param[i].title, ("tH"+QString::number(i)).toLocal8Bit().data(), GROUP_NO_SIZE);
        strncpy(param.history.group_param[i].group_no, ("H"+QString::number(i)).toLocal8Bit().data(), GROUP_NO_SIZE);
    }
    if (!ui->checkBox_HorizontalLayout->isChecked()) {
        m_group_control->SetDispParamData(&param);
        m_panel_window->AttachPanelControl(m_group_control);
    } else {
        m_group_control_horizon->SetDispParamDataHorizon(&param);
        m_panel_window->AttachPanelControl(m_group_control_horizon);

    }
    m_panel_window->show();
    m_panel_window->raise();
}

void MainWindow::CPC_OnColorChanged()
{
    logEvent(QString("CPC color changed: %1").arg(((ColorPickerControl*)sender())->pickerColor().name()));
}


void MainWindow::on_BtnClear_clicked()
{
    ui->EventOutput->clear();
}

void MainWindow::on_LibraryControl_Fake_Open_clicked()
{
    LIBRARY_DISP_PARAM param;
    param.group.count = QRandomGenerator::global()->generate()%100;
    param.group.library_param = (LIBRARY_PARAM*)malloc(param.group.count*sizeof (LIBRARY_PARAM));
    qDebug() <<param.group.count;
    for (int i=0;i< param.group.count;i++)
    {
        param.group.library_param[i].select = false;
        int mode = QRandomGenerator::global()->generate()%4;
        strncpy(param.group.library_param[i].mode, ("ModeL"+QString::number(mode)).toLocal8Bit().data(), LIBRARY_NO_SIZE);
        strncpy(param.group.library_param[i].title, ("tL"+QString::number(i)).toLocal8Bit().data(), LIBRARY_NO_SIZE);
        strncpy(param.group.library_param[i].library_no, (QString::number(mode)+"L"+QString::number(i)).toLocal8Bit().data(), LIBRARY_NO_SIZE);
    }

    param.history.count = QRandomGenerator::global()->generate()%100;
    param.history.library_param = (LIBRARY_PARAM*)malloc(param.history.count*sizeof (LIBRARY_PARAM));
    qDebug() <<param.history.count;
    for (int i=0;i< param.history.count;i++)
    {
        param.history.library_param[i].select = false;
        int mode = QRandomGenerator::global()->generate()%4;
        strncpy(param.history.library_param[i].mode, ("ModeH"+QString::number(mode)).toLocal8Bit().data(), LIBRARY_NO_SIZE);
        strncpy(param.history.library_param[i].title, ("tH"+QString::number(i)).toLocal8Bit().data(), LIBRARY_NO_SIZE);
        strncpy(param.history.library_param[i].library_no, (QString::number(mode)+"H"+QString::number(i)).toLocal8Bit().data(), LIBRARY_NO_SIZE);
    }

    if (!ui->checkBox_HorizontalLayout->isChecked()) {
        m_library_control->SetDispParamData(&param);
        m_panel_window->AttachPanelControl(m_library_control);
    } else {
        m_library_control_horizon->SetDispParamData(&param);
        m_panel_window->AttachPanelControl(m_library_control_horizon);

    }
    m_panel_window->show();
    m_panel_window->raise();
}

void MainWindow::on_InputNumControl_Fake_Set_clicked()
{
    INPUT_NUM_DISP_PARAM param = IN_ParseInput(ui->InputNumControl_Fake_RawInput->toPlainText());

    if (ui->checkBox_HorizontalLayout->isChecked()) {
        m_input_num_control_horizon->SetDispParamDataHorizon(&param);
    } else {
        m_input_num_control->SetDispParamData(&param);
    }
}


void MainWindow::on_ColorPickerControl_Fake_Set_clicked()
{
    COLOR_PICKER_DISP_PARAM params = CPC_ParseInput(ui->ColorPickerControl_RawInput->toPlainText());

    if (ui->checkBox_HorizontalLayout->isChecked()) {
        m_color_picker_control_horizon->SetDispParamDataHorizon(&params);
    } else {
        m_color_picker_control->SetDispParamData(&params);
    }
}


void MainWindow::on_ColorFilterControl_Fake_Set_clicked()
{
    COLOR_FILTER_DISP_PARAM param = CFC_ParseInput(ui->ColorFilterControl_RawInput->toPlainText());

    if (ui->checkBox_HorizontalLayout->isChecked()) {
        m_color_filter_control_horizon->SetDispParamDataHorizon(&param);
    } else {
        m_color_filter_control->setDispParamData(&param);
    }
}


void MainWindow::on_EncoderControl_Fake_Set_clicked()
{
    ENCODER_DISP_PARAM params = EC_ParseInput(ui->EncoderControl_RawInput->toPlainText());

    if (ui->checkBox_HorizontalLayout->isChecked()) {
        m_encoder_control_horizon->SetDispParamDataHorizon(&params);
    } else {
        m_encoder_control->SetDispParamData(&params);
    }
}


void MainWindow::on_TrackControl_Fake_Set_clicked()
{
    TRACK_DISP_PARAM params = TC_ParseInput(ui->TrackControl_RawInput->toPlainText());

    if (ui->checkBox_HorizontalLayout->isChecked()) {
        m_track_control_horizon->SetDispParamDataHorizon(&params);
    } else {
        m_track_control->SetDispParamData(&params);
    }

}

void MainWindow::on_PalletControl_Fake_Open_clicked()
{
    if (ui->checkBox_HorizontalLayout->isChecked()) {
        m_panel_window->AttachPanelControl(m_palette_control);
    } else {
        m_panel_window->AttachPanelControl(m_palette_control);
    }
    m_panel_window->show();
    m_panel_window->raise();
}

