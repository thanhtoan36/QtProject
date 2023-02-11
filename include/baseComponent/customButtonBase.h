#ifndef CUSTOMBUTTONBASE_H
#define CUSTOMBUTTONBASE_H

#include <QPushButton>
#include "baseComponent/dynamicStyleSheet.h"

class CustomButtonBase : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)

    Q_PROPERTY(QColor disabledBackgroundColor READ disabledBackgroundColor WRITE setDisabledBackgroundColor NOTIFY disabledBackgroundColorChanged)
    Q_PROPERTY(QColor disabledBorderColor READ disabledBorderColor WRITE setDisabledBorderColor NOTIFY disabledBorderColorChanged)
    Q_PROPERTY(QColor disabledTextColor READ disabledTextColor WRITE setDisabledTextColor NOTIFY disabledTextColorChanged)

    Q_PROPERTY(int textPixelSize READ textPixelSize WRITE setTextPixelSize NOTIFY textPixelSizeChanged)

public:
    explicit CustomButtonBase(QWidget *parent = nullptr);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &newBackgroundColor);

    QColor textColor() const;
    void setTextColor(const QColor &newTextColor);

    int textPixelSize() const;
    void setTextPixelSize(int newTextPixelSize);

    QColor borderColor() const;
    void setBorderColor(const QColor &newBorderColor);

    QColor disabledBackgroundColor() const;
    void setDisabledBackgroundColor(const QColor &newDisabledBackgroundColor);

    QColor disabledBorderColor() const;
    void setDisabledBorderColor(const QColor &newDisabledBorderColor);

    QColor disabledTextColor() const;
    void setDisabledTextColor(const QColor &newDisabledTextColor);

public slots:

signals:
    void backgroundColorChanged();
    void textColorChanged();
    void textPixelSizeChanged();
    void borderColorChanged();

    void disabledBackgroundColorChanged();
    void disabledBorderColorChanged();

    void disabledTextColorChanged();

protected:
    DynamicStyleSheet &cssStyler();

private:
    DynamicStyleSheet m_styler;
    QString m_stylesheetTemplate;
    QColor m_backgroundColor;
    QColor m_borderColor;
    QColor m_textColor;
    QColor m_disabledBackgroundColor;
    QColor m_disabledBorderColor;
    QColor m_disabledTextColor;
    int m_textPixelSize;
};

#endif // CUSTOMBUTTONBASE_H
