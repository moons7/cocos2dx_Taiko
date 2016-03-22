#ifndef REIMU_SCENE_ACCOUNTSCENE_H
#define REIMU_SCENE_ACCOUNTSCENE_H
#include "cocos2d.h"
#include "Data/DataEntityPool.h"
#include "System/SystemEntityPool.h"

/**结算场景*/
class AccountScene:public cocos2d::Scene
{
public:
    /**获取该Scene实例
    @return Scene实例
    */
	static cocos2d::Scene*  GetSceneInstance();
    static DataEntityPool* GetDataManage(){ return _dataManage; };
    static SystemEntityPool* GetSystemManage(){ return _systemManage; };

    virtual bool init() override;
    
    /**显示node*/
    static  cocos2d::Node *node;
private:
    /**静态scene 指针*/
    static cocos2d::Scene* scene;


    static   DataEntityPool* _dataManage;
    static   SystemEntityPool* _systemManage;

    /**定时器回调函数
    @param speed 这是什么鬼？
    */
    void Run_PerFrame(float speed);

    /**cocos2dx自带静态Create宏*/
    CREATE_FUNC(AccountScene);
};
#endif