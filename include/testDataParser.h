#ifndef TESTDATAPARSER_H
#define TESTDATAPARSER_H

#include "colorFilterControl/colorFilterControl_datatypes.h"
#include "colorPickerControl/colorPickerControl_datatypes.h"
#include "encoderControl/encoderControl_datatypes.h"
#include "trackControl/trackControl_datatypes.h"
#include "inputNumControl/inputNumControl_datatypes.h"
#include "playbackControl/playbackControl_datatypes.h"
#include "groupControl/groupControl_datatypes.h"
#include "libraryControl/libraryControl_datatypes.h"
#include "paletteControl/paletteControl_datatypes.h"

// NOTE: Quick & dirty code, there will be memory leak


COLOR_PICKER_DISP_PARAM CPC_ParseInput(const QString &raw);
COLOR_FILTER_DISP_PARAM CFC_ParseInput(const QString &raw);
ENCODER_DISP_PARAM EC_ParseInput(const QString &raw);
TRACK_DISP_PARAM TC_ParseInput(const QString &raw);
INPUT_NUM_DISP_PARAM INC_ParseInput(const QString &raw);
PLAYBACK_DISP_PARAM PLC_ParseInput(const QString &raw);
GROUP_DISP_PARAM GC_ParseInput(const QString &raw);
LIBRARY_DISP_PARAM LC_ParseInput(const QString &raw);
PALETTE_DISP_PARAM PD_ParseInput(const QString &raw);

#endif // TESTDATAPARSER_H
