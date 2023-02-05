#ifndef CUSTOMBUTTONBASE_H
#define CUSTOMBUTTONBASE_H

#include <QPushButton>

class CustomButtonBase : public QPushButton
{
    Q_OBJECT
public:
    explicit CustomButtonBase(QWidget *parent = nullptr);

    CustomButtonBase(QString text, QWidget *parent = nullptr);

    CustomButtonBase(QString text, int fontSize, QColor backgroundColor, QColor textColor, QWidget *parent = nullptr);

    void SetFontSize(int fontSize);

    void SetBackgroundColor(const QColor &backgroundColor);

    void SetTextColor(const QColor &newText_color);

    int fontSize() const;

    const QColor &BackgroundColor() const;

    const QColor &TextColor() const;

public slots:
    virtual void HandleButtonClicked() {};

protected:
    virtual void UpdateButtonStyles();

private:
    int m_fontSize;
    QColor m_background_color;
    QColor m_text_color;
};

#endif // CUSTOMBUTTONBASE_H
