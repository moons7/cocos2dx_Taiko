#include "Data/BackGroundLayer.h"
#include "cocostudio/CocoStudio.h"
#include "Scene/MainScene.h"
#include "SimpleAudioEngine.h"
#include "Effect/PVEffectSprite.h"
#include "Effect/UVEffectSprite.h"
#include "Data/DrumSurfaceLoader.h"

USING_NS_CC;
void BackGroundLayer::runInterface()
{

}

void BackGroundLayer::initInterface()
{
    this->setName("BackGroundLayer");
    MainScene::GetSceneInstance()->addChild(this);
    LoadSpriteCache(); //先预读精灵帧
    LoadNode();
    LoadAnimationCache();
}


void BackGroundLayer::LoadNode()
{
    topBG = Sprite::create("toppic.png");
    topBG->setPosition(Vec2(0, 640));
    topBG->setAnchorPoint(Vec2(0, 1));
    topBG->setScaleX(1.8750f);
    topBG->setScaleY(1.3370f);
    topBG->runAction(RepeatForever::create(Sequence::create(MoveBy::create(15, Vec2(960.0f, 0)), CallFunc::create([&](){
        topBG->setPosition(Vec2(0, 640));
    }), NULL)));
    this->addChild(topBG);

    topBGclone = Sprite::create("toppic.png");
    topBGclone->setPosition(Vec2(0, 640));
    topBGclone->setAnchorPoint(Vec2(1, 1));
    topBGclone->setScaleX(1.8750f);
    topBGclone->setScaleY(1.3370f);
    topBGclone->runAction(RepeatForever::create(Sequence::create(MoveBy::create(15, Vec2(960, 0)), CallFunc::create([&](){
        topBGclone->setPosition(Vec2(0, 640));
    }), NULL)));
    this->addChild(topBGclone);

    buttomBG = PVEffectSprite::create("miku.jpg");
    buttomBG->setPosition(Vec2(0, 0));
    buttomBG->setAnchorPoint(Vec2(0, 0));
    buttomBG->setScaleY(0.738f);
    buttomBG->setName("buttomBG");
    buttomBG->retain();
    this->addChild(buttomBG);

    //歌词结点
    auto lyrcisNode = Node::create();
    lyrcisNode->setPosition(Vec2(300.0f, 470.0f));
    lyrcisNode->setName("lyrcisNode");
    buttomBG->addChild(lyrcisNode);

    //歌词特效结点
    auto lyrcisParticleNode = Node::create();
    lyrcisParticleNode->setPosition(Vec2(300.0f, 470.0f));
    lyrcisParticleNode->setName("lyrcisParticleNode");
    buttomBG->addChild(lyrcisParticleNode);

	//初始化歌词Node,歌词Node包含5个歌词子结点
	for (int i = 0; i < 5; ++i)
	{
        auto lyrcis = Label::create();
		lyrcis->setAlignment(TextHAlignment::LEFT);
		lyrcis->setOpacity(0);//便于开始的FadeIn动作
        lyrcis->setSystemFontSize(30);
		lyrcis->setPositionY(-i * 40);
		lyrcis->setColor(Color3B{ 241, 125, 170 });
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
		lyrcis->enableOutline(Color4B(255, 192, 203, 255), 1);
		lyrcis->enableGlow(Color4B(255, 255, 255, 255));
#endif
		lyrcisNode->addChild(lyrcis);
	}

    auto lyrcisParticl = ParticleSystemQuad::create("particle/star.plist"); //歌词特效粒子
    lyrcisParticl->setPositionY(40);
    lyrcisParticl->setTotalParticles(20);
    lyrcisParticl->setVisible(false);
	lyrcisParticl->setName("lyrcisParticle");
    lyrcisParticleNode->addChild(lyrcisParticl);


   

    //触摸粒子
    touchparticle = ParticleSystemQuad::create("particle/touch.plist");
    touchparticle->setLocalZOrder(2);
    touchparticle->ignoreAnchorPointForPosition(true);
    touchparticle->setVisible(true);
    this->addChild(touchparticle);



    //初始化魂进度条
    soulProgBar = ProgressTimer::create(Sprite::create("progressUp.png"));
    soulProgBar->setType(ProgressTimer::Type::BAR);
    soulProgBar->setPosition(Vec2(250, 550));
    soulProgBar->ignoreAnchorPointForPosition(true);
    soulProgBar->setMidpoint(Point(0, 1));
    soulProgBar->setBarChangeRate(Point(1, 0));
    soulProgBar->setPercentage(0);
    this->addChild(soulProgBar);

    //添加进度条背景
    auto soulProgBarBG = Sprite::create();
    soulProgBarBG->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("progressDown.png"));
    soulProgBarBG->setPosition(Vec2(-5, -25));
    soulProgBarBG->setAnchorPoint(Vec2(0, 0));
    soulProgBarBG->setName("soul_progBarBG");
    soulProgBarBG->setLocalZOrder(-1);
    soulProgBar->addChild(soulProgBarBG);

    scrollBar_Background = UVEffectSprite::create();  //初始化鼓面背景层
    scrollBar_Background->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sfieldbg.png"));
    scrollBar_Background->setPosition(Vec2(92.65f, 410.83f));   //设置绝对坐标
    scrollBar_Background->setAnchorPoint(Vec2(0, 0));//设置坐标
    scrollBar_Background->setScaleX(1.6885f);
    scrollBar_Background->setScaleY(1.5645f);
    scrollBar_Background->retain();
    this->addChild(scrollBar_Background);

    scrollBar = Node::create(); //初始化鼓面
    scrollBar->setPosition(Vec2(92.65f, 410.83f));//设置绝对坐标
    scrollBar->setAnchorPoint(Vec2(0, 0));//设置坐标
    scrollBar->setScaleX(1.6885f);
    scrollBar->setScaleY(1.5645f);
    scrollBar->setContentSize(scrollBar_Background->getContentSize());//复制上一层的长度
    this->addChild(scrollBar);

    auto scrollBarGu = Node::create(); //滚动条鼓面结点
    scrollBarGu->setPosition(Vec2(0, 0));
    scrollBarGu->setLocalZOrder(2);
    scrollBar->addChild(scrollBarGu);

    scrollBarClone = Node::create();
    scrollBarClone->setName("scrollBarClone");
    scrollBarClone->setAnchorPoint(Vec2(0, 0));
    scrollBarClone->setPosition(Vec2(512, 0));
    auto scrollBarCloneGu = Node::create();//滚动副条鼓面结点
    scrollBarCloneGu->setPosition(Vec2(0, 0));
    scrollBarClone->addChild(scrollBarCloneGu);
    scrollBar->addChild(scrollBarClone);

    GUcharMap = Label::createWithCharMap("combonumber_balloon.png", 20, 24, '0');   //测试计数
    GUcharMap->setAnchorPoint(Vec2(0, 0));
    GUcharMap->setPosition(Vec2(0, -30));
    GUcharMap->setString("0");// 初始化为0分
    GUcharMap->setGlobalZOrder(4);
    scrollBar->addChild(GUcharMap);

    GUcharMapClone = Label::createWithCharMap("combonumber_balloon.png", 20, 24, '0');   //测试计数
    GUcharMapClone->setAnchorPoint(Vec2(0, 0));
    GUcharMapClone->setString("0");// 初始化为0分
    GUcharMapClone->setGlobalZOrder(4);
    GUcharMapClone->setPosition(Vec2(0, -30));
    scrollBarClone->addChild(GUcharMapClone);


