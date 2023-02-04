#ifndef LIBRARYCONTROL_DATATYPES_H
#define LIBRARYCONTROL_DATATYPES_H

#define LIBRARY_NO_SIZE     32 + 1          // ライブラリ番号のサイズ
#define LIBRARY_TITLE_SIZE  32 + 1          // タイトルのサイズ
#define LIBRARY_MODE_SIZE   32 + 1          // モード名のサイズ

// ライブラリパラメータ
typedef struct
{
    bool    select;                         // 選択状態
    char    library_no[LIBRARY_NO_SIZE];    // ライブラリNo
    char    title[LIBRARY_TITLE_SIZE];      // タイトル
} LIBRARY_PARAM;

// ライブラリパラメータグループ
typedef struct
{
    bool    select;                         // 選択状態
    char    mode[LIBRARY_MODE_SIZE];        // モード名
    unsigned short  count;                  // 個数
    LIBRARY_PARAM   *library_param;         // ライブラリパラメータ
} LIBRARY_PARAM_GROUP;


// グループ表示パラメータ
typedef struct
{
    LIBRARY_PARAM_GROUP    group;           // グループ
    LIBRARY_PARAM_GROUP    history;         // 履歴
} LIBRARY_DISP_PARAM;

#endif // LIBRARYCONTROL_DATATYPES_H
