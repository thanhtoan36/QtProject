//--------------------------------------------------------------------------
// [ ファイル名 ] : libraryControl_define.h
// [ 概      要 ] : Constant definitions for LibraryControl Vericcal
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef LIBRARYCONTROL_DEFINE_H
#define LIBRARYCONTROL_DEFINE_H

#define LC_SCREEN_SIZE QSize(312,402)

#define LC_BUTTON_SIZE QSize(78,48)
#define LC_MODE_TOP_LEFT QPoint(0,32)
#define LC_LIB_BUTTON_TOP_LEFT QPoint(0,128)

#define LC_TITLE_GEOMETRY QRect(0   ,0  ,312    ,32)
#define LC_ALL_GEOMETRY QRect(0 ,32 ,78 ,48)
#define LC_INT_GEOMETRY QRect(78    ,32 ,78 ,48)
#define LC_COLOR_GEOMETRY QRect(156 ,32 ,78 ,48)
#define LC_POSITION_GEOMETRY QRect(234  ,32 ,78 ,48)
#define LC_GOBO_GEOMETRY QRect(0    ,80 ,78 ,48)
#define LC__GEOMETRY QRect(78   ,80 ,78 ,48)
#define LC_BEAM_GEOMETRY QRect(156  ,80 ,78 ,48)
#define LC_CONTROL_GEOMETRY QRect(234   ,80 ,78 ,48)
#define LC_EMPTY1_GEOMETRY QRect(0  ,128    ,78 ,48)
#define LC_BUTTON1_GEOMETRY QRect(0 ,128    ,78 ,48)
#define LC_HISTORY_GEOMETRY QRect(0 ,272    ,78 ,48)
#define LC_UP_GEOMETRY QRect(78 ,272    ,78 ,48)
#define LC_DOWN_GEOMETRY QRect(156  ,272    ,78 ,48)
#define LC_RETURN_GEOMETRY QRect(234    ,272    ,78 ,48)
#define LC_SETTING_LABEL_GEOMETRY QRect(0   ,320    ,312    ,32)
#define LC_TITLE_BUTTON_GEOMETRY QRect(0    ,354    ,78 ,48)
#define LC_EMPTY2_GEOMETRY QRect(78 ,354    ,78 ,48)
#define LC_REGISTER_GEOMETRY QRect(156  ,354    ,78 ,48)
#define LC_DELETE_GEOMETRY QRect(234    ,354    ,78 ,48)

#endif // LIBRARYCONTROL_DEFINE_H
