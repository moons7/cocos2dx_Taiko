#include "System/LyricsSystem.h"
#include "System/JudgeSystem.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

void LyricsSystem::runInterface()
{

    if (_playBGMDelay>0)
    {
        --_playBGMDelay;
        return;
    }
    else if (!_isPlay&&_playBGMDelay<=0)
    {
       // playBGM("Song/bad_apple.mp3");
        playBGM("Bgm.mp3");
        _isPlay = true;
    }
    auto LyricsVector = _lyricsEntity->GetLyricsEntityVector();

    if (_playNum >= LyricsVector->size())  return;/**< 播放完就return*/

    ++_playTime;

    auto lyrcis = static_cast<Label*>(_nodeEntity->buttomBG->getChildByName("lyrcisNode")->getChildren().at(_playSN));

    if (_playTime < LyricsVector->at(_playNum)->lyricsStratTime)  return;

    lyrcis->setString(LyricsVector->at(_playNum)->lyricsContent);

    float diaplayTime = LyricsVector->at(_playNum)->displaySpeed;

    lyrcis->runAction(Sequence::create(Spawn::create(MoveBy::create(5.0f, Vec2(-20, 0)), FadeIn::create(5.0f), NULL), 
                                                          Spawn::create(MoveBy::create(5.0f, Vec2(-20, 0)), FadeOut::create(5.0f), NULL), NULL));

    //歌词粒子相关动作
	auto lyrcisParticle = static_cast<ParticleSystemQuad*>(_nodeEntity->buttomBG->getChildByName("lyrcisParticleNode")->getChildByName("lyrcisParticle"));
	lyrcisParticle->resetSystem();
	lyrcisParticle->setDuration(3.0f);
	lyrcisParticle->setVisible(true);
	lyrcisParticle->setPosition(lyrcis->getPosition().x - 200, lyrcis->getPosition().y);
	lyrcisParticle->runAction(Sequence::create(MoveBy::create(2.0f, Vec2(300 + CCRANDOM_0_1() * 300, 0)), MoveBy::create(2.0f, Vec2(-CCRANDOM_0_1() * 300 - 300, -60)), NULL));
    ++_playNum;
    _playSN = (++_playSN >= 5) ? 0 : _playSN;
}

void	LyricsSystem::initInterface()
{
    _playBGMDelay = DrumSurfaceLoader::PlayDelay;
}


void LyricsSystem::playBGM(const std::string & fileName)
{
    _isPlay = true;
     CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
     CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(fileName.c_str());
     CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(fileName.c_str());
}