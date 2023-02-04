#ifndef CUSTOMTOGGLEBUTTONBASE_H
#define CUSTOMTOGGLEBUTTONBASE_H

#include "customButtonBase.h"

class CustomToggleButtonBase : public CustomButtonBase
{
    Q_OBJECT
public:
    enum ToggleButtonState
    {
        TOGGLE_BUTTON_STATE_ON,
        TOGGLE_BUTTON_STATE_OFF
    };
    explicit CustomToggleButtonBase(QWidget *parent = nullptr);

    CustomToggleButtonBase(QString text, QWidget *parent = nullptr);

    CustomToggleButtonBase(QString text, int fontSize, QColor backgroundColor, QColor textColor, QWidget *parent = nullptr);

    const QColor &PressBackgroundColor() const;
    void SetPressBackgroundColor(const QColor &backgroundColor);

    const QColor &PressTextColor() const;
    void SetPressTextColor(const QColor &textColor);

    ToggleButtonState ButtonState() const;
    void SetButtonState(ToggleButtonState state);

public slots:
    virtual void HandleButtonClicked() override;
    virtual void HandleButtonStateChanged(uint8_t state);

signals:
    virtual void ButtonStateChange(uint8_t newValue);

protected:
    virtual void SetStyleButton() override;

private:
    QColor m_press_background_color;
    QColor m_press_text_color;
    ToggleButtonState m_button_state = TOGGLE_BUTTON_STATE_OFF;
};

#endif // CUSTOMTOGGLEBUTTONBASE_H
