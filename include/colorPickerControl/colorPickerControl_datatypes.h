//--------------------------------------------------------------------------
// [ ファイル名 ] : colorPickerControl_datatypes.h.h
// [ 概      要 ] : Type definitions for ColorPickerControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef COLORPICKERCONTROL_DATATYPES_H
#define COLORPICKERCONTROL_DATATYPES_H

#include <QColor>

// カラーピッカー表示タイプ
enum ColorPickerType
{
    COLOR_PICKER_TYPE_XY,           // xy
    COLOR_PICKER_TYPE_RGB           // RGB
};

// カラーピッカー表示パラメータ
typedef struct
{
    ColorPickerType     type;       // 表示するカラーピッカータイプ
    QColor              color;      // カラー
} COLOR_PICKER_DISP_PARAM;

#endif // COLORPICKERCONTROL_DATATYPES_H
