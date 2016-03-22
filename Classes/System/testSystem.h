#ifndef REIMU_SYSTEM_TESTSYSTEM_H
#define REIMU_SYSTEM_TESTSYSTEM_H
#include "Abstract/AbstractEventListener.h"
#include "Abstract/AbstractPollEntity.h"

class testSystem : public AbstractPollEntity, public  AbstractEventListener
{
	
private:
	virtual void runInterface();

	virtual void initInterface();

};

#endif