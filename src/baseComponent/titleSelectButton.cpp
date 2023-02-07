#include "baseComponent/titleSelectButton.h"
#include "baseComponent/designPolicyDefine.h"
#include <QDebug>

TitleSelectButton::TitleSelectButton(QWidget *parent) : SelectButton(parent) , m_title_label(this)
{
    m_title_label.setText("");
    SetTitleFontSize(12);
    SetTitleTextColor();
    m_title_label.setAlignment(Qt::AlignCenter);
}


void TitleSelectButton::SetTitleGeometry(int width, int height)
{
    m_title_label.setGeometry(0,3*height/4,width,height/4);
}

void TitleSelectButton::SetTitleFontSize(int size)
{
    QFont font = m_title_label.font();
    font.setPixelSize(size);
    m_title_label.setFont(font);
}

void TitleSelectButton::SetTitleTextColor()
{
    QString style_enable = QString("QLabel { background-color:rgb(51,63,79); color:rgb(217,217,217);}");

    m_title_label.setStyleSheet(style_enable);
}

void TitleSelectButton::SetTitleText(const QString &text)
{
    if (m_is_title_enable)
    {
        m_title_label.setText(text);
    }
}

