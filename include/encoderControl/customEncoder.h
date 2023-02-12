#ifndef CUSTOMENCODER_H
#define CUSTOMENCODER_H

#include <QAbstractSlider>
#include <QLabel>
#include "../baseComponent/customPushButton.h"

class CustomEncoder : public QAbstractSlider {
    Q_OBJECT
    Q_PROPERTY(int upperRestrictValue READ upperRestrictValue WRITE setUpperRestrictValue NOTIFY upperRestrictValueChanged)

public:
    CustomEncoder(QWidget *parent = nullptr);

    int upperRestrictValue() const;
    void setUpperRestrictValue(int newUpperRestrictValue);

signals:
    void encoderNameChanged();

    void upperRestrictValueChanged();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    // disable mouse wheel scrolling
    virtual void wheelEvent(QWheelEvent *) override {}

    void setupChildComponents();

private:
    QRect m_sliderBoundary;
    CustomPushButton m_button_decrease;
    CustomPushButton m_button_increase;
    int m_upperRestrictValue;
};

#endif // CUSTOMENCODER_H
