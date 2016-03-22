#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"  
#include <regex>
#include "iostream"
#include <vector>
#include "data/BackGroundLayer.h"
#include "tools/AESTool.h"
#include "Data/BackGroundLayer.h"
#include "System/JudgeSystem.h"



USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainScene::scene = nullptr;
DataEntityPool* MainScene::_dataManage = nullptr;
SystemEntityPool* MainScene::_systemManage=nullptr;


Scene* MainScene::GetSceneInstance()
{
    // 'scene' is an autorelease object
    if (scene) return scene;
    else
    {
        scene = MainScene::create();
        // 'layer' is an autorelease object
    
        scene->retain();
        // add layer as a child to scene
        return scene;
    }

}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    scene = this;

    FileUtils::getInstance()->addSearchPath("res");

    //设置主要每帧定时器
    this->schedule(CC_SCHEDULE_SELECTOR(MainScene::Run_PerFrame));

    /** char test[] = "testqqqqqqqqqqqjbhhgdfgdgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg";
     char test2[8192];
     aes_context aes_ctx;
     unsigned char IV[16];
     unsigned char key[32];
     memset(IV, 0, sizeof(IV));
     memset(key, 0, sizeof(key));
     char password[32] = "123456";
     memcpy(key, password, strlen(password));
     aes_setkey_enc(&aes_ctx, key, 256);
     CCLOG("lenth %d", strlen(test));
     aes_crypt_cbc(&aes_ctx, AES_ENCRYPT, strlen(test)*sizeof(char), IV, (unsigned char*)test, (unsigned char*)test2);
     unsigned char IV2[16];
     memset(IV2, 0, sizeof(IV2));
     aes_setkey_dec(&aes_ctx, key, 256);
     char test3[8192];
     aes_crypt_cbc(&aes_ctx, AES_DECRYPT, strlen(test2)*sizeof(char), IV2, (unsigned char*)test2, (unsigned char*)test3);
     CCLOG("buffer dec:%s", test3);*/

    //AESTool *aestoll = new AESTool();
    //char test[] = "1234537890123451234537890123459";
    //char password[32] = "HJSDASDNMSANDASJHDJAGHDF";
    //unsigned  char test3[1];
    //aestoll->encodeString(test, password, test3);
    //// CCLOG("buffer enc:%s", test3);
    //aestoll->decodeString(test3, password);



    //开启命令行调试
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    //注册键盘事件
    auto listener = EventListenerKeyboard::create();
    //listener->onKeyPressed=[](EventKeyboard::KeyCode keycode, cocos2d::Event *event){
    //	printf("输入了%d \n", keycode);
    //};
    listener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



    _dataManage = new DataEntityPool();
    _dataManage->init(SceneType::Main);
    _systemManage = new SystemEntityPool();
    _systemManage->init(SceneType::Main);

    //注册触摸时间
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    auto listen = EventListenerTouchAllAtOnce::create();
    listen->onTouchesBegan = CC_CALLBACK_2(JudgeSystem::OnTouchJudgeMent, static_cast<JudgeSystem*>(_systemManage->getEntity("judgeSystem")));
    eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);
    return true;
}


#pragma  region 按键事件
/**
 处理键盘按下的事件(用lambda表达式会封闭整个类的成员,所以采用CALL_BACK)
 */
void MainScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d pressed", keyCode);
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_PAUSE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_SCROLL_LOCK:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_PRINT:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_SYSREQ:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_BREAK:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_TAB:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_BACK_TAB:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RETURN:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPS_LOCK:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_SHIFT:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CTRL:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_CTRL:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_ALT:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ALT:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_MENU:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_HYPER:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_INSERT:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_HOME:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_PG_UP:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DELETE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_END:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_PG_DOWN:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_NUM_LOCK:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_PLUS:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_MINUS:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_MULTIPLY:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_DIVIDE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_ENTER:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_HOME:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_UP:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_PG_UP:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_LEFT:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_FIVE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_RIGHT:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_END:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_DOWN:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_PG_DOWN:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_INSERT:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_KP_DELETE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F1: /**< F1==自动演奏 */
        (static_cast<JudgeSystem*>(_systemManage->getEntity("judgeSystem")))->setGameMode(); 
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F2:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F3:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F4:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F5:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F6:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F7:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F8:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F9:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F10:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F11:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F12:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_EXCLAM:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_QUOTE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_NUMBER:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DOLLAR:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_PERCENT:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CIRCUMFLEX:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_AMPERSAND:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_APOSTROPHE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_PARENTHESIS:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_PARENTHESIS:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_ASTERISK:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_PLUS:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_COMMA:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_MINUS:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_PERIOD:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_SLASH:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_0:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_1:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_2:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_3:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_4:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_5:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_6:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_7:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_8:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_9:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_COLON:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_SEMICOLON:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_LESS_THAN:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_EQUAL:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_GREATER_THAN:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_QUESTION:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_AT:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_B:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_C:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_D:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_E:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_F:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_G:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_H:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_I:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_J:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_K:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_L:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_M:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_N:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_O:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_P:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Q:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_R:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_T:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_U:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_V:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_X:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Y:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Z:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_BRACKET:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_BACK_SLASH:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_BRACKET:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_UNDERSCORE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_GRAVE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_B:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_C:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_E:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F:
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("musiceffect/dong.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_G:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_H:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_I:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_J:
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("musiceffect/ka.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_K:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_L:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_M:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_N:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_O:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_P:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_Q:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_R:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_S:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_T:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_U:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_V:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_W:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_X:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_Y:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_Z:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_BRACE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_BAR:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_BRACE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_TILDE:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_EURO:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_POUND:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_YEN:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_MIDDLE_DOT:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_SEARCH:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_LEFT:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_UP:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_DOWN:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_CENTER:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_PLAY:
        break;
    default:
        break;
    }
}
#pragma  endregion

/**
背景地图的判定(主要的逻辑判定放入)
*/
void MainScene::Run_PerFrame(float speed)
{
    _systemManage->run();
}






