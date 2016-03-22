#ifndef REIMU_ABSTRACT_ABSTRACTEVENT_H
#define REIMU_ABSTRACT_ABSTRACTEVENT_H
#include<string>
typedef  std::string EVENT_KEY_TYPE;

#define   REIMU_EVENT(_name)     std::string("_name")
/************************************************************************
/* 抽象事件类 
 @brief 供监听类调用其事件对象并实现回调方法                                                    
/************************************************************************/
class AbstractEvent
{
public:
	explicit AbstractEvent(const EVENT_KEY_TYPE& _eventname){ this->_eventName = _eventname; };

	bool operator < (const AbstractEvent & cmp) const /**std::map作为key的要求*/
	{
		return _eventName < cmp._eventName;
	}

	inline EVENT_KEY_TYPE getEventName() const { return _eventName; };

protected:
	virtual void* acceptEvent(void*){ return nullptr; };
	EVENT_KEY_TYPE _eventName;
};

#endif