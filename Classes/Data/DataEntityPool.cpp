#include "Data/DataEntityPool.h"
#include "Data/BackGroundLayer.h"
#include "Data/DrumSurfaceLoader.h"
#include "Data/LyricslableLoader.h"
#include "Data/UILayer.h"
#include "Data/MainLayer.h"
#include "Data/AccountSceneMainLayer.h"



void DataEntityPool::init(const SceneType & type)
{
    if (type == SceneType::Main)
    {
        registe(new DrumSurfaceLoader(), "drumSurface");
        registe(new LyricslableLoader(), "lyricslable");
        registe(new BackGroundLayer(), "BackGroundLayer");
        registe(new UILayer(), "UILayer");
        registe(new MainLayer(), "MainLayer");    
    }
    else if (type == SceneType::Account)
    {
        registe(new AccountSceneMainLayer(), "AccountSceneMainLayer");
    }
    else
    {
        CCASSERT(1 == 0, "SceneType error!");
    }
    AbstractPollManager::init();
}



