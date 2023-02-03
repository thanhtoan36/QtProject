#ifndef PANELWIDGETBASE_H
#define PANELWIDGETBASE_H

#include <QWidget>

class PanelWidgetBase : public QWidget
{
    Q_OBJECT
public:
    explicit PanelWidgetBase(int width, int height, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;
    void closeEvent(QCloseEvent*) override;
private:
    int m_width;
    int m_hieght;
};

#endif // PANELWIDGETBASE_H
