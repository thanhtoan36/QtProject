//--------------------------------------------------------------------------
// [ ファイル名 ] : colorFilterControl_define.h
// [ 概      要 ] : Constant definitions for ColorFilterControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef COLORFILTERCONTROL_DEFINE_H
#define COLORFILTERCONTROL_DEFINE_H

#define CFC_SCREENSIZE QSize(312, 402) //画面サイズ縦

#define CFC_TITLE_GEOMETRY           QRect(0, 0, 312, 32) //タイトル ジオメトリ
#define CFC_FIRST_TAB_GEOMETRY       QRect(0, 32, 78, 48) //最初のタブ ボタンの形状
#define CFC_PREVIOUS_BUTTON_GEOMETRY QRect(156, 32, 78, 48) //前のボタンの形状
#define CFC_NEXT_BUTTON_GEOMETRY     QRect(234, 32, 78, 48) //次のボタンの形状
#define CFC_FIRST_BUTTON_GEOMETRY    QRect(0, 80, 78, 48) //最初の色のボタンの形状
#define CFC_HISTORY_GEOMETRY         QRect(0, 272, 78, 48) //履歴ボタンの形状
#define CFC_UP_BUTTON_GEOMETRY       QRect(78, 272, 78, 48) //上ボタンの形状
#define CFC_DOWN_BUTTON_GEOMETRY     QRect(156, 272, 78, 48) //下ボタンの形状
#define CFC_BACK_BUTTON_GEOMETRY     QRect(234, 272, 78, 48) //戻るボタンの形状
#define CFC_SETTING_GEOMETRY         QRect(0, 320, 312, 32) //ラベル ジオメトリの設定
#define CFC_TITLE_BUTTON_GEOMETRY    QRect(0, 354, 78, 48) //タイトルボタンの形状
#define CFC_EMPTY_GEOMETRY           QRect(78, 354, 78, 48) //空のボタン ジオメトリ
#define CFC_REGISTER_GEOMETRY        QRect(156, 354, 78, 48) //ボタンの形状を登録する
#define CFC_DELETE_GEOMETRY          QRect(234, 354, 78, 48) //ボタンのジオメトリを削除

#define CFC_HORIZON_SCREENSIZE               QSize(468, 276) //画面サイズの地平線

#define CFC_HORIZON_FIRST_TAB_GEOMETRY       QRect(0, 34, 78, 48) //最初のタブ ボタンのジオメトリの地平線
#define CFC_HORIZON_UP_BUTTON_GEOMETRY       QRect(0, 178, 78, 48) //タブ ボタン ジオメトリ ホライズンのアップ ボタン
#define CFC_HORIZON_DOWN_BUTTON_GEOMETRY     QRect(0, 226, 78, 48) //タブ ボタン ジオメトリ ホライズンの下向きボタン
#define CFC_HORIZON_TITLE_GEOMETRY           QRect(78, 2, 390, 32) //タイトル 幾何学の地平線
#define CFC_HORIZON_FIRST_BUTTON_GEOMETRY    QRect(78, 34, 78, 48) //最初の色のボタン ジオメトリの地平線
#define CFC_HORIZON_TITLE_BUTTON_GEOMETRY    QRect(390, 34, 78, 48) //タイトル ボタン ジオメトリ 地平線
#define CFC_HORIZON_REGISTER_BUTTON_GEOMETRY QRect(390, 130, 78, 48) //ボタンの形状を登録する
#define CFC_HORIZON_DELETE_BUTTON_GEOMETRY   QRect(390, 178, 78, 48) //削除ボタン ジオメトリ ホライズン
#define CFC_HORIZON_HISTORY_BUTTON_GEOMETRY  QRect(78, 226, 78, 48) //履歴ボタン ジオメトリ 地平線
#define CFC_HORIZON_UP2_BUTTON_GEOMETRY      QRect(156, 226, 78, 48) //カラー ボタン ジオメトリのアップ ボタン
#define CFC_HORIZON_DOWN2_BUTTON_GEOMETRY    QRect(234, 226, 78, 48) //カラー ボタン ジオメトリの下向きボタン
#define CFC_HORIZON_BACK_BUTTON_GEOMETRY     QRect(390, 226, 78, 48) //戻るボタンの形状

#endif // COLORFILTERCONTROL_DEFINE_H
