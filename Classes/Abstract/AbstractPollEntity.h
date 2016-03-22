#ifndef REIMU_ABSTRACT_ABSTRACTEVENTPOLLENTITY_H
#define REIMU_ABSTRACT_ABSTRACTEVENTPOLLENTITY_H
#include "Abstract/AbstractPollEntity.h"

class AbstractPollEntity
{
public:
    /**析构函数*/
    virtual ~AbstractPollEntity(){};

    /**运行接口*/
    virtual void runInterface() = 0;

    /**初始化接口*/
    virtual void initInterface() = 0;
};
#endif