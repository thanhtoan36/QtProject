//--------------------------------------------------------------------------
// [ ファイル名 ] : playbackControl_datatypes.h
// [ 概      要 ] : プレイバックコントロールの型定義
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef PLAYBACKCONTROL_DATATYPES_H
#define PLAYBACKCONTROL_DATATYPES_H

#define PLAYBACK_MARKING_SIZE   3 + 1       // マーキングのサイズ
#define PLAYBACK_QUEUE_SIZE     32 + 1      // キューのサイズ
#define PLAYBACK_FADE_SIZE      32 + 1      // フェードのサイズ
#define PLAYBACK_DELAY_SIZE     32 + 1      // ディレイのサイズ
#define PLAYBACK_WEIGHT_SIZE    32 + 1      // ウェイトのサイズ
#define PLAYBACK_LINK_SIZE     32 + 1       // リンクのサイズ
#define PLAYBACK_TITLE_SIZE    32 + 1       // タイトルのサイズ

#include <QColor>

// マーキング
typedef struct
{
    char    marking[PLAYBACK_MARKING_SIZE]; // マーキング
    QColor  color;                          // カラー
} MARKING;

// プレイバックパラメータ
typedef struct
{
    bool    select;                         // 選択状態
    MARKING marking;                        // マーキング
    char    queue[PLAYBACK_QUEUE_SIZE];     // キュー
    char    fade[PLAYBACK_FADE_SIZE];       // フェード
    char    delay[PLAYBACK_DELAY_SIZE];     // ディレイ
    char    weight[PLAYBACK_WEIGHT_SIZE];   // ウェイト
    char    link[PLAYBACK_LINK_SIZE];       // リンク
    char    title[PLAYBACK_TITLE_SIZE];     // タイトル
} PLAYBACK_PARAM;

// プレイバック表示パラメータ
typedef struct
{
    unsigned short  count;      // 個数
    PLAYBACK_PARAM  *param;     // プレイバックパラメータ
} PLAYBACK_DISP_PARAM;

#endif // PLAYBACKCONTROL_DATATYPES_H
