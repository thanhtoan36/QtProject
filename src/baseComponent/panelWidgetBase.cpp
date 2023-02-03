#include "baseComponent/panelWidgetBase.h"
#include "baseComponent/customButtonBase.h"
#include <QLabel>
PanelWidgetBase::PanelWidgetBase(int width, int height, QWidget *parent) : QWidget(parent), m_width(width), m_hieght(height)
{
    resize(m_width, m_hieght);
    setStyleSheet("background:rgb(50,64,75);");
    CustomButtonBase* btn = new CustomButtonBase("Toan",5,QColor(Qt::red),QColor(Qt::yellow),this);
    QLabel * a = new QLabel("√",this);
    a->setGeometry(130,10,50,50);
    btn->setGeometry(10,10,100,100);
}

void PanelWidgetBase::paintEvent(QPaintEvent *)
{

}

void PanelWidgetBase::closeEvent(QCloseEvent *)
{
    hide();
}
