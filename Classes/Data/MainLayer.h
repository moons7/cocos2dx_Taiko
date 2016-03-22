#ifndef  REIMU_DATA_MAINSCENE_LAYER_MAIN_H
#define  REIMU_DATA_MAINSCENE_LAYER_MAIN_H
#include "cocos2d.h"
#include "Abstract/AbstractPollEntity.h"

/**@brief 游戏主要的Layer,包含鼓面水平方向的布局,包含靶心以及相关的状态显示
*/
class MainLayer : public AbstractPollEntity, public cocos2d::Layer
{
public:
    cocos2d::Sprite *_leftStateSprite = nullptr; /**< 左边显示状态精灵(当前是显示一个鼓) */

protected:
    virtual void runInterface() override;
    virtual void initInterface() override;
};
#endif