#pragma region 初始游戏谱面
    for (int i = 0; i < DrumSurfaceLoader::PerDrumCount; ++i) //初始化  scrollBarGu与 scrollBarCloneGu的结点	
    {
        auto tempSprite = Sprite::create();
        tempSprite->setVisible(false);
        tempSprite->setPosition(Vec2((i % DrumSurfaceLoader::PerDrumCount) * scrollBar->getContentSize().width / DrumSurfaceLoader::PerDrumCount, 30));
        scrollBarGu->addChild(tempSprite);
        auto tempSprite2 = Sprite::create();
        tempSprite2->setVisible(false);
        tempSprite2->setPosition(Vec2((i % DrumSurfaceLoader::PerDrumCount) * scrollBar->getContentSize().width / DrumSurfaceLoader::PerDrumCount, 30));
        scrollBarCloneGu->addChild(tempSprite2);
    }
    scrollBarSpriteVector = scrollBarGu->getChildren();
    for (const auto &node : scrollBarCloneGu->getChildren())
    {
        scrollBarSpriteVector.pushBack(node);
    }
#pragma endregion

}


void BackGroundLayer::LoadAnimationCache()
{
    auto animationGuBlue = Animation::create();   	//创建鼓面显示动画
    animationGuBlue->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blueGu.png"));
    animationGuBlue->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blueGu_2.png"));
    animationGuBlue->setDelayPerUnit(0.2f);
    animationGuBlue->setRestoreOriginalFrame(true);
    auto animationGuRed = Animation::create();
    animationGuRed->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("redGu.png"));
    animationGuRed->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("redGu_2.png"));
    animationGuRed->setDelayPerUnit(0.2f);
    animationGuRed->setRestoreOriginalFrame(true);
    AnimationCache::getInstance()->addAnimation(animationGuBlue, "guBlue_Ani"); //添加为动画缓存
    AnimationCache::getInstance()->addAnimation(animationGuRed, "guRed_Ani");
}


void BackGroundLayer::LoadSpriteCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainScene.plist", "mainScene.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainscene_1.plist", "mainscene_1.png");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Bgm.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("musiceffect/dong.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("musiceffect/ka.wav");
}

BackGroundLayer::~BackGroundLayer()
{
    scrollBarSpriteVector.clear();
}