//--------------------------------------------------------------------------
// [ ファイル名 ] : colorFilterControl_define.h
// [ 概      要 ] : Constant definitions for ColorFilterControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef COLORFILTERCONTROL_DEFINE_H
#define COLORFILTERCONTROL_DEFINE_H

#define CFC_SCREENSIZE QSize(312, 402) //サイズ

#define CFC_TITLE_GEOMETRY           QRect(0, 0, 312, 32)    //タイトル
#define CFC_FIRST_TAB_GEOMETRY       QRect(0, 32, 78, 48)    //TB標準
#define CFC_PREVIOUS_BUTTON_GEOMETRY QRect(156, 32, 78, 48)  //◀
#define CFC_NEXT_BUTTON_GEOMETRY     QRect(234, 32, 78, 48)  //▶
#define CFC_FIRST_BUTTON_GEOMETRY    QRect(0, 80, 78, 48)    //カラーボタン1
#define CFC_HISTORY_GEOMETRY         QRect(0, 272, 78, 48)   //最近使ったもの
#define CFC_UP_BUTTON_GEOMETRY       QRect(78, 272, 78, 48)  //▲
#define CFC_DOWN_BUTTON_GEOMETRY     QRect(156, 272, 78, 48) //▼
#define CFC_BACK_BUTTON_GEOMETRY     QRect(234, 272, 78, 48) //戻す
#define CFC_SETTING_GEOMETRY         QRect(0, 320, 312, 32)  //設定
#define CFC_TITLE_BUTTON_GEOMETRY    QRect(0, 354, 78, 48)   //タイトル
#define CFC_EMPTY_GEOMETRY           QRect(78, 354, 78, 48)  //空欄
#define CFC_REGISTER_GEOMETRY        QRect(156, 354, 78, 48) //登録
#define CFC_DELETE_GEOMETRY          QRect(234, 354, 78, 48) //削除

#define CFC_HORIZON_SCREENSIZE       QSize(468, 276)         //サイズ

#define CFC_HORIZON_FIRST_TAB_GEOMETRY       QRect(0, 34, 78, 48)    //TB標準
#define CFC_HORIZON_UP_BUTTON_GEOMETRY       QRect(0, 178, 78, 48)   //▲
#define CFC_HORIZON_DOWN_BUTTON_GEOMETRY     QRect(0, 226, 78, 48)   //▼
#define CFC_HORIZON_TITLE_GEOMETRY           QRect(78, 2, 390, 32)   //タイトル
#define CFC_HORIZON_FIRST_BUTTON_GEOMETRY    QRect(78, 34, 78, 48)   //カラーボタン1
#define CFC_HORIZON_TITLE_BUTTON_GEOMETRY    QRect(390, 34, 78, 48)  //タイトル
#define CFC_HORIZON_REGISTER_BUTTON_GEOMETRY QRect(390, 130, 78, 48) //登録
#define CFC_HORIZON_DELETE_BUTTON_GEOMETRY   QRect(390, 178, 78, 48) //削除
#define CFC_HORIZON_HISTORY_BUTTON_GEOMETRY  QRect(78, 226, 78, 48)  //最近使ったもの
#define CFC_HORIZON_UP2_BUTTON_GEOMETRY      QRect(156, 226, 78, 48) //▲
#define CFC_HORIZON_DOWN2_BUTTON_GEOMETRY    QRect(234, 226, 78, 48) //▼
#define CFC_HORIZON_BACK_BUTTON_GEOMETRY     QRect(390, 226, 78, 48) //戻す

#endif // COLORFILTERCONTROL_DEFINE_H
