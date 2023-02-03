#ifndef CUSTOMBUTTONBASE_H
#define CUSTOMBUTTONBASE_H

#include <QPushButton>

class CustomButtonBase : public QPushButton
{
    Q_OBJECT
public:
    explicit CustomButtonBase(QString text, QWidget *parent = nullptr);

    CustomButtonBase(QString text, int fontSize, QColor backgroundColor, QColor textColor, QWidget *parent = nullptr);

    void setFontSize(int newFont_size);

    void setBackgroundColor(const QColor &newBackground_color);

    void setTextColor(const QColor &newText_color);

private:
    int m_fontSize;
    QColor m_background_color;
    QColor m_text_color;
};

#endif // CUSTOMBUTTONBASE_H
