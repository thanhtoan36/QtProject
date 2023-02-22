//--------------------------------------------------------------------------
// [ ファイル名 ] : paletteControl_define.h
// [ 概      要 ] : Constant definitions for PaletteControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef PALETTECONTROL_DEFINE_H
#define PALETTECONTROL_DEFINE_H

#define PC_SCREEN_SIZE QSize(312,320)
#define PC_BUTTON_SIZE QSize(78,48)
#define PC_MENU_TOP_LEFT QPoint(0,80)
#define PC_BUTTON_TOP_LEFT QPoint(0,128)

#define PC_TITLE_GEOMETRY QRect(0   ,0  ,312    ,32)
#define PC_EMPTY1_GEOMETRY QRect(0  ,32 ,78 ,48)
#define PC_EMPTY2_GEOMETRY QRect(78 ,32 ,78 ,48)
#define PC_PREV_GEOMETRY QRect(156  ,32 ,78 ,48)
#define PC_NEXT_GEOMETRY QRect(234  ,32 ,78 ,48)
#define PC_MENU1_GEOMETRY QRect(0   ,80 ,78 ,48)

#define PC_BUTTON1_GEOMETRY QRect(0 ,128    ,78 ,48)


#define PC_UP_GEOMETRY QRect(78 ,272    ,78 ,48)
#define PC_DOWN_GEOMETRY QRect(156  ,272    ,78 ,48)
#define PC_RETURN_GEOMETRY QRect(234    ,272    ,78 ,48)

#endif // PALETTECONTROL_DEFINE_H
