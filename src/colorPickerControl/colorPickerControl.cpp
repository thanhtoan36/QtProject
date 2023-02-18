#include "colorPickerControl/colorPickerControl.hpp"
#include "colorPickerControl/colorPickerControl_define.hpp"
#include "utility.h"

#include <QDebug>
#include <QColorDialog>

ColorPickerControl::ColorPickerControl(QWidget *parent)
    : PanelControlBase(parent),
      m_menu_background(this),
      m_slider_background(this),
      m_label_title(this),
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
      m_picker_rgb(this),
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
      m_children_rgb{&m_picker_rgb, &m_label_value_h, &m_label_title_h, &m_slider_h, &m_label_value_s, &m_label_title_s, &m_slider_s, &m_label_value_v, &m_label_title_v, &m_slider_v},
      m_pickerType(COLOR_PICKER_TYPE_XY), m_pickerColor(Qt::white)
{
    setFixedSize(CPC_SCREENSIZE);

    m_slider_x.setRange(0, 1000);
    m_slider_y.setRange(0, 1000);
    m_slider_h.setRange(0, 359);
    m_slider_s.setRange(0, 255);
    m_slider_v.setRange(0, 255);

    m_label_title.setObjectName("title_label");
    m_label_setting.setObjectName("title_label_with_border");

    m_slider_background.setGridSize(QSize(1, 1));
    m_slider_background.setBackgroundColor(QColor::fromRgb(89, 89, 89));
    m_slider_background.setGridLineColor(Qt::transparent);
    m_slider_background.move(0, CPC_LABEL_SETTING_GEOMETRY.bottom());
    m_slider_background.setCellSize(QSize(width(), height() - CPC_LABEL_SETTING_GEOMETRY.bottom()));

    m_menu_background.setGridSize(QSize(4, 1));
    m_menu_background.setCellSize(CPC_BUTTON_XY_GEOMETRY.size());
    m_menu_background.move(CPC_BUTTON_XY_GEOMETRY.topLeft());

    m_label_title.setGeometry(CPC_TITLE_GEOMETRY);

    m_button_previous_tab.setGeometry(CPC_BUTTON_PREVIOUS_TAB_GEOMETRY);
    m_button_previous_tab.setText("◀");
    m_button_previous_tab.setVisible(false);

    m_button_next_tab.setGeometry(CPC_BUTTON_NEXT_TAB_GEOMETRY);
    m_button_next_tab.setText("▶");
    m_button_next_tab.setVisible(false);

    m_label_setting.setGeometry(CPC_LABEL_SETTING_GEOMETRY);
    m_label_setting.setText("設定");

    m_picker_xy.setGeometry(CPC_PICKER_XY_GEOMETRY);
    m_picker_rgb.setGeometry(CPC_PICKER_RGB_GEOMETRY);

    m_label_title_x.setGeometry(CPC_LABEL_TITLE_X_GEOMETRY);
    m_label_title_x.setText("x");

    m_label_value_x.setGeometry(CPC_LABEL_VALUE_X_GEOMETRY);

    m_slider_x.setGeometry(CPC_SLIDER_X_GEOMETRY);
    m_slider_x.setOrientation(Qt::Horizontal);

    m_label_title_y.setGeometry(CPC_LABEL_TITLE_Y_GEOMETRY);
    m_label_title_y.setText("y");

    m_label_value_y.setGeometry(CPC_LABEL_VALUE_Y_GEOMETRY);

    m_slider_y.setGeometry(CPC_SLIDER_Y_GEOMETRY);
    m_slider_y.setOrientation(Qt::Horizontal);

    // RGB Tab
    m_label_title_h.setGeometry(CPC_LABEL_TITLE_H_GEOMETRY);
    m_label_title_h.setText("H");

    m_label_value_h.setGeometry(CPC_LABEL_VALUE_H_GEOMETRY);

    m_slider_h.setGeometry(CPC_SLIDER_X_GEOMETRY);
    m_slider_h.setOrientation(Qt::Horizontal);

    m_label_title_s.setGeometry(CPC_LABEL_TITLE_S_GEOMETRY);
    m_label_title_s.setText("S");

    m_label_value_s.setGeometry(CPC_LABEL_VALUE_S_GEOMETRY);

    m_slider_s.setGeometry(CPC_SLIDER_S_GEOMETRY);
    m_slider_s.setOrientation(Qt::Horizontal);

    m_label_title_v.setGeometry(CPC_LABEL_TITLE_V_GEOMETRY);
    m_label_title_v.setText("V");

    m_label_value_v.setGeometry(CPC_LABEL_VALUE_V_GEOMETRY);

    m_slider_v.setGeometry(CPC_SLIDER_V_GEOMETRY);
    m_slider_v.setOrientation(Qt::Horizontal);

    addPickerTypeButton(COLOR_PICKER_TYPE_XY, "xy");
    addPickerTypeButton(COLOR_PICKER_TYPE_RGB, "RGB");

    placeChildrenIntoPanel(pickerTypeButtons(), CPC_BUTTON_XY_GEOMETRY.size(), CPC_BUTTON_XY_GEOMETRY.topLeft(), QSize(2, 1));

    onPickerTypeChanged();
    SetupUiEvents();

    m_picker_xy.SetColor(Qt::gray);
    m_picker_rgb.SetColor(Qt::gray);

    auto xy = m_picker_xy.Xy();
    m_slider_x.setValue(xy.x() * 1000);
    m_slider_y.setValue(xy.y() * 1000);

    auto hsv = m_picker_rgb.HSV();
    m_slider_h.setValue(hsv.h);
    m_slider_s.setValue(hsv.s);
    m_slider_v.setValue(hsv.v);

    connect(this, &ColorPickerControl::pickerTypeChanged, this, &ColorPickerControl::onPickerTypeChanged);
    //xy picker
    connect(&m_picker_xy, &CustomColorPickerXY::XyChanged, this, [&](QPointF xy) {
        m_label_value_x.setText(QString::asprintf("%.03f", xy.x()));
        m_label_value_y.setText(QString::asprintf("%.03f", xy.y()));
    });
    connect(&m_picker_xy, &CustomColorPickerXY::picked, this, [&]() {
        pauseSliderEvents();

        setPickerColor(m_picker_xy.Color());
        auto xy = m_picker_xy.Xy();
        m_slider_x.setValue(xy.x() * 1000);
        m_slider_y.setValue(xy.y() * 1000);

        resumeSliderEvents();
    });

    connect(&m_slider_x, &QSlider::valueChanged, this, [&](int) {
        m_picker_xy.SetXy(QPointF(m_slider_x.value() / 1000.0, m_slider_y.value() / 1000.0));
        setPickerColor(m_picker_xy.Color());
        // m_picker_rgb.SetColor(pickerColor());
    });
    connect(&m_slider_y, &QSlider::valueChanged, this, [&](int) {
        m_picker_xy.SetXy(QPointF(m_slider_x.value() / 1000.0, m_slider_y.value() / 1000.0));
        setPickerColor(m_picker_xy.Color());
        // m_picker_rgb.SetColor(pickerColor());
    });

    //rgb picker event
    connect(&m_picker_rgb, &CustomColorPickerRGB::HSVChanged, this, [&](hsv_t hsv) {
        m_label_value_h.setText(QString::number(hsv.h));
        m_label_value_s.setText(QString::number(hsv.s));
        m_label_value_v.setText(QString::number(hsv.v));
    });
    connect(&m_picker_rgb, &CustomColorPickerRGB::picked, this, [&]() {
        pauseSliderEvents();

        setPickerColor(m_picker_rgb.Color());
        // m_picker_xy.SetColor(pickerColor());
        auto hsv = m_picker_rgb.HSV();
        m_slider_h.setValue(hsv.h);
        m_slider_s.setValue(hsv.s);
        m_slider_v.setValue(hsv.v);

        resumeSliderEvents();
    });

    connect(&m_slider_h, &QSlider::valueChanged, this, [&](int) {
        m_picker_rgb.SetHSV(m_slider_h.value(), m_slider_s.value(), m_slider_v.value() );
        setPickerColor(m_picker_rgb.Color());
        // m_picker_xy.SetColor(pickerColor());
    });
    connect(&m_slider_s, &QSlider::valueChanged, this, [&](int) {
        m_picker_rgb.SetHSV(m_slider_h.value(), m_slider_s.value(), m_slider_v.value() );
        setPickerColor(m_picker_rgb.Color());
        // m_picker_xy.SetColor(pickerColor());
    });
    connect(&m_slider_v, &QSlider::valueChanged, this, [&](int) {
        m_picker_rgb.SetHSV(m_slider_h.value(), m_slider_s.value(), m_slider_v.value() );
        setPickerColor(m_picker_rgb.Color());
        // m_picker_xy.SetColor(pickerColor());
    });
}

