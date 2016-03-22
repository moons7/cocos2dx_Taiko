#ifndef REIMU_SCENE_MENUSCENE_H
#define REIMU_SCENE_MENUSCENE_H
#include "cocos2d.h"

/**菜单场景
@warning 暂时没做
*/
class MenuScene :public cocos2d::Layer
{
public:
    static cocos2d::Scene* MenuScene::GetSceneInstance();

private:
    static cocos2d::Scene* scene;
    virtual bool init() override;

    /**定时器回调函数
    @param speed 这是什么鬼？
    */
    void Run_PerFrame(float speed);
};
#endif