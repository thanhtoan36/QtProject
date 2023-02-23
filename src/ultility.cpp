//--------------------------------------------------------------------------
// [ ファイル名 ] : utility.cpp
// [ 概      要 ] : Include utility functions
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "utility.h"
#include <QPoint>
#include <QVector>
#include <QWidget>

//--------------------------------------------------------------------------
//  [ 関数名 ] : Map
//  [ 機　能 ] : Map value from a range to another
//  [ 引　数 ] : float x : value to map
//              float in_min : input range minimum
//              float in_max : input range maximum
//              float out_min : output range minimum
//              float out_max : output range maximum
//  [ 戻り値 ] : QColor : background color
//--------------------------------------------------------------------------
float Map( float x, float in_min, float in_max, float out_min, float out_max )
{
    // https://cdn.arduino.cc/reference/en/language/functions/math/map/
    return ( x - in_min ) * ( out_max - out_min ) / ( in_max - in_min ) + out_min;
}
