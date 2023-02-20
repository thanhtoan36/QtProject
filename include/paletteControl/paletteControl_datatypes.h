#ifndef PALETTECONTROL_DATATYPES_H
#define PALETTECONTROL_DATATYPES_H
#include <QImage>

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
    QImage  image;                      // 画面表示イメージ
} PALETTE_PARAM;

// パレットパラメータグループ
typedef struct
{
    bool    select;                     // 選択状態
    char    name[PALETTE_NAME_SIZE];    // パレットグループ名
    QImage  image;                      // 画面表示イメージ
    unsigned short  count;              // 個数
    PALETTE_PARAM   *palette;           // パレットパラメータ
} PALETTE_PARAM_GROUP;

// パレット表示パラメータ
typedef struct
{
    PaletteType         type;           // 表示するパレットタイプ
    unsigned short      count;          // 個数
    PALETTE_PARAM_GROUP *data;          // パレットパラメータグループ
} PALETTE_DISP_PARAM;
#endif // PALETTECONTROL_DATATYPES_H
