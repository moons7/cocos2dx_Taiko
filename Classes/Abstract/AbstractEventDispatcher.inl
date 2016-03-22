#ifndef REIMU_ABSTRACT_ABSTRACTEVENTDISPATCHER_H
#define REIMU_ABSTRACT_ABSTRACTEVENTDISPATCHER_H
#include "Abstract/AbstractEventListener.h"
#include <map>
#include <string>



/**< 抽象事件分发类*/ 
class AbstractEventDispatcher
{
public:
    /**析构函数*/
    virtual ~AbstractEventDispatcher(){
		auto& it = m_listeners.begin();
		while (it != m_listeners.end())
		{
			CC_SAFE_DELETE(it->second);
			m_listeners.erase(it++);
		}
		m_listeners.clear();
	};

    /**分发事件
    @param  listenName 监听器名
    @param  eventKey 事件Key索引结构
    @param  paramIn 输入结构指针
    */
	inline void* dispatchEvent(const std::string &listenName, const EVENT_KEY_TYPE & eventKey, void *paramIn) const
    {
        auto& iter = m_listeners.find(listenName);
        if (iter != m_listeners.end())
        {
            auto method = iter->second;
			return method->execEvent(eventKey, paramIn);
        }
		else  return nullptr;
    }

    /**注册监听者
	  @param  listenName 监听者标识
      @param  listener 监听者
      */
	inline void addListener(const std::string &listenName, AbstractEventListener  *listener)
	{
		m_listeners.insert(std::pair<std::string, AbstractEventListener*>(listenName, listener));
	}

    /**移除监听者
    @param  listenName 监听者标识
    */
    inline void removeListener(const std::string &listenName)  //删除监听者事件
    {
        m_listeners.erase(listenName);
    }

protected:
	std::map<EVENT_KEY_TYPE, AbstractEventListener*> m_listeners; /**< 监听者Map容器*/
    unsigned int _listenCount = 0; /**< 监听者ID计数*/
};
#endif