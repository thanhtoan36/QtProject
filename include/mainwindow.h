#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "baseComponent/panelWindow.h"

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

private:
    Ui::MainWindow *ui;
    PanelWindow *m_panel_window = new PanelWindow();
};
#endif // MAINWINDOW_H
