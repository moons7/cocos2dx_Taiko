#include "Effect/RippleEffectSprite.h"

USING_NS_CC;

RippleEffectSprite* RippleEffectSprite::create(const char *pszFileName,Rect rect) {
	auto pRet = new (std::nothrow) RippleEffectSprite();
	if (!pRet) {
		CC_SAFE_DELETE(pRet);
		return  pRet;
	}

	if (&rect == nullptr){
		if (pRet->initWithFile(pszFileName)) pRet->autorelease();
		else CC_SAFE_DELETE(pRet);
	}
	else{	
		if (pRet->initWithFile(pszFileName, rect)) pRet->autorelease();
		else CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void RippleEffectSprite::initGLProgram() {
	GLProgram * p = new GLProgram();
	p->initWithFilenames("shaders/font_advance.vsh", "shaders/font_advance.fsh");
	p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
	p->link();
    p->updateUniforms();
    setGLProgram(p);

	// NOTE: now we need schedule update here
}

void RippleEffectSprite::update() {
	//if (!isVaild) return;
 //
	//// TODO: improve
	float rippleSpeed = 0.10f;
	float maxRippleDistance = 3.0f;//最大遍历距离
	_m_rippleDistance += rippleSpeed * _delta;
	_m_rippleRange = (1 - _m_rippleDistance / maxRippleDistance) * 0.01f;
	if (_m_rippleDistance > maxRippleDistance)
    {
		_m_rippleDistance = 0.0f;
		_isVaild = false;
	}
	_test += 0.005f;
    if (_test > 1.00f) _test = 0.0f;
	getGLProgramState()->setUniformFloat("u_rippleDistance", _m_rippleDistance);
	getGLProgramState()->setUniformFloat("u_rippleRange", _m_rippleRange);
	getGLProgramState()->setUniformFloat("v_x",this-> _v_x);
	getGLProgramState()->setUniformFloat("v_y", this->_v_y);
	getGLProgramState()->setUniformFloat("progress", this->_test);
	
}

void RippleEffectSprite::initGL(const float delta, const float v_x, const float v_y)
{
	_isVaild = true;
	this->_delta = delta;
	this->_v_x = v_x;
	this->_v_y = v_y;
}
