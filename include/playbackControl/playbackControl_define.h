//--------------------------------------------------------------------------
// [ ファイル名 ] : playbackControl_define.h
// [ 概      要 ] : Constant definitions for PlaybackControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef PLAYBACKCONTROL_DEFINE_H
#define PLAYBACKCONTROL_DEFINE_H

#define PLC_SCREENSIZE            QSize(312, 320)                             // サイズ
#define PLC_LIST_GEOMETRY         QRect(0, 0, 312, 320)                       // リスト
#define PLC_COLUMN_WIDTH          (QVector<int>{20, 67, 75, 75, 75})          // 表の列幅

#define PLC_HORIZON_SCREENSIZE    QSize(858, 276)                             // サイズ
#define PLC_HORIZON_LIST_GEOMETRY QRect(78, 2, 780, 272)                      // リスト
#define PLC_HORIZON_COLUMN_WIDTH  (QVector<int>{78, 78, 78, 78, 78, 78, 312}) // 表の列幅

#endif // PLAYBACKCONTROL_DEFINE_H
