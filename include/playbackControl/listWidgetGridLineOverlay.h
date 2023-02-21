#ifndef LISTWIDGETGRIDLINEOVERLAY_H
#define LISTWIDGETGRIDLINEOVERLAY_H

#include <QWidget>

class ListWidgetGridLineOverlay : public QWidget
{
    Q_OBJECT
public:
    ListWidgetGridLineOverlay(QWidget *parent = nullptr);
    void SetColumnsWidth(const QVector<int> &value);

protected:
    virtual void paintEvent(QPaintEvent *e) override;
private:
    QVector<int> m_columns_width;
};


#endif // LISTWIDGETGRIDLINEOVERLAY_H
