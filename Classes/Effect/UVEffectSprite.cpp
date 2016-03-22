#include  "Effect/UVEffectSprite.h"

USING_NS_CC;

void UVEffectSprite::InitShader()
{
    auto  p = new GLProgram();
    p->initWithFilenames("Shaders/uv.vsh", "Shaders/uv.fsh");
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    p->link();
    p->updateUniforms();
    this->setGLProgram(p);
    auto textrue = Director::getInstance()->getTextureCache()->addImage("soroll_uv3.png");
    Texture2D::TexParams tRepeatParams;//设置纹理渲染方式
    tRepeatParams.magFilter = GL_LINEAR_MIPMAP_LINEAR;
    tRepeatParams.minFilter = GL_LINEAR;
    tRepeatParams.wrapS = GL_REPEAT;
    tRepeatParams.wrapT = GL_REPEAT;
    textrue->setTexParameters(tRepeatParams);//将贴图设置给Shader中的变量值u_texture1
    _lightani.x = _lightani.y = 0.0f;
   getGLProgramState()->setUniformTexture("u_lightTexture", textrue);
    getGLProgramState()->setUniformVec2("v_animLight", _lightani);
}

void UVEffectSprite::updateShader()
{
    --_delay;
    if (_delay > 0) return;
    else _delay = 2;
    _lightani.x += 0.01f;
    if (_lightani.x > 1.0f)
    {
        _lightani.x -= 1.0f;
    }

    _lightani.y += 0.001f;
    if (_lightani.y > 1.0f)
    {
        _lightani.y -= 1.0f;
    }
    getGLProgramState()->setUniformVec2("v_animLight", _lightani);//设置UV坐标
}

