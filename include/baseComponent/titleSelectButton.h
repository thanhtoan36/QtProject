#ifndef TITLESELECTBUTTON_H
#define TITLESELECTBUTTON_H
#include "selectButton.h"

class TitleSelectButton : public SelectButton
{
public:
    explicit TitleSelectButton(QWidget *parent = nullptr);

    void SetTitleGeometry(int width, int height);

    void SetTitleFontSize(int size);

    void SetTitleTextColor();

    void SetTitleText(const QString& text);

private:
    QLabel m_title_label;
    bool m_is_title_enable = false;
};

#endif // TITLESELECTBUTTON_H
