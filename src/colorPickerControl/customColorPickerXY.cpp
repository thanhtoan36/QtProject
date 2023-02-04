#include "colorPickerControl/customColorPickerXY.h"
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

CustomColorPickerXY::CustomColorPickerXY(QWidget *parent) : QWidget(parent),
    m_plotArea(QRectF(36, 0,240, 240))
{
    QImage img(":/img/cie_img.png");
    m_img = img.scaled(240, 240, Qt::KeepAspectRatio,Qt::SmoothTransformation);

    m_mousePos.setParent(this);
    m_mousePos.setGeometry(0, 0, 200, 50);
    m_mousePos.show();

    setMouseTracking(true);
}

float CustomColorPickerXY::PointerX() const
{
    return m_pointer_x;
}

void CustomColorPickerXY::SetPointerX(float x)
{
    if (m_pointer_x != x)
    {
        m_pointer_x = x;
        emit PointerXChanged(x);
    }
}

float CustomColorPickerXY::PointerY() const
{
    return m_pointer_y;
}

void CustomColorPickerXY::SetPointerY(float y)
{
    if (m_pointer_y != y)
    {
        m_pointer_y = y;
        emit PointerYChanged(y);
    }
}

void CustomColorPickerXY::SetColor(const QColor &color)
{
    float x,y;
    RBG2XY(color.red(),color.green(),color.blue(),x,y);
    if (m_cie_maker.isPointInsideBound(CPointF(x,y)))
    {
        qDebug() << "SetColor\n";
        SetPointerX(x);
        SetPointerX(y);
        QPointF pos = mapToPosition(QPointF(x,y));
        m_pointer.setX(pos.x());
        m_pointer.setY(pos.y());
        m_pointer_visible = true;
        update();
    }
    else
    {
        qDebug() << "Color out of Boundary\n";
    }
}

void CustomColorPickerXY::paintEvent(QPaintEvent *)
{
    qDebug()<< "paint";
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
    if (m_pointer_visible)
    {
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
            m_mousePos.setText(QString("x:%1\ny:%2").arg(QString::number(p.x(), 'f', 3)).arg(QString::number(p.y(), 'f', 3)));
            SetPointerX(p.x());
            SetPointerX(p.y());
            m_pointer.setX(event->pos().x());
            m_pointer.setY(event->pos().y());
            m_pointer_visible = true;
            update();
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

