//--------------------------------------------------------------------------
// [ ファイル名 ] : customEncoder.h
// [ 概      要 ] : CustomEncoderControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef CUSTOMENCODER_H
#define CUSTOMENCODER_H

#include <QAbstractSlider>
#include <QLabel>
#include "baseComponent/customPushButton.h"

class CustomEncoder : public QAbstractSlider {
    Q_OBJECT
    Q_PROPERTY(int UpperRestrictValue READ UpperRestrictValue WRITE SetUpperRestrictValue NOTIFY UpperRestrictValueChanged)

public:
    CustomEncoder(QWidget *parent = nullptr);

    int UpperRestrictValue() const;
    void SetUpperRestrictValue(int value);

signals:
    void UpperRestrictValueChanged();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    // disable mouse wheel scrolling
    virtual void wheelEvent(QWheelEvent *) override {}

    void SetupChildComponents();

private:
    QRect m_slider_boundary;
    CustomPushButton m_button_decrease;
    CustomPushButton m_button_increase;
    int m_upper_restrict_value;
};

#endif // CUSTOMENCODER_H
