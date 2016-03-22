#include "System/JudgeSystem.h"
#include "SimpleAudioEngine.h"
#include "Effect/PVEffectSprite.h"
#include "System/ScrollSystem.h"
#include "Static/PlayStatusStatic.h"
#include "Untils/RandomUntil.inl"

USING_NS_CC;

bool JudgeSystem::isLock = false;

void	JudgeSystem::initInterface()
{
	std::thread JudgeThread(&JudgeSystem::JudgeThreadExecute, this); // 此处可更改为编辑线程
	JudgeThread.detach();
	if (_JudgeMode == JudgeStrength::Judge_Easy) //根据滚动速度动态计算判定距离
	{
		_judgeDistance.miss = -scrollSpeed*0.5;
		_judgeDistance.leftGood = -scrollSpeed*0.2;
		_judgeDistance.rightGood = scrollSpeed*1.0;
		_judgeDistance.leftPerfer = -scrollSpeed*0.15;
		_judgeDistance.rightPerfert = scrollSpeed*0.8;
	}
	else  if (_JudgeMode == JudgeStrength::Judge_Normal)
	{
		_judgeDistance.miss = -scrollSpeed*0.4;
		_judgeDistance.leftGood = -scrollSpeed*0.15;
		_judgeDistance.rightGood = scrollSpeed*0.8;
		_judgeDistance.leftPerfer = -scrollSpeed*0.12;
		_judgeDistance.rightPerfert = scrollSpeed*0.7;
	}
	else if (_JudgeMode == JudgeStrength::Judge_Hard)
	{
		_judgeDistance.miss = -20;
		_judgeDistance.leftGood = -20;
		_judgeDistance.rightGood = 40;
		_judgeDistance.leftPerfer = -10;
		_judgeDistance.rightPerfert = 30;
	}
	for (int i = 0; i < 10; ++i)
	{
		p_bezierSpriteStruct.BezierSpriteStatus_Vector.push_back(BezierSpriteStatus::Wait_Nothing);
	}

}

JudgeSystem::JudgeSystem(const JudgeStrength& judgeStrength)
{
	_JudgeMode = judgeStrength;
}


void JudgeSystem::JudgeThreadExecute()
{
	auto maxSurfaceSize = _surfaceEntity->GetSurfaceEntityVector()->size();//获取鼓点的最大值
	DrumSufaceStruct *_tempDrumStruct = nullptr;//临时鼓面结构缓冲
	float distance = 0.0f;//距离
	Node* CheckedNode = nullptr;
	bool  onesFlag = false;//标志重新遍历了一次
	auto target = _mainLayer->_leftStateSprite->getChildByName("Target"); /**< 靶心Sprite,用于计算水平距离*/
	_hitStatusArray = new HitStatus[DrumSurfaceLoader::PerDrumCount * 2];
	auto system = MainScene::GetSystemManage();
	std::mutex _mutex;/**<线程互斥结构体*/

	//初始化
	while (true)//循环计算最近鼓点距离
	{
		if (!system->isSystemRuning)  break;
		onesFlag = true;
		for (int i = 0; i < DrumSurfaceLoader::PerDrumCount * 2; ++i)
		{
			CheckedNode = _nodeEntity->scrollBarSpriteVector.at(i);//根据鼓点数据推算相应的显示Node
			auto isVisible = false;
			if (_mutex.try_lock())
			{
				isLock = true;
				isVisible = CheckedNode->isVisible();
				isLock = false;
				_mutex.unlock();
			}
			else continue;

			if (!isVisible)
			{
				_hitStatusArray[i] = HitStatus::HIT_WAIT;
				continue;
			}
			distance = target->convertToNodeSpace(CheckedNode->convertToWorldSpace(Point(0, 0))).x;//计算与靶点相对的水平距离
			if (distance > -100 && distance < _judgeDistance.miss)
			{
				_hitStatusArray[i] = HitStatus::HIT_MISS;
				if (onesFlag&&_progBarCount > 0)
				{
					onesFlag = false;
					--_progBarCount;
				}
				if (PlayStatusStatic::playStatus->nowHit > PlayStatusStatic::playStatus->maxHit)PlayStatusStatic::playStatus->maxHit = PlayStatusStatic::playStatus->nowHit;
				PlayStatusStatic::playStatus->nowHit = 0;
				++PlayStatusStatic::playStatus->missHit;
			}
			else if (distance < _judgeDistance.rightPerfert&&distance > _judgeDistance.leftPerfer)//优先匹配Perfer
			{
				_hitStatusArray[i] = HitStatus::HIT_PERFER;
			}
			else if (distance < _judgeDistance.rightGood&&distance > _judgeDistance.leftGood)
			{
				_hitStatusArray[i] = HitStatus::HIT_GOOD;
			}
			else if (distance > _judgeDistance.rightPerfert)
			{
				_hitStatusArray[i] = HitStatus::HIT_WAIT;
			}
		}
	}
	CC_SAFE_DELETE_ARRAY(_hitStatusArray);
}



