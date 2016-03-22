#include "SystemEntityPool.h"
 #include "System/JudgeSystem.h"
#include "System/ScrollSystem.h"
#include "System/LyricsSystem.h"
#include "System/ShaderSystem.h"
#include "Scene/AccountScene.h"
#include "Scene/MainScene.h"
#include "Abstract/AbstractPollEntity.h"
#include "System/AccountSystem.h"
#include "System/testSystem.h"

USING_NS_CC;


void SystemEntityPool::init(const SceneType &type)
{
    if (type == SceneType::Main)//主场景
    {
        auto g_scrollSystem = new ScrollSystem();
        auto g_judgeSystem = new JudgeSystem(JudgeStrength::Judge_Hard);
        auto g_lyricsSystem = new LyricsSystem();
        auto g_shaderSystem = new ShaderSystem();
        registe(g_scrollSystem,"scrollSystem");
        registe(g_judgeSystem, "judgeSystem");
        registe(g_lyricsSystem, "lyricsSystem");
        registe(g_shaderSystem,"shaderSystem");
		registe(new testSystem());
    }
    else if (type == SceneType::Account)//结算场景
    {
        registe(new AccountSystem());
    }
    else
    {
        CCASSERT(1 == 0, "SceneType error!");
    }
        AbstractPollManager::init();
        isSystemRuning = true;
        _sceneType = type;
}


void SystemEntityPool::destory()
{
    if (_sceneType==SceneType::Main)
    {
        Director::getInstance()->replaceScene(AccountScene::GetSceneInstance());/**< 切换场景无效果,麻蛋白改了*/
        Director::getInstance()->getTextureCache()->removeAllTextures();
        SpriteFrameCache::getInstance()->destroyInstance();
        AnimationCache::getInstance()->destroyInstance();  
        MainScene::GetDataManage()->destory();
        MainScene::GetSceneInstance()->removeAllChildrenWithCleanup(true);
    }
    else if (_sceneType == SceneType::Account)
    {

    }
    else
    {
        CCASSERT(1 == 0, "SceneType error!");
    }
       AbstractPollManager::destory();
}