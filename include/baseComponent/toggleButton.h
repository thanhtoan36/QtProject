#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include "customToggleButtonBase.h"
#include <QLabel>

class ToggleButton : public CustomToggleButtonBase
{
    Q_OBJECT
    Q_PROPERTY(bool checkMarkVisible READ checkMarkVisible WRITE setCheckMarkVisible NOTIFY checkMarkVisibleChanged)

public:
    explicit ToggleButton(QWidget *parent = nullptr);

    bool checkMarkVisible() const;
    void setCheckMarkVisible(bool newCheckMarkVisible);

public slots:

signals:
    void checkMarkVisibleChanged();

protected:

private:
    QLabel m_check_label;
    bool m_checkMarkVisible;
};

#endif // TOGGLEBUTTON_H
