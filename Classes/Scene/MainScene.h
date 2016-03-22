#ifndef REIMU_SCENE_MAINTSCENE_H
#define REIMU_SCENE_MAINTSCENE_H

#include "cocos2d.h"
#include "Data/DataEntityPool.h"
#include "System/SystemEntityPool.h"

/**主要游戏场景*/
class MainScene : public cocos2d::Scene
{

public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer

    static Scene* GetSceneInstance();
    static DataEntityPool* GetDataManage(){ return _dataManage; };
    static SystemEntityPool* GetSystemManage(){ return _systemManage; };
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init() override;

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);

private:
    /**定时器回调函数
    @param speed 这是什么鬼？
    */
    inline void Run_PerFrame(float speed);

    static   DataEntityPool* _dataManage;
    static   SystemEntityPool* _systemManage;

    /**键盘触摸响应函数
    @param keyCode 键盘码
    @param event cocos2dx自带事件
    */
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    static Scene* scene;/**该scene指针*/
};
#endif 
