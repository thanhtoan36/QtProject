#ifndef PALETTECONTROLHORIZON_H
#define PALETTECONTROLHORIZON_H

#include "paletteControl.hpp"

class PaletteControlHorizon : public PaletteControl
{
public:
    explicit PaletteControlHorizon(QWidget* parent = nullptr);
protected:
    virtual void SetupUiComponents() override;
};

#endif // PALETTECONTROLHORIZON_H