#ifndef REIMU_SYSTEM_SHADERSYSTEM_H
#define REIMU_SYSTEM_SHADERSYSTEM_H

#include "Data/BackGroundLayer.h"
#include "Abstract/AbstractEventDispatcher.inl"
#include "Scene/MainScene.h"
#include "Data/UILayer.h"

class ShaderSystem :public AbstractPollEntity
{
public:
    ~ShaderSystem();
   
protected:
	virtual void runInterface() override;
    virtual void initInterface() override;
    BackGroundLayer* _nodeEntity = static_cast<BackGroundLayer*>(MainScene::GetDataManage()->getEntity("BackGroundLayer"));/**界面数据实体*/
    UILayer* _uiLayer = static_cast<UILayer*>(MainScene::GetDataManage()->getEntity("UILayer"));/**界面数据实体*/

};
#endif