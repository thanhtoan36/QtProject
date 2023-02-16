#ifndef INTENSITYCONTROLHORIZON_H
#define INTENSITYCONTROLHORIZON_H

#include "intensityControl/intensityControl.hpp"

class IntensityControlHorizon : public IntensityControl
{
    Q_OBJECT
public:
    IntensityControlHorizon(QWidget *parent = nullptr);

protected:
    virtual void SetupUiComponents() override;
};

#endif // INTENSITYCONTROLHORIZON_H
