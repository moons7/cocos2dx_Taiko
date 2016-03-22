#ifndef REIMU_EFFECT_RIPPLEEFFECTSPRITE_H
#define REIMU_EFFECT_RIPPLEEFFECTSPRITE_H

#include "cocos2d.h"

class RippleEffectSprite : public  cocos2d::Sprite
{
public:
	static RippleEffectSprite* create(const char *pszFileName, cocos2d::Rect rect);
	void initGLProgram();
	void update();
    void initGL(const float delta, const float v_x, const float v_y);

private:
	float _m_rippleDistance{ 0.0f };
	float _m_rippleRange{ 0.02f };
    float _v_x = 0.5f;
    float _v_y = 0.5f;
    float _delta = 0.0f;
    bool _isVaild = true;
    float _test = 0.0f;
};

#endif