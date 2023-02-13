#include "markingPickerPopup.h"
#include "utility.h"

#include <QDebug>

#define SCREEN_BACKGROUND_COLOR qRgb(34, 43, 53)  // background color of panels

#define PLC_PICKER_CELL_SIZE QSize(78, 48)
#define PLC_PICKER_GRID_SIZE QSize(2, 5);

MarkingPickerPopup::MarkingPickerPopup(QWidget *parent)
    : QWidget{parent}
{
    // Turn off window border and default buttons
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::Popup);

    QPalette palette {};
    palette.setColor(QPalette::Window, SCREEN_BACKGROUND_COLOR);
    palette.setColor(QPalette::Foreground, Qt::white);

    setFixedSize(PLC_PICKER_CELL_SIZE.width() * 2, PLC_PICKER_CELL_SIZE.height() * 5);

    QVector<Marking> markings = {
        {"●", QColor(Qt::red)},    {"●",  QColor(Qt::lightGray)},
        {"●", QColor(Qt::cyan)},   {"■",  QColor(Qt::lightGray)},
        {"●", QColor(Qt::yellow)}, {"🟊", QColor(Qt::lightGray)},
        {"●", QColor(Qt::green)},  {"▲",  QColor(Qt::lightGray)},
        {"●", QColor(Qt::white)},  {"▼",  QColor(Qt::lightGray)},
    };

    for (const auto &m : markings) {
        const auto button = MakeSharedQObject<CustomPushButton>(this);
        button->setVisible(true);
        button->setTextPixelSize(24);
        button->setText(m.marking);
        button->setTextColor(m.color);
        button->setFixedSize(PLC_PICKER_CELL_SIZE);
        m_marking_buttons.append(button);

        connect(button.get(), &CustomPushButton::clicked, this, &MarkingPickerPopup::onMarkingClicked);
    }

    placeChildrenIntoPanel(m_marking_buttons, PLC_PICKER_CELL_SIZE, QPoint(0, 0), 2, 5);
}

void MarkingPickerPopup::onMarkingClicked()
{
    auto button = (CustomPushButton*) sender();
    Q_ASSERT(button);
    emit markingSelected(button->text(), button->textColor());
}
