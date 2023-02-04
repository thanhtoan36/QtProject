#ifndef TITLESELECTBUTTON_H
#define TITLESELECTBUTTON_H
#include "selectButton.h"

class TitleSelectButton : public SelectButton
{
public:
    explicit TitleSelectButton(QWidget *parent = nullptr);

    TitleSelectButton(QString text, bool checkMarkEnable, bool titleEnable, QString title, QWidget *parent = nullptr);

    void SetTitleGeometry(int width, int height);

    void SetTitleFontSize(int size);

    void SetTitleTextColor();

private:
    QLabel m_title_label;
    bool m_is_title_enable = false;
};

#endif // TITLESELECTBUTTON_H