void JudgeSystem::addHit()
{
	++PlayStatusStatic::playStatus->nowHit;
	ss.clear();
	ss.str("");
	ss << PlayStatusStatic::playStatus->nowHit;
	static_cast<Label*>(_mainLayer->_leftStateSprite->getChildByName("HitCharMap"))->setString(ss.str());
	static_cast<Label*>(_mainLayer->_leftStateSprite->getChildByName("HitCharMap"))->runAction(Sequence::create(
		ScaleTo::create(0.1f, 1.0f, 1.3f),
		ScaleTo::create(0.1f, 1.0f, 1.0f),
		NULL));//文字缩放效果
}


void JudgeSystem::OnTouchJudgeMent(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	for (const auto &item : touches)
	{
		_touchPos = item->getLocation(); //获取Opengl坐标
		_isHitScreen = true;
		_delay = 3;
	}
}


void JudgeSystem::runInterface()
{
	ss.clear();
	ss.str("");
	ss << PlayStatusStatic::playStatus->nowHit;
	static_cast<Label*>(_mainLayer->_leftStateSprite->getChildByName("HitCharMap"))->setString(ss.str());

	if (!_IsAuto&&!_isHitScreen) return; //只有手动模式才可执行以下判定

	for (int i = 0; i < 2 * DrumSurfaceLoader::PerDrumCount; ++i)
	{
		_hitStatus = _hitStatusArray[i];
		if (_hitStatus == HitStatus::HIT_PERFER || (!_IsAuto&&_hitStatus == HitStatus::HIT_GOOD))
		{
			displayHit(i);
			break;
		}
	}
	_isHitScreen = (--_delay < 0) ? false : _isHitScreen;
}


void JudgeSystem::addTotalMark(const unsigned int &mark)
{
	ss.clear();
	ss.str("");
	PlayStatusStatic::playStatus->Mark += (mark + PlayStatusStatic::playStatus->nowHit * 10);
	ss << PlayStatusStatic::playStatus->Mark;
	auto totalMarkcharMap = _uiLayer->totalMarkcharMap;
	totalMarkcharMap->setString(ss.str());
	totalMarkcharMap->stopAllActions();
	totalMarkcharMap->setScale(0.9f);
	totalMarkcharMap->setOpacity(255);
	totalMarkcharMap->runAction(Spawn::create(ScaleTo::create(0.6f, 1.1f), FadeOut::create(2.0f), NULL));
}




void JudgeSystem::displayHit(const int hitNum)
{
	auto CheckedNode = _nodeEntity->scrollBarSpriteVector.at(hitNum);
	CheckedNode->setVisible(false);
	auto   tag = CheckedNode->getTag();
	CheckedNode->stopAllActions();
	addHit();

#pragma region 鼓面的动作逻辑(加入UI动作并随机2段曲线加速)
	auto bezierNodeVector = _mainLayer->_leftStateSprite->getChildByName("Target")->getChildByName("BezierVector")->getChildren();
	bool onlyOne = false; /**< 每帧只会有一个鼓面会击中*/
	for (int i = 0; i < 10; ++i)
	{
		auto& bezierDisplaySpriteStatus = p_bezierSpriteStruct.BezierSpriteStatus_Vector.at(i);//直接引用
		if ((bezierDisplaySpriteStatus&BezierSpriteStatus::Working) == BezierSpriteStatus::Working) continue;
		auto  bezierDisplaySprite = static_cast<Sprite*>(bezierNodeVector.at(i));//因为是指针,不必要auto &
		bezierDisplaySprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("redGu.png"));
		if (!onlyOne)
		{
			if ((bezierDisplaySpriteStatus&BezierSpriteStatus::Wait_Nothing) == BezierSpriteStatus::Wait_Nothing)
			{
				bezierDisplaySprite->setVisible(true);
				bezierDisplaySprite->setOpacity(255);
				bezierDisplaySprite->setPosition(Vec2::ZERO);
				bezierDisplaySpriteStatus = BezierSpriteStatus::Wait_FIRST_Bezier;
				onlyOne = true;
			}
		}
		if ((bezierDisplaySpriteStatus&BezierSpriteStatus::Wait_SENCOND_Bezier) != BezierSpriteStatus::Wait_SENCOND_Bezier && (bezierDisplaySpriteStatus&BezierSpriteStatus::Wait_FIRST_Bezier) == BezierSpriteStatus::Wait_FIRST_Bezier)
		{
			ccBezierConfig config1{ Vec2(0, RandomUntil::fgRangeRand(70, 100)), Vec2(RandomUntil::fgRangeRand(-50, -30), 90), Vec2(50, 110) }; /**< 随机贝塞尔曲线*/
			if (tag == 1)    //检测鼓面所在的类型
			{
				_nodeEntity->scrollBar_Background->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sfieldflash_red.png"));
				bezierDisplaySprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("redGu.png"));
			}
			else
			{
				_nodeEntity->scrollBar_Background->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sfieldflash_blue.png"));
				bezierDisplaySprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blueGu.png"));
			}
			bezierDisplaySprite->runAction(Sequence::create(BezierBy::create(1.5, config1),
				CallFunc::create([=](){
				ccBezierConfig config2{ Vec2(585, 0), Vec2(100, 30), Vec2(450, -80) };
				bezierDisplaySprite->runAction(Sequence::create(Spawn::create(BezierBy::create(1.5, config2), FadeOut::create(1.5f), NULL), Hide::create(),
					CallFunc::create([=](){// 按值传递捕获外部作用域的局部变量,性能会有点损失吧(保存当前局部状态,虽然只需要一个变量)
					p_bezierSpriteStruct.BezierSpriteStatus_Vector.at(i) = BezierSpriteStatus::Wait_Nothing;
				}), NULL));
				p_bezierSpriteStruct.BezierSpriteStatus_Vector.at(i) = BezierSpriteStatus::Wait_SENCOND_Bezier;
			}), NULL));
			bezierDisplaySpriteStatus = (BezierSpriteStatus)(bezierDisplaySpriteStatus | BezierSpriteStatus::Working);
		}
	}

