/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameAbstract.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
#define DUR 0.10f
#define SPIN_ROUND 15
#define SLOT_ROW    3
#define SLOT_ITEM_H    120
Scene* GameAbstract::createScene()
{
    return GameAbstract::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameAbstract.cpp\n");
}

bool GameAbstract::init()
{

    if ( !Scene::init() )
    {
        return false;
    }
    isRun = false;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    isPlaying = false;
    return true;
}


void GameAbstract::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
void GameAbstract::timeTick(float dt)
{
    log("GameAbstract::timeTick %d",tickCounter);
    tickCounter++;
    //updateGameState(tickCounter);
   
}
void GameAbstract::resetGame()
{
    tickCounter = 0;
    isPlaying = false;
}
void GameAbstract::startGame()
{
    isPlaying = true;
    schedule(schedule_selector(GameAbstract::timeTick), 1.0f);
}
void GameAbstract::stopGame()
{
    isPlaying = false;
    //unschedule(schedule_selector(GameAbstract::timeTick));
}

//void GameAbstract::updateStat()
//{
//    updateGameState(tickCounter);
//    auto label2 = mainLayer->getChildByName<Label*>("txtState");
//    string msg = StringUtils::format("State:%d",stateGame);
//    label2->setString(msg.c_str());
//    
//    switch (stateGame) {
//        case GAME_RESET:
//            break;
//        case GAME_START:
//            break;
//        case GAME_UPDATE:
//            break;
//        case GAME_OVER:
//            break;
//        default:
//            break;
//    }
//}
void GameAbstract::updateGameState(int tick)
{
    //log("updateGameState::state %d",tick);
    if(tick==0)
    {
        stateGame = GAME_RESET;
    }
    else if(tick==1)
    {
         stateGame = GAME_START;
    }else if(tick==3)
    {
        stateGame = GAME_UPDATE;
    }else if(tick==30)
    {
        stateGame = GAME_OVER;
    }
    else if(tick==34)
    {
        stateGame = GAME_RESET;
        tickCounter=-1;
    }
//    auto label2 = mainLayer->getChildByName<Label*>("txtState");
//    string msg = StringUtils::format("State:%d",stateGame);
//    label2->setString(msg.c_str());
//    
//    auto label3 = mainLayer->getChildByName<Label*>("txtClock");
//    msg = StringUtils::format("Speed:%d",spinSpeed);
//    label3->setString(msg.c_str());

    
}
void GameAbstract::updateGame(float delta)
{
    
}
void GameAbstract::update(float delta)
{
    
}
void GameAbstract::showTopMenu()
{
    if(mainLayer)
        menuTop = mainLayer->getChildByName("pnlInfo");
    if(menuTop)
    {
        auto move = MoveBy::create(0.5f,Vec2(0, 100));
        auto move_back = move->reverse();
//        auto move_ease_inout = EaseBounceInOut::create(move->clone());
//        auto move_ease_inout2 = EaseBounceOut::create(move_back->clone());
//        auto move_ease_inout = EaseIn::create(move->clone(),0.3);
//        auto move_ease_inout2 = EaseIn::create(move_back->clone(),0.3);
//        auto move_ease_inout = EaseOut::create(move->clone(),0.3);
//        auto move_ease_inout2 = EaseOut::create(move_back->clone(),0.3);
        auto move_ease_inout = EaseExponentialOut::create(move->clone());
        auto move_ease_inout2 = EaseExponentialOut::create(move_back->clone());
        menuTop->runAction(move_ease_inout2->clone());
    }
}

void GameAbstract::showBotMenu()
{
    if(mainLayer)
        menuBot= mainLayer->getChildByName("pnlControler");
    if(menuBot)
    {
        auto move = MoveBy::create(0.5f,Vec2(0, +150));
        auto move_back = move->reverse();
        //        auto move_ease_inout = EaseBounceInOut::create(move->clone());
        //        auto move_ease_inout2 = EaseBounceOut::create(move_back->clone());
        //        auto move_ease_inout = EaseIn::create(move->clone(),0.3);
        //        auto move_ease_inout2 = EaseIn::create(move_back->clone(),0.3);
        //        auto move_ease_inout = EaseOut::create(move->clone(),0.3);
        //        auto move_ease_inout2 = EaseOut::create(move_back->clone(),0.3);
        auto move_ease_inout = EaseExponentialOut::create(move->clone());
        auto move_ease_inout2 = EaseExponentialOut::create(move->clone());
        menuBot->runAction(move_ease_inout2->clone());
    }
}
