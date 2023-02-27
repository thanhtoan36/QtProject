#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colorPickerControl/colorPickerControlHorizon.h"
#include "colorPickerControl/colorPickerControl.h"
#include "trackControl/trackControl.h"
#include "trackControl/trackControlHorizon.h"
#include "intensityControl/intensityControl.h"
#include "utility.h"

#include <cstring>
#include <cmath>
#include <QDebug>
#include <QRandomGenerator>

#include "testDataParser.h"
#include <QDateTime>

QRandomGenerator gRandom;

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
{
    ui->setupUi( this );

    m_color_picker_control = MakeSharedQObject<ColorPickerControl>();
    m_color_picker_control_horizon = MakeSharedQObject<ColorPickerControlHorizon>();

    m_track_control = MakeSharedQObject<TrackControl>();
    m_track_control_horizon = MakeSharedQObject<TrackControlHorizon>();

    m_intensity_control = MakeSharedQObject<IntensityControl>();
    m_intensity_control_horizon = MakeSharedQObject<IntensityControlHorizon>();

    m_encoder_control = MakeSharedQObject<EncoderControl>();
    m_encoder_control_horizon = MakeSharedQObject<EncoderControlHorizon>();

    m_color_filter_control = MakeSharedQObject<ColorFilterControl>();
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

    ConnectColorFilterEvent();
    ConnectColorPickerEvent();
    ConnectIntensityEvent();
    ConnectInputNumEvent();
    ConnectPaletteEvent();
    ConnectEncoderEvent();
    ConnectGroupEvent();
    ConnectLibraryEvent();
    ConnectTrackEvent();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LogEvent( const QString &log )
{
    const QString TIME_FORMAT = "HH:mm:ss.zzz";
    const auto time = QTime::currentTime().toString( TIME_FORMAT );
    ui->EventOutput->appendPlainText( QString( "[%1 %2] %3" ).arg( time,  sender()->metaObject()->className(), log) );
}

void MainWindow::ConnectColorPickerEvent()
{
    const auto slot_color_changed = [&]() { LogEvent( QString( "color changed: %1" ).arg( ( ( ColorPickerControl * )sender() )->PickerColor().name() ) ); };
    const auto slot_picker_type_changed = [&]()
    {
        const QStringList types = {"COLOR_PICKER_TYPE_XY", "COLOR_PICKER_TYPE_RGB"};
        LogEvent( QString( "picker type changed: %1" ).arg( types[( ( ColorPickerControl * )sender() )->PickerType()] ) );
    };
    const auto slot_next_clicked = [&]() { LogEvent( QString( "next clicked" ) ); };
    const auto slot_prev_clicked = [&]() { LogEvent( QString( "prev clicked" ) ); };

    connect( m_color_picker_control.get(), &ColorPickerControl::PickerColorChanged, this, slot_color_changed );
    connect( m_color_picker_control.get(), &ColorPickerControl::PickerTypeChanged, this, slot_picker_type_changed );
    connect( m_color_picker_control.get(), &ColorPickerControl::NextButtonClicked, this, slot_next_clicked );
    connect( m_color_picker_control.get(), &ColorPickerControl::PrevButtonClicked, this, slot_prev_clicked );

    connect( m_color_picker_control_horizon.get(), &ColorPickerControl::PickerColorChanged, this, slot_color_changed );
    connect( m_color_picker_control_horizon.get(), &ColorPickerControl::PickerTypeChanged, this, slot_picker_type_changed );
    connect( m_color_picker_control_horizon.get(), &ColorPickerControl::NextButtonClicked, this, slot_next_clicked );
    connect( m_color_picker_control_horizon.get(), &ColorPickerControl::PrevButtonClicked, this, slot_prev_clicked );
}

void MainWindow::ConnectColorFilterEvent()
{
    const auto slot_tb_selected_button_changed = [&]()
    {
        QString log = "TB Tab Button Active Changed: ";
        auto button_active = ( ( ColorFilterControl * )sender() )->SelectedTbButton();
        log += QString( "(text: %1, %2)" ).arg( button_active.text ).arg( button_active.color.name() );
        LogEvent( log );
    };

    const auto slot_custom_selected_button_changed = [&]()
    {
        QString log = "Custom Tab Button Active Changed: ";
        auto button_active = ( ( ColorFilterControl * )sender() )->SelectedCustomButton();
        log += QString( "(text: %1, %2)" ).arg( button_active.text ).arg( button_active.color.name() );
        LogEvent( log );
    };

    const auto slot_history_selected_button_changed = [&]()
    {
        QString log = "History Button Active Changed: ";
        auto button_active = ( ( ColorFilterControl * )sender() )->SelectedHistoryButton();
        log += QString( "(text: %1, %2)" ).arg( button_active.text ).arg( button_active.color.name() );
        LogEvent( log );
    };

    const auto slot_footer_button_changed = [&]()
    {
        QString log = QString( "Footer Button Active Changed: %1" ).arg( ( ( ColorFilterControl * )sender() )->SelectedFooterButton() );
        LogEvent( log );
    };

    const auto slot_return_button_clicked = [&]() { LogEvent( "Return Button Clicked" ); };
    const auto slot_next_clicked = [&]() { LogEvent( QString( "next clicked" ) ); };
    const auto slot_prev_clicked = [&]() { LogEvent( QString( "prev clicked" ) ); };

    connect( m_color_filter_control.get(), &ColorFilterControl::SelectedTbButtonChanged, this, slot_tb_selected_button_changed );
    connect( m_color_filter_control.get(), &ColorFilterControl::SelectedCustomButtonChanged, this, slot_custom_selected_button_changed );
    connect( m_color_filter_control.get(), &ColorFilterControl::SelectedHistoryButtonChanged, this, slot_history_selected_button_changed );
    connect( m_color_filter_control.get(), &ColorFilterControl::SelectedFooterButtonChanged, this, slot_footer_button_changed );
    connect( m_color_filter_control.get(), &ColorFilterControl::ReturnButtonClicked, this, slot_return_button_clicked );
    connect( m_color_filter_control.get(), &ColorFilterControl::NextButtonClicked, this, slot_next_clicked );
    connect( m_color_filter_control.get(), &ColorFilterControl::PrevButtonClicked, this, slot_prev_clicked );

    connect( m_color_filter_control_horizon.get(), &ColorFilterControl::SelectedTbButtonChanged, this, slot_tb_selected_button_changed );
    connect( m_color_filter_control_horizon.get(), &ColorFilterControl::SelectedCustomButtonChanged, this, slot_custom_selected_button_changed );
    connect( m_color_filter_control_horizon.get(), &ColorFilterControl::SelectedHistoryButtonChanged, this, slot_history_selected_button_changed );
    connect( m_color_filter_control_horizon.get(), &ColorFilterControl::SelectedFooterButtonChanged, this, slot_footer_button_changed );
    connect( m_color_filter_control_horizon.get(), &ColorFilterControl::ReturnButtonClicked, this, slot_return_button_clicked );
    connect( m_color_filter_control_horizon.get(), &ColorFilterControl::NextButtonClicked, this, slot_next_clicked );
    connect( m_color_filter_control_horizon.get(), &ColorFilterControl::PrevButtonClicked, this, slot_prev_clicked );
}

void MainWindow::ConnectIntensityEvent()
{
    const auto slot_intensity_button_clicked = [&]( const QString & name )
    {
        QString log = QString( "Button %1 Clicked" ).arg( name );
        LogEvent( log );
    };

    const auto slot_return_button_clicked = [&]() { LogEvent( "Return Button Clicked" ); };

    connect( m_intensity_control.get(), &IntensityControl::IntensityButtonClicked, this, slot_intensity_button_clicked );
    connect( m_intensity_control.get(), &IntensityControl::ReturnButtonClicked, this, slot_return_button_clicked );

    connect( m_intensity_control_horizon.get(), &IntensityControl::IntensityButtonClicked, this, slot_intensity_button_clicked );
    connect( m_intensity_control_horizon.get(), &IntensityControl::ReturnButtonClicked, this, slot_return_button_clicked );
}

void MainWindow::ConnectInputNumEvent()
{
    const auto slot_mode_changed = [&]()
    {
        auto mode = ( ( InputNumControl * )sender() )->Mode();
        QStringList modes = {"INPUT_NUM_MODE_PERCENT", "INPUT_NUM_MODE_255", "INPUT_NUM_MODE_ANGLE"};
        LogEvent( QString( "Mode: %1" ).arg( modes[mode] ) );
    };

    const auto slot_value_mode_changed = [&]()
    {
        auto mode = ( ( InputNumControl * )sender() )->ValueMode();
        QStringList modes = {"INPUT_NUM_MODE_RELATIVE", "INPUT_NUM_MODE_ABSOLUTE"};
        LogEvent( QString( "ValueMode: %1" ).arg( modes[mode] ) );
    };

    const auto slot_selected_mode_changed = [&]()
    {
        QString log = "Button Mode Changed: " + ( ( InputNumControl * )sender() )->SelectedModeButton();
        LogEvent( log );
    };

    const auto slot_num_button_clicked = [&]( const QString & text ) { LogEvent( "Button Clicked: " + text ); };
    const auto slot_return_clicked = [&]() { LogEvent( "Return clicked" ); };

    connect( m_input_num_control.get(), &InputNumControl::ModeChanged, this, slot_mode_changed );
    connect( m_input_num_control.get(), &InputNumControl::ValueModeChanged, this, slot_value_mode_changed );
    connect( m_input_num_control.get(), &InputNumControl::InputNumButtonClicked, this, slot_num_button_clicked );
    connect( m_input_num_control.get(), &InputNumControl::SelectedModeButtonChanged, this, slot_selected_mode_changed );
    connect( m_input_num_control.get(), &InputNumControl::ReturnClicked, this, slot_return_clicked );

    connect( m_input_num_control_horizon.get(), &InputNumControl::ModeChanged, this, slot_mode_changed );
    connect( m_input_num_control_horizon.get(), &InputNumControl::ValueModeChanged, this, slot_value_mode_changed );
    connect( m_input_num_control_horizon.get(), &InputNumControl::InputNumButtonClicked, this, slot_num_button_clicked );
    connect( m_input_num_control_horizon.get(), &InputNumControl::SelectedModeButtonChanged, this, slot_selected_mode_changed );
    connect( m_input_num_control_horizon.get(), &InputNumControl::ReturnClicked, this, slot_return_clicked );
}

void MainWindow::ConnectPaletteEvent()
{
    const auto slot_mode_changed = [&]()
    {
        LogEvent( "mode changed: " + ( ( PaletteControl * )sender() )->SelectedMode() );
    };
    const auto slot_palette_changed = [&]()
    {
        LogEvent( "palette changed: " + ( ( PaletteControl * )sender() )->SelectedPalette() );
    };
    const auto slot_next_mode_page_clicked = [&]() { LogEvent( "next mode page" ); };
    const auto slot_prev_mode_page_clicked = [&]() { LogEvent( "prev mode page" ); };
    const auto slot_next_palette_page_clicked = [&]() { LogEvent( "next palette page" ); };
    const auto slot_prev_palette_page_clicked = [&]() { LogEvent( "prev palette page" ); };
    const auto slot_return_clicked = [&]() { LogEvent( "Return clicked" ); };

    connect( m_palette_control.get(), &PaletteControl::SelectedModeChanged, this, slot_mode_changed );
    connect( m_palette_control.get(), &PaletteControl::SelectedPaletteChanged, this, slot_palette_changed );
    connect( m_palette_control.get(), &PaletteControl::NextModePageClicked, this, slot_next_mode_page_clicked );
    connect( m_palette_control.get(), &PaletteControl::PrevModePageClicked, this, slot_prev_mode_page_clicked );
    connect( m_palette_control.get(), &PaletteControl::NextPalettePageClicked, this, slot_next_palette_page_clicked );
    connect( m_palette_control.get(), &PaletteControl::PrevPalettePageClicked, this, slot_prev_palette_page_clicked );
    connect( m_palette_control.get(), &PaletteControl::ReturnButtonClicked, this, slot_return_clicked );

    connect( m_palette_control_horizon.get(), &PaletteControl::SelectedModeChanged, this, slot_mode_changed );
    connect( m_palette_control_horizon.get(), &PaletteControl::SelectedPaletteChanged, this, slot_palette_changed );
    connect( m_palette_control_horizon.get(), &PaletteControl::NextModePageClicked, this, slot_next_mode_page_clicked );
    connect( m_palette_control_horizon.get(), &PaletteControl::PrevModePageClicked, this, slot_prev_mode_page_clicked );
    connect( m_palette_control_horizon.get(), &PaletteControl::NextPalettePageClicked, this, slot_next_palette_page_clicked );
    connect( m_palette_control_horizon.get(), &PaletteControl::PrevPalettePageClicked, this, slot_prev_palette_page_clicked );
    connect( m_palette_control_horizon.get(), &PaletteControl::ReturnButtonClicked, this, slot_return_clicked );
}

void MainWindow::ConnectEncoderEvent()
{
    const auto slot_mode_changed = [&]()
    {
        QStringList modes = { "ENCODER_MODE_PERCENT", "ENCODER_MODE_255", "ENCODER_MODE_ANGLE", };
        LogEvent( "mode changed: " + modes[( ( EncoderControl * )sender() )->Mode()] );
    };

    const auto slot_encoder_value_changed = [&]( int index, const QString & name, int value )
    {
        LogEvent( QString( "Encoder #%1 (%2) value changed %3" ).arg( index ).arg( name ).arg( value ) );
        const auto encoders = ( ( EncoderControl * )sender() )->Encoders();

        QString log = "All encoders: ";

        for( const auto &e : encoders )
        {
            log += QString( "(%1 %2), " ).arg( QString( e.name ) ).arg( e.level );
        }

        LogEvent( log );
    };

    connect( m_encoder_control.get(), &EncoderControl::ModeChanged, this, slot_mode_changed );
    connect( m_encoder_control.get(), &EncoderControl::EncoderValueChanged, this, slot_encoder_value_changed );

    connect( m_encoder_control_horizon.get(), &EncoderControl::ModeChanged, this, slot_mode_changed );
    connect( m_encoder_control_horizon.get(), &EncoderControl::EncoderValueChanged, this, slot_encoder_value_changed );
}

void MainWindow::ConnectTrackEvent()
{
    const auto slot_track_points_changed = [&]()
    {
        QString log = "track points changed\n";
        auto points = ( ( TrackControl * )sender() )->TrackPoints();

        for( const auto &p : points )
        {
            log += QString( "(%1,%2), " ).arg( p.pan.current ).arg( p.tilt.current );
        }

        LogEvent( log );
    };

    connect( m_track_control.get(), &TrackControl::TrackPointsChanged, this, slot_track_points_changed );
    connect( m_track_control_horizon.get(), &TrackControl::TrackPointsChanged, this, slot_track_points_changed );
}

void MainWindow::ConnectGroupEvent()
{
    const auto slot_group_button_changed = [&]()
    {
        QString log = "button changed: ";
        auto button = ( ( GroupControl * )sender() )->CurrentGroupButton();

        log += QString( "text: %1, title: %2" ).arg( button.text ).arg( button.title );

        LogEvent( log );
    };

    const auto slot_history_button_changed = [&]()
    {
        QString log = "history button changed: ";
        auto button = ( ( GroupControl * )sender() )->CurrentHistoryButton();

        log += QString( "text: %1, title: %2" ).arg( button.text ).arg( button.title );

        LogEvent( log );
    };
    const auto slot_return_button_clicked = [&]()
    {
        QString log = "return button clicked";

        LogEvent( log );
    };
    const auto slot_footer_button_changed = [&]()
    {
        QString log = "footer button changed: " + ( ( GroupControl * )sender() )->CurrentFooterButton();

        LogEvent( log );
    };

    connect( m_group_control.get(), &GroupControl::CurrentGroupButtonChanged, this, slot_group_button_changed );
    connect( m_group_control_horizon.get(), &GroupControl::CurrentGroupButtonChanged, this, slot_group_button_changed );
    connect( m_group_control.get(), &GroupControl::CurrentHistoryButtonChanged, this, slot_history_button_changed );
    connect( m_group_control_horizon.get(), &GroupControl::CurrentHistoryButtonChanged, this, slot_history_button_changed );
    connect( m_group_control.get(), &GroupControl::ReturnButtonClicked, this, slot_return_button_clicked );
    connect( m_group_control_horizon.get(), &GroupControl::ReturnButtonClicked, this, slot_return_button_clicked );
    connect( m_group_control.get(), &GroupControl::CurrentFooterButtonChanged, this, slot_footer_button_changed );
    connect( m_group_control_horizon.get(), &GroupControl::CurrentFooterButtonChanged, this, slot_footer_button_changed );
}

void MainWindow::ConnectLibraryEvent()
{
    const auto slot_mode_button_changed = [&]()
    {
        QString log = "mode button changed: " + ( ( LibraryControl * )sender() )->SelectedModeButton();

        LogEvent( log );
    };

    const auto slot_history_mode_button_changed = [&]()
    {
        QString log = "history mode button changed: " + ( ( LibraryControl * )sender() )->SelectedHistoryModeButton();

        LogEvent( log );
    };

    const auto slot_library_button_changed = [&]()
    {
        QString log = "library button changed: ";
        auto button = ( ( LibraryControl * )sender() )->SelectedLibraryButton();

        log += QString( "text: %1, title: %2" ).arg( button.text ).arg( button.title );

        LogEvent( log );
    };

    const auto slot_history_button_changed = [&]()
    {
        QString log = "history button changed: ";
        auto button = ( ( LibraryControl * )sender() )->SelectedHistoryButton();

        log += QString( "text: %1, title: %2" ).arg( button.text ).arg( button.title );

        LogEvent( log );
    };

    const auto slot_return_button_clicked = [&]()
    {
        QString log = "return button clicked";

        LogEvent( log );
    };
    const auto slot_footer_button_changed = [&]()
    {
        QString log = "footer button changed: " + ( ( LibraryControl * )sender() )->SelectedFooterButton();

        LogEvent( log );
    };

    connect( m_library_control.get(), &LibraryControl::SelectedModeButtonChanged, this, slot_mode_button_changed );
    connect( m_library_control_horizon.get(), &LibraryControl::SelectedModeButtonChanged, this, slot_mode_button_changed );

    connect( m_library_control.get(), &LibraryControl::SelectedHistoryModeButtonChanged, this, slot_history_mode_button_changed );
    connect( m_library_control_horizon.get(), &LibraryControl::SelectedHistoryModeButtonChanged, this, slot_history_mode_button_changed );

    connect( m_library_control.get(), &LibraryControl::SelectedLibraryButtonChanged, this, slot_library_button_changed );
    connect( m_library_control_horizon.get(), &LibraryControl::SelectedLibraryButtonChanged, this, slot_library_button_changed );

    connect( m_library_control.get(), &LibraryControl::SelectedHistoryButtonChanged, this, slot_history_button_changed );
    connect( m_library_control_horizon.get(), &LibraryControl::SelectedHistoryButtonChanged, this, slot_history_button_changed );

    connect( m_library_control.get(), &LibraryControl::SelectedFooterButtonChanged, this, slot_footer_button_changed );
    connect( m_library_control_horizon.get(), &LibraryControl::SelectedFooterButtonChanged, this, slot_footer_button_changed );

    connect( m_library_control.get(), &LibraryControl::ReturnButtonClicked, this, slot_return_button_clicked );
    connect( m_library_control_horizon.get(), &LibraryControl::ReturnButtonClicked, this, slot_return_button_clicked );

}

void MainWindow::on_ColorPickerControl_Fake_Open_clicked()
{
    if( ui->checkBox_HorizontalLayout->isChecked() )
    {
        m_panel_window->AttachPanelControl( m_color_picker_control_horizon );
    }
    else
    {
        m_panel_window->AttachPanelControl( m_color_picker_control );
    }

    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_TrackControl_Fake_Open_clicked()
{
    if( ui->checkBox_HorizontalLayout->isChecked() )
    {
        m_panel_window->AttachPanelControl( m_track_control_horizon );
    }
    else
    {
        m_panel_window->AttachPanelControl( m_track_control );
    }

    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_IntensityControl_Fake_Open_clicked()
{
    if( ui->checkBox_HorizontalLayout->isChecked() )
    {
        m_panel_window->AttachPanelControl( m_intensity_control_horizon );
    }
    else
    {
        m_panel_window->AttachPanelControl( m_intensity_control );
    }

    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_EncoderControl_Fake_Open_clicked()
{
    if( ui->checkBox_HorizontalLayout->isChecked() )
    {
        m_panel_window->AttachPanelControl( m_encoder_control_horizon );
    }
    else
    {
        m_panel_window->AttachPanelControl( m_encoder_control );
    }

    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_ColorFilterControl_Fake_Open_clicked()
{
    if( ui->checkBox_HorizontalLayout->isChecked() )
    {
        m_panel_window->AttachPanelControl( m_color_filter_control_horizon );
    }
    else
    {
        m_panel_window->AttachPanelControl( m_color_filter_control );
    }

    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_InputNumControl_Fake_Open_clicked()
{
    if( ui->checkBox_HorizontalLayout->isChecked() )
    {
        m_panel_window->AttachPanelControl( m_input_num_control_horizon );
    }
    else
    {
        m_panel_window->AttachPanelControl( m_input_num_control );
    }

    m_panel_window->show();
    m_panel_window->raise();
}

void MainWindow::on_PlaybackControl_Fake_Open_clicked()
{
    if( ui->checkBox_HorizontalLayout->isChecked() )
    {
        m_panel_window->AttachPanelControl( m_playback_control_horizon );
    }
    else
    {
        m_panel_window->AttachPanelControl( m_playback_control );
    }

    m_panel_window->show();
    m_panel_window->raise();
}

void MainWindow::on_GroupPanelControl_Fake_Open_clicked()
{
    if( !ui->checkBox_HorizontalLayout->isChecked() )
    {
        m_panel_window->AttachPanelControl( m_group_control );
    }
    else
    {
        m_panel_window->AttachPanelControl( m_group_control_horizon );
    }

    m_panel_window->show();
    m_panel_window->raise();
}


void MainWindow::on_BtnClear_clicked()
{
    ui->EventOutput->clear();
}

void MainWindow::on_LibraryControl_Fake_Open_clicked()
{
    if( !ui->checkBox_HorizontalLayout->isChecked() )
    {
        m_panel_window->AttachPanelControl( m_library_control );
    }
    else
    {
        m_panel_window->AttachPanelControl( m_library_control_horizon );
    }

    m_panel_window->show();
    m_panel_window->raise();
}

void MainWindow::on_InputNumControl_Fake_Set_clicked()
{
    INPUT_NUM_DISP_PARAM param = ParseInput_InputNum( ui->InputNumControl_Fake_RawInput->toPlainText() );

    m_input_num_control_horizon->SetDispParamData( &param );
    m_input_num_control->SetDispParamData( &param );
}


void MainWindow::on_ColorPickerControl_Fake_Set_clicked()
{
    COLOR_PICKER_DISP_PARAM params = ParseInput_ColorPicker( ui->ColorPickerControl_RawInput->toPlainText() );

    m_color_picker_control_horizon->SetDispParamData( &params );
    m_color_picker_control->SetDispParamData( &params );
}


void MainWindow::on_ColorFilterControl_Fake_Set_clicked()
{
    COLOR_FILTER_DISP_PARAM param = ParseInput_ColorFilter( ui->ColorFilterControl_RawInput->toPlainText() );

    m_color_filter_control_horizon->setDispParamData( &param );
    m_color_filter_control->setDispParamData( &param );
}


void MainWindow::on_EncoderControl_Fake_Set_clicked()
{
    ENCODER_DISP_PARAM params = ParseInput_Encoder( ui->EncoderControl_RawInput->toPlainText() );

    m_encoder_control_horizon->SetDispParamData( &params );
    m_encoder_control->SetDispParamData( &params );
}


void MainWindow::on_TrackControl_Fake_Set_clicked()
{
    TRACK_DISP_PARAM params = ParseInput_Track( ui->TrackControl_RawInput->toPlainText() );

    m_track_control_horizon->SetDispParamData( &params );
    m_track_control->SetDispParamData( &params );
}

void MainWindow::on_PlaybackControl_Fake_Set_clicked()
{
    PLAYBACK_DISP_PARAM params = ParseInput_Playback( ui->PlaybackControl_Fake_RawInput->toPlainText() );
    m_playback_control_horizon->SetDispParamData( &params );
    m_playback_control->SetDispParamData( &params );
}


void MainWindow::on_LibraryControl_Fake_Set_clicked()
{
    LIBRARY_DISP_PARAM params = ParseInput_Library( ui->LibraryControl_Fake_RawInput->toPlainText() );
    m_library_control_horizon->SetDispParamData( &params );
    m_library_control->SetDispParamData( &params );
}


void MainWindow::on_GroupPanelControl_Fake_Set_clicked()
{
    GROUP_DISP_PARAM param = ParseInput_Group( ui->GroupPanelControl_Fake_RawInput->toPlainText() );
    m_group_control->SetDispParamData( &param );
    m_group_control_horizon->SetDispParamData( &param );
}


void MainWindow::on_PaletteControl_Fake_Set_clicked()
{
    PALETTE_DISP_PARAM param = ParseInput_Palette( ui->PaletteControl_Fake_RawInput->toPlainText() );
    m_palette_control->SetDispParamData( &param );
    m_palette_control_horizon->SetDispParamData( &param );
}


void MainWindow::on_PaletteControl_Fake_Open_clicked()
{
    if( ui->checkBox_HorizontalLayout->isChecked() )
    {
        m_panel_window->AttachPanelControl( m_palette_control_horizon );
    }
    else
    {
        m_panel_window->AttachPanelControl( m_palette_control );
    }

    m_panel_window->show();
    m_panel_window->raise();
}

