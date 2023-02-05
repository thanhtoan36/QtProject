#ifndef CUSTOMTOGGLEBUTTONBASE_H
#define CUSTOMTOGGLEBUTTONBASE_H

#include "customButtonBase.h"

class CustomToggleButtonBase : public CustomButtonBase
{
    Q_OBJECT
public:
    explicit CustomToggleButtonBase(QWidget *parent = nullptr);

    CustomToggleButtonBase(QString text, QWidget *parent = nullptr);

    CustomToggleButtonBase(QString text, int fontSize, QColor backgroundColor, QColor textColor, QWidget *parent = nullptr);

    const QColor &PressBackgroundColor() const;
    void SetPressBackgroundColor(const QColor &backgroundColor);

    const QColor &PressTextColor() const;
    void SetPressTextColor(const QColor &textColor);

public slots:
    virtual void HandleButtonClicked() override;

signals:
    void ButtonStateChange(uint8_t newValue);

protected:
    virtual void UpdateButtonStyles() override;

private:
    QColor m_press_background_color;
    QColor m_press_text_color;
};

#endif // CUSTOMTOGGLEBUTTONBASE_H
