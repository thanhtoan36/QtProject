//--------------------------------------------------------------------------
// [ ファイル名 ] : intensityControl_define.h
// [ 概      要 ] : インテンシティコントロールの定数定義
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef INTENSITYCONTROL_DEFINE_H
#define INTENSITYCONTROL_DEFINE_H

#define ISC_SCREENSIZE                       QSize(312, 320)         //サイズ
#define ISC_TITLE_GOEMETRY                   QRect(0, 0, 312, 32)    //タイトル
#define ISC_EMPTY_BUTON_GOEMETRY             QRect(0, 32, 78, 48)    //空欄
#define ISC_FF_BUTON_GOEMETRY                QRect(0, 80, 78, 48)    //FF
#define ISC_RETURN_GOEMETRY                  QRect(234, 272, 78, 48) //戻す

#define ISC_SCREENSIZE_HORIZON               QSize(468, 276)         //サイズ
#define ISC_TITLE_GOEMETRY_HORIZON           QRect(78, 2, 390, 32)   //タイトル
#define ISC_EMPTY_BUTON_GOEMETRY_HORIZON     QRect(0, 34, 78, 48)    //空欄
#define ISC_FF_BUTON_GOEMETRY_HORIZON        QRect(78, 34, 78, 48)   //FF
#define ISC_RETURN_GOEMETRY_HORIZON          QRect(390, 226, 78, 48) //戻す
#endif // INTENSITYCONTROL_DEFINE_H
