#ifndef ENCODERCONTROL_DATATYPES_H
#define ENCODERCONTROL_DATATYPES_H

#define ENCODER_NAME_SIZE   32 + 1      // エンコーダ名のサイズ

// エンコーダ表示タイプ
enum EncoderType
{
    ENCODER_TYPE_COLOR,                 // カラー
    ENCODER_TYPE_POSITION,              // ポジション
    ENCODER_TYPE_GOBO,                  // ゴボ
    ENCODER_TYPE_BEAM_SHUTTER,          // ビーム、シャッター
    ENCODER_TYPE_CONTROL                // コントロール
};

// エンコーダ表示モード
enum EncoderMode
{
    ENCODER_MODE_PERCENT,               // %
    ENCODER_MODE_255,                   // 255
    ENCODER_MODE_ANGLE                  // 角度
};

// エンコーダパラメータ
typedef struct
{
    char name[ENCODER_NAME_SIZE];       // パラメータ名
    unsigned char level;                // レベル(0～255)
    unsigned char maxLevel;             // 最大レベル(0～255)
} ENCODER_PARAM;

// エンコーダ表示パラメータ
typedef struct
{
    EncoderType     type;               // 表示するエンコーダタイプ
    EncoderMode     mode;               // エンコーダ表示モード
    ENCODER_PARAM   *param;             // エンコーダパラメータ
    unsigned short  count;              // 個数
} ENCODER_DISP_PARAM;

#endif // ENCODERCONTROL_DATATYPES_H
