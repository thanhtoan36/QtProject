#ifndef ENCODERSLIDER_H
#define ENCODERSLIDER_H

#include <QAbstractSlider>
#include <QLabel>
#include "../baseComponent/customPushButton.h"

class EncoderSlider : public QAbstractSlider {
    Q_OBJECT
    Q_PROPERTY(QString encoderName READ encoderName WRITE setEncoderName NOTIFY encoderNameChanged)
    Q_PROPERTY(int upperRestrictValue READ upperRestrictValue WRITE setUpperRestrictValue NOTIFY upperRestrictValueChanged)

public:
    EncoderSlider(QWidget *parent = nullptr);

    QString encoderName() const;
    void setEncoderName(const QString &newEncoderName);

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
    QLabel m_label_name;
    QLabel m_label_value;
    QRect m_sliderBoundary;
    CustomPushButton m_button_decrease;
    CustomPushButton m_button_increase;
    QString m_encoderName;
    int m_upperRestrictValue;
};

#endif // ENCODERSLIDER_H
