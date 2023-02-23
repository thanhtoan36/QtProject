//--------------------------------------------------------------------------
// [ ファイル名 ] : groupControl_define.h
// [ 概      要 ] : Constant definitions for GroupControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef GROUPLIBCONTROL_DEFINE_H
#define GROUPLIBCONTROL_DEFINE_H

#define GC_SCREEN_SIZE              QSize(312, 402) //画面サイズ縦

#define GC_TITLE_GEOMETRY           QRect(0, 0, 312, 32) //タイトル ジオメトリ
#define GC_FIRST_BUTTON_GEOMETRY    QRect(0, 32, 78, 48) //最初のボタンの形状
#define GC_HISTORY_GEOMETRY         QRect(0, 272, 78, 48) //履歴ボタンの形状
#define GC_UP_GEOMETRY              QRect(78, 272, 78, 48) //上ボタンの形状
#define GC_DOWN_GEOMETRY            QRect(156, 272, 78, 48) //下ボタンの形状
#define GC_RETURN_GEOMETRY          QRect(234, 272, 78, 48) //戻るボタンの形状
#define GC_SETTING_GEOMETRY         QRect(0, 320, 312, 32) //ラベル ジオメトリの設定
#define GC_TITLE_BUTTON_GEOMETRY    QRect(0, 354, 78, 48) //タイトルボタンの形状
#define GC_EMPTY_GEOMETRY           QRect(78, 354, 78, 48) //空のボタン ジオメトリ
#define GC_REGISTER_BUTTON_GEOMETRY QRect(156, 354, 78, 48) //ボタンの形状を登録する
#define GC_DELETE_BUTTON_GEOMETRY   QRect(234, 354, 78, 48) //ボタンのジオメトリを削除

#define GC_HORIZON_SCREEN_SIZE           QSize(858, 276) //画面サイズの地平線

#define GC_HORIZON_TITLE_GEOMETRY        QRect(78, 2, 780, 32) //タイトル 幾何学の地平線
#define GC_HORIZON_FIRST_BUTTON_GEOMETRY QRect(78, 34, 78, 48) //最初のボタン ジオメトリの地平線
#define GC_HORIZON_HISTORY_GEOMETRY      QRect(78, 226, 78, 48) //履歴ボタンの形状
#define GC_HORIZON_DOWN_GEOMETRY         QRect(156, 226, 78, 48) //下ボタンの形状
#define GC_HORIZON_UP_GEOMETRY           QRect(234, 226, 78, 48) //上ボタンの形状
#define GC_HORIZON_RETURN_GEOMETRY       QRect(390, 226, 78, 48) //戻るボタンの形状
#define GC_HORIZON_TITLE_BUTTON_GEOMETRY QRect(546, 226, 78, 48) //タイトルボタンの形状
#define GC_HORIZON_REGISTER_GEOMETRY     QRect(702, 226, 78, 48) //ボタンの形状を登録する
#define GC_HORIZON_DELETE_GEOMETRY       QRect(780, 226, 78, 48) //ボタンのジオメトリを削除

#endif // GROUPLIBCONTROL_DEFINE_H
