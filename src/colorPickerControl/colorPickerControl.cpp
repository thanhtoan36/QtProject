#include "colorPickerControl/colorPickerControl.hpp"
#include "colorPickerControl/colorPickerControl_define.hpp"
#include "baseComponent/designPolicyDefine.h"
#include "colorPickerControl/customColorPickerXY.h"
#include "colorPickerControl/customColorPickerXY.h"

ColorPickerControl::ColorPickerControl(QWidget *parent)
    : PanelControlBase(parent),
      m_label_title(this),
      m_disp_param()
{
    resize(CPC_SCREENSIZE);
}

void ColorPickerControl::SetDispParamData(COLOR_PICKER_DISP_PARAM *param)
{
    Q_ASSERT(param);
    m_disp_param = *param;
}

void ColorPickerControl::SetupUiComponents()
{
    m_label_title.setGeometry(CPC_TITLE_GEOMETRY);
    m_label_title.setAlignment(Qt::AlignCenter);

    auto f = GetDefaultFont();
    m_label_title.setFont(f);

    CustomColorPickerXY * chart = new CustomColorPickerXY(this);
    chart->SetColor(QColor(Qt::blue));
    chart->setGeometry(CPC_XY_PICKER_GEOMETRY);

    auto palette = QPalette();
    palette.setColor(QPalette::Foreground, Qt::white);
    m_label_title.setPalette(palette);
    m_label_title.setText("ピッカー xy");
}
