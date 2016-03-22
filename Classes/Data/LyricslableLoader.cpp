#include "Data/LyricslableLoader.h"
#include <regex>
#include "cocos2d.h"

USING_NS_CC;

void LyricslableLoader::initInterface()
{
	auto txt_vec = FileUtils::getInstance()->getValueVectorFromFile("Song/wenchengLyrics.dat");
	for (const auto& e : txt_vec)
	{
		auto txt_map = e.asValueMap();//将键值转化成Map格式，放入txt_map中  
		auto lyricsEntity = new LyricsEntityStruct();
		lyricsEntity->lyricsStratTime = txt_map.at("time").asInt();
		lyricsEntity->displaySpeed = txt_map.at("speed").asFloat();
	  	lyricsEntity->lyricsContent = txt_map.at("contant").asString();
		LyricsEntityVector.push_back(lyricsEntity);
	}
    //重计算时间轴
    for (auto &lyricsEntity : LyricsEntityVector)
    {
        lyricsEntity->lyricsStratTime = lyricsEntity->lyricsStratTime / 60 * 50;
    }
}

LyricslableLoader::~LyricslableLoader()
{
    for (auto &leStruct : LyricsEntityVector)
    {
        CC_SAFE_DELETE(leStruct);
    }
    LyricsEntityVector.clear();
}
