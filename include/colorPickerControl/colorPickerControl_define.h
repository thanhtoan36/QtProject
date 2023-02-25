//--------------------------------------------------------------------------
// [ ファイル名 ] : colorPickerControl_define.h
// [ 概      要 ] : カラー ピッカー コントロールの定数定義
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef COLORPICKERCONTROL_DEFINE_H
#define COLORPICKERCONTROL_DEFINE_H

#define CPC_SCREENSIZE                      QSize(312, 520)          // サイズ

#define CPC_TITLE_GEOMETRY                  QRect(0, 0, 312, 32)     // タイトル
#define CPC_BUTTON_XY_GEOMETRY              QRect(0, 32, 78, 48)     // xy
#define CPC_BUTTON_RGB_GEOMETRY             QRect(78, 32, 78, 48)    // RGB
#define CPC_BUTTON_PREVIOUS_TAB_GEOMETRY    QRect(156, 32, 78, 48)   // ◀
#define CPC_BUTTON_NEXT_TAB_GEOMETRY        QRect(234, 32, 78, 48)   // ▶
#define CPC_LABEL_SETTING_GEOMETRY          QRect(0, 320, 312, 32)   // 設定
#define CPC_PICKER_XY_GEOMETRY              QRect(0, 80, 312, 240)   // カラーピッカーXY
#define CPC_LABEL_TITLE_X_GEOMETRY          QRect(190, 358, 21, 21)  // Xタイトルラベル
#define CPC_SLIDER_X_GEOMETRY               QRect(58, 367, 245, 48)  // Xタイトルラベル
#define CPC_LABEL_VALUE_X_GEOMETRY          QRect(0, 381, 52, 21)    // X値ラベル
#define CPC_LABEL_TITLE_Y_GEOMETRY          QRect(190, 406, 21, 21)  // Yタイトルラベル
#define CPC_SLIDER_Y_GEOMETRY               QRect(58, 417, 245, 48)  // Yスクロールバー
#define CPC_LABEL_VALUE_Y_GEOMETRY          QRect(0, 431, 52, 21)    // Y値ラベル
#define CPC_PICKER_RGB_GEOMETRY             QRect(0, 80, 312, 240)   // カラーピッカーRGB
#define CPC_LABEL_TITLE_H_GEOMETRY          QRect(190, 358, 21, 21)  // Hタイトルラベル
#define CPC_SLIDER_H_GEOMETRY               QRect(58, 367, 245, 48)  // Hスクロールバー
#define CPC_LABEL_VALUE_H_GEOMETRY          QRect(0, 381, 52, 21)    // H値ラベル
#define CPC_LABEL_TITLE_S_GEOMETRY          QRect(190, 406, 21, 21)  // Sタイトルラベル
#define CPC_SLIDER_S_GEOMETRY               QRect(58, 417, 245, 48)  // Sスクロールバー
#define CPC_LABEL_VALUE_S_GEOMETRY          QRect(0, 431, 52, 21)    // S値ラベル
#define CPC_LABEL_TITLE_V_GEOMETRY          QRect(190, 454, 21, 21)  // Vタイトルラベル
#define CPC_SLIDER_V_GEOMETRY               QRect(58, 467, 245, 48)  // Vスクロールバー
#define CPC_LABEL_VALUE_V_GEOMETRY          QRect(0, 481, 52, 21)    // V値ラベル

#define CPC_HORIZON_SCREENSIZE                           QSize(808, 276)         // サイズ
#define CPC_HORIZON_TITLE_GEOMETRY                       QRect(78, 2, 312, 32)   // タイトル
#define CPC_HORIZON_BUTTON_XY_GEOMETRY                   QRect(0, 226, 78, 48)   // xy
#define CPC_HORIZON_BUTTON_RGB_GEOMETRY                  QRect(0, 178, 78, 48)   // RGB
#define CPC_HORIZON_BUTTON_SWITCH_PANEL_PICKER_GEOMETRY  QRect(0, 34, 78, 48)    // ピッカー
#define CPC_HORIZON_BUTTON_SWITCH_PANEL_ENCODER_GEOMETRY QRect(0, 82, 78, 48)    // エンコーダ
#define CPC_HORIZON_BUTTON_SWITCH_PANEL_NUMBER_GEOMETRY  QRect(0, 130, 78, 48)   // 数値
#define CPC_HORIZON_PICKER_XY_GEOMETRY                   QRect(78, 34, 312, 240) // カラーピッカーXY
#define CPC_HORIZON_LABEL_TITLE_X_GEOMETRY               QRect(390, 110, 21, 21) // X値ラベル
#define CPC_HORIZON_SLIDER_X_GEOMETRY                    QRect(390, 34, 78, 235) // Xスクロールバー
#define CPC_HORIZON_LABEL_VALUE_X_GEOMETRY               QRect(390, 2, 78, 32)   // Xタイトルラベル
#define CPC_HORIZON_LABEL_TITLE_Y_GEOMETRY               QRect(468, 110, 21, 21) // Y値ラベル
#define CPC_HORIZON_SLIDER_Y_GEOMETRY                    QRect(468, 34, 78, 235) // Yスクロールバー
#define CPC_HORIZON_LABEL_VALUE_Y_GEOMETRY               QRect(468, 2, 78, 32)   // Yタイトルラベル
#define CPC_HORIZON_PICKER_RGB_GEOMETRY                  QRect(78, 34, 312, 240) // カラーピッカーRGB
#define CPC_HORIZON_LABEL_TITLE_H_GEOMETRY               QRect(390, 110, 21, 21) // H値ラベル
#define CPC_HORIZON_SLIDER_H_GEOMETRY                    QRect(390, 34, 78, 235) // Hスクロールバー
#define CPC_HORIZON_LABEL_VALUE_H_GEOMETRY               QRect(390, 2, 78, 32)   // Hタイトルラベル
#define CPC_HORIZON_LABEL_TITLE_S_GEOMETRY               QRect(468, 110, 21, 21) // S値ラベル
#define CPC_HORIZON_SLIDER_S_GEOMETRY                    QRect(468, 34, 78, 235) // Sスクロールバー
#define CPC_HORIZON_LABEL_VALUE_S_GEOMETRY               QRect(468, 2, 78, 32)   // Sタイトルラベル
#define CPC_HORIZON_LABEL_TITLE_V_GEOMETRY               QRect(546, 110, 21, 21) // V値ラベル
#define CPC_HORIZON_SLIDER_V_GEOMETRY                    QRect(546, 34, 78, 235) // Vスクロールバー
#define CPC_HORIZON_LABEL_VALUE_V_GEOMETRY               QRect(546, 2, 78, 32)   // Vタイトルラベル

#endif // COLORPICKERCONTROL_DEFINE_H
