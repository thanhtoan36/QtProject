//--------------------------------------------------------------------------
// [ ファイル名 ] : colorPickerControl.h
// [ 概      要 ] : ColorPickerControl vertical widget
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef COLORPICKERCONTROL_H
#define COLORPICKERCONTROL_H

#include "baseComponent/panelControlBase.h"
#include "baseComponent/gridBackground.h"
#include "colorPickerControl_datatypes.h"

#include "baseComponent/selectButton.h"
#include "baseComponent/customPushButton.h"
#include "colorPickerControl/customColorPickerXY.h"
#include "colorPickerControl/customColorPickerRGB.h"
#include "baseComponent/gridBackground.h"

#include <QLabel>
#include <QSlider>

class ColorPickerControl : public PanelControlBase
{
    Q_OBJECT

    Q_PROPERTY( ColorPickerType PickerType READ PickerType WRITE SetPickerType NOTIFY PickerTypeChanged )
    Q_PROPERTY( QColor PickerColor READ PickerColor WRITE SetPickerColor NOTIFY PickerColorChanged )
    Q_PROPERTY( int CurrentHeaderButtonsPage READ CurrentHeaderButtonsPage WRITE SetCurrentHeaderButtonsPage NOTIFY CurrentHeaderButtonsPageChanged )

public:
    ColorPickerControl( QWidget *parent = nullptr );
    virtual void SetDispParamData( COLOR_PICKER_DISP_PARAM *param );

    ColorPickerType PickerType() const;
    QColor PickerColor() const;
signals:
    void PickerTypeChanged();
    void PickerColorChanged();
    void CurrentHeaderButtonsPageChanged();

    void NextButtonClicked();
    void PrevButtonClicked();

protected slots:
    void OnPickerTypeChanged();
    void OnPickerTypeButtonClicked();
    void SetupHeaderButtonPages();

protected:
    void PauseSliderEvents();
    void ResumeSliderEvents();
    int CurrentHeaderButtonsPage() const;
    void SetCurrentHeaderButtonsPage( int new_button_page );
    void AddHeaderButton( ColorPickerType type, const QString &text );
    QVector<QSharedPointer<SelectButton> > HeaderButtons() const;
    void SetPickerType( ColorPickerType type );
    void SetPickerColor( const QColor &type );

protected:
    struct PickerButton
    {
        ColorPickerType type;
        QSharedPointer<SelectButton> button;
    };
    QVector<PickerButton> m_header_buttons;

    GridBackground m_menu_background;
    GridBackground m_slider_background;

    QLabel m_label_title;

    CustomPushButton m_button_previous_menu_page; // ◀
    CustomPushButton m_button_next_menu_page;     // ▶

    QLabel m_label_setting;

    // XY tab
    CustomColorPickerXY m_picker_xy;

    QLabel m_label_title_x;
    QLabel m_label_value_x;
    QSlider m_slider_x;

    QLabel m_label_title_y;
    QLabel m_label_value_y;
    QSlider m_slider_y;

    // RGB tab
    CustomColorPickerRGB m_picker_rgb;
    QLabel m_label_title_h;
    QLabel m_label_value_h;
    QSlider m_slider_h;
    QLabel m_label_title_s;
    QLabel m_label_value_s;
    QSlider m_slider_s;
    QLabel m_label_title_v;
    QLabel m_label_value_v;
    QSlider m_slider_v;

    QVector<QWidget *> m_children_xy;
    QVector<QWidget *> m_children_rgb;
    ColorPickerType m_picker_type;
    QColor m_picker_color;
    int m_header_buttons_per_page;
    int m_current_header_buttons_page;
};

#endif // COLORPICKERCONTROL_H
