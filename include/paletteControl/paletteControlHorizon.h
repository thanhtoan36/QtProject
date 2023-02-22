//--------------------------------------------------------------------------
// [ ファイル名 ] : paletteControlHorizon.h
// [ 概      要 ] : PaletteControlHorizon
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef PALETTECONTROLHORIZON_H
#define PALETTECONTROLHORIZON_H

#include "paletteControl.h"

class PaletteControlHorizon : public PaletteControl
{
public:
    explicit PaletteControlHorizon(QWidget* parent = nullptr);

protected:
    virtual void OnTypeChanged() override;
};

#endif // PALETTECONTROLHORIZON_H
