#include "baseComponent/toggleButton.h"
#include "baseComponent/designPolicyDefine.h"
#include <QDebug>
#include <QTimer>

ToggleButton::ToggleButton(QWidget *parent) : CustomToggleButtonBase(parent) ,m_check_label(this)
{
    m_check_label.setText("✓");
    m_check_label.setStyleSheet("QLabel { background-color : transparent; color : white; }");
    m_check_label.setGeometry(2,2,10,10);
    m_check_label.setVisible(m_check_mark_visible && m_is_check_mark_enable);

    connect(this, &QAbstractButton::toggled, this,
            &ToggleButton::HandleToggled);

}

ToggleButton::ToggleButton(QString text, QWidget *parent):
    CustomToggleButtonBase(text,parent),
    m_check_label(this)
{
    m_check_label.setText("✓");
    m_check_label.setStyleSheet("QLabel { background-color : transparent; color : white; }");
    m_check_label.setGeometry(2,2,10,10);
    m_check_label.setVisible(m_check_mark_visible && m_is_check_mark_enable);
    SetFontSize(18);
}

ToggleButton::ToggleButton(QString text, bool isCheckMark, QWidget *parent):
    CustomToggleButtonBase(text, 18, SELECT_BUTTON_BG_COLOR_UNSELECTED, SELECT_BUTTON_TEXT_COLOR_UNSELECTED,parent),
    m_check_label(this),
    m_is_check_mark_enable(isCheckMark)
{
    m_check_label.setText("✓");
    m_check_label.setStyleSheet("QLabel { background-color : transparent; color : white; }");
    m_check_label.setGeometry(2,2,10,10);
    m_check_label.setVisible(m_check_mark_visible && m_is_check_mark_enable);
}

void ToggleButton::UpdateButtonStyles()
{
    QString style_enable = QString("QPushButton { background-color:rgb(13,13,13); color:rgb(128,128,128); border-style: solid; border-width: 1px;border-color: gray;}");
    QString style_disable = QString(" QPushButton:disabled { background-color:rgb(22,22,22); color:rgb(191,191,191); border-style: solid; border-width: 1px;border-color: gray; }");
    QString style_checked = QString(" QPushButton:checked { background-color:rgb(89, 89, 89); color: white; border-style: solid; border-width: 1px;border-color: rgb(0,176,80);}");

    setStyleSheet(style_enable + style_disable + style_checked);
}

bool ToggleButton::IsCheckMarkEnable() const
{
    return m_is_check_mark_enable;
}

void ToggleButton::setIsCheckMarkEnable(bool isCheckMark)
{
    m_is_check_mark_enable = isCheckMark;
    m_check_label.setVisible(m_check_mark_visible && m_is_check_mark_enable);
}

void ToggleButton::HandleToggled(bool checked)
{
    qDebug() << "ToggleButton::HandleButtonStateChanged " <<checked;
    if (!checked)
    {
        // SetBackgroundColor(SELECT_BUTTON_BG_COLOR_UNSELECTED);
        // SetTextColor(SELECT_BUTTON_TEXT_COLOR_UNSELECTED);
        SetCheckMarkVisible(false);
    }
    else
    {
        // SetBackgroundColor(SELECT_BUTTON_BG_COLOR_SELECTED);
        // SetTextColor(SELECT_BUTTON_TEXT_COLOR_SELECTED);
        SetCheckMarkVisible(true);
    }
}

void ToggleButton::SetCheckMarkVisible(bool visible)
{
    m_check_mark_visible = visible;
    m_check_label.setVisible(m_check_mark_visible && m_is_check_mark_enable);
}
