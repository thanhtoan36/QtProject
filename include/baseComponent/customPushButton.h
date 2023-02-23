//--------------------------------------------------------------------------
// [ ファイル名 ] : customPushButton.h
// [ 概      要 ] : Custom Push Button widget
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include "customButtonBase.h"

class CustomPushButton : public CustomButtonBase
{
    Q_OBJECT
public:
    explicit CustomPushButton( QWidget *parent = nullptr );

public slots:

protected:
};

#endif // CUSTOMPUSHBUTTON_H
