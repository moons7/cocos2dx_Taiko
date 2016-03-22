#include "AccountScene.h"
#include "System/SystemEntityPool.h"
#include "Data/DataEntityPool.h"

USING_NS_CC;

Scene* AccountScene::scene = nullptr;
Node*  AccountScene::node = nullptr;
SystemEntityPool* AccountScene::_systemManage = new SystemEntityPool();
DataEntityPool* AccountScene::_dataManage = new DataEntityPool();

Scene* AccountScene::GetSceneInstance()
{
    // 'scene' is an autorelease object
    if (scene) return scene;
    else
    {
        scene = AccountScene::create();

        return scene;
    }

}


bool AccountScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    scene = this;


    //设置主要每帧定时器
    this->schedule(CC_SCHEDULE_SELECTOR(AccountScene::Run_PerFrame));

    _dataManage->init(SceneType::Account);
    _systemManage->init(SceneType::Account);
    return true;
}


void AccountScene::Run_PerFrame(float speed)
{
    _systemManage->run();
}

