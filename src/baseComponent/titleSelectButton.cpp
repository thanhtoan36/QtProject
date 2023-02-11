#include "baseComponent/titleSelectButton.h"
#include "baseComponent/designPolicyDefine.h"
#include <QDebug>

TitleSelectButton::TitleSelectButton(QWidget *parent) : SelectButton(parent),
    m_titleVisible(true),
    m_title(),
    m_title_label(this)
{
    m_title_label.resize(width(), 15);
    m_title_label.move(0, height() - m_title_label.height());
    m_title_label.setObjectName("select_button_title_label");

    setBackgroundColor(Qt::black);
    setSelectedBackgroundColor(Qt::black);

    setTitle("test");
}

bool TitleSelectButton::titleVisible() const
{
    return m_titleVisible;
}

void TitleSelectButton::setTitleVisible(bool newTitleVisible)
{
    if (m_titleVisible == newTitleVisible)
        return;
    m_titleVisible = newTitleVisible;
    emit titleVisibleChanged();

    m_title_label.setVisible(newTitleVisible);
}

QString TitleSelectButton::title() const
{
    return m_title;
}

void TitleSelectButton::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();

    m_title_label.setText(newTitle);
}

void TitleSelectButton::resizeEvent(QResizeEvent *event)
{
    SelectButton::resizeEvent(event);
    m_title_label.setGeometry(0, height() - m_title_label.height(),
                              width(), m_title_label.height());
}
