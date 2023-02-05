#include "colorPickerControl/colorPickerControl.hpp"
#include "colorPickerControl/colorPickerControl_define.hpp"

#include <QDebug>

ColorPickerControl::ColorPickerControl(QWidget *parent)
    : PanelControlBase(parent),
      m_disp_param(),
      m_control_background(this),
      m_label_title(this),
      m_button_xy(this),
      m_button_rgb(this),
      m_button_previous_tab(this),
      m_button_next_tab(this),
      m_label_setting(this),
      m_picker_xy(this),
      m_label_title_x(this),
      m_label_value_x(this),
      m_slider_x(this),
      m_label_title_y(this),
      m_label_value_y(this),
      m_slider_y(this),
      m_label_title_h(this),
      m_label_value_h(this),
      m_slider_h(this),
      m_label_title_s(this),
      m_label_value_s(this),
      m_slider_s(this),
      m_label_title_v(this),
      m_label_value_v(this),
      m_slider_v(this),
      m_children_xy{&m_picker_xy, &m_label_value_x, &m_label_value_y, &m_label_title_x, &m_label_title_y, &m_slider_x, &m_slider_y},
      m_children_rgb{&m_label_value_h, &m_label_title_h, &m_slider_h, &m_label_value_s, &m_label_title_s, &m_slider_s, &m_label_value_v, &m_label_title_v, &m_slider_v}
{
    resize(CPC_SCREENSIZE);
    m_slider_x.setRange(0, 1000);
    m_slider_y.setRange(0, 1000);
}

void ColorPickerControl::SetDispParamData(COLOR_PICKER_DISP_PARAM *param)
{
    Q_ASSERT(param);
    m_disp_param = *param;
    SetupUiComponents();
}

