#ifndef CUSTOMTOGGLEBUTTONBASE_H
#define CUSTOMTOGGLEBUTTONBASE_H

#include "customButtonBase.h"

class CustomToggleButtonBase : public CustomButtonBase
{
    Q_OBJECT
    Q_PROPERTY(QColor selectedBackgroundColor READ selectedBackgroundColor WRITE setSelectedBackgroundColor NOTIFY selectedBackgroundColorChanged)
    Q_PROPERTY(QColor selectedBorderColor READ selectedBorderColor WRITE setSelectedBorderColor NOTIFY selectedBorderColorChanged)
    Q_PROPERTY(QColor selectedTextColor READ selectedTextColor WRITE setSelectedTextColor NOTIFY selectedTextColorChanged)

public:
    explicit CustomToggleButtonBase(QWidget *parent = nullptr);

    QColor selectedBorderColor() const;
    void setSelectedBorderColor(const QColor &newSelectedBorderColor);

    QColor selectedTextColor() const;
    void setSelectedTextColor(const QColor &newSelectedTextColor);

    QColor selectedBackgroundColor() const;
    void setSelectedBackgroundColor(const QColor &newSelectedBackgroundColor);

public slots:

signals:

    void selectedBorderColorChanged();
    void selectedTextColorChanged();
    void selectedBackgroundColorChanged();

protected:

private:
    QColor m_selectedBackgroundColor;
    QColor m_selectedBorderColor;
    QColor m_selectedTextColor;
};

#endif // CUSTOMTOGGLEBUTTONBASE_H
