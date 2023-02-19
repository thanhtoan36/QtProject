#ifndef GROUPCONTROLHORIZON_H
#define GROUPCONTROLHORIZON_H

#include "groupControl.hpp"


class GroupControlHorizon : public GroupControl
{
public:
    explicit GroupControlHorizon(QWidget* parent = nullptr);
    virtual void SetDispParamData(GROUP_DISP_PARAM *param) override;

protected:
    virtual void updateGroupPage() override;
    virtual void updateHistoryPage() override;

    virtual int maxGroupPages() const override;
    virtual int maxHistoryPages() const override;

    virtual void addButtonToHistory(QSharedPointer<TitleSelectButton>& button) override;
};

#endif // GROUPCONTROLHORIZON_H
