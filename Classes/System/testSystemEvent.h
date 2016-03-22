#ifndef REIMU_SYSTEM_TESTSYSTEMEVENT_H
#define REIMU_SYSTEM_TESTSYSTEMEVENT_H
#include "Abstract/AbstractEvent.h"
#include "cocos2d.h"

class testSystemEvent_1 :public AbstractEvent
{
public:
	testSystemEvent_1() :AbstractEvent(REIMU_EVENT(TEST_4233)){};
	virtual void* acceptEvent(void* parmIN)
	{
		if (parmIN!=nullptr)
			CCLOG("OK");
		CCLOG("test");
		return (void*)5;
	};
};
#endif