void ColorPickerControl::SetupUiComponents()
{
    m_label_title.setGeometry(CPC_TITLE_GEOMETRY);
    m_label_title.setText("ピッカー xy");
    setWindowTitle(m_label_title.text());

    m_button_xy.setGeometry(CPC_BUTTON_XY_GEOMETRY);
    m_button_xy.setText("xy");

    m_button_rgb.setGeometry(CPC_BUTTON_RGB_GEOMETRY);
    m_button_rgb.setText("RGB");

    m_button_previous_tab.setGeometry(CPC_BUTTON_PREVIOUS_TAB_GEOMETRY);
    m_button_previous_tab.setText("◀");

    m_button_next_tab.setGeometry(CPC_BUTTON_NEXT_TAB_GEOMETRY);
    m_button_next_tab.setText("▶");

    m_label_setting.setGeometry(CPC_LABEL_SETTING_GEOMETRY);
    m_label_setting.setText("設定");

    m_control_background.setObjectName("control_background");
    m_control_background.setGeometry(QRect(
                                         0,
                                         m_label_setting.geometry().bottom(),
                                         this->width(),
                                         this->height() - m_label_setting.geometry().bottom()
                                         ));
    // XY tab
    m_picker_xy.SetColor(m_disp_param.color);
    m_picker_xy.setGeometry(CPC_PICKER_XY_GEOMETRY);
    const auto xy = m_picker_xy.Xy();

    m_label_title_x.setGeometry(CPC_LABEL_TITLE_X_GEOMETRY);
    m_label_title_x.setText("x");

    m_label_value_x.setGeometry(CPC_LABEL_VALUE_X_GEOMETRY);
    m_label_value_x.setText(QString::asprintf("%.03f", xy.x()));

    m_slider_x.setGeometry(CPC_SLIDER_X_GEOMETRY);
    m_slider_x.setOrientation(Qt::Horizontal);
    m_slider_x.setValue(xy.x() * 1000);

    m_label_title_y.setGeometry(CPC_LABEL_TITLE_Y_GEOMETRY);
    m_label_title_y.setText("y");

    m_label_value_y.setGeometry(CPC_LABEL_VALUE_Y_GEOMETRY);
    m_label_value_y.setText(QString::asprintf("%.03f", xy.y()));

    m_slider_y.setGeometry(CPC_SLIDER_Y_GEOMETRY);
    m_slider_y.setOrientation(Qt::Horizontal);
    m_slider_y.setValue(xy.y() * 1000);

    // RGB Tab
    m_label_title_h.setGeometry(CPC_LABEL_TITLE_H_GEOMETRY);
    m_label_title_h.setText("x");

    m_label_value_h.setGeometry(CPC_LABEL_VALUE_H_GEOMETRY);
    // m_label_value_h.setText(QString::asprintf("%.03f", xy.x()));

    m_slider_h.setGeometry(CPC_SLIDER_X_GEOMETRY);
    m_slider_h.setOrientation(Qt::Horizontal);
    // m_slider_h.setValue(xy.y() * 1000);

    m_label_title_s.setGeometry(CPC_LABEL_TITLE_S_GEOMETRY);
    m_label_title_s.setText("x");

    m_label_value_s.setGeometry(CPC_LABEL_VALUE_S_GEOMETRY);
    // m_label_value_h.setText(QString::asprintf("%.03f", xy.x()));

    m_slider_s.setGeometry(CPC_SLIDER_S_GEOMETRY);
    m_slider_s.setOrientation(Qt::Horizontal);
    // m_slider_h.setValue(xy.y() * 1000);

    m_label_title_v.setGeometry(CPC_LABEL_TITLE_V_GEOMETRY);
    m_label_title_v.setText("x");

    m_label_value_v.setGeometry(CPC_LABEL_VALUE_V_GEOMETRY);
    // m_label_value_h.setText(QString::asprintf("%.03f", xy.x()));

    m_slider_v.setGeometry(CPC_SLIDER_V_GEOMETRY);
    m_slider_v.setOrientation(Qt::Horizontal);
    // m_slider_h.setValue(xy.y() * 1000);


    if (m_disp_param.type == COLOR_PICKER_TYPE_XY) {
        foreach(auto &child, m_children_xy)
            child->setVisible(true);
        foreach(auto &child, m_children_rgb)
            child->setVisible(false);

        m_button_xy.setChecked(true);
        m_button_rgb.setChecked(false);
    }
    if (m_disp_param.type == COLOR_PICKER_TYPE_RGB) {
        foreach(auto &child, m_children_xy)
            child->setVisible(false);
        foreach(auto &child, m_children_rgb)
            child->setVisible(true);

        m_button_xy.setChecked(false);
        m_button_rgb.setChecked(true);
    }
}

void ColorPickerControl::SetupUiEvents()
{
    connect(&m_picker_xy, &CustomColorPickerXY::XyChanged, this, [&](QPointF xy) {
        m_slider_x.setValue(xy.x() * 1000);
        m_slider_y.setValue(xy.y() * 1000);
        m_label_value_x.setText(QString::asprintf("%.03f", xy.x()));
        m_label_value_y.setText(QString::asprintf("%.03f", xy.y()));
        m_disp_param.color = m_picker_xy.Color();
    });
    connect(&m_slider_x, &QSlider::valueChanged, this, [&](int) {
        m_picker_xy.SetXy(QPointF(m_slider_x.value() / 1000.0, m_slider_y.value() / 1000.0));
    });
    connect(&m_slider_y, &QSlider::valueChanged, this, [&](int) {
        m_picker_xy.SetXy(QPointF(m_slider_x.value() / 1000.0, m_slider_y.value() / 1000.0));
    });
    connect(&m_button_xy, &QAbstractButton::clicked, this, [&]() {
        m_disp_param.type = COLOR_PICKER_TYPE_XY;
        SetDispParamData(&m_disp_param);
    });
    connect(&m_button_rgb, &QAbstractButton::clicked, this, [&]() {
        m_disp_param.type = COLOR_PICKER_TYPE_RGB;
        SetDispParamData(&m_disp_param);
    });
}
