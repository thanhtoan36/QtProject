#ifndef CUSTOMTOGGLEBUTTONBASE_H
#define CUSTOMTOGGLEBUTTONBASE_H

#include "customButtonBase.h"

class CustomToggleButtonBase : public CustomButtonBase
{
    Q_OBJECT
    Q_PROPERTY(QColor SelectedBackgroundColor READ SelectedBackgroundColor WRITE SetSelectedBackgroundColor NOTIFY SelectedBackgroundColorChanged)
    Q_PROPERTY(QColor SelectedBorderColor READ SelectedBorderColor WRITE SetSelectedBorderColor NOTIFY SelectedBorderColorChanged)
    Q_PROPERTY(QColor SelectedTextColor READ SelectedTextColor WRITE SetSelectedTextColor NOTIFY SelectedTextColorChanged)

public:
    explicit CustomToggleButtonBase(QWidget *parent = nullptr);

    QColor SelectedBorderColor() const;
    void SetSelectedBorderColor(const QColor &value);

    QColor SelectedTextColor() const;
    void SetSelectedTextColor(const QColor &value);

    QColor SelectedBackgroundColor() const;
    void SetSelectedBackgroundColor(const QColor &value);

signals:
    void SelectedBorderColorChanged();
    void SelectedTextColorChanged();
    void SelectedBackgroundColorChanged();

protected:

private:
    QColor m_selected_background_color;
    QColor m_selected_border_color;
    QColor m_selected_text_color;
};

#endif // CUSTOMTOGGLEBUTTONBASE_H
