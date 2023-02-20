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
    m_color_picker_control_horizon = MakeSharedQObject<ColorPickerControlHorizon>();

    m_track_control = MakeSharedQObject<TrackControl>();
    m_track_control_horizon = MakeSharedQObject<TrackControlHorizon>();

    m_intensity_control = MakeSharedQObject<IntensityControl>();
    m_intensity_control_horizon = MakeSharedQObject<IntensityControlHorizon>();

    m_encoder_control = MakeSharedQObject<EncoderControl>();
    m_encoder_control_horizon = MakeSharedQObject<EncoderControlHorizon>();

    m_color_filter_control= MakeSharedQObject<ColorFilterControl>();
    m_color_filter_control_horizon = MakeSharedQObject<ColorFilterControlHorizon>();

    m_input_num_control = MakeSharedQObject<InputNumControl>();
    m_input_num_control_horizon = MakeSharedQObject<InputNumControlHorizon>();

    m_group_control = MakeSharedQObject<GroupControl>();
    m_group_control_horizon = MakeSharedQObject<GroupControlHorizon>();

    m_library_control = MakeSharedQObject<LibraryControl>();
    m_library_control_horizon = MakeSharedQObject<LibraryControlHorizon>();

    m_playback_control = MakeSharedQObject<PlaybackControl>();
    m_playback_control_horizon = MakeSharedQObject<PlaybackControlHorizon>();

    m_palette_control = MakeSharedQObject<PaletteControl>();
    m_palette_control_horizon = MakeSharedQObject<PaletteControlHorizon>();

    connect(m_track_control.get(), &TrackControl::trackPointsChanged, this, &MainWindow::TC_OnTrackPointsChanged);
    connect(m_track_control_horizon.get(), &TrackControl::trackPointsChanged, this, &MainWindow::TC_OnTrackPointsChanged);

    ConnectColorFilterEvent();
    ConnectColorPickerEvent();
    ConnectIntensityEvent();
    ConnectInputNumEvent();
    ConnectPaletteEvent();
    ConnectEncoderEvent();
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

void MainWindow::ConnectColorPickerEvent()
{
    connect(m_color_picker_control.get(), &ColorPickerControl::pickerColorChanged, this, &MainWindow::CPC_OnColorChanged);
    connect(m_color_picker_control_horizon.get(), &ColorPickerControl::pickerColorChanged, this, &MainWindow::CPC_OnColorChanged);
}

void MainWindow::ConnectColorFilterEvent()
{
    connect(m_color_filter_control.get(), &ColorFilterControl::currentTBTabButtonActiveChanged, this, &MainWindow::CFC_OnTBTabButtonActiveChanged);
    connect(m_color_filter_control_horizon.get(), &ColorFilterControl::currentTBTabButtonActiveChanged, this, &MainWindow::CFC_OnTBTabButtonActiveChanged);
    connect(m_color_filter_control.get(), &ColorFilterControl::currentCustomTabButtonActiveChanged, this, &MainWindow::CFC_OnCustomTabButtonActiveChanged);
    connect(m_color_filter_control_horizon.get(), &ColorFilterControl::currentCustomTabButtonActiveChanged, this, &MainWindow::CFC_OnCustomTabButtonActiveChanged);
    connect(m_color_filter_control.get(), &ColorFilterControl::currentHistoryButtonActiveChanged, this, &MainWindow::CFC_OnHistoryButtonActiveChanged);
    connect(m_color_filter_control_horizon.get(), &ColorFilterControl::currentHistoryButtonActiveChanged, this, &MainWindow::CFC_OnHistoryButtonActiveChanged);
    connect(m_color_filter_control.get(), &ColorFilterControl::ReturnButtonClicked, this, &MainWindow::CFC_OnReturnButtonClicked);
    connect(m_color_filter_control_horizon.get(), &ColorFilterControl::ReturnButtonClicked, this, &MainWindow::CFC_OnReturnButtonClicked);
}

void MainWindow::ConnectIntensityEvent()
{
    connect(m_intensity_control.get(), &IntensityControl::returnButtonClicked, this, &MainWindow::IC_OnReturnButtonClicked);
    connect(m_intensity_control_horizon.get(), &IntensityControl::returnButtonClicked, this, &MainWindow::IC_OnReturnButtonClicked);

    connect(m_intensity_control.get(), &IntensityControl::IntensityButtonClicked, this, &MainWindow::IC_OnIntensityButtonClicked);
    connect(m_intensity_control_horizon.get(), &IntensityControl::IntensityButtonClicked, this, &MainWindow::IC_OnIntensityButtonClicked);
}

