#ifndef TITLESELECTBUTTON_H
#define TITLESELECTBUTTON_H
#include "selectButton.h"

class TitleSelectButton : public SelectButton
{
    Q_OBJECT

    Q_PROPERTY(bool TitleVisible READ TitleVisible WRITE SetTitleVisible NOTIFY TitleVisibleChanged)
    Q_PROPERTY(QString Title READ Title WRITE SetTitle NOTIFY TitleChanged)

public:
    explicit TitleSelectButton(QWidget *parent = nullptr);

    bool TitleVisible() const;
    void SetTitleVisible(bool value);

    QString Title() const;
    void SetTitle(const QString &value);

signals:
    void TitleVisibleChanged();
    void TitleChanged();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    bool m_title_visible;
    QString m_title;

    QLabel m_title_label;
};

#endif // TITLESELECTBUTTON_H
