#ifndef TITLESELECTBUTTON_H
#define TITLESELECTBUTTON_H
#include "selectButton.h"

class TitleSelectButton : public SelectButton
{
    Q_OBJECT

    Q_PROPERTY(bool titleVisible READ titleVisible WRITE setTitleVisible NOTIFY titleVisibleChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

public:
    explicit TitleSelectButton(QWidget *parent = nullptr);

    bool titleVisible() const;
    void setTitleVisible(bool newTitleVisible);

    QString title() const;
    void setTitle(const QString &newTitle);

signals:
    void titleVisibleChanged();
    void titleChanged();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    bool m_titleVisible;
    QString m_title;

    QLabel m_title_label;
};

#endif // TITLESELECTBUTTON_H
