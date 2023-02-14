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

    m_playback_control_horizon = MakeSharedQObject<PlaybackControlHorizon>();
    m_playback_control_horizon->PrepareUi();

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
        m_panel_window->AttachPanelControl(m_playback_control_horizon);
    } else {
        m_panel_window->AttachPanelControl(m_playback_control);
    }
    m_panel_window->show();
    m_panel_window->raise();
}

void MainWindow::on_GroupPanelControl_Fake_Open_clicked()
{
    if (!ui->checkBox_HorizontalLayout->isChecked()) {
        m_panel_window->AttachPanelControl(m_group_control);
    } else {
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
    if (!ui->checkBox_HorizontalLayout->isChecked()) {
        m_panel_window->AttachPanelControl(m_library_control);
    } else {
        m_panel_window->AttachPanelControl(m_library_control_horizon);
    }
    m_panel_window->show();
    m_panel_window->raise();
}

void MainWindow::on_InputNumControl_Fake_Set_clicked()
{
    INPUT_NUM_DISP_PARAM param = INC_ParseInput(ui->InputNumControl_Fake_RawInput->toPlainText());

    m_input_num_control_horizon->SetDispParamDataHorizon(&param);
    m_input_num_control->SetDispParamData(&param);
}


void MainWindow::on_ColorPickerControl_Fake_Set_clicked()
{
    COLOR_PICKER_DISP_PARAM params = CPC_ParseInput(ui->ColorPickerControl_RawInput->toPlainText());

    m_color_picker_control_horizon->SetDispParamDataHorizon(&params);
    m_color_picker_control->SetDispParamData(&params);
}


void MainWindow::on_ColorFilterControl_Fake_Set_clicked()
{
    COLOR_FILTER_DISP_PARAM param = CFC_ParseInput(ui->ColorFilterControl_RawInput->toPlainText());

    m_color_filter_control_horizon->SetDispParamDataHorizon(&param);
    m_color_filter_control->setDispParamData(&param);
}


void MainWindow::on_EncoderControl_Fake_Set_clicked()
{
    ENCODER_DISP_PARAM params = EC_ParseInput(ui->EncoderControl_RawInput->toPlainText());

    m_encoder_control_horizon->SetDispParamDataHorizon(&params);
    m_encoder_control->SetDispParamData(&params);
}


void MainWindow::on_TrackControl_Fake_Set_clicked()
{
    TRACK_DISP_PARAM params = TC_ParseInput(ui->TrackControl_RawInput->toPlainText());

    m_track_control_horizon->SetDispParamDataHorizon(&params);
    m_track_control->SetDispParamData(&params);
}

void MainWindow::on_PlaybackControl_Fake_Set_clicked()
{
    PLAYBACK_DISP_PARAM params = PLC_ParseInput(ui->PlaybackControl_Fake_RawInput->toPlainText());
    m_playback_control_horizon->setDispParamData(&params);
    m_playback_control->setDispParamData(&params);
}


void MainWindow::on_LibraryControl_Fake_Set_clicked()
{
    LIBRARY_DISP_PARAM params = LC_ParseInput(ui->LibraryControl_Fake_RawInput->toPlainText());
    m_library_control_horizon->SetDispParamData(&params);
    m_library_control->SetDispParamData(&params);
}


void MainWindow::on_GroupPanelControl_Fake_Set_clicked()
{
    GROUP_DISP_PARAM param = GC_ParseInput(ui->GroupPanelControl_Fake_RawInput->toPlainText());
    m_group_control->SetDispParamData(&param);
    m_group_control_horizon->SetDispParamDataHorizon(&param);
}


void MainWindow::on_PaletteControl_Fake_Set_clicked()
{
    PALETTE_DISP_PARAM param = PD_ParseInput(ui->PaletteControl_Fake_RawInput->toPlainText());
    m_palette_control->SetDispParamData(&param);
    // m_palette_control_horizon->SetDispParamData(&param);
}


void MainWindow::on_PaletteControl_Fake_Open_clicked()
{
    if (ui->checkBox_HorizontalLayout->isChecked()) {
        m_panel_window->AttachPanelControl(m_palette_control);
    } else {
        m_panel_window->AttachPanelControl(m_palette_control);
    }
    m_panel_window->show();
    m_panel_window->raise();
}

