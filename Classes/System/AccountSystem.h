#ifndef REIMU_STATIC_ACCOUNTSYSTEM_H
#define REIMU_STATIC_ACCOUNTSYSTEM_H

#include "Abstract/AbstractPollEntity.h"
#include "Data/AccountSceneMainLayer.h"
#include "Scene/AccountScene.h"


/**分数结算系统*/
class AccountSystem :public AbstractPollEntity
{
protected:
    virtual void runInterface() override;
    virtual void initInterface() override;
    AccountSceneMainLayer* _mainLayer = static_cast<AccountSceneMainLayer*>(AccountScene::GetDataManage()->getEntity("AccountSceneMainLayer"));
    bool _isShake = false; /**< 开启抖动功能 */
    cocos2d::Vec2 _originPostion = cocos2d::Vec2::ZERO;/**< 保存原始地址,以便还原 */
    short _shakeTime = 0;/**<  抖动持续时间 */
    /**@brief 生成范围内的随机数
        @param min 最小值
        @param max 最大值
        */
   unsigned short _tempMaxHit = 0;
   unsigned short _tempPerferHit = 0;
   unsigned short _tempGoodHit = 0;
   unsigned int _tempMark = 0;
   std::stringstream ss;
};
#endif
