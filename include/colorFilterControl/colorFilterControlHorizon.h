//--------------------------------------------------------------------------
// [ ファイル名 ] : colorFilterControl.h
// [ 概      要 ] : ColorFilterControl horizon widget
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef COLORFILTERCONTROLHORIZON_H
#define COLORFILTERCONTROLHORIZON_H

#include "colorFilterControl.h"
class ColorFilterControlHorizon : public ColorFilterControl
{
    Q_OBJECT
public:
    explicit ColorFilterControlHorizon(QWidget * parent = nullptr);
    virtual void setDispParamData(COLOR_FILTER_DISP_PARAM *param) override;

protected:
    virtual void AddButtonToHistory(QSharedPointer<SelectButton> button) override;

};

#endif // COLORFILTERCONTROLHORIZON_H
