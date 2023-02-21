#include "encoderControl/customEncoder.h"
#include "encoderControl/encoderControl_define.hpp"

#include <QPainter>
#include <QMouseEvent>
#include "utility.h"

#define EC_BUTTON_HEIGHT 25

// NOTE: currently only support vertical orientation

CustomEncoder::CustomEncoder(QWidget *parent)
    : QAbstractSlider(parent),
      m_button_decrease(this),
      m_button_increase(this),
      m_upper_restrict_value(-1) // -1 means unset
{
    setOrientation(Qt::Vertical);
    setFixedSize(EC_CUSTOM_ENCODER_SIZE);
    SetupChildComponents();

    connect(&m_button_decrease, &QAbstractButton::clicked, this, [&](){
        setValue(value() - singleStep());
        emit sliderMoved(value());
    });
    connect(&m_button_increase, &QAbstractButton::clicked, this, [&](){
        setValue(value() + singleStep());
        emit sliderMoved(value());
    });
    connect(this, &QAbstractSlider::valueChanged, this, [&](){
        // limit the slider movement
        if (UpperRestrictValue() > minimum() && value() > UpperRestrictValue())
        {
            setValue(UpperRestrictValue());
        }
    });
}

void CustomEncoder::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    // p.fillRect(QRect(0, 0, width(), height()), Qt::black); // black background
    p.fillRect(m_slider_boundary, Qt::black); // black background

    p.setPen(Qt::darkGray);
    p.drawRect(m_slider_boundary.left(), 0, m_slider_boundary.width(), height()); // border

    p.fillRect(m_slider_boundary, QColor::fromRgb(64, 64, 64)); // gray background

    constexpr int EC_YELLOW_SLIDER_WIDTH = 10;
    constexpr int GRID_LINES = 13;

    float normalized_value = map(value(), minimum(), maximum(), 0.0f, 1.0f);

    // Draw grid lines
    const float grid_spacing = m_slider_boundary.height() * 1.0f / GRID_LINES;
    for (int i = 0; i < GRID_LINES; i++) {
        const int y = m_slider_boundary.top() + i * grid_spacing;
        p.drawLine(m_slider_boundary.left() + EC_YELLOW_SLIDER_WIDTH, y, m_slider_boundary.right(), y);
    }
    // Draw yellow bar
    p.setBrush(QColor::fromRgb(34, 43, 53)); // blue gray (background of the yellow bar)
    p.drawRect(QRect(m_slider_boundary.left(), m_slider_boundary.top(), EC_YELLOW_SLIDER_WIDTH, m_slider_boundary.height()));

    const int yellowBarHeight = m_slider_boundary.height() * normalized_value;
    p.setBrush(QColor::fromRgb(255, 192, 0)); // yellow
    p.drawRect(QRect(m_slider_boundary.left(), m_slider_boundary.bottom() - yellowBarHeight, EC_YELLOW_SLIDER_WIDTH, yellowBarHeight));
}

void CustomEncoder::mousePressEvent(QMouseEvent *event)
{
    if (!m_slider_boundary.contains(event->pos()))
    {
        return;
    }

    const auto p = event->pos() - m_slider_boundary.topLeft();
    setValue(map(p.y(), m_slider_boundary.height(), 0.0f, minimum(), maximum()));

    emit sliderMoved(value());
}

void CustomEncoder::resizeEvent(QResizeEvent *event)
{
    SetupChildComponents();
    QAbstractSlider::resizeEvent(event);
}

void CustomEncoder::SetupChildComponents()
{
    m_slider_boundary = QRect(QPoint(EC_ENCODER_WIDTH_PADDING, EC_BUTTON_HEIGHT),
                             QSize(width() - EC_ENCODER_WIDTH_PADDING * 2, height() - EC_BUTTON_HEIGHT * 2));

    const auto button_size = QSize(width() - EC_ENCODER_WIDTH_PADDING * 2, EC_BUTTON_HEIGHT);
    m_button_decrease.setFixedSize(button_size);
    m_button_increase.setFixedSize(button_size);

    m_button_increase.move(m_slider_boundary.topLeft() - QPoint(0, EC_BUTTON_HEIGHT));
    m_button_decrease.move(m_slider_boundary.bottomLeft());

    m_button_increase.setText("▲");
    m_button_decrease.setText("▼");
}

int CustomEncoder::UpperRestrictValue() const
{
    return m_upper_restrict_value;
}

void CustomEncoder::SetUpperRestrictValue(int value)
{
    if (m_upper_restrict_value == value)
        return;
    m_upper_restrict_value = value;
    emit UpperRestrictValueChanged();
}
