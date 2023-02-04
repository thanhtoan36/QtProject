#ifndef TRACKCONTROL_DATATYPES_H
#define TRACKCONTROL_DATATYPES_H

// トラック表示モード
enum TrackMode
{
    TRACK_MODE_PERCENT,     // %
    TRACK_MODE_255,         // 255
    TRACK_MODE_ANGLE        // 角度
};

// トラック表示値モード
enum TrackValueMode
{
    TRACK_MODE_RELATIVE,    // 相対
    TRACK_MODE_ABSOLUTE     // 絶対
};

// トラックパラメータ
typedef struct
{
    unsigned short  current;    // 現在の値
    unsigned short  min;        // 最小値
    unsigned short  max;        // 最大値
} TRACK_PARAM;

// トラックパラメータグループ
typedef struct
{
    TRACK_PARAM     pan;        // パン
    TRACK_PARAM     tilt;       // チルト
} TRACK_PARAM_GROUP;

// トラック表示パラメータ
typedef struct
{
    TrackMode           mode;       // トラック表示モード
    TrackValueMode      valueMode;  // トラック表示値モード
    unsigned short      count;      // 個数 ※最大8個まで
    TRACK_PARAM_GROUP   data;       // トラックパラメータグループ
} TRACK_DISP_PARAM;

#endif // TRACKCONTROL_DATATYPES_H
