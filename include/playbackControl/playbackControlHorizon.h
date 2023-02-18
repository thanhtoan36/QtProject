#ifndef PLAYBACKCONTROLHORIZON_H
#define PLAYBACKCONTROLHORIZON_H

#include "playbackControl.hpp"

class PlaybackControlHorizon : public PlaybackControl
{
    Q_OBJECT

public:
    PlaybackControlHorizon(QWidget *parent = nullptr);
};

#endif // PLAYBACKCONTROLHORIZON_H
