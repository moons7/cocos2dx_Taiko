#ifndef REIMU_EFFECT_UVEFFECTSPRITE_H
#define REIMU_EFFECT_UVEFFECTSPRITE_H
#include "cocos2d.h"


class UVEffectSprite :public  cocos2d::Sprite
{
public:
    /**更新Shader*/
	void updateShader();

    /**初始化Shader*/
	void InitShader();

private:
    cocos2d::Vec2 _lightani = { 0.0f, 0.0f };/**偏移位置*/

    int _delay = 10;/**更新延迟*/
};
#endif