void ColorPickerControl::SetDispParamData(COLOR_PICKER_DISP_PARAM *param)
{
    Q_ASSERT(param);
    setPickerType(param->type);
    setPickerColor(param->color);

    m_picker_xy.SetColor(pickerColor());
    m_picker_rgb.SetColor(pickerColor());

    pauseSliderEvents();
    auto xy = m_picker_xy.Xy();
    m_slider_x.setValue(xy.x() * 1000);
    m_slider_y.setValue(xy.y() * 1000);

    auto hsv = m_picker_rgb.HSV();
    m_slider_h.setValue(hsv.h);
    m_slider_s.setValue(hsv.s);
    m_slider_v.setValue(hsv.v);
    resumeSliderEvents();
}

void ColorPickerControl::pauseSliderEvents()
{
    m_slider_x.blockSignals(true);
    m_slider_y.blockSignals(true);
    m_slider_h.blockSignals(true);
    m_slider_s.blockSignals(true);
    m_slider_v.blockSignals(true);
}

void ColorPickerControl::resumeSliderEvents()
{
    m_slider_x.blockSignals(false);
    m_slider_y.blockSignals(false);
    m_slider_h.blockSignals(false);
    m_slider_s.blockSignals(false);
    m_slider_v.blockSignals(false);
}

