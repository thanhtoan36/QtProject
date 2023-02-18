#ifndef TRACKCONTROLHORIZON_H
#define TRACKCONTROLHORIZON_H

#include "trackControl.hpp"


class TrackControlHorizon : public TrackControl
{
public:
    TrackControlHorizon(QWidget *parent = nullptr);

protected:
    SelectButton m_button_emply_field_2; // place holder
};

#endif // TRACKCONTROLHORIZON_H
