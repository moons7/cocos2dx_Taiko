#ifndef REIMU_SYSTEM_JUDGESYSTEM_H
#define  REIMU_SYSTEM_JUDGESYSTEM_H
#include "GameDefine.h"
#include "Data/BackGroundLayer.h"
#include "Data/UILayer.h"
#include "Data/DrumSurfaceLoader.h"
#include "Data/MainLayer.h"
#include "cocos2d.h"
#include "Scene/MainScene.h"
#include "Abstract/AbstractEventDispatcher.inl"


/**判定难度枚举类*/
enum class JudgeStrength
{
    Judge_Easy,/**容易*/
    Judge_Normal,/**一般*/
    Judge_Hard/**困难*/
};


/**打击状态枚举类*/
enum class HitStatus
{
    HIT_PERFER,/**完美*/
    HIT_GOOD,/**良好*/
    HIT_MISS,/**已经Miss*/
    HIT_WAIT,/**等待判定*/
};

/**排序使用结构体*/
typedef struct _drumSortStruct
{
    unsigned short DrumSN = 0;
    float distance = 0.0f;
}DrumSortStruct;



/**击打判定系统*/
class JudgeSystem :public AbstractPollEntity
{
public:
    /**构造函数
    @param judgeStrength 难度选择
    */
    explicit JudgeSystem(const JudgeStrength& judgeStrength);

    virtual void	initInterface() override;

    /**触摸判定*/
    void   OnTouchJudgeMent(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

    static bool isLock;/**< 生成锁*/
   
    /** @brief 改变游戏模式*/
    void setGameMode();

private:
    BackGroundLayer* _nodeEntity = static_cast<BackGroundLayer*>(MainScene::GetDataManage()->getEntity("BackGroundLayer"));
    UILayer* _uiLayer = static_cast<UILayer*>(MainScene::GetDataManage()->getEntity("UILayer"));
    MainLayer* _mainLayer = static_cast<MainLayer*>(MainScene::GetDataManage()->getEntity("MainLayer"));
    DrumSurfaceLoader* _surfaceEntity = static_cast<DrumSurfaceLoader*>(MainScene::GetDataManage()->getEntity("drumSurface"));/**鼓面数据实体*/

    bool _IsAuto = true;/**< 自动模式*/
    std::stringstream ss; /**< string转换流*/
    const float _halfScreenPostionX = cocos2d::Director::getInstance()->getVisibleSize().width / 2.0;/**计算半屏判定点*/
    bool _isHitScreen = false;/**< 是否产生击打屏幕动作*/

protected:
    virtual	void   runInterface() override;

private:
#pragma region 结构体
    /**距离靶心(target)的距离结构体*/
    struct  JudgeDistance
    {
        float miss = 0; /**Miss过期距离*/
        float  leftGood = 0;/**左区域判定(可)*/
        float  rightGood = 0;/**右区域判定(可)*/
        float  leftPerfer = 0;/**左区域判定(良)*/
        float  rightPerfert = 0;/**右区域判定(良)*/
    }_judgeDistance;
#pragma endregion

    /**增加Hit数*/
    inline  void addHit(); 
    /**增加总分*/
    inline  void addTotalMark(const unsigned int &mark);


    void	 JudgeThreadExecute();    /**< 计算判定距离核心函数*/

    void	 EditThreadExecute();   /**< 编辑模式判定函数*/

    JudgeStrength _JudgeMode;  /**< 计算判定距离核心函数*/

    HitStatus *_hitStatusArray;/**< 击鼓状态数组*/

    /**执行击中后的逻辑
    @param num 击鼓状态的索引
    */
    void displayHit(const int num);

    int _delay = 3; /**击鼓状态延迟帧数*/

    enum  BezierSpriteStatus
    {
        Wait_FIRST_Bezier = 0x01,
        Wait_SENCOND_Bezier=0x02,
        Wait_Nothing=0x0F,
        Working = 0x10,
    };

    struct  BezierSpriteStruct /**< 贝塞尔曲线运动的精灵状态*/
    {
        unsigned short _BezierSpriteCount = 0; /**< 贝塞尔结点使用计数(总计使用了10个结点)*/
        std::vector<BezierSpriteStatus> BezierSpriteStatus_Vector;
    }p_bezierSpriteStruct;

    unsigned short _StarCount = 0; /**触摸星星结点计数(总计使用10个结点)*/

    unsigned short _progBarCount = 0;/**进度条计数*/

    HitStatus _hitStatus = HitStatus::HIT_MISS;/**< 鼓面的打击状态*/

    cocos2d::Vec2 _touchPos = cocos2d::Vec2::ZERO;/**触摸点击时的坐标*/

    float scrollSpeed = 0.0f;/**鼓条滚动速度*/
};


#endif