#ifndef INPUTNUMCONTROL_DATATYPES_H
#define INPUTNUMCONTROL_DATATYPES_H

#define INPUT_NUM_NAME_SIZE      32 + 1     // 数値入力名のサイズ

// 数値入力表示タイプ
enum InputNumType
{
    INPUT_NUM_TYPE_COLOR,                   // カラー
    INPUT_NUM_TYPE_POSITION,                // ポジション
    INPUT_NUM_TYPE_GOBO,                    // ゴボ
    INPUT_NUM_TYPE_BEAM_SHUTTER,            // ビーム、シャッター
    INPUT_NUM_TYPE_CONTROL                  // コントロール
};

// 数値入力表示モード
enum InputNumMode
{
    INPUT_NUM_MODE_PERCENT,                 // %
    INPUT_NUM_MODE_255,                     // 255
    INPUT_NUM_MODE_ANGLE                    // 角度
};

// 数値入力パラメータ
typedef struct
{
    bool    select;                         // 選択状態
    char    name[INPUT_NUM_NAME_SIZE];      // パラメータ名
} INPUT_NUM_PARAM;

// 数値入力表示パラメータ
typedef struct
{
    InputNumType        type;               // 表示する数値入力タイプ
    InputNumMode        mode;               // 表示する数値入力モード
    INPUT_NUM_PARAM     *param;             // 数値入力パラメータ
    unsigned short      count;              // 個数
} INPUT_NUM_DISP_PARAM;

#endif // INPUTNUMCONTROL_DATATYPES_H
