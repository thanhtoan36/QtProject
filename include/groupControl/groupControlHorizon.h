#ifndef GROUPCONTROLHORIZON_H
#define GROUPCONTROLHORIZON_H

#include "groupControl.hpp"


class GroupControlHorizon : public GroupControl
{
public:
    explicit GroupControlHorizon(QWidget* parent = nullptr);
    virtual void SetDispParamData(GROUP_DISP_PARAM *param) override;

protected:
    virtual void addButtonToHistory(QSharedPointer<TitleSelectButton>& button) override;
};

#endif // GROUPCONTROLHORIZON_H
