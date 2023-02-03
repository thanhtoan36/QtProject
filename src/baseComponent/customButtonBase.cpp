#include "baseComponent/customButtonBase.h"


CustomButtonBase::CustomButtonBase(QString text, QWidget *parent) : QPushButton(parent)
{
    setText(text);
}

CustomButtonBase::CustomButtonBase(QString text, int fontSize, QColor backgroundColor, QColor textColor, QWidget *parent):
    QPushButton(parent),
    m_fontSize(fontSize),
    m_background_color(backgroundColor),
    m_text_color(textColor)
{
    setText(text);
    QFont font = this->font();
    font.setPointSize(m_fontSize);
    setFont(font);
    setBackgroundColor(backgroundColor);
    setTextColor(textColor);
}

void CustomButtonBase::setFontSize(int newFont_size)
{
    m_fontSize = newFont_size;
    QFont font = this->font();
    font.setPointSize(newFont_size);
    setFont(font);
}

void CustomButtonBase::setBackgroundColor(const QColor &newBackground_color)
{
    m_background_color = newBackground_color;
    QString style = "background:rgb(%1,%2,%3);";
    setStyleSheet(style.arg(m_background_color.red()).arg(m_background_color.green()).arg(m_background_color.blue()));
}

void CustomButtonBase::setTextColor(const QColor &newText_color)
{
    m_text_color = newText_color;
    QPalette pal = this->palette();
    pal.setColor(QPalette::ButtonText, m_text_color);
    this->setPalette(pal);
    this->repaint();
}



