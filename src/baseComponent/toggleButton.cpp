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
    SetBackgroundColor(QColor::fromRgb(13,13,13));
    SetTextColor(QColor::fromRgb(128,128,128));
    connect(this, &QAbstractButton::toggled, this,
            &ToggleButton::HandleToggled);

}

void ToggleButton::UpdateButtonStyles()
{
    QString style_enable = QString("QPushButton { background-color:rgb(%1,%2,%3); color:rgb(%4,%5,%6); border-style: solid; border-width: 1px;border-color: gray;}")
            .arg(BackgroundColor().red()).arg(BackgroundColor().green()).arg(BackgroundColor().blue())
            .arg(TextColor().red()).arg(TextColor().green()).arg(TextColor().blue());
    QString style_disable = QString(" QPushButton:disabled { background-color:rgb(22,22,22); color:rgb(191,191,191); border-style: solid; border-width: 1px;border-color: gray; }");
    QString style_checked = QString(" QPushButton:checked { background-color:rgb(89, 89, 89); color: white; border-style: solid; border-width: 2px;border-color: rgb(0,176,80);}");

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
    qDebug() << __func__ << checked;
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
