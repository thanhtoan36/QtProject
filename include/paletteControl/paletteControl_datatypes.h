#ifndef PALETTECONTROL_DATATYPES_H
#define PALETTECONTROL_DATATYPES_H

#define PALETTE_NAME_SIZE      32 + 1   // パレット名のサイズ

// パレット表示タイプ
enum PaletteType
{
    PALETTE_TYPE_GOBO,                  // ゴボ
    PALETTE_BEAM_SHUTTER,               // ビーム、シャッター
    PALETTE_TYPE_CONTROL                // コントロール
};

// パレットパラメータ
typedef struct
{
    bool    select;                     // 選択状態
    char    name[PALETTE_NAME_SIZE];    // パレット名
} PALETTE_PARAM;

// パレットパラメータグループ
typedef struct
{
    bool    select;                     // 選択状態
    unsigned short  count;              // 個数
    PALETTE_PARAM   *palette;           // カラーフィルタ
} PALETTE_PARAM_GROUP;

// パレット表示パラメータ
typedef struct
{
    unsigned short      count;          // 個数
    PALETTE_PARAM_GROUP *data;          // パレットパラメータグループ
} PALETTE_DISP_PARAM;

#endif // PALETTECONTROL_DATATYPES_H