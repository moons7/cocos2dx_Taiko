#ifndef  REIMU_DATA_MAINSCNEN_LAYER_UI_H
#define  REIMU_DATA_MAINSCNEN_LAYER_UI_H
#include "cocos2d.h"
#include "Abstract/AbstractPollEntity.h"


/**@brief UI层,放置跟玩家有视觉互动的布局,比如计分与按钮等等
*/
class UILayer : public AbstractPollEntity, public cocos2d::Layer
{
 
public:
    cocos2d::Label  * totalMarkcharMap = nullptr; /**< 计分面板  */
    cocos2d::ClippingNode *heartNode = nullptr;/**< 心型结点*/
    cocos2d::Node  *_StarUINode = nullptr; /**< 星星UI结点 */

protected:
    virtual void runInterface() override;
    virtual void initInterface() override;
};
#endif