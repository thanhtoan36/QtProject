//--------------------------------------------------------------------------
// [ ファイル名 ] : testDataParser.h
// [ 概      要 ] : Create test data from JSON
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

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


COLOR_PICKER_DISP_PARAM ParseInput_ColorPicker( const QString &raw );
COLOR_FILTER_DISP_PARAM ParseInput_ColorFilter( const QString &raw );
ENCODER_DISP_PARAM ParseInput_Encoder( const QString &raw );
TRACK_DISP_PARAM ParseInput_Track( const QString &raw );
INPUT_NUM_DISP_PARAM ParseInput_InputNum( const QString &raw );
PLAYBACK_DISP_PARAM ParseInput_Playback( const QString &raw );
GROUP_DISP_PARAM ParseInput_Group( const QString &raw );
LIBRARY_DISP_PARAM ParseInput_Library( const QString &raw );
PALETTE_DISP_PARAM ParseInput_Palette( const QString &raw );

#endif // TESTDATAPARSER_H
