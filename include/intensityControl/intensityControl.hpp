#ifndef INTENSITYCONTROL_H
#define INTENSITYCONTROL_H

#include "baseComponent/panelControlBase.h"
#include "baseComponent/customPushButton.h"
#include "baseComponent/gridBackground.h"
#include <QLabel>
#include <QVector>
#include <QSharedPointer>

class IntensityControl : public PanelControlBase
{
    Q_OBJECT
public:
    IntensityControl(QWidget *parent = nullptr);

signals:
    void IntensityButtonClicked(const QString &name);
    void returnButtonClicked();

protected:
    GridBackground m_grid_background;
    QLabel m_label_title;
    QVector<QSharedPointer<CustomPushButton>> m_intensity_buttons;
    CustomPushButton m_return_button;
};

#endif // INTENSITYCONTROL_H
