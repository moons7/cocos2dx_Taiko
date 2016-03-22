#ifndef REIMU_EFFECT_DOOREFFECTSPRITE_H
#define REIMU_EFFECT_DOOREFFECTSPRITE_H

#include "cocos2d.h"


class DoorEffectSprite :public cocos2d::Sprite
{
public:

    /**更新Shader数据(主要是Uniform数据)
    @param progressNow 显示进度(0~100)
    */
    void updateShader(const float progress);

    /**初始化Shader
    @warning  需显示调用
    */
    void InitShader();

    void endMainScene();

private:
    float iGlobalTime = 0.0f;
    bool _isFirst = true;
    int _waitTime = 10;
    bool _isEnd = false;
};
#endif 