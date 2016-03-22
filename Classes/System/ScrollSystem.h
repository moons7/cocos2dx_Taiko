#ifndef REIMU_SYSTEM_SCROLLSYSTEM_H
#define REIMU_SYSTEM_SCROLLSYSTEM_H
#include "Effect/PVEffectSprite.h"
#include "System/SystemEntityPool.h"
#include "Data/DrumSurfaceLoader.h"
#include "Data/BackGroundLayer.h"
#include "Scene/MainScene.h"
#include "Data/UILayer.h"



class ScrollSystem :public AbstractPollEntity
{
public:
    short BPMCount = 0;/**< BPM计数*/

protected:
    float _scrollSpeed = 0.0f; /**< 滚动条滚动速度*/
    float  _srollBarPostionX = 0.0f;/**< 滚动条位置*/
    float  criticalPoint = 0;/**< 地图滚动临界点(超过此临界点则说明第一图已经显示完毕,开始第二滚动图条的初始化和加载)*/
    float  mapSetPoint = 0;/**< 地图设定临界点*/
    bool scrollLock = false; /**< 滚动判定锁*/
   
protected:
    virtual void initInterface() override final;
    virtual void runInterface() override final;

private:
    BackGroundLayer* _nodeEntity = static_cast<BackGroundLayer*>(MainScene::GetDataManage()->getEntity("BackGroundLayer"));/**< 界面数据实体 直接从Scene中通过getChild获取Layer也是一样的,是同一个对象*/
    DrumSurfaceLoader* _surfaceEntity = static_cast<DrumSurfaceLoader*>(MainScene::GetDataManage()->getEntity("drumSurface"));/**< 鼓面数据实体*/
    UILayer* _uiLayer = static_cast<UILayer*>(MainScene::GetDataManage()->getEntity("UILayer"));/**界面数据实体*/


    unsigned short _SrollState = 0x111;/**滚动数据状态*/
    std::stringstream ss; /**string转化流*/

    /**滚动状态检测
    判断是否需要初始化,进行初始化,然后加入对方的锁,1面出现,初始化2面
    */
    inline  void CheckSroll()
    {
        _SrollState = (_SrollState | 0x000) == 0x000 ? 0x111 : _SrollState;
    }

    /**进行初始化,然后加入对方的锁,2面出现,初始化1面*/
    inline void CheckSrollClone()
    {
        _SrollState = (_SrollState & 0x110) == 0x100 ? 0x010 : _SrollState;
    }

    inline bool  IsSrollChange() const
    {
        return (_SrollState & 0x010) == 0x010;
    }

    inline bool IsSrollInit() const
    {
        return (_SrollState & 0x001) == 0x000;
    }

    inline void SetInitOver()
    {
        _SrollState = _SrollState & 0x101;
    }

private:
    inline void addBPMCount();/** < 显示当前的BPM数,仅供测试用*/
};
#endif

///**
//**滚动状态说明
//**/
//typedef struct _DrumSrollState
//{
//	enum {
//		SrollInit = 0x000, //1面初始化
//		SrollCloneInit = 0x100, //2面初始化
//		SrollOverInit = 0x111,//1面已初始化
//		SrollCloneOverInit = 0x010//2面已初始化
//	};
//}DrumSrollState;