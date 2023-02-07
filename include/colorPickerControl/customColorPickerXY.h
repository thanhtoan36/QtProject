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

    void SetColor(const QColor& color);
    void SetXy(const QPointF& xy);
    QPointF Xy() const;
    QColor Color() const;
    QColor getColor(QPointF xy) const;

signals:
    void picked();
    void XyChanged(QPointF xy);
    void ColorChanged(QColor color);

private:
    QPointF mapToPosition(const QPointF &p);
    QPointF mapToValue(const QPoint &p);
    void RBG2XY(float R,float G, float B, float& x, float& y, float &z);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QRectF m_plotArea;
    QSize m_offset;
    QPointF m_xy;
    QImage m_img;
    CIEMaker m_cie_maker;

    QPointF m_pointer;
    bool m_pointer_visible = false;
};

#endif // CUSTOMCOLORPICKERXY_H
