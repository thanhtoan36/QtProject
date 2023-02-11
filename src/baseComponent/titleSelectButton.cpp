#include "baseComponent/titleSelectButton.h"
#include "baseComponent/designPolicyDefine.h"
#include <QDebug>

#define TITLE_PADDING 1

TitleSelectButton::TitleSelectButton(QWidget *parent) : SelectButton(parent),
    m_titleVisible(true),
    m_title(),
    m_title_label(this)
{
    m_title_label.resize(width() - 2 * TITLE_PADDING, 12);
    m_title_label.move(TITLE_PADDING, height() - m_title_label.height() - TITLE_PADDING);
    m_title_label.setObjectName("select_button_title_label");

    setBackgroundColor(Qt::black);
    setSelectedBackgroundColor(Qt::black);
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
    m_title_label.setGeometry(TITLE_PADDING, height() - m_title_label.height() - TITLE_PADDING,
                              width() - 2 * TITLE_PADDING, m_title_label.height());
}
