#include "System/AccountSystem.h"
#include "Scene/AccountScene.h"
#include "cocos2d/cocos/ui/UIText.h"
#include "ui/UITextBMFont.h"
#include "cocos2d.h"
#include "Static/PlayStatusStatic.h"
#include <sstream>
#include "Untils/RandomUntil.inl"


USING_NS_CC;
void AccountSystem::runInterface()
{
    auto resultBoard = _mainLayer->getChildByName("ResultBoard");
    if (_tempMaxHit<PlayStatusStatic::playStatus->maxHit)
    {
        auto MaxHit = static_cast<Label*>(resultBoard->getChildByName("MaxHit"));
        ss.clear();
        ss.str("");
        ss << ++_tempMaxHit;
        MaxHit->setString(ss.str());
    }
    if (_tempPerferHit<PlayStatusStatic::playStatus->perferHit)
    {
        auto Perfer = static_cast<Label*>(resultBoard->getChildByName("Perfer"));
        ss.clear();
        ss.str("");
        ss << ++_tempPerferHit;
        Perfer->setString(ss.str());
    }
    if (_tempGoodHit<PlayStatusStatic::playStatus->goodHit)
    {
        auto Good = static_cast<Label*>(resultBoard->getChildByName("Good"));
        ss.clear();
        ss.str("");
        ss << ++_tempGoodHit;
        Good->setString(ss.str());
    }
  

    if (_tempMark<PlayStatusStatic::playStatus->Mark)
    {
        auto Mark = static_cast<Label*>(resultBoard->getChildByName("Mark"));
        ss.clear();
        ss.str("");
        ss << ++_tempMark;
        Mark->setString(ss.str());
    }

    if (PlayStatusStatic::playStatus->maxHit == 100)
    {
        auto AtomicSeal = _mainLayer->getChildByName("AtomicSeal");
        AtomicSeal->setVisible(true);
        AtomicSeal->setOpacity(0);
        AtomicSeal->runAction(Sequence::create(Spawn::create(ScaleTo::create(2.0f, 1.0f), FadeIn::create(2.0f), NULL), CallFunc::create([&](){
            PlayStatusStatic::playStatus->Mark = 0;
            _isShake = true;
            _originPostion = _mainLayer->getPosition();
            _shakeTime = 10;
        }),NULL));
    }

    if (_isShake&&_shakeTime>0)/**< 开启抖动效果*/
    {
        _mainLayer->setPosition(Vec2(_originPostion.x + RandomUntil::fgRangeRand(-5.0f, 5.0f), _originPostion.y + RandomUntil::fgRangeRand(-5.0f, 5.0f)));
        --_shakeTime;
    }
    else
    {
            _mainLayer->setPosition(_originPostion);
            _isShake = false;
    }
}

void AccountSystem::initInterface()
{

}





