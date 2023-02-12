#ifndef TESTDATAPARSER_H
#define TESTDATAPARSER_H

#include "colorFilterControl/colorFilterControl_datatypes.h"
#include "colorPickerControl/colorPickerControl_datatypes.h"

// NOTE: Quick & dirty code, there will be memory leak


COLOR_PICKER_DISP_PARAM CPC_ParseInput(const QString &raw);

#endif // TESTDATAPARSER_H
