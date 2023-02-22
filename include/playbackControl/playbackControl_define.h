//--------------------------------------------------------------------------
// [ ファイル名 ] : playbackControl_define.h
// [ 概      要 ] : Constant definitions for PlaybackControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef PLAYBACKCONTROL_DEFINE_H
#define PLAYBACKCONTROL_DEFINE_H

#define PLC_SCREENSIZE            QSize(312, 320)
#define PLC_LIST_GEOMETRY         QRect(0, 0, 312, 320)
#define PLC_COLUMN_WIDTH          (QVector<int>{20, 67, 75, 75, 75})
#define PLC_COLUMN_WIDTH_HORIZON  (QVector<int>{78, 78, 78, 78, 78, 78, 312})
#define PLC_SCREENSIZE_HORIZON    QSize(858, 276)
#define PLC_LIST_GEOMETRY_HORIZON QRect(78, 2, 780, 272)

#endif // PLAYBACKCONTROL_DEFINE_H
