//--------------------------------------------------------------------------
// [ ファイル名 ] : intensityControlHorizon.h
// [ 概      要 ] : インテンシティコントロール水平ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef INTENSITYCONTROLHORIZON_H
#define INTENSITYCONTROLHORIZON_H

#include "intensityControl/intensityControl.h"

class IntensityControlHorizon : public IntensityControl
{
    Q_OBJECT
public:
    IntensityControlHorizon( QWidget *parent = nullptr );
};

#endif // INTENSITYCONTROLHORIZON_H
