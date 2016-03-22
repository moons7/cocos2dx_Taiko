#include "MenuScene.h"
#include "System/SystemEntityPool.h"

USING_NS_CC;

Scene* MenuScene::scene = nullptr;
Scene* MenuScene::GetSceneInstance()
{
    // 'scene' is an autorelease object
    if (scene) return scene;
    else
    {
        scene = Scene::create();
        // 'layer' is an autorelease object
        auto layer = MenuScene::create();

        // add layer as a child to scene
        scene->addChild(layer);
        return scene;
    }

}


bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    auto accountSpite = Sprite::create("resultbg_clear.png");
    this->addChild(accountSpite);
    //设置主要每帧定时器
    this->schedule(CC_SCHEDULE_SELECTOR(MenuScene::Run_PerFrame));

   
    return true;
}


void MenuScene::Run_PerFrame(float speed)
{

}