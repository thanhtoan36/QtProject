//--------------------------------------------------------------------------
// [ ファイル名 ] : inputNumControl_define.h
// [ 概      要 ] : 数値入力制御定数定義
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef INPUTNUMCONTROL_DEFINE_H
#define INPUTNUMCONTROL_DEFINE_H

#define IC_SCREEN_SIZE                        QSize(312, 320)         // サイズ
#define IC_TITLE_GEOMETRY                     QRect(0, 0, 312, 32)    // タイトル
#define IC_FIRST_MODE_BUTTON_GEOMETRY         QRect(0, 80, 78, 48)    // メニュー1
#define IC_PERCENT_GEOMETRY                   QRect(0, 32, 78, 24)    // %
#define IC_255_GEOMETRY                       QRect(0, 56, 78, 24)    // 255
#define IC_ANGEL_GEOMETRY                     QRect(78, 32, 78, 48)   // 角度
#define IC_PREV_GEOMETRY                      QRect(156, 32, 78, 48)  // ◀/空欄
#define IC_NEXT_GEOMETRY                      QRect(234, 32, 78, 48)  // ▶/空欄
#define IC_RELATIVE_GEOMETRY                  QRect(234, 80, 78, 24)  // 相対
#define IC_ABSOLUTE_GEOMETRY                  QRect(234, 104, 78, 24) // 絶対
#define IC_FIRST_NUM_BUTTON_GEOMETRY          QRect(0, 128, 78, 48)   // 7
#define IC_RETURN_GEOMETRY                    QRect(234, 272, 78, 48) // 戻る

#define IC_HORIZON_SCREEN_SIZE                QSize(808, 276)         // サイズ
#define IC_HORIZON_PICKER_GEOMETRY            QRect(0, 34, 78, 48)    // ピッカー
#define IC_HORIZON_ENCODER_GEOMETRY           QRect(0, 82, 78, 48)    // エンコーダ
#define IC_HORIZON_NUMBER_GEOMETRY            QRect(0, 130, 78, 48)   // 数値
#define IC_HORIZON_PERCENT_GEOMETRY           QRect(0, 226, 78, 24)   // %
#define IC_HORIZON_255_GEOMETRY               QRect(0, 250, 78, 24)   // 255
#define IC_HORIZON_PREV_GEOMETRY              QRect(652, 34, 78, 48)  // ◀
#define IC_HORIZON_NEXT_GEOMETRY              QRect(730, 34, 78, 48)  // ▶
#define IC_HORIZON_TITLE_GEOMETRY             QRect(78, 2, 390, 32)   // タイトル
#define IC_HORIZON_FIRST_MODE_BUTTON_GEOMETRY QRect(78, 34, 78, 48)   // 固定値ボタン1
#define IC_HORIZON_FIRST_NUM_BUTTON_GEOMETRY  QRect(78, 82, 78, 48)   // 7
#define IC_HORIZON_RETURN_GEOMETRY            QRect(312, 226, 78, 48) // 戻す
#endif // INPUTNUMCONTROL_DEFINE_H
