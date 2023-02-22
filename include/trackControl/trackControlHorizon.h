//--------------------------------------------------------------------------
// [ ファイル名 ] : trackControlHorizon.h
// [ 概      要 ] : TrackControlHorizon
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef TRACKCONTROLHORIZON_H
#define TRACKCONTROLHORIZON_H

#include "trackControl.h"


class TrackControlHorizon : public TrackControl
{
public:
    TrackControlHorizon(QWidget *parent = nullptr);

protected:
    SelectButton m_button_emply_field_2; // place holder
};

#endif // TRACKCONTROLHORIZON_H
