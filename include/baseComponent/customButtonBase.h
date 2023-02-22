#ifndef CUSTOMBUTTONBASE_H
#define CUSTOMBUTTONBASE_H

#include <QPushButton>
#include "baseComponent/dynamicStyleSheet.h"

class CustomButtonBase : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY( QColor BackgroundColor READ BackgroundColor WRITE SetBackgroundColor NOTIFY BackgroundColorChanged )
    Q_PROPERTY( QColor BorderColor READ BorderColor WRITE SetBorderColor NOTIFY BorderColorChanged )
    Q_PROPERTY( QColor TextColor READ TextColor WRITE SetTextColor NOTIFY TextColorChanged )

    Q_PROPERTY( QColor DisabledBackgroundColor READ DisabledBackgroundColor WRITE SetDisabledBackgroundColor NOTIFY DisabledBackgroundColorChanged )
    Q_PROPERTY( QColor DisabledBorderColor READ DisabledBorderColor WRITE SetDisabledBorderColor NOTIFY DisabledBorderColorChanged )
    Q_PROPERTY( QColor DisabledTextColor READ DisabledTextColor WRITE SetDisabledTextColor NOTIFY DisabledTextColorChanged )

    Q_PROPERTY( int TextPixelSize READ TextPixelSize WRITE SetTextPixelSize NOTIFY TextPixelSizeChanged )

public:
    explicit CustomButtonBase( QWidget *parent = nullptr );

    QColor BackgroundColor() const;
    void SetBackgroundColor( const QColor &value );

    QColor TextColor() const;
    void SetTextColor( const QColor &value );

    int TextPixelSize() const;
    void SetTextPixelSize( int value );

    QColor BorderColor() const;
    void SetBorderColor( const QColor &value );

    QColor DisabledBackgroundColor() const;
    void SetDisabledBackgroundColor( const QColor &value );

    QColor DisabledBorderColor() const;
    void SetDisabledBorderColor( const QColor &value );

    QColor DisabledTextColor() const;
    void SetDisabledTextColor( const QColor &value );

public slots:

signals:
    void BackgroundColorChanged();
    void TextColorChanged();
    void TextPixelSizeChanged();
    void BorderColorChanged();

    void DisabledBackgroundColorChanged();
    void DisabledBorderColorChanged();

    void DisabledTextColorChanged();

protected:
    DynamicStyleSheet &CssStyler();

private:
    DynamicStyleSheet m_styler;
    QColor m_background_color;
    QColor m_border_color;
    QColor m_text_color;
    QColor m_disabled_background_color;
    QColor m_disabled_border_color;
    QColor m_disabled_text_color;
    int m_text_pixel_size;
};

#endif // CUSTOMBUTTONBASE_H
