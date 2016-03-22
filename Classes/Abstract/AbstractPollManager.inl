#ifndef REIMU_ABSTRACT_ABSTRACTEVENTPOLLMANAGER_H
#define REIMU_ABSTRACT_ABSTRACTEVENTPOLLMANAGER_H
#include "Abstract/AbstractPollEntity.h"
#include <vector>
#include "cocos2d.h"

template<class T> class AbstractPollManager
{
public:
    /**析构函数
      @warning 需要delete对象才会执行
      */
    virtual ~AbstractPollManager()
    {  
        _vect.clear();
		_entityMap.clear(); /**< 轮询对象容器中的指针由destory()函数负责释放*/
    };

    /**注册轮询对象
    @param _system 轮询对象
    */
    inline virtual void registe(T *const _system)//注册Sysyem
    {
        _vect.push_back(_system);
    };

    /**注册轮询对象
    @param _system 轮询对象
    @param entityName 对象标识
    */
    inline virtual void registe(T *const _system, const std::string & entityName)//注册Sysyem
    {
        registe(_system);
        if (entityName == "") return;
        CCASSERT(_entityMap.find(entityName) == _entityMap.end(), "the entity map had one which could be repeat.");
        _entityMap.insert(std::pair<std::string, T*>(entityName, _system));
    };

    /**注册指针对象
    */
    inline virtual void registePoint(const std::string & pointName, void *_point)
    {
        if (pointName == "") return;
        CCASSERT(_pointMap.find(pointName) == _pointMap.end(), "the point map had one which could be repeat.");
        _pointMap.insert(std::pair<std::string, void*>(pointName, _point));
    };

    /**获取指针对象
    */
    inline virtual void* getPoint(const std::string & pointName)
    {
        auto 	iter = _pointMap.find(pointName);
        if (iter != _pointMap.end())
        {
            return iter->second;
        }
        else
        {
            CCASSERT(1 == 0, "the point map hasn't  one.");
            return nullptr;
        }
    };


    /**销毁实例*/
    virtual inline void destory()
    {
        for (auto &system : _vect)
        {
            if (!dynamic_cast<cocos2d::Layer*>(system)) CC_SAFE_DELETE(system); /**< Layer层的资源由cocos2dx释放*/
        }
        _vect.clear();
        _entityMap.clear();
    };

    /**获取轮询对象
    @param entityName 对象标识
    */
    virtual  inline T* getEntity(const std::string & entityName) const
    {
        auto& iter = _entityMap.find(entityName);
        if (iter != _entityMap.end())
        {
            return iter->second;
        }
        else
        {
            CCASSERT(1 == 0, "the entity map hasn't  one.");
            return nullptr;
        }
    };

    /**执行方法*/
    virtual  inline void  run() 
    {
        for (const auto &system : _vect)
        {
            system->runInterface();
        }
    }

    /**初始化方法*/
    virtual void  init() const
    {
        for (const auto &system : _vect)
        {
            system->initInterface();
        }
    }

protected:
    std::vector<T*> _vect; /**轮询对象容器Vector(用于高效率执行)*/
    std::map<std::string, T*> _entityMap; /**轮询对象容器Map(用于根据标识获取对象)*/
    std::map<std::string, void*> _pointMap;//指针map
};
#endif