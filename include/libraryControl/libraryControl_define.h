//--------------------------------------------------------------------------
// [ ファイル名 ] : libraryControl_define.h
// [ 概      要 ] : Constant definitions for LibraryControl Vericcal
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef LIBRARYCONTROL_DEFINE_H
#define LIBRARYCONTROL_DEFINE_H

#define LC_SCREEN_SIZE            QSize(312, 402)             // サイズ
#define LC_TITLE_GEOMETRY         QRect(0, 0, 312, 32)        // タイトル
#define LC_ALL_GEOMETRY           QRect(0, 32, 78, 48)        // ALL
#define LC_FIRST_BUTTON_GEOMETRY  QRect(0, 128, 78, 48)       // ライブラリ ボタンの左上隅
#define LC_HISTORY_GEOMETRY       QRect(0, 272, 78, 48)       // 最近使ったもの
#define LC_UP_GEOMETRY            QRect(78, 272, 78, 48)      // ▲
#define LC_DOWN_GEOMETRY          QRect(156, 272, 78, 48)     // ▼
#define LC_RETURN_GEOMETRY        QRect(234, 272, 78, 48)     // 戻す
#define LC_SETTING_LABEL_GEOMETRY QRect(0, 320, 312, 32)      // 設定
#define LC_TITLE_BUTTON_GEOMETRY  QRect(0, 354, 78, 48)       // タイトル
#define LC_EMPTY2_GEOMETRY        QRect(78, 354, 78, 48)      // (空欄)
#define LC_REGISTER_GEOMETRY      QRect(156, 354, 78, 48)     // 登録
#define LC_DELETE_GEOMETRY        QRect(234, 354, 78, 48)     // 削除

#define LC_HORIZON_SCREENSIZE            QSize(858, 276)             // サイズ
#define LC_HORIZON_ALL_GEOMETRY          QRect(78, 34, 78, 48)       // ALL
#define LC_HORIZON_TITLE_GEOMETRY        QRect(78, 2, 780, 32)       // タイトル
#define LC_HORIZON_FIRST_BUTTON_GEOMETRY QRect(78, 82, 78, 48)       // ライブラリ ボタンの左上隅
#define LC_HORIZON_HISTORY_GEOMETRY      QRect(78, 226, 78, 48)      // 最近使ったもの
#define LC_HORIZON_UP_GEOMETRY           QRect(234, 226, 78, 48)     // ▲
#define LC_HORIZON_DOWN_GEOMETRY         QRect(156, 226, 78, 48)     // ▼
#define LC_HORIZON_RETURN_GEOMETRY       QRect(390, 226, 78, 48)     // 戻す
#define LC_HORIZON_TITLE_BUTTON_GEOMETRY QRect(546, 226, 78, 48)     // タイトル
#define LC_HORIZON_REGISTER_GEOMETRY     QRect(702, 226, 78, 48)     // 登録
#define LC_HORIZON_DELETE_GEOMETRY       QRect(780, 226, 78, 48)     // 削除


#endif // LIBRARYCONTROL_DEFINE_H
