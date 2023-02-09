#include "encoderControl/encoderSlider.h"

#include <QPainter>
#include <QMouseEvent>
#include "utility.h"

#define EC_WIDTH_PADDING 10
#define EC_BUTTON_HEIGHT 25

Encoder::Encoder(QWidget *parent)
    : QAbstractSlider(parent),
      m_button_decrease(this),
      m_button_increase(this)
{
    // FIXME: if orientation is set after constructor is called, since it has no signal, we can re-setup the geometries
    setOrientation(Qt::Vertical);
    setupGeometries();

    connect(&m_button_decrease, &QAbstractButton::clicked, this, [&](){
        setValue(value() - singleStep());
    });
    connect(&m_button_increase, &QAbstractButton::clicked, this, [&](){
        setValue(value() + singleStep());
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
    const int GRID_LINES = 13;

    float normalizedValue = map(value(), minimum(), maximum(), 0.0f, 1.0f);

    if (orientation() == Qt::Vertical) {
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

    if (orientation() == Qt::Horizontal) {
        // Draw grid lines
        const float gridSpacing = m_sliderBoundary.width() * 1.0f / GRID_LINES;
        for (int i = 0; i < GRID_LINES; i++) {
            const int x = m_sliderBoundary.left() + i * gridSpacing;
            p.drawLine(x, m_sliderBoundary.top() + EC_YELLOW_SLIDER_WIDTH, x, m_sliderBoundary.bottom());
        }
        // Draw yellow bar
        p.setBrush(QColor::fromRgb(34, 43, 53)); // blue gray (background of the yellow bar)
        p.drawRect(QRect(m_sliderBoundary.left(), m_sliderBoundary.top(), m_sliderBoundary.width(), EC_YELLOW_SLIDER_WIDTH));

        const int yellowBarWidth = m_sliderBoundary.width() * normalizedValue;
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
        setValue(map(p.y(), m_sliderBoundary.height(), 0.0f, minimum(), maximum()));
    }
    if (orientation() == Qt::Horizontal) {
        setValue(map(p.x(), 0.0f, m_sliderBoundary.width(), minimum(), maximum()));
    }

    emit sliderMoved(value());
}

void Encoder::resizeEvent(QResizeEvent *event)
{
    setupGeometries();
    QAbstractSlider::resizeEvent(event);
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
