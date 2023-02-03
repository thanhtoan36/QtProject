#include "baseComponent/panelWidgetBase.h"

PanelWidgetBase::PanelWidgetBase(int width, int height, QWidget *parent) : QWidget(parent), m_width(width), m_hieght(height)
{

}

void PanelWidgetBase::paintEvent(QPaintEvent *)
{
    this->resize(m_width, m_hieght);
    this->setStyleSheet("background:rgb(50,64,75);");
}

void PanelWidgetBase::closeEvent(QCloseEvent *)
{
    hide();
}
