#include "System/ScrollSystem.h"
#include "System/JudgeSystem.h"
#include "AppDelegate.h"
#include "Scene/MainScene.h"
#include "Effect/DoorEffectSprite.h"

USING_NS_CC;



void	ScrollSystem::initInterface()
{
		auto scale = _nodeEntity->scrollBar->getScaleX(); //获取缩变系数
		_scrollSpeed = DrumSurfaceLoader::BPM / 2 * _nodeEntity->scrollBar->getContentSize().width * scale / (50 * 60);//地图滚动速度,其中50为帧数
		_srollBarPostionX = _nodeEntity->scrollBar->getPositionX(); // 获取滚动条的X坐标
		criticalPoint = 92.65 - _nodeEntity->scrollBar->getContentSize().width * scale;//地图滚动临界点
		mapSetPoint = 92.65 + _nodeEntity->scrollBar->getContentSize().width * scale;	     
}


void ScrollSystem::runInterface()
{
 
	/// 每一帧地图滚动速度
	/** 两张地图向上滚动（两张地图是相邻的，所以要一起滚动，否则会出现空隙） */
        _srollBarPostionX -= _scrollSpeed;
	///** 当第1个地图完全离开屏幕时，让第2个地图完全出现在屏幕上，同时让第1个地图紧贴在第2个地图后面 */
		if (!scrollLock&&_srollBarPostionX <= 92.65f && _srollBarPostionX > criticalPoint)
        {
            float postion = 512;
           _nodeEntity->scrollBarClone->setPositionX(512);
            CheckSroll();
            scrollLock = true;
		}
		else if (_srollBarPostionX <= criticalPoint) 
		{
            _srollBarPostionX = mapSetPoint;
            _nodeEntity->scrollBarClone->setPositionX(-512);
	        CheckSrollClone();
		    scrollLock = false;
		}
        if (IsSrollChange())
        {//最后判断鼓面是否切换      
            Sprite *spirteCache = nullptr;//精灵缓存
            DrumSufaceStruct *drumSurfaceCache = nullptr;//鼓面数据缓存
            if (!JudgeSystem::isLock)
            {
                for (int i = (BPMCount)* DrumSurfaceLoader::PerDrumCount; i < (BPMCount + 1) * DrumSurfaceLoader::PerDrumCount; ++i)
                {       
                    if (i >= (int)_surfaceEntity->GetSurfaceEntityVector()->size() - 10) /**< 提前结束?*/
                    {
                        static_cast<DoorEffectSprite*>(_uiLayer->getChildByName("WaitingPage"))->endMainScene();
                        return;
                    }
                    drumSurfaceCache = _surfaceEntity->GetSurfaceEntityVector()->at(i);
                    spirteCache = static_cast<Sprite*> (_nodeEntity->scrollBarSpriteVector.at((1 - BPMCount % 2)*DrumSurfaceLoader::PerDrumCount + i % (DrumSurfaceLoader::PerDrumCount)));
                    spirteCache->setVisible(false);
                    spirteCache->stopAllActions();
                    if (drumSurfaceCache->type == 0)	//如果没有则跳过
                        continue;
                    spirteCache->setTag(drumSurfaceCache->type);
                    spirteCache->setVisible(true);
                    if (drumSurfaceCache->type==1)
                    spirteCache->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("guRed_Ani"))));
                    else
                     spirteCache->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("guBlue_Ani"))));
                }
                addBPMCount();
                SetInitOver();
                ++BPMCount;
            }
        }
        _nodeEntity->scrollBar->setPositionX(_srollBarPostionX);
}



void ScrollSystem::addBPMCount()
{
		ss.clear();
		ss.str("");
		ss << BPMCount+2;
		_nodeEntity->GUcharMap->setString(ss.str());
}



