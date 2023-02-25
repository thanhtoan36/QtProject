//--------------------------------------------------------------------------
// [ ファイル名 ] : paletteControl_define.h
// [ 概      要 ] : パレットコントロールの定数定義
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef PALETTECONTROL_DEFINE_H
#define PALETTECONTROL_DEFINE_H

#define PC_SCREEN_SIZE      QSize(312, 320)          // サイズ
#define PC_BUTTON_SIZE      QSize(78, 48)            // 通常のボタンサイズ
#define PC_MENU_TOP_LEFT    QPoint(0, 80)            // メニューボタンの左上隅
#define PC_PALETTE_TOP_LEFT QPoint(0, 128)           // パレットボタンの左上隅
#define PC_BUTTON_SIZE      QSize(78, 48)            // 通常のボタンサイズ
#define PC_TITLE_GEOMETRY   QRect(0, 0, 312, 32)     // タイトル
#define PC_PREV_GEOMETRY    QRect(156, 32, 78, 48)   // ◀
#define PC_NEXT_GEOMETRY    QRect(234, 32, 78, 48)   // ▶
#define PC_UP_GEOMETRY      QRect(78, 272, 78, 48)   // ▲
#define PC_DOWN_GEOMETRY    QRect(156, 272, 78, 48)  // ▼
#define PC_RETURN_GEOMETRY  QRect(234, 272, 78, 48)  // 戻す


#define PC_HORIZON_SCREEN_SIZE           QSize(468, 276)            // サイズ
#define PC_HORIZON_MENU_TOP_LEFT         QPoint(0, 34)              // メニューボタンの左上隅
#define PC_HORIZON_PALETTE_TOP_LEFT      QPoint(78, 34)             // パレットボタンの左上隅
#define PC_HORIZON_BUTTON_SIZE           QSize(78, 48)              // 通常のボタンサイズ
#define PC_HORIZON_TITLE_GEOMETRY        QRect(78, 2, 390, 32)      // タイトル
#define PC_HORIZON_UP_MODE_GEOMETRY      QRect(0, 178, 78, 48)      // ▲
#define PC_HORIZON_DOWN_MODE_GEOMETRY    QRect(0, 226, 78, 48)      // ▼
#define PC_HORIZON_UP_PALETTE_GEOMETRY   QRect(234, 226, 78, 48)    // ▲
#define PC_HORIZON_DOWN_PALETTE_GEOMETRY QRect(156, 226, 78, 48)    // ▼
#define PC_HORIZON_RETURN_GEOMETRY       QRect(390, 226, 78, 48)    // 戻す

#endif // PALETTECONTROL_DEFINE_H
