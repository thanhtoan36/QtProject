#include "colorFilterControl/colorFilterControl.hpp"
#include "colorFilterControl/colorFilterControl_define.hpp"

#include <QLabel>

#include "colorFilterControl/colorFilterControl_define.hpp"
#include <QFont>

ColorFilterControl::ColorFilterControl()
{
    resize(CFC_SCREENSIZE);
    auto title = new QLabel(this);

    title->setGeometry(CFC_TITLE_GEOMETRY);
    title->setAlignment(Qt::AlignCenter);
    title->setFont(QFont("MS PGothic", 9, QFont::Bold));

    auto palette = QPalette();
    palette.setColor(QPalette::Foreground, Qt::white);
    title->setPalette(palette);
    title->setText("ピッカー xy");
}
