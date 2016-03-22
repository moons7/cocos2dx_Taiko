#include  "Effect/PVEffectSprite.h"
#include "cocos2d.h"
USING_NS_CC;

PVEffectSprite::PVEffectSprite() :
progress(0.0f),
PVcount(0.0f)
{
}



void PVEffectSprite::InitShader()
{
    auto p = new GLProgram();
	p->initWithFilenames("Shaders/PV.vsh", "Shaders/PV.fsh");
	p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    p->link();
	p->updateUniforms();
	setGLProgram(p);
	progress = 1.0f;
	PVcount = 0.0f;
}

int PVEffectSprite::updateShader(const float progressNow, Sprite  *  const temp)
{
	
		getGLProgramState()->setUniformFloat("progress", 1.0f);
		getGLProgramState()->setUniformFloat("x_offset", 0.0f);
		getGLProgramState()->setUniformFloat("y_offset", 0.0f);
		getGLProgramState()->setUniformFloat("region", 1.0f);

    if (progressNow < 0.9f) return 0;
    else if (progressNow >= 0.9f&&status == 0)
	{
		progress -= 0.001f;
		if (progress <0.5f)
        {
			status = 1;
			temp->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("wencheng.jpg"));
			temp->setScaleY(4.0f);
			getGLProgramState()->setUniformFloat("progress", progress);
			getGLProgramState()->setUniformFloat("x_offset", 0.0f);
			getGLProgramState()->setUniformFloat("y_offset", 0.0f);
			getGLProgramState()->setUniformFloat("region", 1.0f);
			return 2;
		}
        return 0;
	}
	  
	  if (PVcount < progressNow) PVcount += 0.00007f;
		progress += 0.001f;
		if (progress > 1.00f)
		{
			progress = 1.0f;
		if (status == 1) status = 2;
		}
		getGLProgramState()->setUniformFloat("progress", progress);

		x_offset = 0.8f -   PVcount;
		if (x_offset <= 0.0f) x_offset = 0.0f;
		getGLProgramState()->setUniformFloat("x_offset", x_offset);

		y_offset = 0.8f -  PVcount;
		if (y_offset <= 0.0f) y_offset = 0.0f;
		getGLProgramState()->setUniformFloat("y_offset", y_offset);

		region = 0.3+ PVcount;
		if (region >= 1.0f) region = 1.0f;
		getGLProgramState()->setUniformFloat("region",PVcount);
		return 0;
	}



