//--------------------------------------------------------------------------
// [ ファイル名 ] : customColorPickerXY.h
// [ 概   要 ] : ColorPickerXY Widget
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
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
    QColor GetColor(QPointF xy) const;

signals:
    void Picked();
    void XyChanged(QPointF xy);
    void ColorChanged(QColor color);

private:
    QPointF MapToPosition(const QPointF &p);
    QPointF MapToValue(const QPoint &p);
    void RBG2XY(float R,float G, float B, float& x, float& y, float &z);
    QPointF FindNearestXy(QPointF target);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QRectF m_plot_area;
    QSize m_offset;
    QPointF m_valid_xy;
    QPointF m_white_xy;
    QImage m_img;
    CIEMaker m_cie_maker;

    QPointF m_pointer;
    bool m_pointer_visible = false;
};

#endif // CUSTOMCOLORPICKERXY_H
