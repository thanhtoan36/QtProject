#include "encoderControl/encoderSlider.h"

#include <QPainter>
#include <QMouseEvent>

#define EC_WIDTH_PADDING 10
#define EC_BUTTON_HEIGHT 25

Encoder::Encoder(QWidget *parent)
    : QWidget(parent),
      m_orientation(Qt::Orientation::Vertical),
      m_sliderBoundary(),
      m_value(0.0f),
      m_step(0.1f),
      m_button_decrease(this),
      m_button_increase(this)
{
    setupGeometries();
    connect(&m_button_decrease, &QAbstractButton::clicked, this, [&](){
        setValue(value() - step());
    });
    connect(&m_button_increase, &QAbstractButton::clicked, this, [&](){
        setValue(value() + step());
    });
}

void Encoder::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.fillRect(QRect(QPoint(0, 0), size()), Qt::black); // black background

    p.setPen(Qt::darkGray);
    p.setBrush(QColor::fromRgb(64, 64, 64)); // gray background
    p.drawRect(m_sliderBoundary);

    const int EC_YELLOW_SLIDER_WIDTH = 10;
    const int gridLines = 13;

    if (orientation() == Qt::Vertical) {
        // Draw grid lines
        const float gridSpacing = m_sliderBoundary.height() * 1.0f / gridLines;
        for (int i = 0; i < gridLines; i++) {
            const int y = m_sliderBoundary.top() + i * gridSpacing;
            p.drawLine(m_sliderBoundary.left() + EC_YELLOW_SLIDER_WIDTH, y, m_sliderBoundary.right(), y);
        }
        // Draw yellow bar
        p.setBrush(QColor::fromRgb(34, 43, 53)); // blue gray (background of the yellow bar)
        p.drawRect(QRect(m_sliderBoundary.left(), m_sliderBoundary.top(), EC_YELLOW_SLIDER_WIDTH, m_sliderBoundary.height()));

        const int yellowBarHeight = m_sliderBoundary.height() * value();
        p.setBrush(QColor::fromRgb(255, 192, 0)); // yellow
        p.drawRect(QRect(m_sliderBoundary.left(), m_sliderBoundary.bottom() - yellowBarHeight, EC_YELLOW_SLIDER_WIDTH, yellowBarHeight));
    }

    if (orientation() == Qt::Horizontal) {
        // Draw grid lines
        const float gridSpacing = m_sliderBoundary.width() * 1.0f / gridLines;
        for (int i = 0; i < gridLines; i++) {
            const int x = m_sliderBoundary.left() + i * gridSpacing;
            p.drawLine(x, m_sliderBoundary.top() + EC_YELLOW_SLIDER_WIDTH, x, m_sliderBoundary.bottom());
        }
        // Draw yellow bar
        p.setBrush(QColor::fromRgb(34, 43, 53)); // blue gray (background of the yellow bar)
        p.drawRect(QRect(m_sliderBoundary.left(), m_sliderBoundary.top(), m_sliderBoundary.width(), EC_YELLOW_SLIDER_WIDTH));

        const int yellowBarWidth = m_sliderBoundary.width() * value();
        p.setBrush(QColor::fromRgb(255, 192, 0)); // yellow
        p.drawRect(QRect(m_sliderBoundary.left(), m_sliderBoundary.top(), yellowBarWidth, EC_YELLOW_SLIDER_WIDTH));
    }
}

void Encoder::mousePressEvent(QMouseEvent *event)
{
    if (!m_sliderBoundary.contains(event->pos()))
        return;

    const auto p = event->pos() - m_sliderBoundary.topLeft();

    if (orientation() == Qt::Vertical) {
        setValue((m_sliderBoundary.height() - p.y()) * 1.0f / m_sliderBoundary.height());
    }
    if (orientation() == Qt::Horizontal) {
        setValue(p.x() * 1.0f / m_sliderBoundary.width());
    }
    emit picked();
}

void Encoder::resizeEvent(QResizeEvent *event)
{
    setupGeometries();
    QWidget::resizeEvent(event);
}

void Encoder::setupGeometries()
{
    if (orientation() == Qt::Vertical) {
        const auto buttonSize = QSize(width() - EC_WIDTH_PADDING * 2, EC_BUTTON_HEIGHT);
        m_button_decrease.setFixedSize(buttonSize);
        m_button_increase.setFixedSize(buttonSize);

        m_button_increase.move(EC_WIDTH_PADDING, 0);
        m_button_decrease.move(EC_WIDTH_PADDING, height() - buttonSize.height());

        m_button_increase.setText("▲");
        m_button_decrease.setText("▼");

        m_sliderBoundary = QRect(QPoint(EC_WIDTH_PADDING, EC_BUTTON_HEIGHT),
                                 QSize(width() - EC_WIDTH_PADDING * 2, height() - EC_BUTTON_HEIGHT * 2));
    } else {
        const auto buttonSize = QSize(EC_BUTTON_HEIGHT, height() - EC_WIDTH_PADDING * 2);
        m_button_decrease.setFixedSize(buttonSize);
        m_button_increase.setFixedSize(buttonSize);

        m_button_increase.move(width() - buttonSize.width(), EC_WIDTH_PADDING);
        m_button_decrease.move(0, EC_WIDTH_PADDING);

        m_button_increase.setText("▶");
        m_button_decrease.setText("◀");

        m_sliderBoundary = QRect(QPoint(EC_BUTTON_HEIGHT, EC_WIDTH_PADDING),
                                 QSize(width() - EC_BUTTON_HEIGHT * 2, height() - EC_WIDTH_PADDING * 2));
    }
}

Qt::Orientation Encoder::orientation() const
{
    return m_orientation;
}

void Encoder::setOrientation(Qt::Orientation newOrientation)
{
    if (m_orientation == newOrientation)
        return;
    m_orientation = newOrientation;
    emit orientationChanged();
    setupGeometries();
    update();
}

float Encoder::value() const
{
    return m_value;
}

void Encoder::setValue(float newValue)
{
    if (newValue < 0.0) newValue = 0.0;
    if (newValue > 1.0) newValue = 1.0;
    if (qFuzzyCompare(m_value, newValue))
        return;
    m_value = newValue;
    emit valueChanged();
    update();
}

float Encoder::step() const
{
    return m_step;
}

void Encoder::setStep(float newStep)
{
    if (qFuzzyCompare(m_step, newStep))
        return;
    m_step = newStep;
    emit stepChanged();
}
