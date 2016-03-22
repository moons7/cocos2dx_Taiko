#ifndef REIMU_ABSTRACT_ABSTRACTEVENTLISTENER_H
#define REIMU_ABSTRACT_ABSTRACTEVENTLISTENER_H
#include"Abstract\AbstractEvent.h"
#include <functional>
#include <map>
#include <vector>
#include "cocos2d.h"


/**事件监听类
*@brief 执行分发者所分配的任务
*/
class AbstractEventListener
{
public:
    /**析构函数*/
    virtual ~AbstractEventListener(){
		_eventMap.clear();
		for (auto &event : _eventList)
		{
			CC_SAFE_DELETE(event); 
		}
		_eventList.clear();
	};

    /**执行事件
     @param eventID  事件ID结构
     @param parmIN 输入结构指针
    */
	inline virtual void*  execEvent(const EVENT_KEY_TYPE& event, void *parmIN)
    {
		auto& iter = _eventMap.find(event);
		if (iter != _eventMap.end())
		{
			auto& method = iter->second;
			return  method(parmIN);
		}
		else return nullptr;
    };

	/*
	*@brief 注册监听方法
	* @param event  事件结构
	*@param method 回调函数指针
	*/
	virtual  void registerEvent(AbstractEvent * const event, std::function<void*(void*)> method)
	{
		_eventList.push_back(event);
		_eventMap.insert(std::pair<EVENT_KEY_TYPE, std::function<void*(void*)>>(event->getEventName(), method));
	}

protected:
	std::string _listenName;/**< 监听名*/
	std::map<EVENT_KEY_TYPE, std::function<void*(void*)>> _eventMap; /**< 监听事件名--方法容器*/
	std::vector<AbstractEvent*> _eventList;/**< 保存事件指针,便于统一释放*/
};
#endif