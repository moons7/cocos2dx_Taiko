#ifndef _REIMU_DATA_DATAMANAGE_H
#define _REIMU_DATA_DATAMANAGE_H

#include "vector"
#include "GameDefine.h"
#include "Abstract/AbstractPollManager.inl"
#include "GameConst.h"


/**数据管理类*/
class DataEntityPool :public AbstractPollManager<AbstractPollEntity>
{
 
public:
    /**析构函数*/
    virtual ~DataEntityPool(){};

    /**初始化函数*/
    void  init(const SceneType &);

};
#endif 