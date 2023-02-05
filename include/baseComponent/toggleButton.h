#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include "customToggleButtonBase.h"
#include <QLabel>

class ToggleButton : public CustomToggleButtonBase
{
    Q_OBJECT
public:
    explicit ToggleButton(QWidget *parent = nullptr);
    ToggleButton(QString text, QWidget *parent = nullptr);
    ToggleButton(QString text, bool isCheckMark, QWidget *parent = nullptr);

    bool IsCheckMarkEnable() const;
    void setIsCheckMarkEnable(bool isCheckMark);
    void SetCheckMarkVisible(bool visible);

public slots:
    virtual void HandleToggled(bool checked);

protected:
    virtual void UpdateButtonStyles() override;

private:
    QLabel m_check_label;
    bool m_is_check_mark_enable = true;
    bool m_check_mark_visible = false;
};

#endif // TOGGLEBUTTON_H
