#ifndef GROUPCONTROLHORIZON_H
#define GROUPCONTROLHORIZON_H

#include "groupControl.hpp"
#include "groupControlHorizon_define.h"

class GroupControlHorizon : public GroupControl
{
public:
    explicit GroupControlHorizon(QWidget* parent = nullptr);
    void SetDispParamDataHorizon(GROUP_DISP_PARAM *param);

protected:
    virtual void SetupUiComponents() override;

    virtual void updateGroupPage() override;
    virtual void updateHistoryPage() override;

    virtual int maxGroupPages() const override;
    virtual int maxHistoryPages() const override;
};

#endif // GROUPCONTROLHORIZON_H
