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
      m_upperRestrictValue(-1) // -1 means unset
{
    setOrientation(Qt::Vertical);
    setFixedSize(EC_CUSTOM_ENCODER_SIZE);
    setupChildComponents();

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
        if (upperRestrictValue() > minimum() && value() > upperRestrictValue())
            setValue(upperRestrictValue());
    });
}

void CustomEncoder::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    // p.fillRect(QRect(0, 0, width(), height()), Qt::black); // black background
    p.fillRect(m_sliderBoundary, Qt::black); // black background

    p.setPen(Qt::darkGray);
    p.drawRect(m_sliderBoundary.left(), 0, m_sliderBoundary.width(), height()); // border

    p.fillRect(m_sliderBoundary, QColor::fromRgb(64, 64, 64)); // gray background

    const int EC_YELLOW_SLIDER_WIDTH = 10;
    const int GRID_LINES = 13;

    float normalizedValue = map(value(), minimum(), maximum(), 0.0f, 1.0f);

    // Draw grid lines
    const float gridSpacing = m_sliderBoundary.height() * 1.0f / GRID_LINES;
    for (int i = 0; i < GRID_LINES; i++) {
        const int y = m_sliderBoundary.top() + i * gridSpacing;
        p.drawLine(m_sliderBoundary.left() + EC_YELLOW_SLIDER_WIDTH, y, m_sliderBoundary.right(), y);
    }
    // Draw yellow bar
    p.setBrush(QColor::fromRgb(34, 43, 53)); // blue gray (background of the yellow bar)
    p.drawRect(QRect(m_sliderBoundary.left(), m_sliderBoundary.top(), EC_YELLOW_SLIDER_WIDTH, m_sliderBoundary.height()));

    const int yellowBarHeight = m_sliderBoundary.height() * normalizedValue;
    p.setBrush(QColor::fromRgb(255, 192, 0)); // yellow
    p.drawRect(QRect(m_sliderBoundary.left(), m_sliderBoundary.bottom() - yellowBarHeight, EC_YELLOW_SLIDER_WIDTH, yellowBarHeight));
}

void CustomEncoder::mousePressEvent(QMouseEvent *event)
{
    if (!m_sliderBoundary.contains(event->pos()))
        return;

    const auto p = event->pos() - m_sliderBoundary.topLeft();
    setValue(map(p.y(), m_sliderBoundary.height(), 0.0f, minimum(), maximum()));

    emit sliderMoved(value());
}

void CustomEncoder::resizeEvent(QResizeEvent *event)
{
    setupChildComponents();
    QAbstractSlider::resizeEvent(event);
}

void CustomEncoder::setupChildComponents()
{
    m_sliderBoundary = QRect(QPoint(EC_ENCODER_WIDTH_PADDING, EC_BUTTON_HEIGHT),
                             QSize(width() - EC_ENCODER_WIDTH_PADDING * 2, height() - EC_BUTTON_HEIGHT * 2));

    const auto buttonSize = QSize(width() - EC_ENCODER_WIDTH_PADDING * 2, EC_BUTTON_HEIGHT);
    m_button_decrease.setFixedSize(buttonSize);
    m_button_increase.setFixedSize(buttonSize);

    m_button_increase.move(m_sliderBoundary.topLeft() - QPoint(0, EC_BUTTON_HEIGHT));
    m_button_decrease.move(m_sliderBoundary.bottomLeft());

    m_button_increase.setText("▲");
    m_button_decrease.setText("▼");
}

int CustomEncoder::upperRestrictValue() const
{
    return m_upperRestrictValue;
}

void CustomEncoder::setUpperRestrictValue(int newUpperRestrictValue)
{
    if (m_upperRestrictValue == newUpperRestrictValue)
        return;
    m_upperRestrictValue = newUpperRestrictValue;
    emit upperRestrictValueChanged();
}
