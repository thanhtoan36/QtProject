#ifndef ENCODERCONTROL_DEFINE_H
#define ENCODERCONTROL_DEFINE_H

#define EC_SCREENSIZE                       QSize(312, 320)

#define EC_LABEL_TITLE_GEOMETRY             QRect(0, 0, 312, 32)
#define EC_BUTTON_PERCENT_GEOMETRY          QRect(0, 32, 78, 24)
#define EC_BUTTON_255_GEOMETRY              QRect(0, 56, 78, 24)
#define EC_BUTTON_EMPTY_1_GEOMETRY          QRect(78, 32, 78, 48)
#define EC_BUTTON_PREVIOUS_GEOMETRY         QRect(156, 32, 78, 48)
#define EC_BUTTON_NEXT_GEOMETRY             QRect(234, 32, 78, 48)

#define EC_LABLE_PARAM_SIZE                 QSize(78, 36)
#define EC_LABEL_PARAM_PLACEMENT_START      QPoint(0, 82)
#define EC_ENCODER_SIZE                     QSize(78, 204 + 36)
#define EC_ENCODER_PLACEMENT_START          QPoint(0, 82)

#define EC_MAX_ENCODER_ITEMS                4

#endif // ENCODERCONTROL_DEFINE_H
