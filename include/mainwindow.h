#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "baseComponent/panelWindow.h"

#include "colorPickerControl/colorPickerControlHorizon.h"
#include "colorPickerControl/colorPickerControl.h"
#include "trackControl/trackControl.h"
#include "trackControl/trackControlHorizon.h"

#include "intensityControl/intensityControl.h"
#include "intensityControl/intensityControlHorizon.h"

#include "encoderControl/encoderControl.h"
#include "encoderControl/encoderControlHorizon.h"

#include "colorFilterControl/colorFilterControl.h"
#include "colorFilterControl/colorFilterControlHorizon.h"

#include "inputNumControl/inputNumControl.h"
#include "inputNumControl/inputNumControlHorizon.h"

#include "groupControl/groupControlHorizon.h"
#include "libraryControl/libraryControlHorizon.h"

#include "playbackControl/playbackControl.h"
#include "playbackControl/playbackControlHorizon.h"

#include "paletteControl/paletteControlHorizon.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr );
    ~MainWindow();

    void LogEvent( const QString &log );

    void ConnectColorPickerEvent();
    void ConnectColorFilterEvent();
    void ConnectIntensityEvent();
    void ConnectInputNumEvent();
    void ConnectPaletteEvent();
    void ConnectEncoderEvent();
    void ConnectTrackEvent();
    void ConnectGroupEvent();
    void ConnectLibraryEvent();

private slots:
    void on_ColorPickerControl_Fake_Open_clicked();
    void on_TrackControl_Fake_Open_clicked();
    void on_IntensityControl_Fake_Open_clicked();
    void on_ColorFilterControl_Fake_Open_clicked();
    void on_EncoderControl_Fake_Open_clicked();
    void on_InputNumControl_Fake_Open_clicked();
    void on_GroupPanelControl_Fake_Open_clicked();
    void on_BtnClear_clicked();
    void on_LibraryControl_Fake_Open_clicked();
    void on_InputNumControl_Fake_Set_clicked();
    void on_ColorPickerControl_Fake_Set_clicked();
    void on_ColorFilterControl_Fake_Set_clicked();
    void on_EncoderControl_Fake_Set_clicked();
    void on_TrackControl_Fake_Set_clicked();
    void on_PlaybackControl_Fake_Open_clicked();
    void on_PlaybackControl_Fake_Set_clicked();
    void on_LibraryControl_Fake_Set_clicked();
    void on_GroupPanelControl_Fake_Set_clicked();
    void on_PaletteControl_Fake_Set_clicked();
    void on_PaletteControl_Fake_Open_clicked();

private:
    Ui::MainWindow *ui;
    PanelWindow *m_panel_window = new PanelWindow();

    QSharedPointer<ColorPickerControl> m_color_picker_control;
    QSharedPointer<ColorPickerControlHorizon> m_color_picker_control_horizon;

    QSharedPointer<TrackControl> m_track_control;
    QSharedPointer<TrackControlHorizon> m_track_control_horizon;

    QSharedPointer<IntensityControl> m_intensity_control;
    QSharedPointer<IntensityControlHorizon> m_intensity_control_horizon;

    QSharedPointer<EncoderControl> m_encoder_control;
    QSharedPointer<EncoderControlHorizon> m_encoder_control_horizon;

    QSharedPointer<ColorFilterControl> m_color_filter_control;
    QSharedPointer<ColorFilterControlHorizon> m_color_filter_control_horizon;

    QSharedPointer<InputNumControl> m_input_num_control;
    QSharedPointer<InputNumControlHorizon> m_input_num_control_horizon;

    QSharedPointer<GroupControl> m_group_control;
    QSharedPointer<GroupControlHorizon> m_group_control_horizon;

    QSharedPointer<LibraryControl> m_library_control;
    QSharedPointer<LibraryControlHorizon> m_library_control_horizon;

    QSharedPointer<PlaybackControl> m_playback_control;
    QSharedPointer<PlaybackControlHorizon> m_playback_control_horizon;

    QSharedPointer<PaletteControl> m_palette_control;
    QSharedPointer<PaletteControlHorizon> m_palette_control_horizon;
};
#endif // MAINWINDOW_H
