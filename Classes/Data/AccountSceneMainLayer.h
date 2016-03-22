#ifndef  REIMU_DATA_ACCOUNTSCENE_MAINLAYER_MAIN_H
#define  REIMU_DATA_ACCOUNTSCENE_MAINLAYER_MAIN_H
#include "cocos2d.h"
#include "Abstract/AbstractPollEntity.h"

/**@brief 游戏主要的Layer,包含鼓面水平方向的布局,包含靶心以及相关的状态显示
*/
class AccountSceneMainLayer : public AbstractPollEntity, public cocos2d::Layer
{
public:


protected:
    virtual void runInterface() override;
    virtual void initInterface() override;

};
#endif