#include "System/testSystem.h"
#include "System/testSystemEvent.h"
#include "System/testEventDispatcher.h"
#include "cocos2d.h"

void testSystem::runInterface()
{

}

void testSystem::initInterface()
{
	testEventDispatcher::getInstance()->addListener("testListen", this);
	auto testevent = new testSystemEvent_1();
	this->registerEvent(testevent, std::bind(&testSystemEvent_1::acceptEvent, testevent, std::placeholders::_1));
	auto x=testEventDispatcher::getInstance()->dispatchEvent("testListen", REIMU_EVENT(TEST_4233), (void*)5353);
	CCLOG("test %d", (int)x);
}



