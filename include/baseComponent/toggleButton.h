#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include "customToggleButtonBase.h"
#include <QLabel>

class ToggleButton : public CustomToggleButtonBase
{
    Q_OBJECT
    Q_PROPERTY(bool CheckMarkVisible READ CheckMarkVisible WRITE SetCheckMarkVisible NOTIFY CheckMarkVisibleChanged)

public:
    explicit ToggleButton(QWidget *parent = nullptr);

    bool CheckMarkVisible() const;
    void SetCheckMarkVisible(bool value);

public slots:

signals:
    void CheckMarkVisibleChanged();

protected:

private:
    QLabel m_check_label;
    bool m_check_mark_vsible;
};

#endif // TOGGLEBUTTON_H
