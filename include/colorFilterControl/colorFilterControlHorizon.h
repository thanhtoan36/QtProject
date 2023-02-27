//--------------------------------------------------------------------------
// [ ファイル名 ] : colorFilterControlHorizon.h
// [ 概      要 ] : カラーフィルターコントロール水平ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef COLORFILTERCONTROLHORIZON_H
#define COLORFILTERCONTROLHORIZON_H

#include "colorFilterControl.h"

class ColorFilterControlHorizon : public ColorFilterControl
{
    Q_OBJECT
public:
    explicit ColorFilterControlHorizon( QWidget *parent = nullptr );
    virtual void SetDispParamData( COLOR_FILTER_DISP_PARAM *param ) override;

protected:
    virtual void AddButtonToHistory( QSharedPointer<SelectButton> button ) override;

    virtual void OnModeChanged() override;

};

#endif // COLORFILTERCONTROLHORIZON_H
