#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "baseComponent/panelWindow.h"

#include "utility.h"

#include "colorPickerControl/colorPickerControlHorizon.h"
#include "colorPickerControl/colorPickerControl.hpp"
#include "trackControl/trackControl.hpp"
#include "trackControl/trackControlHorizon.h"

#include "intensityControl/intensityControl.hpp"
#include "intensityControl/intensityControlHorizon.h"

#include "encoderControl/encoderControl.hpp"
#include "encoderControl/encoderControlHorizon.h"

#include "colorFilterControl/colorFilterControl.hpp"
#include "colorFilterControl/colorFilterControlHorizon.h"

#include "inputNumControl/inputNumControl.hpp"
#include "inputNumControl/inputNumControlHorizon.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ColorPickerControl_Fake_Open_clicked();
    void on_TrackControl_Fake_Open_clicked();
    void on_IntensityControl_Fake_Open_clicked();


    void on_ColorFilterControl_Fake_Open_clicked();

    void on_EncoderControl_Fake_Open_clicked();


    void on_InputNumControl_Fake_Open_clicked();

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
};
#endif // MAINWINDOW_H
