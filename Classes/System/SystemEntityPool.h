#ifndef REIMU_SYSTEM_SYSTEMMANAGE_H
#define REIMU_SYSTEM_SYSTEMMANAGE_H

#include "Data/DataEntityPool.h"
#include <vector>
#include "GameDefine.h"
#include "GameConst.h"
#include "Abstract/AbstractPollManager.inl"
#include "Abstract/AbstractEventDispatcher.inl"



class SystemEntityPool:public AbstractPollManager<AbstractPollEntity>
{
 
public:

    virtual ~SystemEntityPool(){};

    /**根据场景初始不同的System
    @param type 场景枚举类
    */
    void init(const SceneType  &type);


    /**重写运行方法*/
    inline void  run()    override
    {
        for (const auto &system : _vect)
        {         
            system->runInterface();
            if (!isSystemRuning) break;
        }
        if (!isSystemRuning) destory();
    }

    /**运行结束,执行方法后会结束该场景并释放
    @warning 暂时只针对主要游戏场景
    */
    void destory();

public:
    bool isSystemRuning = true; /**系统运行标识*/
    SceneType _sceneType;
};
#endif