#ifndef   REIMU_DATA_LYRICSLABLELOADER_H
#define  REIMU_DATA_LYRICSLABLELOADER_H
#include "Data/DataEntityPool.h"
#include "Abstract/AbstractPollEntity.h"


/**歌词数据结构体*/
struct LyricsEntityStruct
{
    unsigned int lyricsStratTime; /**歌词开始时间(以帧数统计)*/
    float displaySpeed;/**歌词显示时间*/
    std::string lyricsContent;/**歌词内容*/
};


/**歌词数据读取类*/
class LyricslableLoader : public AbstractPollEntity
{
public:
    /**析构函数*/
    ~LyricslableLoader();

    /**获取歌词数据
    @return 歌词数据容器Vector
    */
    inline  std::vector<LyricsEntityStruct*>* GetLyricsEntityVector()  { return &LyricsEntityVector; };

protected:
    virtual void runInterface() override  final {};
    virtual void initInterface() override  final;
    std::vector<LyricsEntityStruct*>LyricsEntityVector;/**歌词数据集合*/
};
#endif