//--------------------------------------------------------------------------
// [ ファイル名 ] : colorFilterControl_datatypes.h
// [ 概      要 ] : カラーフィルターコントロールの型定義
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef COLORFILTERCONTROL_DATATYPES_H
#define COLORFILTERCONTROL_DATATYPES_H

#define COLOR_FILTER_NAME_SIZE      32 + 1  // カラーフィルタ名のサイズ

#include <QColor>

// カラーフィルタパラメータ
typedef struct
{
    bool    select;                         // 選択状態
    char    name[COLOR_FILTER_NAME_SIZE];   // カラーフィルタ名
    QColor  color;                          // カラーフィルタ色
} COLOR_FILTER_PARAM;

// カラーフィルタパラメータグループ
typedef struct
{
    bool    select;                         // 選択状態
    unsigned short      count;              // 個数
    COLOR_FILTER_PARAM  *color_filter;      // カラーフィルタ
} COLOR_FILTER_PARAM_GROUP;


// カラーフィルタ表示パラメータ
typedef struct
{
    COLOR_FILTER_PARAM_GROUP    tb;        // カラーフィルタ(TB標準)
    COLOR_FILTER_PARAM_GROUP    custom;    // カラーフィルタ(カスタム)
    COLOR_FILTER_PARAM_GROUP    history;   // カラーフィルタ(履歴)
} COLOR_FILTER_DISP_PARAM;

#endif // COLORFILTERCONTROL_DATATYPES_H
