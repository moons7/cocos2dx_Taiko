#ifndef  REIMU_DATA_LAYER_MAINSCENE_BACKGROUND_H
#define  REIMU_DATA_LAYER_MAINSCENE_BACKGROUND_H
#include "cocos2d.h"
#include "Abstract/AbstractPollEntity.h"

/**@brief 背景层,主要放置相对静止的布局,如顶部循环图。
    @attention 歌词显示布局也放这里？
*/
class BackGroundLayer : public AbstractPollEntity, public cocos2d::Layer
{
public:
    virtual void runInterface() override;
    virtual void initInterface() override;
    ~BackGroundLayer();

 public:

    cocos2d::Sprite *buttomBG = nullptr;//底背景(PV背景)

    //鼓面布局
    cocos2d::Label  * GUcharMap = nullptr;//鼓面连打计数面板
    cocos2d::Label  * GUcharMapClone = nullptr;//鼓面连打计数面板
    cocos2d::Sprite  *guDisplayBlue = nullptr;//鼓面蓝色圈
    cocos2d::Sprite   *guDisplay = nullptr;//鼓面显示层
    cocos2d::Label    * charMap = nullptr;//鼓面连打计数面板1

    //滚动面布局
    cocos2d::Sprite  *scrollBar_Background = nullptr;//滚动背景
    cocos2d::Node  *scrollBar = nullptr;
    cocos2d::Node  *scrollBarClone = nullptr;
    cocos2d::Sprite  *spirteCache = nullptr; //缓冲Spite
    cocos2d::Vector<cocos2d::Node*>   scrollBarSpriteVector;//总的鼓点精灵集合
    cocos2d::Sprite *gu = nullptr;

    //魂布局
    cocos2d::Sprite *soul = nullptr;
    cocos2d::ProgressTimer *soulProgBar = nullptr;//魂进度条
	cocos2d::ParticleSystemQuad  *touchparticle = nullptr; /**<  触摸粒子效果*/

  
protected:
    cocos2d::Sprite *topBG = nullptr;/**< 顶背景 仅用于lamba回调 */
    cocos2d::Sprite *topBGclone = nullptr;/**< 顶背景Clone 仅用于lamba回调 */

    void  LoadSpriteCache(); /**<先预读精灵帧*/
    void  LoadNode();
    void LoadAnimationCache();
};
#endif