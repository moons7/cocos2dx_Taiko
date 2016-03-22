#ifndef REIMU_EFFECT_PVEFFECTSPRITE_H
#define REIMU_EFFECT_PVEFFECTSPRITE_H

#include "cocos2d.h"


class PVEffectSprite :public cocos2d::Sprite
{
public:
    /**构造函数*/
	PVEffectSprite();

    /**更新Shader数据(主要是Uniform数据)
    @param progressNow 显示进度(0~100)
    @param temp  作用于改Effect的显示精灵
    */
    int updateShader(const float progressNow, Sprite * const temp);

    /**初始化Shader
    @warning  需显示调用
    */
	void InitShader();

private:
    float PVcount = 0.0f;/**进度缓冲计数*/
	float progress = 1.0f; /**alpha进度*/
	float region = 0.0f; /**PV截取区间*/
	float x_offset = 0.0f; /**x坐标偏移*/
	float y_offset = 0.0f; /**y坐标偏移*/
	unsigned short status= 0;/**0为普通状态 1位显出状态  2为PV状态 3为淡出状态*/
};
#endif 