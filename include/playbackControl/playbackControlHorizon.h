//--------------------------------------------------------------------------
// [ ファイル名 ] : playbackControlHorizon.h
// [ 概      要 ] : PlaybackControlHorizon
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef PLAYBACKCONTROLHORIZON_H
#define PLAYBACKCONTROLHORIZON_H

#include "playbackControl.h"

class PlaybackControlHorizon : public PlaybackControl
{
    Q_OBJECT

public:
    PlaybackControlHorizon(QWidget *parent = nullptr);
};

#endif // PLAYBACKCONTROLHORIZON_H
