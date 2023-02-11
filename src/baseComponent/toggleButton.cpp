#include "baseComponent/toggleButton.h"
#include "baseComponent/designPolicyDefine.h"
#include <QDebug>
#include <QTimer>

ToggleButton::ToggleButton(QWidget *parent) : CustomToggleButtonBase(parent), m_check_label(this)
{
    m_check_label.setText("✓");
    m_check_label.setStyleSheet("QLabel { background-color: transparent; color : white; }");
    m_check_label.setGeometry(2,2,10,10);


    connect(this, &QAbstractButton::toggled, this, [&](bool) {
       m_check_label.setVisible(isChecked() && checkMarkVisible());
    });
    connect(this, &ToggleButton::checkMarkVisibleChanged, this, [&]() {
       m_check_label.setVisible(isChecked() && checkMarkVisible());
    });

    setCheckMarkVisible(false);
    m_check_label.setVisible(isChecked() && checkMarkVisible());
}

bool ToggleButton::checkMarkVisible() const
{
    return m_checkMarkVisible;
}

void ToggleButton::setCheckMarkVisible(bool newCheckMarkVisible)
{
    if (m_checkMarkVisible == newCheckMarkVisible)
        return;
    m_checkMarkVisible = newCheckMarkVisible;
    emit checkMarkVisibleChanged();
}
