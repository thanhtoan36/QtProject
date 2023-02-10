#include "intensityControl/intensityControlHorizon.h"
#include "intensityControl/intensityControl_define.hpp"
#include "utility.h"
#include <QDebug>

IntensityControlHorizon::IntensityControlHorizon(QWidget *parent)
    : IntensityControl(parent)
{
    setFixedSize(ISC_SCREENSIZE_HORIZON);
    m_label_title.setObjectName("title_label");
}

void IntensityControlHorizon::SetupUiComponents()
{
    m_label_title.setGeometry(ISC_TITLE_GOEMETRY_HORIZON);
    m_label_title.setText("数値入力");
    m_label_title.setObjectName("title_label_horizon");

    m_return_button.setGeometry(ISC_RETURN_GOEMETRY_HORIZON);
    m_return_button.setText("戻す");

    QStringList intensityModel = {
        "FF", "+10", "+5", "+1", "",
        "00", "-10", "-5", "-1", "",
        "70", "80", "90", "", "",
        "40", "50", "60", "", "",
        "10", "20", "30", "",
    };

    m_intensity_buttons.clear();
    for (const QString &b : intensityModel) {
        auto button = MakeSharedQObject<CustomPushButton>(this);
        button->setFixedSize(ISC_INTENSITY_BUTTON_SIZE_HORIZON);
        button->setVisible(true);
        button->setText(b);

        if (b.isEmpty())
            button->setEnabled(false);

        connect(button.get(), &QPushButton::clicked, this, [&]() {
            qDebug() << ((CustomPushButton*)sender())->text();
        });

        m_intensity_buttons.append(button);
    }

    placeChildrenIntoPanel(m_intensity_buttons, ISC_INTENSITY_BUTTON_SIZE_HORIZON, ISC_INTENSITY_BUTTON_TOPLEFT_HORIZON, 5, 5);


    QStringList menuModel = {
        "", "", "", "", ""
    };
    m_menu_buttons.clear();
    for (const QString &b : menuModel) {
        auto button = MakeSharedQObject<CustomPushButton>(this);
        button->setFixedSize(ISC_MENU_BUTTON_SIZE_HORIZON);
        button->setVisible(true);
        button->setText(b);

        if (b.isEmpty())
            button->setEnabled(false);

        m_menu_buttons.append(button);
    }

    placeChildrenIntoPanel(m_menu_buttons, ISC_MENU_BUTTON_SIZE_HORIZON, ISC_MENU_BUTTON_TOPLEFT_HORIZON, 1, 5);
}
