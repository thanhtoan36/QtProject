//--------------------------------------------------------------------------
// [ ファイル名 ] : markingPickerPopup.h
// [ 概      要 ] : A popup control to present the markings for users to select
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------

#ifndef MARKINGPICKERPOPUP_H
#define MARKINGPICKERPOPUP_H

#include <QWidget>
#include <QSharedPointer>
#include "baseComponent/customPushButton.h"

class MarkingPickerPopup : public QWidget
{
    Q_OBJECT
public:
    explicit MarkingPickerPopup( QWidget *parent = nullptr );

signals:
    void MarkingSelected( const QString &marking, const QColor &color );

public slots:
    void OnMarkingClicked();

private:
    struct Marking
    {
        QString marking;  // The marking
        QColor color;     // The marking color
    };
    QVector<QSharedPointer<CustomPushButton>> m_marking_buttons;
};

#endif // MARKINGPICKERPOPUP_H
