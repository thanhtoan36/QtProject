#ifndef TESTDATAPARSER_H
#define TESTDATAPARSER_H

#include "colorFilterControl/colorFilterControl_datatypes.h"
#include "colorPickerControl/colorPickerControl_datatypes.h"
#include "encoderControl/encoderControl_datatypes.h"
#include "trackControl/trackControl_datatypes.h"
#include "inputNumControl/inputNumControl_datatypes.h"

// NOTE: Quick & dirty code, there will be memory leak


COLOR_PICKER_DISP_PARAM CPC_ParseInput(const QString &raw);
COLOR_FILTER_DISP_PARAM CFC_ParseInput(const QString &raw);
ENCODER_DISP_PARAM EC_ParseInput(const QString &raw);
TRACK_DISP_PARAM TC_ParseInput(const QString &raw);
INPUT_NUM_DISP_PARAM IN_ParseInput(const QString &raw);

#endif // TESTDATAPARSER_H
