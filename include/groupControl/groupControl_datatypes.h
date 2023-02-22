//--------------------------------------------------------------------------
// [ ファイル名 ] : groupControl_datatypes.h
// [ 概      要 ] : Type definitions for GroupControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef GROUPCONTROL_DATATYPES_H
#define GROUPCONTROL_DATATYPES_H

#define GROUP_NO_SIZE       32 + 1      // グループ番号のサイズ
#define GROUP_TITLE_SIZE    32 + 1      // タイトルのサイズ

// グループパラメータ
typedef struct
{
    bool    select;                     // 選択状態
    char    group_no[GROUP_NO_SIZE];    // グループナンバー
    char    title[GROUP_TITLE_SIZE];   // タイトル
} GROUP_PARAM;

// グループパラメータグループ
typedef struct
{
    unsigned short  count;              // 個数
    GROUP_PARAM   *group_param;         // グループパラメータ
} GROUP_PARAM_GROUP;

// グループ表示パラメータ
typedef struct
{
    GROUP_PARAM_GROUP    group;         // グループ
    GROUP_PARAM_GROUP    history;       // 履歴
} GROUP_DISP_PARAM;

#endif // GROUPCONTROL_DATATYPES_H
