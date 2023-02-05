#include "colorPickerControl/customColorPickerXY.h"
#include "colorPickerControl/colorPickerControl_define.hpp"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <math.h>

/**
 * @brief Inverse sRGB gamma correction, transforms R' to R
 */
#define INVGAMMACORRECTION(t)	\
    (((t) <= 0.0404482362771076) ? \
    ((t)/12.92) : pow(((t) + 0.055)/1.055, 2.4))

#define PICKER_XY_WIDTH  CPC_PICKER_XY_GEOMETRY.width()
#define PICKER_XY_HIEGHT CPC_PICKER_XY_GEOMETRY.height()

CustomColorPickerXY::CustomColorPickerXY(QWidget *parent) : QWidget(parent),
    m_plotArea(QRectF(36, 0,PICKER_XY_HIEGHT, PICKER_XY_HIEGHT))
{
    QImage img(":/img/cie_img.png");
    m_img = img.scaled(PICKER_XY_HIEGHT, PICKER_XY_HIEGHT, Qt::KeepAspectRatio,Qt::SmoothTransformation);
    setMouseTracking(true);
}

void CustomColorPickerXY::SetColor(const QColor &color)
{
    float x,y;
    RBG2XY(color.red(),color.green(),color.blue(),x,y);
    SetXy(QPointF(x, y));
}

void CustomColorPickerXY::SetXy(const QPointF &xy)
{
    if (m_cie_maker.isPointInsideBound(CPointF(xy.x(), xy.y())))
    {
        qDebug() << "SetColor\n";
        m_pointer = mapToPosition(xy);
        m_pointer_visible = true;
        update();

        if (xy != m_xy) {
            m_xy = xy;
            emit XyChanged(xy);
            emit ColorChanged(Color());
        }
    }
    else
    {
        qDebug() << "Color out of Boundary\n";
    }
}

QPointF CustomColorPickerXY::Xy() const
{
    return m_xy;
}

QColor CustomColorPickerXY::Color() const
{
    // TODO: add conversions
    return QColor();
}

void CustomColorPickerXY::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);


    p.setPen(QPen(Qt::gray, 1));
    p.drawLine(m_plotArea.bottomLeft(), m_plotArea.topLeft());
    p.drawLine(m_plotArea.bottomLeft(), m_plotArea.bottomRight());

    for (int i = 1; i <= 10; i++)
    {
        p.setPen(QPen(Qt::lightGray, 0.1));
        p.drawLine(QPointF(m_plotArea.bottomLeft().rx() +24*i,m_plotArea.bottomLeft().ry()), QPointF(m_plotArea.topLeft().rx() +24*i,m_plotArea.topLeft().ry()));
        p.drawLine(QPointF(m_plotArea.topLeft().rx() ,m_plotArea.topLeft().ry()+24*(i-1)), QPointF(m_plotArea.topRight().rx(),m_plotArea.topRight().ry() +24*(i-1)));
    }

    p.drawImage(m_plotArea, m_img);
    if (m_pointer_visible) {
        p.setPen(QPen(Qt::white, 1));
        p.drawEllipse(m_pointer, 5, 5);
    }
}

void CustomColorPickerXY::mousePressEvent(QMouseEvent *event)
{
    if(m_plotArea.contains(event->pos())){
        QPointF p = mapToValue(event->pos());
        CPointF curP(p.x(),p.y());
        if(m_cie_maker.isPointInsideBound(curP)){
            SetXy(p);
        }
    }
}

QPointF CustomColorPickerXY::mapToPosition(const QPointF &p)
{
    return QPointF(m_plotArea.x()+m_plotArea.width()*p.x(),
                  m_offset.height()+m_plotArea.height()*(1-p.y()));
}

QPointF CustomColorPickerXY::mapToValue(const QPoint &p)
{
    return QPointF(1.0f*(p.x()-m_plotArea.x())/m_plotArea.width(),
                   1.0f*(m_plotArea.y()+m_plotArea.height()-p.y())/m_plotArea.height());
}

void CustomColorPickerXY::RBG2XY(float R, float G, float B, float &x, float &y)
{
    R = INVGAMMACORRECTION(R);
    G = INVGAMMACORRECTION(G);
    B = INVGAMMACORRECTION(B);

    float X,Y,Z;
    X = (float)(0.4123955889674142161*R + 0.3575834307637148171*G + 0.1804926473817015735*B);
    Y = (float)(0.2125862307855955516*R + 0.7151703037034108499*G + 0.07220049864333622685*B);
    Z = (float)(0.01929721549174694484*R + 0.1191838645808485318*G + 0.9504971251315797660*B);

    x = X / (X + Y + Z);
    y = Y / (X + Y + Z);
}

