#include "System/ShaderSystem.h"
#include "System/JudgeSystem.h"
#include "cocos2d.h"
#include "Effect/PVEffectSprite.h"
#include "Effect/UVEffectSprite.h"
#include "System/LyricsSystem.h"
#include "Effect/DoorEffectSprite.h"


USING_NS_CC;



void ShaderSystem::runInterface()
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
  /**  auto playTime = static_cast<LyricsSystem*>(SystemManage::getInstance()->getEntity("lyricsSystem"))->_playTime;
    if (2 == static_cast<PVEffectSprite*>(_nodeEntity->buttomBG)->updateShader(playTime / 1300.0f, _nodeEntity->buttomBG))
	{
        _nodeEntity->scrollBar_Background->runAction(Sequence::create(MoveBy::create(20.0f,Vec2(0,120)),NULL));
		_nodeEntity->scrollBar->runAction(Sequence::create(MoveBy::create(20.0f, Vec2(0, 120)), NULL));
        _nodeEntity->gu->runAction(Sequence::create(MoveBy::create(20.0f, Vec2(0, 120)), NULL));
		_nodeEntity->gu_song->runAction(Sequence::create(FadeOut::create(20.0f), NULL));
		_nodeEntity->gu_songClone->runAction(Sequence::create(FadeOut::create(20.0f), NULL));
		_nodeEntity->gu_diaplay->runAction(Sequence::create(FadeOut::create(20.0f), NULL));
		_nodeEntity->lyrcis->runAction(Sequence::create(MoveBy::create(20.0f, Vec2(80, -200)), NULL));
	}*/
    static_cast<UVEffectSprite*>(_nodeEntity->scrollBar_Background)->updateShader();
    static_cast<DoorEffectSprite*>(_uiLayer->getChildByName("WaitingPage"))->updateShader(0.0f);
#endif
}


void ShaderSystem::initInterface()
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
  // static_cast<PVEffectSprite*>(_nodeEntity->buttomBG)->InitShader();
   static_cast<UVEffectSprite*>(_nodeEntity->scrollBar_Background)->InitShader();
   static_cast<DoorEffectSprite*>(_uiLayer->getChildByName("WaitingPage"))->InitShader();
#endif
}

ShaderSystem::~ShaderSystem()
{
    //_nodeEntity->buttomBG->getGLProgramState()->release();
    _nodeEntity->scrollBar_Background->getGLProgramState()->release();
    _uiLayer->getChildByName("WaitingPage")->getGLProgramState()->release();
}
