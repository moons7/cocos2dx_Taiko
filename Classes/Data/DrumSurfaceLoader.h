#ifndef   REIMU_DATA_DRUMSURFACELOADER_H
#define  REIMU_DATA_DRUMSURFACELOADER_H

#include "Data/DataEntityPool.h"
#include "Abstract/AbstractPollEntity.h"
#include <regex>


/**
鼓点数据结构体
*/
struct DrumSufaceStruct
{
    short type = 0;/** 0表示空白,1为红鼓,2为蓝鼓 */
};

/**鼓点数据读取类*/
class DrumSurfaceLoader :public AbstractPollEntity
{
public:
    /**获取鼓面数据容器
    @return 鼓点数据容器Vector的引用
    */
    inline  std::vector<DrumSufaceStruct*>* GetSurfaceEntityVector()   { return &DrumSurfaceEntityVector; };
    
    static  unsigned short PerDrumCount;/**< 每条鼓面的鼓数*/
    static  unsigned short BPM;/**< 该歌的BPM*/
    static  int PlayDelay;/**< 该歌的BPM*/

    void  loadDrumData(const std::string & filename);


protected:

    /**析构函数*/
    ~DrumSurfaceLoader();;

protected:
    std::vector<DrumSufaceStruct*> DrumSurfaceEntityVector;/**鼓点数据容器Vector*/
	inline std::vector<std::string> getLineScript(const std::string& scriptString, const std::string& pattern);
	inline std::string& trim(std::string& text);
    virtual void runInterface() override  final {};
    virtual void initInterface() override  final;

    /**@brief 根据正则表达式寻找对应的字符串
       *@param content 被寻找内容
       *@param _regex 正则表达式
       */
    std::string  findString(const std::string  &content, const std::string &_regex);

    bool _isDirty = false; /**< 是否含有脏数据*/
    bool _isEditMode = false; /**< 是否为编辑模式*/

};

#endif