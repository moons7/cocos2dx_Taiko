#include "Data/UILayer.h"
#include "Scene/MainScene.h"
#include "Effect/DoorEffectSprite.h"

USING_NS_CC;

void UILayer::initInterface()
{
    this->setName("UILayer");
    MainScene::GetSceneInstance()->addChild(this);
#pragma region 计分面板相关
    totalMarkcharMap = Label::createWithCharMap("totalMark.png", 26, 35, '0');  //初始化总计分面板
    totalMarkcharMap->setAnchorPoint(Vec2(1, 0));
    totalMarkcharMap->setString("0");// 初始化为0分
    totalMarkcharMap->setPosition(Vec2(940, 520));
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
    /**< 添加遮罩效果 */
    auto clippingNode = ClippingNode::create(); //整个计分面板为一个剪裁结点
    clippingNode->setPosition(Vec2(0, 0));
    auto spark = Sprite::create("spark.png"); //创建遮罩图片
    spark->setPosition(940 - totalMarkcharMap->getContentSize().width, 520);
    spark->setAnchorPoint(Vec2(1, 0));
    auto moveBackAction = MoveTo::create(2.0f, Vec2(930 - totalMarkcharMap->getContentSize().width * 2 - 10, 520));
    auto moveAction = MoveTo::create(2.0f, Vec2(930 + totalMarkcharMap->getContentSize().width * 2 + 10, 520));
    spark->runAction(RepeatForever::create(Sequence::create(moveAction, moveBackAction, NULL)));
    clippingNode->setAlphaThreshold(0.05f); //设置alpha闸值
    clippingNode->setStencil(totalMarkcharMap);
    clippingNode->addChild(totalMarkcharMap, 1);
    clippingNode->addChild(spark, 2);
    this->addChild(clippingNode);
#else
    mainScene->addChild(totalMarkcharMap);
#endif
#pragma endregion 计分面板相关
#pragma region 星星与心型UI
    _StarUINode = Node::create();
    _StarUINode->ignoreAnchorPointForPosition(true);
    this->addChild(_StarUINode);
    // 初始化触摸星星的拖尾结点
    auto streakNodeVector = Node::create();
    streakNodeVector->setName("StreakNodeVector");/**< 拖尾结点集合*/
    for (int i = 0; i < 10; ++i) /**< 添加10个拖尾结点是为了解决1个无法在1个显示周期 */
    {
        auto  streak = MotionStreak::create(1.0f, 2, 10, Color3B(251, 4, 132), SpriteFrameCache::getInstance()->getSpriteFrameByName("test1.png")->getTexture());/**< 分别添加拖尾效果*/
        streak->setVisible(false);
        streakNodeVector->addChild(streak);
    }
    _StarUINode->addChild(streakNodeVector);
    // 初始化触摸星星结点
    auto  touchStarNode = Node::create();
    touchStarNode->setName("StarDisplayVector");/**< 拖尾结点前端的星星显示*/
    for (int i = 0; i < 10; ++i) /**< 同样和上面对应 */
    {
        auto  touchStar = Sprite::create("Star_1.png");
        touchStar->setVisible(false);
        touchStarNode->addChild(touchStar);
    }
    _StarUINode->addChild(touchStarNode);
    //心型计数槽
    heartNode = ClippingNode::create(); //整个计分面板为一个剪裁结点
    auto heartIn = Sprite::create("heart_in.png"); //创建遮罩图片
    heartIn->setScale(0.6f);
    heartIn->setName("heartin");
    auto heart = Sprite::create("heart.png");
    heart->setScale(0.6f);
    heartNode->setAlphaThreshold(0.05f); //设置alpha闸值
    heartNode->setStencil(heart);
    heartNode->addChild(heart, 1);
    heartNode->addChild(heartIn, 2);
    heartNode->setPosition(Vec2(880, 270));
    heartIn->setPosition(Vec2(0, -100));
    this->addChild(heartNode);

    auto heartNodeParticle = ParticleSystemQuad::create("particle/progress_2.plist"); /**<  心型的粒子效果*/
    heartNodeParticle->setPosition(heartNode->getPosition());
    this->addChild(heartNodeParticle);
#pragma endregion 星星UI
#pragma region 等待界面相关
    auto waitingPage = DoorEffectSprite::create("waiting.png");
    waitingPage->setGlobalZOrder(2);
    waitingPage->setAnchorPoint(Vec2(0, 0));
    waitingPage->setScaleY(1.1f);
    waitingPage->setName("WaitingPage");
    waitingPage->retain();
    this->addChild(waitingPage);

    auto waitingFont = Label::create(); /**< 等待说明文字*/
    waitingFont->setString("Loading...");
    waitingFont->setPosition(Vec2(850, 100));
    waitingFont->setColor(Color3B{ 250, 3, 235 });
    waitingFont->retain();
    waitingFont->setGlobalZOrder(4);
    waitingFont->runAction(Sequence::create(Blink::create(5.0, 5),Hide::create(),NULL));
    waitingPage->addChild(waitingFont);
#pragma endregion 


}



void UILayer::runInterface()
{

}
