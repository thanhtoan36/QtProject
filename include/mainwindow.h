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

#include "encoderControl/encoderControl.hpp"

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


private:
    Ui::MainWindow *ui;
    PanelWindow *m_panel_window = new PanelWindow();

    QSharedPointer<ColorPickerControl> m_color_picker_control;
    QSharedPointer<ColorPickerControlHorizon> m_color_picker_control_horizon;

    QSharedPointer<TrackControl> m_track_control;
    QSharedPointer<TrackControlHorizon> m_track_control_horizon;

    QSharedPointer<IntensityControl> m_intensity_control;
    QSharedPointer<EncoderPanelControl> m_encoder_control;
};
#endif // MAINWINDOW_H
