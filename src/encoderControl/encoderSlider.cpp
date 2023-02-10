#include "encoderControl/encoderSlider.h"
#include <QApplication>

#include <QPainter>
#include <QMouseEvent>
#include "utility.h"

#define EC_WIDTH_PADDING 10
#define EC_LABEL_HEIGHT  36 // the height of the label rectangle
#define EC_BUTTON_HEIGHT 25

// NOTE: currently only support vertical orientation

EncoderSlider::EncoderSlider(QWidget *parent)
    : QAbstractSlider(parent),
      m_label_name(this),
      m_label_value(this),
      m_button_decrease(this),
      m_button_increase(this),
      m_upperRestrictValue(-1) // -1 means unset
{
    // FIXME: if orientation is set after constructor is called, since it has no signal, we can re-setup the geometries
    setOrientation(Qt::Vertical);
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
        m_label_value.setText(QString::number(value()));
    });

    auto font = m_label_name.font();
    font.setPixelSize(14);

    m_label_name.setFont(font);
    m_label_value.setText(QString::number(value()));

    m_label_name.setAlignment(Qt::AlignCenter);
    m_label_value.setAlignment(Qt::AlignCenter);

}

void EncoderSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.fillRect(QRect(0, 0, width(), height()), Qt::black); // black background

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

void EncoderSlider::mousePressEvent(QMouseEvent *event)
{
    if (!m_sliderBoundary.contains(event->pos()))
        return;

    const auto p = event->pos() - m_sliderBoundary.topLeft();
    setValue(map(p.y(), m_sliderBoundary.height(), 0.0f, minimum(), maximum()));

    emit sliderMoved(value());
}

void EncoderSlider::resizeEvent(QResizeEvent *event)
{
    setupChildComponents();
    QAbstractSlider::resizeEvent(event);
}

void EncoderSlider::setupChildComponents()
{
    m_sliderBoundary = QRect(QPoint(EC_WIDTH_PADDING, EC_LABEL_HEIGHT + EC_BUTTON_HEIGHT),
                             QSize(width() - EC_WIDTH_PADDING * 2, height() - EC_LABEL_HEIGHT - EC_BUTTON_HEIGHT * 2));

    const auto buttonSize = QSize(width() - EC_WIDTH_PADDING * 2, EC_BUTTON_HEIGHT);
    m_button_decrease.setFixedSize(buttonSize);
    m_button_increase.setFixedSize(buttonSize);

    m_button_increase.move(m_sliderBoundary.topLeft() - QPoint(0, EC_BUTTON_HEIGHT));
    m_button_decrease.move(m_sliderBoundary.bottomLeft());

    m_button_increase.setText("▲");
    m_button_decrease.setText("▼");

    m_label_name.setGeometry(QRect(0, 0, width(), EC_LABEL_HEIGHT / 2));
    m_label_value.setGeometry(QRect(0, EC_LABEL_HEIGHT / 2, width(), EC_LABEL_HEIGHT / 2));
}

QString EncoderSlider::encoderName() const
{
    return m_encoderName;
}

void EncoderSlider::setEncoderName(const QString &newEncoderName)
{
    if (m_encoderName == newEncoderName)
        return;
    m_encoderName = newEncoderName;
    emit encoderNameChanged();
    m_label_name.setText(encoderName());
}

int EncoderSlider::upperRestrictValue() const
{
    return m_upperRestrictValue;
}

void EncoderSlider::setUpperRestrictValue(int newUpperRestrictValue)
{
    if (m_upperRestrictValue == newUpperRestrictValue)
        return;
    m_upperRestrictValue = newUpperRestrictValue;
    emit upperRestrictValueChanged();
}