void MainWindow::ConnectInputNumEvent()
{
    const auto slot_mode_changed = [&]() {
        QString log = "IC Mode Changed: ";
        auto mode = ((InputNumControl*)sender())->mode();

        if (mode == INPUT_NUM_MODE_PERCENT)
        {
            log+= "PERCENT";
        }
        else if(mode == INPUT_NUM_MODE_255)
        {
            log+= "255";
        }
        else
        {
            log+= "ANGEL";
        }

        this->logEvent(log);
    };

    const auto slot_value_mode_changed = [&]() {
        QString log = "IC Value Mode Changed: ";
        auto mode = ((InputNumControl*)sender())->valueMode();

        if (mode == INPUT_NUM_MODE_RELATIVE)
        {
            log+= "RELATIVE";
        }
        else
        {
            log+= "ABSOLUTE";
        }

        this->logEvent(log);
    };

    const auto slot_num_button_clicked = [&](const QString &text) {
        QString log = "IC Button Clicked: " + text;
        this->logEvent(log);
    };

    const auto slot_current_mode_changed = [&]() {
        QString log = "IC Button Mode Changed: " + ((InputNumControl*)sender())->CurrentModeButton();
        this->logEvent(log);
    };

    const auto slot_return_clicked = [&]() {
        QString log = "IC Return clicked";
        this->logEvent(log);
    };

    connect(m_input_num_control.get(),&InputNumControl::modeChanged, this, slot_mode_changed);
    connect(m_input_num_control.get(),&InputNumControl::valueModeChanged, this, slot_value_mode_changed);
    connect(m_input_num_control.get(),&InputNumControl::InputNumButtonClicked, this, slot_num_button_clicked);
    connect(m_input_num_control.get(),&InputNumControl::CurrentModeButtonChanged, this, slot_current_mode_changed);
    connect(m_input_num_control.get(),&InputNumControl::ReturnClicked, this, slot_return_clicked);

    connect(m_input_num_control_horizon.get(),&InputNumControl::modeChanged, this, slot_mode_changed);
    connect(m_input_num_control_horizon.get(),&InputNumControl::valueModeChanged, this, slot_value_mode_changed);
    connect(m_input_num_control_horizon.get(),&InputNumControl::InputNumButtonClicked, this, slot_num_button_clicked);
    connect(m_input_num_control_horizon.get(),&InputNumControl::CurrentModeButtonChanged, this, slot_current_mode_changed);
    connect(m_input_num_control_horizon.get(),&InputNumControl::ReturnClicked, this, slot_return_clicked);
}

void MainWindow::ConnectPaletteEvent()
{
    const auto slot_mode_changed = [&](){
        logEvent("Palette mode changed: " + ((PaletteControl*)sender())->selectedMode());
    };
    const auto slot_palette_changed = [&](){
        logEvent("Palette palette changed: " + ((PaletteControl*)sender())->selectedPalette());
    };
    const auto slot_next_mode_page_clicked = [&](){ logEvent("Palette next mode page"); };
    const auto slot_prev_mode_page_clicked = [&](){ logEvent("Palette prev mode page"); };
    const auto slot_next_palette_page_clicked = [&](){ logEvent("Palette next palette page"); };
    const auto slot_prev_palette_page_clicked = [&](){ logEvent("Palette prev palette page"); };

    connect(m_palette_control.get(),&PaletteControl::selectedModeChanged, this, slot_mode_changed);
    connect(m_palette_control.get(),&PaletteControl::selectedPaletteChanged, this, slot_palette_changed);
    connect(m_palette_control.get(),&PaletteControl::NextModePageClicked, this, slot_next_mode_page_clicked);
    connect(m_palette_control.get(),&PaletteControl::PrevModePageClicked, this, slot_prev_mode_page_clicked);
    connect(m_palette_control.get(),&PaletteControl::NextPalettePageClicked, this, slot_next_palette_page_clicked);
    connect(m_palette_control.get(),&PaletteControl::PrevPalettePageClicked, this, slot_prev_palette_page_clicked);

    connect(m_palette_control_horizon.get(),&PaletteControl::selectedModeChanged, this, slot_mode_changed);
    connect(m_palette_control_horizon.get(),&PaletteControl::selectedPaletteChanged, this, slot_palette_changed);
    connect(m_palette_control_horizon.get(),&PaletteControl::NextModePageClicked, this, slot_next_mode_page_clicked);
    connect(m_palette_control_horizon.get(),&PaletteControl::PrevModePageClicked, this, slot_prev_mode_page_clicked);
    connect(m_palette_control_horizon.get(),&PaletteControl::NextPalettePageClicked, this, slot_next_palette_page_clicked);
    connect(m_palette_control_horizon.get(),&PaletteControl::PrevPalettePageClicked, this, slot_prev_palette_page_clicked);
}

