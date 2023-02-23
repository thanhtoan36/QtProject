//--------------------------------------------------------------------------
// [ ファイル名 ] : intensityControl.h
// [ 概      要 ] : IntensityControl vertical widget
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
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
    IntensityControl( QWidget *parent = nullptr );

signals:
    void IntensityButtonClicked( const QString &name );
    void ReturnButtonClicked();

protected:
    GridBackground m_grid_background;
    QLabel m_label_title;
    QVector<QSharedPointer<CustomPushButton>> m_intensity_buttons;
    CustomPushButton m_return_button;
};

#endif // INTENSITYCONTROL_H