void ColorPickerControl::addPickerTypeButton(ColorPickerType type, const QString &text)
{
    auto button = MakeSharedQObject<SelectButton>(this);
    button->setText(text);
    button->setFixedSize(CPC_BUTTON_XY_GEOMETRY.size());

    m_pickertype_buttons.append({type, button});
    connect(button.get(), &QPushButton::clicked, this, &ColorPickerControl::onPickerTypeButtonClicked);
}

QVector<QSharedPointer<SelectButton>> ColorPickerControl::pickerTypeButtons() const
{
    QVector<QSharedPointer<SelectButton>> buttons;
    for (const auto &button: qAsConst(m_pickertype_buttons))
        buttons.append(button.button);
    return buttons;
}

ColorPickerType ColorPickerControl::pickerType() const
{
    return m_pickerType;
}

void ColorPickerControl::setPickerType(ColorPickerType newPickerType)
{
    if (m_pickerType == newPickerType)
        return;
    m_pickerType = newPickerType;
    emit pickerTypeChanged();
}

QColor ColorPickerControl::pickerColor() const
{
    return m_pickerColor;
}

void ColorPickerControl::setPickerColor(const QColor &newPickerColor)
{
    if (m_pickerColor == newPickerColor)
        return;
    m_pickerColor = newPickerColor;
    emit pickerColorChanged();
}

void ColorPickerControl::onPickerTypeChanged()
{
    auto button = std::find_if(m_pickertype_buttons.begin(), m_pickertype_buttons.end(), [&](const PickerButton &button) {
       return button.type == pickerType();
    });

    if (button != m_pickertype_buttons.end()) {
        m_label_title.setText(QString("ピッカー %1").arg(button->button->text()));
    }

    for (const auto &button: qAsConst(m_pickertype_buttons))
    {
        button.button->setChecked(button.type == pickerType());
    }

    if (pickerType() == COLOR_PICKER_TYPE_XY) {
        foreach(auto &child, m_children_xy)
            child->setVisible(true);
        foreach(auto &child, m_children_rgb)
            child->setVisible(false);
    }

    if (pickerType() == COLOR_PICKER_TYPE_RGB) {
        foreach(auto &child, m_children_xy)
            child->setVisible(false);
        foreach(auto &child, m_children_rgb)
            child->setVisible(true);
    }
}

void ColorPickerControl::onPickerTypeButtonClicked()
{
    auto button = std::find_if(m_pickertype_buttons.begin(), m_pickertype_buttons.end(), [&](const PickerButton &button) {
       return button.button.get() == sender();
    });
    if (button != m_pickertype_buttons.end()) {
        setPickerType(button->type);
    }
}
