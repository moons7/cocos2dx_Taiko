#ifndef REIMU_SYSTEM_LYRICSSYSTEM_H
#define REIMU_SYSTEM_LYRICSSYSTEM_H
#include "Data/LyricslableLoader.h"
#include "Data/BackGroundLayer.h"
#include "Abstract/AbstractEventDispatcher.inl"
#include "Scene/MainScene.h"

class LyricsSystem :public AbstractPollEntity
{
public:

    /**播放BGM
    @param fileName  文件名
    */
    void playBGM(const std::string & fileName);

    unsigned int _playTime = 0;/**< 已播放时间*/

protected:
	virtual void runInterface() override final;
    virtual void initInterface() override final;

private:
    LyricslableLoader *_lyricsEntity = static_cast<LyricslableLoader*>(MainScene::GetDataManage()->getEntity("lyricslable"));/**歌词数据实体*/
    BackGroundLayer* _nodeEntity = static_cast<BackGroundLayer*>(MainScene::GetDataManage()->getEntity("BackGroundLayer"));/**界面数据实体*/
    bool _isPlay = false;/**< 播放标识*/
    unsigned int _playNum = 0;/**< 播放序号*/
    unsigned short _playSN = 0;/**< 已使用显示结点的序号(当前总计有5个结点显示歌词)*/
    unsigned short _playBGMDelay = 0;/**< 播放BGM的延迟*/
};
#endif