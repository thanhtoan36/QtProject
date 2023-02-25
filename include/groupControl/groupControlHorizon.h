//--------------------------------------------------------------------------
// [ ファイル名 ] : groupControlHorizon.h
// [ 概      要 ] : グループコントロール垂直ウィジェット
// [ 作成  環境 ] : Linux （RedHatEnterpriseLinux 7.9 （64bit））
//--------------------------------------------------------------------------
#ifndef GROUPCONTROLHORIZON_H
#define GROUPCONTROLHORIZON_H

#include "groupControl.h"


class GroupControlHorizon : public GroupControl
{
public:
    explicit GroupControlHorizon( QWidget *parent = nullptr );
    virtual void SetDispParamData( GROUP_DISP_PARAM *param ) override;

protected:
    virtual void AddButtonToHistory( QSharedPointer<TitleSelectButton> &button ) override;
};

#endif // GROUPCONTROLHORIZON_H
