#ifndef MARKINGPICKERPOPUP_H
#define MARKINGPICKERPOPUP_H

#include <QWidget>
#include <QSharedPointer>
#include "baseComponent/customPushButton.h"

class MarkingPickerPopup : public QWidget
{
    Q_OBJECT
public:
    explicit MarkingPickerPopup(QWidget *parent = nullptr);

signals:
    void MarkingSelected(const QString &marking, const QColor &color);

public slots:
    void OnMarkingClicked();

private:
    struct Marking
    {
        QString marking;
        QColor color;
    };
    QVector<QSharedPointer<CustomPushButton>> m_marking_buttons;
};

#endif // MARKINGPICKERPOPUP_H
