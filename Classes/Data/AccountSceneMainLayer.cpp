#include "Data/AccountSceneMainLayer.h"
#include "Scene/AccountScene.h"
#include "ui/UITextBMFont.h"


USING_NS_CC;


void AccountSceneMainLayer::runInterface()
{

}

void AccountSceneMainLayer::initInterface()
{
#pragma region 背景布局
    this->setName("BackGroundLayer");
    AccountScene::GetSceneInstance()->addChild(this);
    auto backGround = Sprite::create("resultbg_clear.png");
    backGround->setName("BackGround");
    backGround->setPosition(Vec2(483.04f, 318.01f));
    backGround->setScaleX(1.8921f);
    backGround->setScaleY(1.6778f);
    this->addChild(backGround);

    auto resultBoard = Sprite::create("resultboard.png");
    resultBoard->setName("ResultBoard");
    resultBoard->setPosition(Vec2(609.99f, 431.99f));
    resultBoard->setScaleX(1.8160f);
    resultBoard->setScaleY(1.3677f);
    this->addChild(resultBoard);



    auto atomicSeal = Sprite::create("test2.png"); /**< 印章Sprite*/
    atomicSeal->setName("AtomicSeal");
    atomicSeal->setPosition(Vec2(750.0f, 390.0f));
    atomicSeal->setVisible(false);
    atomicSeal->setScale(5.0f);
    this->addChild(atomicSeal);

#pragma endregion 背景布局
#pragma region 数字布局
    auto MaxHit = Label::createWithCharMap("totalMark.png", 26, 35, '0');
    MaxHit->setName("MaxHit");
    MaxHit->setPosition(Vec2(151.64f, 97.70f));
    MaxHit->setScale(0.8f);
    MaxHit->setString("0");
    resultBoard->addChild(MaxHit);

    auto RightRate = Label::createWithCharMap("totalMark.png", 26, 35, '0');
    RightRate->setName("RightRate");
    RightRate->setPosition(Vec2(306.38f, 97.70f));;
    RightRate->setScale(0.8f);
    RightRate->setString("0");
    resultBoard->addChild(RightRate);

    auto Perfer = Label::createWithCharMap("totalMark.png", 26, 35, '0');
    Perfer->setName("Perfer");
    Perfer->setScale(0.8f);
    Perfer->setPosition(Vec2(63.35f, 67.04f));
    Perfer->setString("0");
    resultBoard->addChild(Perfer);

    auto Good = Label::createWithCharMap("totalMark.png", 26, 35, '0');
    Good->setName("Good");
    Good->setPosition(Vec2(150.36f, 67.04f));
    Good->setScale(0.8f);
    Good->setString("0");
    resultBoard->addChild(Good);

    auto Miss = Label::createWithCharMap("totalMark.png", 26, 35, '0');
    Miss->setName("Miss");
    Miss->setString("0");
    Miss->setPosition(Vec2(246.73f, 67.04f));
    Miss->setScale(0.8f);
    resultBoard->addChild(Miss);

    auto Hit = Label::createWithCharMap("totalMark.png", 26, 35, '0');
    Hit->setName("Hit");
    Hit->setPosition(Vec2(335.94f, 67.04f));
    Hit->setString("0");
    Hit->setScale(0.8f);
    resultBoard->addChild(Hit);

    auto Mark = Label::createWithCharMap("totalMark.png", 26, 35, '0');
    Mark->setName("Mark");
    Mark->setPosition(Vec2(78.24f, 26.10f));
    Mark->setScale(0.8f);
    Mark->setString("0");
    resultBoard->addChild(Mark);

#pragma endregion 数字布局
}

