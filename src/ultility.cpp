//--------------------------------------------------------------------------
// [ ファイル名 ] : utility.cpp
// [ 概      要 ] : ユーティリティ関数を含める
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#include "utility.h"
#include <QPoint>
#include <QVector>
#include <QWidget>

//--------------------------------------------------------------------------
//  [ 関数名 ] : Map
//  [ 機　能 ] : ある範囲の値を別の範囲にマッピングする
//  [ 引　数 ] : float x : マッピングする値
//              float in_min : 入力の最小範囲
//              float in_max : 入力の最大範囲
//              float out_min : 出力の最小範囲
//              float out_max :背景色
//  [ 戻り値 ] : float : 換算値
//--------------------------------------------------------------------------
float Map( float x, float in_min, float in_max, float out_min, float out_max )
{
    // https://cdn.arduino.cc/reference/en/language/functions/math/map/
    return ( x - in_min ) * ( out_max - out_min ) / ( in_max - in_min ) + out_min;
}
