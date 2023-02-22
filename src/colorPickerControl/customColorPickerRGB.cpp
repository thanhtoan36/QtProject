//--------------------------------------------------------------------------
// [ ファイル名 ] : customColorPickerRGB.cpp
// [ 概      要 ] : ColorPickerRGB Widget
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "colorPickerControl/customColorPickerRGB.h"
#include "colorPickerControl/colorPickerControl_define.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#define PICKER_RGB_WIDTH  CPC_PICKER_RGB_GEOMETRY.width()
#define PICKER_RGB_HEIGHT CPC_PICKER_RGB_GEOMETRY.height()
#define H_MAX 359
#define S_MAX 255
#define V_MAX 255

CustomColorPickerRGB::CustomColorPickerRGB(QWidget *parent) : QWidget(parent),
    m_plot_area(QRectF(0, 0, PICKER_RGB_WIDTH, PICKER_RGB_HEIGHT)),
    m_img(PICKER_RGB_WIDTH, PICKER_RGB_HEIGHT, QImage::Format_RGB32)
{
    for(int x=0; x < PICKER_RGB_WIDTH; x++){
       for(int y=0; y < PICKER_RGB_HEIGHT; y++){
           QColor color;
           int h = (x * H_MAX)/ (PICKER_RGB_WIDTH - 1);
           int s = (y * S_MAX) / (PICKER_RGB_HEIGHT - 1);
           color.setHsv(h, s, 200);
           m_img.setPixel(x, PICKER_RGB_HEIGHT - y - 1, color.rgb());
       }
    }
}

hsv_t CustomColorPickerRGB::HSV() const
{
    return m_hsv;
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetHSV
//  [ 機能名   ] : Set H S V value and update pointer to picker widget
//  [ 引数	  ] : const int h : h value
//                const int s : s value
//                const int v : v value
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void CustomColorPickerRGB::SetHSV(const int h, const int s, const int v)
{
    if (m_hsv.h != h || m_hsv.s != s || m_hsv.v != v)
    {
        m_hsv.h = h;
        m_hsv.s = s;
        m_hsv.v = v;
        m_color = QColor::fromHsv(h, s, v);
        int x = (h * (PICKER_RGB_WIDTH - 1)) / H_MAX;
        int y = PICKER_RGB_HEIGHT - 1 - (s * (PICKER_RGB_HEIGHT - 1)) / S_MAX;
        m_pointer = QPointF(x,y);
        m_pointer_visible  = true;
        emit HSVChanged(m_hsv);
        update();
    }
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : SetColor
//  [ 機能名   ] : Set picked color
//  [ 引数	  ] : const QColor &color : color need to set
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void CustomColorPickerRGB::SetColor(const QColor &color)
{
    if (m_color == color)
        return;

    int h,s,v;
    color.getHsv(&h,&s,&v);
    SetHSV(h,s,v);
    emit ColorChanged(m_color);
}

QColor CustomColorPickerRGB::Color() const
{
    return m_color;
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : paintEvent
//  [ 機能名   ] : overwrite paint event and draw widget
//  [ 引数	  ] : QPaintEvent *
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void CustomColorPickerRGB::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    p.drawImage(m_plot_area, m_img);

    if (m_pointer_visible) {
        p.setPen(QPen(Qt::white, 1));
        p.drawEllipse(m_pointer, 5, 5);
        p.setPen(QPen(Qt::gray, 1));
        p.drawEllipse(m_pointer, 6, 6);
    }
}

//--------------------------------------------------------------------------
//  [ 関数名   ] : mousePressEvent
//  [ 機能名   ] : handle press event to pick color
//  [ 引数	  ] : QMouseEvent *event : press event
//  [ 戻り値    ] : void
//--------------------------------------------------------------------------
void CustomColorPickerRGB::mousePressEvent(QMouseEvent *event)
{
    QPointF pos = event->pos();
    if(m_plot_area.contains(pos)){
         m_pointer = pos;
         m_pointer_visible = true;
         int h = (m_pointer.x()) * H_MAX / (PICKER_RGB_WIDTH - 1);
         int s = (PICKER_RGB_HEIGHT - 1 - m_pointer.y()) * S_MAX / (PICKER_RGB_HEIGHT - 1);
         SetColor(QColor::fromHsv(h,s,m_hsv.v));
         emit Picked();
    }
}
