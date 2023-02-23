//--------------------------------------------------------------------------
// [ ファイル名 ] : trackControl_define.h
// [ 概      要 ] : Constant definitions for TrackControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef TRACKCONTROL_DEFINE_H
#define TRACKCONTROL_DEFINE_H

#define TC_SCREENSIZE                                 QSize(312, 320)           // サイズ
#define TC_LABEL_TITLE_GEOMETRY                       QRect(0, 0, 312, 32)      // タイトル
#define TC_BUTTON_MODE_PERCENT_GEOMETRY               QRect(0, 32, 78, 24)      // ％
#define TC_BUTTON_MODE_255_GEOMETRY                   QRect(0, 56, 78, 24)      // 255
#define TC_BUTTON_MODE_ANGLE_GEOMETRY                 QRect(78, 32, 78, 48)     // 角度
#define TC_BUTTON_VALUEMODE_RELATIVE_GEOMETRY         QRect(156, 32, 78, 24)    // 相対
#define TC_BUTTON_VALUEMODE_ABSOLUTE_GEOMETRY         QRect(156, 56, 78, 24)    // 絶対
#define TC_BUTTON_EMPTY_1_GEOMETRY                    QRect(234, 32, 78, 48)    // (空欄)
#define TC_PANTILTCONTROL_GEOMETRY                    QRect(0, 80, 312, 240)    // パンチルト

#define TC_HORIZON_SCREENSIZE                         QSize(468, 276)           // サイズ
#define TC_HORIZON_LABEL_TITLE_GEOMETRY               QRect(78, 2, 312, 32)     // タイトル
#define TC_HORIZON_BUTTON_MODE_PERCENT_GEOMETRY       QRect(0, 34, 78, 24)      // %
#define TC_HORIZON_BUTTON_MODE_255_GEOMETRY           QRect(0, 58, 78, 24)      // 255
#define TC_HORIZON_BUTTON_MODE_ANGLE_GEOMETRY         QRect(0, 82, 78, 48)      // 角度
#define TC_HORIZON_BUTTON_VALUEMODE_RELATIVE_GEOMETRY QRect(0, 226, 78, 24)     // 相対
#define TC_HORIZON_BUTTON_VALUEMODE_ABSOLUTE_GEOMETRY QRect(0, 250, 78, 24)     // 絶対
#define TC_HORIZON_BUTTON_EMPTY_1_GEOMETRY            QRect(0, 130, 78, 48)     // (空欄)
#define TC_HORIZON_BUTTON_EMPTY_2_GEOMETRY            QRect(0, 178, 78, 48)     // (空欄)
#define TC_HORIZON_PANTILTCONTROL_GEOMETRY            QRect(78, 36, 312, 240)   // パンチルト

#endif // TRACKCONTROL_DEFINE_H
