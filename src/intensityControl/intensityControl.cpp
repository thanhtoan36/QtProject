#include "intensityControl/intensityControl.hpp"
#include "intensityControl/intensityControl_define.hpp"
#include "utility.h"
#include <QDebug>

IntensityControl::IntensityControl(QWidget *parent) : PanelControlBase(parent),
    m_grid_background(this),
    m_label_title(this),
    m_intensity_buttons(),
    m_return_button(this)

{
    setFixedSize(ISC_SCREENSIZE);
    m_grid_background.SetGridSize(QSize(4, 6));
    m_grid_background.SetCellSize(ISC_INTENSITY_BUTTON_SIZE);
    m_grid_background.move(ISC_MENU_BUTTON_TOPLEFT);

    m_label_title.setObjectName("title_label");
    m_return_button.SetTextColor(Qt::yellow);

    m_label_title.setGeometry(ISC_TITLE_GOEMETRY);
    m_label_title.setText("数値入力");

    m_return_button.setGeometry(ISC_RETURN_GOEMETRY);
    m_return_button.setText("戻す");

    connect(&m_return_button, &QPushButton::clicked, this, &IntensityControl::ReturnButtonClicked);

    QStringList intensity_model = {
        "FF", "+10", "+5", "+1",
        "00", "-10", "-5", "-1",
        "70", "80", "90", "",
        "40", "50", "60", "",
        "10", "20", "30",
    };

    m_intensity_buttons.clear();
    for (const QString &b : intensity_model)
    {
        auto button = MakeSharedQObject<CustomPushButton>(this);
        button->setFixedSize(ISC_INTENSITY_BUTTON_SIZE);
        button->setVisible(true);
        button->setText(b);

        if (b.isEmpty())
        {
            button->setEnabled(false);
        }

        connect(button.get(), &QPushButton::clicked, this, [&]() {
            emit IntensityButtonClicked(((CustomPushButton*)sender())->text());
        });

        m_intensity_buttons.append(button);
    }

    PlaceChildrenIntoPanel(m_intensity_buttons, ISC_INTENSITY_BUTTON_SIZE, ISC_INTENSITY_BUTTON_TOPLEFT, QSize(4, 5));
}
