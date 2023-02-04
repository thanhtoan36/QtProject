#include "colorFilterControl/colorFilterControl.hpp"
#include "colorFilterControl/colorFilterControl_define.hpp"

#include <QLabel>

#include "colorFilterControl/colorFilterControl_define.hpp"
#include <QFont>

ColorFilterControl::ColorFilterControl()
{
    resize(CFC_SCREENSIZE);
}

void ColorFilterControl::SetupUiComponents()
{
    m_label_title = new QLabel(this);

    m_label_title->setGeometry(CFC_TITLE_GEOMETRY);
    m_label_title->setAlignment(Qt::AlignCenter);

    auto f = GetDefaultFont();
    m_label_title->setFont(f);

    auto palette = QPalette();
    palette.setColor(QPalette::Foreground, Qt::white);
    m_label_title->setPalette(palette);
    m_label_title->setText("ピッカー xy");
}
