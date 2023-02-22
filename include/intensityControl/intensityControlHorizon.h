#ifndef INTENSITYCONTROLHORIZON_H
#define INTENSITYCONTROLHORIZON_H

#include "intensityControl/intensityControl.h"

class IntensityControlHorizon : public IntensityControl
{
    Q_OBJECT
public:
    IntensityControlHorizon(QWidget *parent = nullptr);

protected:
    QVector<QSharedPointer<CustomPushButton>> m_menu_buttons;
};

#endif // INTENSITYCONTROLHORIZON_H