#pragma endregion 鼓面的动作逻辑

#pragma region 星星UI以及心型槽动作逻辑

	auto position = _uiLayer->heartNode->getPosition();

	//贝塞尔曲线
	ccBezierConfig config{ position, Vec2(position.x - 200, position.y + 20), Vec2(position.x - 50, position.y + 50) };

	auto StarUINode = _uiLayer->_StarUINode;/**< 获取星星UI总结点 */

	auto touchstarNodeVector = StarUINode->getChildByName("StarDisplayVector")->getChildren();
	auto  touchstarNode = static_cast<Sprite*>(touchstarNodeVector.at(_StarCount));
	touchstarNode->setVisible(true);
	touchstarNode->setPosition(_touchPos);

	auto touchStreakNodeVector = StarUINode->getChildByName("StreakNodeVector")->getChildren();
	auto   touchStreakNode = static_cast<MotionStreak*>(touchStreakNodeVector.at(_StarCount));
	touchStreakNode->setVisible(true);
	touchStreakNode->setPosition(_touchPos);
	touchstarNode->stopAllActions();
	touchStreakNode->stopAllActions();
	//初始化动作信息
	touchstarNode->setOpacity(0);
	touchstarNode->runAction(Sequence::create(Spawn::create(BezierTo::create(1.0, config), RotateBy::create(1.0, 1080), FadeIn::create(1.0f), NULL)
		, Hide::create(), NULL));
	touchStreakNode->setVisible(true);
	touchStreakNode->runAction(Sequence::create(BezierTo::create(1.0, config), Hide::create(), NULL));

	_StarCount = (++_StarCount >= 10) ? 0 : _StarCount;
	(static_cast<MotionStreak*>(touchStreakNodeVector.at(_StarCount)))->reset();

	/**< 每次击鼓正确心形槽上移0.5距离 */
	_uiLayer->heartNode->getChildByName("heartin")->setPositionY(_uiLayer->heartNode->getChildByName("heartin")->getPositionY() + 0.5f);
#pragma endregion 星星UI动作逻辑(重做~~)

#pragma region 粒子效果

	//显示触摸粒子效果
	_nodeEntity->touchparticle->resetSystem();
	_nodeEntity->touchparticle->setPosition(_touchPos);
#pragma endregion 粒子效果



#pragma region 判定数变化的动作逻辑
	if (PlayStatusStatic::playStatus->nowHit / 100 > 0 && PlayStatusStatic::playStatus->nowHit % 100 < 50)    _mainLayer->_leftStateSprite->getChildByName("upDisplay")->setVisible(true); //更改鼓面显示
	else    _mainLayer->_leftStateSprite->getChildByName("upDisplay")->setVisible(false);

	if (PlayStatusStatic::playStatus->nowHit > 100)  static_cast<Label*>(_mainLayer->_leftStateSprite->getChildByName("HitCharMap"))->setCharMap("combonumber_l.png", 25, 38, '0'); //更改鼓面字体
	else      static_cast<Label*>(_mainLayer->_leftStateSprite->getChildByName("HitCharMap"))->setCharMap("combonumber_balloon.png", 20, 24, '0');
