//--------------------------------------------------------------------------
// [ ファイル名 ] : encoderControl_define.h
// [ 概      要 ] : Constant definitions for EncoderControl
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef ENCODERCONTROL_DEFINE_H
#define ENCODERCONTROL_DEFINE_H

#define EC_ENCODER_WIDTH_PADDING             10
#define EC_CUSTOM_ENCODER_SIZE               QSize(78, 204)
#define EC_ENCODER_LABEL_SIZE                QSize(78, 36)
#define EC_SCREENSIZE                        QSize(312, 320)
#define EC_LABEL_TITLE_GEOMETRY              QRect(0, 0, 312, 32)
#define EC_BUTTON_PERCENT_GEOMETRY           QRect(0, 32, 78, 24)
#define EC_BUTTON_255_GEOMETRY               QRect(0, 56, 78, 24)
#define EC_BUTTON_ANGLE_GEOMETRY             QRect(78, 32, 78, 48)
#define EC_BUTTON_PREVIOUS_GEOMETRY          QRect(156, 32, 78, 48)
#define EC_BUTTON_NEXT_GEOMETRY              QRect(234, 32, 78, 48)
#define EC_ENCODER_LABELS_TOPLEFT            QPoint(0, 82)
#define EC_ENCODER_TOPLEFT                   QPoint(0, 118)
#define EC_SCREENSIZE_HORIZON                QSize(808, 276)
#define EC_LABEL_TITLE_GEOMETRY_HORIZON      QRect(78, 2, 390, 32)
#define EC_BUTTON_PERCENT_GEOMETRY_HORIZON   QRect(0, 226, 78, 24)
#define EC_BUTTON_255_GEOMETRY_HORIZON       QRect(0, 250, 78, 24)
#define EC_BUTTON_ANGLE_GEOMETRY_HORIZON     QRect(0, 178, 78, 48)
#define EC_BUTTON_PREVIOUS_GEOMETRY_HORIZON  QRect(652, 34, 78, 48)
#define EC_BUTTON_NEXT_GEOMETRY_HORIZON      QRect(730, 34, 78, 48)
#define EC_ENCODER_SIZE_HORIZON              QSize(78, 204)
#define EC_ENCODER_LABELS_TOPLEFT_HORIZON    QPoint(78, 34)
#define EC_ENCODER_TOPLEFT_HORIZON           QPoint(78, 70)
#define EC_HORIZON_BUTTON_1_GEOMETRY_HORIZON QRect(0, 34, 78, 48)
#define EC_HORIZON_BUTTON_2_GEOMETRY_HORIZON QRect(0, 82, 78, 48)
#define EC_HORIZON_BUTTON_3_GEOMETRY_HORIZON QRect(0, 130, 78, 48)

#endif // ENCODERCONTROL_DEFINE_H
