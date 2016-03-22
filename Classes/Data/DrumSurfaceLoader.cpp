#include "DrumSurfaceLoader.h"
#include <regex>
#include "cocos2d.h"

USING_NS_CC;



unsigned short DrumSurfaceLoader::PerDrumCount = 0;
unsigned short DrumSurfaceLoader::BPM = 0;
int DrumSurfaceLoader::PlayDelay = 0;

void  DrumSurfaceLoader::initInterface()
{
    if (!_isEditMode)
    {
        loadDrumData("Song/wencheng.dat");
    }
    else
    {
        for (int i = 0; i < 30000;++i) /**<动态个毛线！*/
        {
            auto endPosition = new  DrumSufaceStruct();
            endPosition->type = 0;
            DrumSurfaceEntityVector.push_back(endPosition);
        }    
    }
}

std::string DrumSurfaceLoader::findString(const std::string &content, const std::string &_regex)
{
    //使用正则表达式
    std::regex regExpress(_regex);//正则需找主要鼓谱

    // 保存查找的结果     
    std::smatch ms;

    std::string main; /**<  结果转换为String*/

    if (std::regex_search(content, ms, regExpress))
    {
        for (size_t i = 0; i < ms.size(); ++i)
        {
            main = ms.str(i);
        }
    }
    return std::move(main);/**< 使用move语义减少临时对象的析构开销*/
}

DrumSurfaceLoader::~DrumSurfaceLoader()
{
    for (auto &drStruct : DrumSurfaceEntityVector)
    {
        CC_SAFE_DELETE(drStruct);
    }
    DrumSurfaceEntityVector.clear();
}

void DrumSurfaceLoader::loadDrumData(const std::string & filename)
{
    if (_isDirty)
    {
        for (auto &drStruct : DrumSurfaceEntityVector)
        {
            CC_SAFE_DELETE(drStruct);
        }
        DrumSurfaceEntityVector.clear();
    }
#pragma region 读取谱面文件
    std::string fileContent = FileUtils::getInstance()->getStringFromFile(filename);

    std::string main = findString(fileContent, "MAIN:[a-zA-Z0-9\\r\\n]+(?=MAINEND)"); /**<  结果转换为String*/

    CCASSERT(main.size() != 0, "Have no mainString.");

    std::string perLengthString = findString(fileContent, "PERSIZE:[0-9\\s]+(?=END)");

    CCASSERT(perLengthString.size() != 0, "Have no lengthString.");

    perLengthString = perLengthString.substr(perLengthString.find(":") + 1, perLengthString.size() - perLengthString.find(":"));/**< 可以不用管空格了,被自动处理了 */

    std::stringstream ss;
    ss.clear();
    ss.str("");
    ss << perLengthString;
    ss >> DrumSurfaceLoader::PerDrumCount;

    std::string BPMString = findString(fileContent, "BPM:[0-9\\s]+(?=END)"); /**< 该歌的BPM*/

    CCASSERT(BPMString.size() != 0, "Have no lengthString.");

    BPMString = BPMString.substr(BPMString.find(":") + 1, BPMString.size() - BPMString.find(":"));/**< 可以不用管空格了,被自动处理了 */

    ss.clear();
    ss.str("");
    ss << BPMString;
    ss >> DrumSurfaceLoader::BPM;

    CCASSERT(DrumSurfaceLoader::PerDrumCount != 0, "Have no BPM.");

    std::string playDelayString = findString(fileContent, "PlAYDELAY:[0-9\\s]+(?=END)"); /**< 该歌的BPM*/

    CCASSERT(playDelayString.size() != 0, "Have no lengthString.");

    playDelayString = playDelayString.substr(playDelayString.find(":") + 1, playDelayString.size() - playDelayString.find(":"));/**< 可以不用管空格了,被自动处理了 */

    ss.clear();
    ss.str("");
    ss << playDelayString;
    ss >> DrumSurfaceLoader::PlayDelay;

    CCASSERT(DrumSurfaceLoader::PlayDelay != 0, "Have no PlayDelay.");

    //提取谱面数据
    int startPosition = 0;
    int endPosition = 0;

    //读取每行谱面
    std::vector<std::string> dataVector=getLineScript(main,"\r\n");  //谱面数据序列后的vector
	dataVector.erase(dataVector.begin());//删除第一行的标签

    //谱面转换为int数据
    int *data_int = (int*)malloc(sizeof(int)*dataVector.size() * DrumSurfaceLoader::PerDrumCount);
    int positionx = -1;

    for (auto &itor : dataVector)
    {
        for (size_t i = 0; i < itor.size(); ++i)
        {
            ss.clear();
            ss.str("");
            ss << itor.at(i);
            ss >> data_int[++positionx];
        }
    }
#pragma endregion 读取谱面文件
#pragma region 初始游戏谱面
    //初始动画
    for (int i = 0; i < (int)dataVector.size() * DrumSurfaceLoader::PerDrumCount; ++i)
    {
        auto endPosition = new  DrumSufaceStruct();
        endPosition->type = data_int[i]; //判定数据赋值
        DrumSurfaceEntityVector.push_back(endPosition);
    }
    free(data_int);
    dataVector.clear();
#pragma endregion
    _isDirty = true;
}


inline   std::vector<std::string> DrumSurfaceLoader::getLineScript(const std::string& scriptString,const std::string& pattern)
{
	std::string tempReslut;
	std::string::size_type  pos;
	std::vector<std::string> stringVector;
	for (size_t i = 0; i<scriptString.length(); ++i)
	{
		pos = scriptString.find(pattern, i);
		if (pos == std::string::npos) break;
		tempReslut = trim(scriptString.substr(i, pos - i));
		if (tempReslut.size()<=0)  continue;
		stringVector.push_back(tempReslut);
		i = pos + std::string(pattern).size() - 1;
		tempReslut.clear();
	}
	return std::move(stringVector);
};

inline  std::string& DrumSurfaceLoader::trim(std::string& text)
{
	if (!text.empty())
	{
		text.erase(0, text.find_first_not_of(" \n\r\t"));
		text.erase(text.find_last_not_of(" \n\r\t") + 1);
	}
	return text;
};










