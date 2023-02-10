#include "baseComponent/customButtonBase.h"
#include <QDebug>
#include <QTimer>

CustomButtonBase::CustomButtonBase(QWidget *parent) : QPushButton(parent)
{
    QObject::connect(this, &QPushButton::clicked,this, &CustomButtonBase::HandleButtonClicked);
    QTimer::singleShot(0, [&](){ UpdateButtonStyles(); });
}

void CustomButtonBase::SetFontSize(int fontSize)
{
    m_fontSize = fontSize;
    QFont font = this->font();
    font.setPixelSize(fontSize);
    setFont(font);
}

void CustomButtonBase::SetBackgroundColor(const QColor &backgroundColor)
{
    m_background_color = backgroundColor;
    QTimer::singleShot(0, [&](){ UpdateButtonStyles(); });
}

void CustomButtonBase::SetTextColor(const QColor &newText_color)
{
    m_text_color = newText_color;
    QTimer::singleShot(0, [&](){ UpdateButtonStyles(); });
}

void CustomButtonBase::UpdateButtonStyles()
{
    QString style = QString("QPushButton { background-color:rgb(%1,%2,%3); color:rgb(%4,%5,%6);border-style: solid;border-width: 1px;border-color: gray;}")
            .arg(m_background_color.red()).arg(m_background_color.green()).arg(m_background_color.blue())
            .arg(m_text_color.red()).arg(m_text_color.green()).arg(m_text_color.blue());

    setStyleSheet(style);
}

int CustomButtonBase::fontSize() const
{
    return m_fontSize;
}

const QColor &CustomButtonBase::BackgroundColor() const
{
    return m_background_color;
}

const QColor &CustomButtonBase::TextColor() const
{
    return m_text_color;
}


