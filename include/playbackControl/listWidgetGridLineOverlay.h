#ifndef LISTWIDGETGRIDLINEOVERLAY_H
#define LISTWIDGETGRIDLINEOVERLAY_H

#include <QWidget>

class ListWidgetGridLineOverlay : public QWidget
{
    Q_OBJECT
public:
    ListWidgetGridLineOverlay(QWidget *parent = nullptr);
    void setColumnsWidth(const QVector<int> &columnsWidth);

protected:
    virtual void paintEvent(QPaintEvent *e) override;
private:
    QVector<int> m_columnsWidth;
};


#endif // LISTWIDGETGRIDLINEOVERLAY_H
