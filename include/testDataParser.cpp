#include "testDataParser.h"
#include <QDebug>

/**
 * Format:   "#000000"
 */
COLOR_PICKER_DISP_PARAM CPC_ParseInput(const QString &raw)
{
    COLOR_PICKER_DISP_PARAM p;
    p.color = QColor(raw);
    return p;
}
