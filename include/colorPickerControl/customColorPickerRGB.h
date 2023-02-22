//--------------------------------------------------------------------------
// [ ファイル名 ] : customColorPickerRGB.h
// [ 概   要 ] : ColorPickerRGB Widget
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef CUSTOMCOLORPICKERRGB_H
#define CUSTOMCOLORPICKERRGB_H

#include <QWidget>

typedef struct
{
    int h = 0;
    int s = 0;
    int v = 0;
} hsv_t;

class CustomColorPickerRGB : public QWidget
{
    Q_OBJECT
public:
    explicit CustomColorPickerRGB( QWidget *parent = nullptr );

    hsv_t HSV() const;

    void SetHSV( const int h, const int s, const int v );

    void SetColor( const QColor &color );

    QColor Color() const;
signals:
    void HSVChanged( const hsv_t &value );
    void ColorChanged( const QColor &color );
    void Picked();

protected:
    void paintEvent( QPaintEvent *event ) override;
    void mousePressEvent( QMouseEvent *event ) override;

private:
    QRectF m_plot_area;
    QImage m_img;
    hsv_t m_hsv;
    QColor m_color;
    QPointF m_pointer;
    bool m_pointer_visible = false;
};
#endif // CUSTOMCOLORPICKERRGB_H
