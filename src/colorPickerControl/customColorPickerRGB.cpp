#include "colorPickerControl/customColorPickerRGB.h"
#include "colorPickerControl/colorPickerControl_define.hpp"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#define PICKER_RGB_WIDTH  CPC_PICKER_RGB_GEOMETRY.width()
#define PICKER_RGB_HIEGHT CPC_PICKER_RGB_GEOMETRY.height()
#define H_MAX 359
#define S_MAX 255
#define V_MAX 255

CustomColorPickerRGB::CustomColorPickerRGB(QWidget *parent) : QWidget(parent),
    m_plotArea(QRectF(0, 0, PICKER_RGB_WIDTH, PICKER_RGB_HIEGHT)),
    m_img(PICKER_RGB_WIDTH, PICKER_RGB_HIEGHT, QImage::Format_RGB32)
{
    for(int x=0; x < PICKER_RGB_WIDTH; x++){
       for(int y=0; y < PICKER_RGB_HIEGHT; y++){
           QColor color;
           float h = (float)(x * H_MAX)/ (PICKER_RGB_WIDTH - 1);
           float s = (float)(y * S_MAX) / (PICKER_RGB_HIEGHT - 1);
           color.setHsv(h, s, 200);
           m_img.setPixel(PICKER_RGB_WIDTH - x - 1, PICKER_RGB_HIEGHT - y - 1, color.rgb());
       }
    }
}

hsv_t CustomColorPickerRGB::HSV() const
{
    return m_hsv;
}

void CustomColorPickerRGB::SetHSV(const int h, const int s, const int v)
{
    if (m_hsv.h != h || m_hsv.s != s || m_hsv.v != v)
    {
        m_hsv.h = h;
        m_hsv.s = s;
        m_hsv.v = v;
        int x = PICKER_RGB_WIDTH - 1 - (h * (PICKER_RGB_WIDTH - 1)) / H_MAX;
        int y = PICKER_RGB_HIEGHT - 1 - (s * (PICKER_RGB_HIEGHT - 1)) / S_MAX;
        m_pointer = QPointF(x,y);
        qDebug() << "x: " <<m_pointer.x() << "y: " << m_pointer.y();
        m_pointer_visible  = true;
        emit HSVChanged(m_hsv);
        update();
    }
}

void CustomColorPickerRGB::SetColor(const QColor &color)
{
    int h,s,v;
    color.getHsv(&h,&s,&v);
    SetHSV(h,s,v);
    m_color = color;
    emit ColorChanged(m_color);
}

QColor CustomColorPickerRGB::Color() const
{
    return m_color;
}

void CustomColorPickerRGB::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    p.drawImage(m_plotArea, m_img);

    if (m_pointer_visible) {
        p.setPen(QPen(Qt::white, 1));
        p.drawEllipse(m_pointer, 5, 5);
    }
}

void CustomColorPickerRGB::mousePressEvent(QMouseEvent *event)
{
    QPointF pos = event->pos();
    if(m_plotArea.contains(pos)){
         m_pointer = pos;
         m_pointer_visible = true;
         QColor c(m_img.pixel( pos.x(), pos.y() ));
         int h,s,v;
         c.getHsv(&h,&s,&v);
         qDebug() << "h: " << h <<"\n";
         qDebug() << "s: " << s <<"\n";
         qDebug() << "v: " << v <<"\n";
         SetHSV(h,s,m_hsv.v);
         update();
    }
}