#pragma endregion 判定数变化的动作逻辑

#pragma region 进度条动作逻辑
	if (_progBarCount < 100)
	{
		++_progBarCount;
		auto to = ProgressTo::create(1.0f, _progBarCount);
		_nodeEntity->soulProgBar->runAction(to);
	}
#pragma endregion 进度条动作逻辑

#pragma region 靶心区的动作显示

	auto targetJadgeFontSprite = static_cast<Sprite*>(_mainLayer->_leftStateSprite->getChildByName("Target")->getChildByName("JadgeFont"));/**< 靶心的上方判断文字 */
	if (_hitStatus == HitStatus::HIT_PERFER)
	{
		targetJadgeFontSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("judgement_perfer.png"));
		++PlayStatusStatic::playStatus->perferHit;
		addTotalMark(200);
	}
	else if (_hitStatus == HitStatus::HIT_GOOD)
	{
		targetJadgeFontSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("judgement_good.png"));
		++PlayStatusStatic::playStatus->goodHit;
		addTotalMark(100);
	}
	targetJadgeFontSprite->setVisible(true);	/**< 良\中的跳跃动作*/
	targetJadgeFontSprite->runAction(Sequence::create(JumpBy::create(0.15f, Vec2(0, 0), 10, 1), Hide::create(), NULL));

	/**< 靶心上层动作显示 */
	auto  targetUpDisplaySprite = static_cast<Sprite*>(_mainLayer->_leftStateSprite->getChildByName("Target")->getChildByName("TargetUpDisplay"));/**< 靶心的顶层显示精灵 */
	targetUpDisplaySprite->setVisible(true);
	targetUpDisplaySprite->runAction(Sequence::create(ScaleTo::create(0.05f, 1.1f),
		FadeIn::create(0.05f),
		ScaleTo::create(0.05f, 1.0f),
		FadeOut::create(0.05f),
		NULL));
#pragma endregion 靶心区的动作显示

#pragma region 跟鼓面类型(红|蓝)相关的动作逻辑

	if (tag == 1)    //检测鼓面所在的类型
	{
		_nodeEntity->scrollBar_Background->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sfieldflash_red.png"));
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("musiceffect/dong.wav");
	}
	else
	{
		_nodeEntity->scrollBar_Background->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sfieldflash_blue.png"));
		   CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("musiceffect/ka.wav");
	}
#pragma endregion 跟鼓面类型(红|蓝)相关的动作逻辑

#pragma region 跟鼓条相关的动作逻辑
	auto backgroundFadeAction = FadeIn::create(0.15f);
	_nodeEntity->scrollBar_Background->runAction(Sequence::create(backgroundFadeAction,
		backgroundFadeAction->reverse(),
		CallFunc::create([&](){
		_nodeEntity->scrollBar_Background->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sfieldbg.png"));
	}), NULL));
#pragma endregion 跟鼓条相关的动作逻辑
}

void JudgeSystem::setGameMode()
{
	_IsAuto = !_IsAuto;
}


void JudgeSystem::EditThreadExecute()
{
	auto& BPM = (static_cast<ScrollSystem*>(MainScene::GetSystemManage()->getEntity("scrollSystem")))->BPMCount;
	float distance = 0.0f;//距离
	Node* CheckedNode = nullptr;
	bool  onesFlag = false;//标志重新遍历了一次
	auto  target = _mainLayer->_leftStateSprite->getChildByName("Target"); /**< 靶心Sprite,用于计算水平距离*/
	auto durmDataVector = (static_cast<DrumSurfaceLoader*>(MainScene::GetDataManage()->getEntity("drumSurface")))->GetSurfaceEntityVector();/**< 获取空白数据*/

	auto distanceArray = new DrumSortStruct[DrumSurfaceLoader::PerDrumCount * 2];
	//初始化
	while (true)//循环计算最近鼓点距离
	{
		for (int i = 0; i < DrumSurfaceLoader::PerDrumCount * 2; ++i)
		{
			CheckedNode = _nodeEntity->scrollBarSpriteVector.at(i);//根据鼓点数据推算相应的显示Node
			distanceArray[i].DrumSN = i;
			distanceArray[i].distance = abs(target->convertToNodeSpace(CheckedNode->convertToWorldSpace(Point(0, 0))).x);
			std::sort(distanceArray, distanceArray + DrumSurfaceLoader::PerDrumCount * 2, [](const DrumSortStruct &m1, const DrumSortStruct &m2){
				return  m1.distance < m2.distance;
			});
		}
		printf("当前的BPM为:%d ,最近距离为 %f ,鼓面编号为 %d \n", BPM, distanceArray[0].distance, distanceArray[0].DrumSN);
	}
	CC_SAFE_DELETE_ARRAY(distanceArray);
}
