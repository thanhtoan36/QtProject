#include "baseComponent/titleSelectButton.h"
#include "baseComponent/designPolicyDefine.h"
#include <QDebug>

#define TITLE_PADDING 1

TitleSelectButton::TitleSelectButton(QWidget *parent) : SelectButton(parent),
    m_title_visible(true),
    m_title(),
    m_title_label(this)
{
    m_title_label.resize(width() - 2 * TITLE_PADDING, 12);
    m_title_label.move(TITLE_PADDING, height() - m_title_label.height() - TITLE_PADDING);
    m_title_label.setObjectName("select_button_title_label");

    SetBackgroundColor(Qt::black);
    SetSelectedBackgroundColor(Qt::black);
}

bool TitleSelectButton::TitleVisible() const
{
    return m_title_visible;
}

void TitleSelectButton::SetTitleVisible(bool newTitleVisible)
{
    if (m_title_visible == newTitleVisible)
        return;
    m_title_visible = newTitleVisible;
    emit TitleVisibleChanged();

    m_title_label.setVisible(newTitleVisible);
}

QString TitleSelectButton::Title() const
{
    return m_title;
}

void TitleSelectButton::SetTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit TitleChanged();

    m_title_label.setText(newTitle);
}

void TitleSelectButton::resizeEvent(QResizeEvent *event)
{
    SelectButton::resizeEvent(event);
    m_title_label.setGeometry(TITLE_PADDING, height() - m_title_label.height() - TITLE_PADDING,
                              width() - 2 * TITLE_PADDING, m_title_label.height());
}