void MainWindow::ConnectEncoderEvent()
{
    const auto slot_mode_changed = [&](){
        QStringList modes = { "ENCODER_MODE_PERCENT", "ENCODER_MODE_255", "ENCODER_MODE_ANGLE", };
        logEvent("Encoder mode changed: " + modes[((EncoderControl*)sender())->mode()]);
    };

    connect(m_encoder_control.get(),&EncoderControl::modeChanged, this, slot_mode_changed);

    connect(m_encoder_control_horizon.get(),&EncoderControl::modeChanged, this, slot_mode_changed);
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

void MainWindow::TC_OnTrackPointsChanged()
{
    QString log = "TC points changed\n";
    auto points = ((TrackControl*)sender())->trackPoints();

    for (const auto &p : points) {
        log += QString("(%1,%2), ").arg(p.pan.current).arg(p.tilt.current);
    }

    logEvent(log);
}

void MainWindow::CFC_OnTBTabButtonActiveChanged()
{
    QString log = "CFC TB Tab Button Active Changed: ";
    auto button_active = ((ColorFilterControl*)sender())->currentTBTabButtonActive();

    log += QString("(text: %1,RGB:(%2, %3, %4))").arg(button_active.text).arg(button_active.color.red()).arg(button_active.color.green()).arg(button_active.color.blue());

    logEvent(log);
}

void MainWindow::CFC_OnCustomTabButtonActiveChanged()
{
    QString log = "CFC Custom Tab Button Active Changed: ";
    auto button_active = ((ColorFilterControl*)sender())->currentCustomTabButtonActive();

    log += QString("(text: %1, RGB:(%2, %3, %4))").arg(button_active.text).arg(button_active.color.red()).arg(button_active.color.green()).arg(button_active.color.blue());

    logEvent(log);
}

void MainWindow::CFC_OnHistoryButtonActiveChanged()
{
    QString log = "CFC History Button Active Changed: ";
    auto button_active = ((ColorFilterControl*)sender())->currentHistoryButtonActive();

    log += QString("(text: %1,RGB:(%2, %3, %4))").arg(button_active.text).arg(button_active.color.red()).arg(button_active.color.green()).arg(button_active.color.blue());

    logEvent(log);
}

void MainWindow::CFC_OnReturnButtonClicked()
{
    QString log = "CFC Return Button Clicked";

    logEvent(log);
}

void MainWindow::IC_OnIntensityButtonClicked(const QString &text)
{
    QString log = QString("IC Button %1 Clicked").arg(text);
    logEvent(log);
}

void MainWindow::IC_OnReturnButtonClicked()
{
    QString log = "IC Return Button Clicked";
    logEvent(log);
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

    m_input_num_control_horizon->SetDispParamData(&param);
    m_input_num_control->SetDispParamData(&param);
}


void MainWindow::on_ColorPickerControl_Fake_Set_clicked()
{
    COLOR_PICKER_DISP_PARAM params = CPC_ParseInput(ui->ColorPickerControl_RawInput->toPlainText());

    m_color_picker_control_horizon->SetDispParamData(&params);
    m_color_picker_control->SetDispParamData(&params);
}


void MainWindow::on_ColorFilterControl_Fake_Set_clicked()
{
    COLOR_FILTER_DISP_PARAM param = CFC_ParseInput(ui->ColorFilterControl_RawInput->toPlainText());

    m_color_filter_control_horizon->setDispParamData(&param);
    m_color_filter_control->setDispParamData(&param);
}


void MainWindow::on_EncoderControl_Fake_Set_clicked()
{
    ENCODER_DISP_PARAM params = EC_ParseInput(ui->EncoderControl_RawInput->toPlainText());

    m_encoder_control_horizon->SetDispParamData(&params);
    m_encoder_control->SetDispParamData(&params);
}


void MainWindow::on_TrackControl_Fake_Set_clicked()
{
    TRACK_DISP_PARAM params = TC_ParseInput(ui->TrackControl_RawInput->toPlainText());

    m_track_control_horizon->SetDispParamData(&params);
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
    m_group_control_horizon->SetDispParamData(&param);
}


void MainWindow::on_PaletteControl_Fake_Set_clicked()
{
    PALETTE_DISP_PARAM param = PD_ParseInput(ui->PaletteControl_Fake_RawInput->toPlainText());
    m_palette_control->SetDispParamData(&param);
    m_palette_control_horizon->SetDispParamData(&param);
}


void MainWindow::on_PaletteControl_Fake_Open_clicked()
{
    if (ui->checkBox_HorizontalLayout->isChecked()) {
        m_panel_window->AttachPanelControl(m_palette_control_horizon);
    } else {
        m_panel_window->AttachPanelControl(m_palette_control);
    }
    m_panel_window->show();
    m_panel_window->raise();
}

