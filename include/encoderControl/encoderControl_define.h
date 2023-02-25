//--------------------------------------------------------------------------
// [ ファイル名 ] : encoderControl_define.h
// [ 概      要 ] : エンコーダーコントロールの定数定義
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef ENCODERCONTROL_DEFINE_H
#define ENCODERCONTROL_DEFINE_H

#define EC_ENCODER_WIDTH_PADDING             10                         // エンコード幅パディング
#define EC_CUSTOM_ENCODER_SIZE               QSize(78, 204)             // エンコーダサイズ
#define EC_ENCODER_LABEL_SIZE                QSize(78, 36)              // エンコーダラベルサイズ

#define EC_SCREENSIZE                        QSize(312, 320)            // サイズ
#define EC_LABEL_TITLE_GEOMETRY              QRect(0, 0, 312, 32)       // タイトル
#define EC_BUTTON_PERCENT_GEOMETRY           QRect(0, 32, 78, 24)       // %
#define EC_BUTTON_255_GEOMETRY               QRect(0, 56, 78, 24)       // 255
#define EC_BUTTON_ANGLE_GEOMETRY             QRect(78, 32, 78, 48)      // 角度
#define EC_BUTTON_PREVIOUS_GEOMETRY          QRect(156, 32, 78, 48)     // ◀/空欄
#define EC_BUTTON_NEXT_GEOMETRY              QRect(234, 32, 78, 48)     // ▶/空欄
#define EC_ENCODER_LABELS_TOPLEFT            QPoint(0, 82)              // エンコーダ ラベルの左上隅
#define EC_ENCODER_TOPLEFT                   QPoint(0, 118)             // エンコーダーの左上隅

#define EC_HORIZON_ENCODER_SIZE              QSize(78, 204)             // エンコード幅パディング

#define EC_HORIZON_SCREENSIZE                QSize(808, 276)            // サイズ
#define EC_HORIZON_LABEL_TITLE_GEOMETRY      QRect(78, 2, 390, 32)      // タイトル
#define EC_HORIZON_BUTTON_PERCENT_GEOMETRY   QRect(0, 226, 78, 24)      // %
#define EC_HORIZON_BUTTON_255_GEOMETRY       QRect(0, 250, 78, 24)      // 255
#define EC_HORIZON_BUTTON_ANGLE_GEOMETRY     QRect(0, 178, 78, 48)      // 角度
#define EC_HORIZON_BUTTON_PREVIOUS_GEOMETRY  QRect(652, 34, 78, 48)     // ◀/空欄
#define EC_HORIZON_BUTTON_NEXT_GEOMETRY      QRect(730, 34, 78, 48)     // ▶/空欄
#define EC_HORIZON_ENCODER_LABELS_TOPLEFT    QPoint(78, 34)             // エンコーダ ラベルの左上隅
#define EC_HORIZON_ENCODER_TOPLEFT           QPoint(78, 70)             // エンコーダーの左上隅

#define EC_HORIZON_BUTTON_PICKER_GEOMETRY    QRect(0, 34, 78, 48)       // ピッカー
#define EC_HORIZON_BUTTON_ENCODER_GEOMETRY   QRect(0, 82, 78, 48)       // エンコーダ
#define EC_HORIZON_BUTTON_INPUT_NUM_GEOMETRY QRect(0, 130, 78, 48)      // 数値


#endif // ENCODERCONTROL_DEFINE_H
