#ifndef CUSTOMCOLORPICKERXY_H
#define CUSTOMCOLORPICKERXY_H

#include <QWidget>
#include <QLabel>
#include "colorPickerControl/ciemaker.h"
class CustomColorPickerXY : public QWidget
{
    Q_OBJECT
public:
    explicit CustomColorPickerXY(QWidget *parent = nullptr);

    float PointerX() const;
    void SetPointerX(const float x);

    float PointerY() const;
    void SetPointerY(const float y);

    void SetColor(const QColor& color);
signals:
    void PointerXChanged(float value);
    void PointerYChanged(float value);

private:
    QPointF mapToPosition(const QPointF &p);
    QPointF mapToValue(const QPoint &p);
    void RBG2XY(float R,float G, float B, float& x, float& y);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QRectF m_plotArea;
    QSize m_offset;
    QLabel m_mousePos;
    QPointF m_pointer;
    bool m_pointer_visible = false;
    QPixmap m_ciePic;
    QImage m_img;
    CIEMaker m_cie_maker;

    float m_pointer_x;
    float m_pointer_y;
};

#endif // CUSTOMCOLORPICKERXY_H
