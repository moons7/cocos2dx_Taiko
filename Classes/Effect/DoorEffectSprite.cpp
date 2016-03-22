#include "DoorEffectSprite.h"
#include "Scene/MainScene.h"

USING_NS_CC;

void DoorEffectSprite::InitShader()
{
    auto p = new GLProgram();
    p->initWithFilenames("Shaders/door.vsh", "Shaders/door.fsh");
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    p->link();
    p->updateUniforms();
    setGLProgram(p);
    iGlobalTime = 0.0f;
    getGLProgramState()->setUniformFloat("iGlobalTime", iGlobalTime);
    _waitTime = 0;
    _isEnd = false;
}

void  DoorEffectSprite::updateShader(const float progress)
{
    if (_isEnd) return;
    if (_waitTime > 0)
    {
        --_waitTime;
        return;
    }
    if (_isFirst)iGlobalTime += 0.005f;
    getGLProgramState()->setUniformFloat("iGlobalTime", iGlobalTime);
    if (iGlobalTime > 0.5f)
    {
        _isFirst = false;
        this->setVisible(false);
    }
}

void DoorEffectSprite::endMainScene()
{
    if (!_isFirst)
    {
        this->setVisible(true);
        iGlobalTime = 0.5f;
        _isFirst = true;
        _isEnd = true;
    }
    if (_isFirst)iGlobalTime -= 0.002f;
    if (iGlobalTime >= -0.001f)
    {
        getGLProgramState()->setUniformFloat("iGlobalTime", iGlobalTime);
    }
    else if (iGlobalTime <= -0.2f)
    {
        MainScene::GetSystemManage()->isSystemRuning = false;
    }
}
