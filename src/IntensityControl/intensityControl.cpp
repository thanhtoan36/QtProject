#include "intensityControl/intensityControl.hpp"
#include "intensityControl/intensityControl_define.hpp"


IntensityControl::IntensityControl(QWidget *parent) : PanelControlBase(parent),
    m_label_title(this),
    m_ff_button(this),
    m_p10_button(this),
    m_p5_button(this),
    m_p1_button(this),
    m_00_button(this),
    m_n10_button(this),
    m_n5_button(this),
    m_n1_button(this),
    m_70_button(this),
    m_80_button(this),
    m_90_button(this),
    m_40_button(this),
    m_50_button(this),
    m_60_button(this),
    m_10_button(this),
    m_20_button(this),
    m_30_button(this),
    m_return_button(this),
    m_empty1_button(this),
    m_empty2_button(this),
    m_empty3_button(this),
    m_empty4_button(this),
    m_empty5_button(this),
    m_empty6_button(this)

{
    setFixedSize(ISC_SCREENSIZE);
    m_label_title.setObjectName("title_label");
}

void IntensityControl::SetupUiComponents()
{
    m_label_title.setGeometry(ISC_TITLE_GOEMETRY);
    m_label_title.setText("数値入力");

    m_ff_button.setGeometry(ISC_FF_GOEMETRY);
    m_ff_button.setText("FF");

    m_p10_button.setGeometry(ISC_P10_GOEMETRY);
    m_p10_button.setText("10");

    m_p5_button.setGeometry(ISC_P5_GOEMETRY);
    m_p5_button.setText("5");

    m_p1_button.setGeometry(ISC_P1_GOEMETRY);
    m_p1_button.setText("1");

    m_00_button.setGeometry(ISC_00_GOEMETRY);
    m_00_button.setText("00");

    m_n10_button.setGeometry(ISC_N10_GOEMETRY);
    m_n10_button.setText("-10");

    m_n5_button.setGeometry(ISC_N5_GOEMETRY);
    m_n5_button.setText("-5");

    m_n1_button.setGeometry(ISC_N1_GOEMETRY);
    m_n1_button.setText("-1");

    m_70_button.setGeometry(ISC_70_GOEMETRY);
    m_70_button.setText("70");

    m_80_button.setGeometry(ISC_80_GOEMETRY);
    m_80_button.setText("80");

    m_90_button.setGeometry(ISC_90_GOEMETRY);
    m_90_button.setText("90");

    m_40_button.setGeometry(ISC_40_GOEMETRY);
    m_40_button.setText("40");

    m_50_button.setGeometry(ISC_50_GOEMETRY);
    m_50_button.setText("50");

    m_60_button.setGeometry(ISC_60_GOEMETRY);
    m_60_button.setText("60");

    m_10_button.setGeometry(ISC_10_GOEMETRY);
    m_10_button.setText("10");

    m_20_button.setGeometry(ISC_20_GOEMETRY);
    m_20_button.setText("20");

    m_30_button.setGeometry(ISC_30_GOEMETRY);
    m_30_button.setText("30");

    m_return_button.setGeometry(ISC_RETURN_GOEMETRY);
    m_return_button.setText("戻す");

    m_empty1_button.setGeometry(ISC_EMPTY_1_GOEMETRY);
    m_empty1_button.setText("");

    m_empty2_button.setGeometry(ISC_EMPTY_2_GOEMETRY);
    m_empty2_button.setText("");

    m_empty3_button.setGeometry(ISC_EMPTY_3_GOEMETRY);
    m_empty3_button.setText("");

    m_empty4_button.setGeometry(ISC_EMPTY_4_GOEMETRY);
    m_empty4_button.setText("");

    m_empty5_button.setGeometry(ISC_EMPTY_5_GOEMETRY);
    m_empty5_button.setText("");

    m_empty6_button.setGeometry(ISC_EMPTY_6_GOEMETRY);
    m_empty6_button.setText("");

}

void IntensityControl::SetupUiEvents()
{

}
