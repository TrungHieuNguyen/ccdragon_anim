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

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
#define DUR 0.10f
#define SPIN_ROUND 15
#define SLOT_ROW    3
#define SLOT_ITEM_H    120
Scene* GameScene::createScene()
{
    return GameScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

bool GameScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }
    spinCounter = 0;
    spinSpeed = 30;
    spinWheel1Counter = 0;
    isRun = false;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    mainLayer = CSLoader::createNode("SceneGame.csb");
    mainLayer->setAnchorPoint(Point(0.5f, 0.5f));
    mainLayer->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2));
    Layout* frameSlot = mainLayer->getChildByName<Layout*>("frameSlot");
    frameSlot->setClippingEnabled(true);
    auto btnStart = mainLayer->getChildByName<Button*>("btnStart");
    btnStart->addClickEventListener([&, this](Ref* sender){
        isRun = false;
        Layout* frameSlot = mainLayer->getChildByName<Layout*>("frameSlot");
        frameSlot->removeAllChildrenWithCleanup(true);
        schedule(schedule_selector(GameScene::onStartSlot), DUR);
        
    });
    auto btnUp = mainLayer->getChildByName<Button*>("btnUp");
    btnUp->addClickEventListener([&, this](Ref* sender){
        spinSpeed -= 5;
    });
    auto btnDown = mainLayer->getChildByName<Button*>("btnDown");
    btnDown->addClickEventListener([&, this](Ref* sender){
        spinSpeed += 5;
    });
    this->addChild(mainLayer,101);
    
    auto label = Label::createWithTTF("Demo", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        mainLayer->addChild(label, 1);
    }
    
    auto label2 = Label::createWithTTF("State:", "fonts/Marker Felt.ttf", 16);
    label2->setName("txtState");
    if (label2 == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label2->setPosition(Vec2(origin.x +50,
                                origin.y + visibleSize.height - label->getContentSize().height));
        
        mainLayer->addChild(label2, 1);
    }
    
    auto label3 = Label::createWithTTF("Tick:", "fonts/Marker Felt.ttf", 16);
    label3->setName("txtClock");
    if (label3 == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label3->setPosition(Vec2(origin.x +50,
                                 origin.y + visibleSize.height - 3*label->getContentSize().height));
        
        mainLayer->addChild(label3, 1);
    }

//    auto sprite = Sprite::create("GameScene.png");
//    if (sprite == nullptr)
//    {
//        problemLoading("'GameScene.png'");
//    }
//    else
//    {
//        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//        this->addChild(sprite, 0);
//    }
    
    schedule(schedule_selector(GameScene::timeTick), 1.0f);
    //schedule(schedule_selector(GameScene::spinColumn), 0.01f);
    schedule(schedule_selector(GameScene::onStartSlot), DUR);
    //this->scheduleUpdate();
    return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
void GameScene::timeTick(float dt)
{
    log("GameScene::timeTick %d",tickCounter);
    tickCounter++;
    updateGameState(tickCounter);
   
}
void GameScene::resetGame()
{
    tickCounter = 0;
}
void GameScene::startGame()
{
    
}
void GameScene::updateGame()
{
    updateGameState(tickCounter);
    auto label2 = mainLayer->getChildByName<Label*>("txtState");
    string msg = StringUtils::format("State:%d",stateGame);
    label2->setString(msg.c_str());
    
    switch (stateGame) {
        case GAME_RESET:
            break;
        case GAME_START:
            break;
        case GAME_UPDATE:
            break;
        case GAME_OVER:
            break;
        default:
            break;
    }
}
void GameScene::updateGameState(int tick)
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
    auto label2 = mainLayer->getChildByName<Label*>("txtState");
    string msg = StringUtils::format("State:%d",stateGame);
    label2->setString(msg.c_str());
    
    auto label3 = mainLayer->getChildByName<Label*>("txtClock");
    msg = StringUtils::format("Speed:%d",spinSpeed);
    label3->setString(msg.c_str());

    
}

void GameScene::update(float delta)
{
    
}
void GameScene::spinColumn(float dt)
{
    log("spinColumn");
    Layout* franeSlot = mainLayer->getChildByName<Layout*>("frameSlot");

    for(int i = 0; i < 4; i++)
    {
        
        string name = StringUtils::format("item0%d",i);
        Sprite* item = franeSlot->getChildByName<Sprite*>(name);
        item->setPositionY(item->getPositionY()-spinSpeed);
        int delta = -54 - item->getPositionY();
        if(delta>0)
        {
            item->setPositionY(415 -delta);
            if(i==3)
            {
                spinWheel1Counter ++;
                auto text1 = mainLayer->getChildByName<Text*>("lbRound1");
                string msg = StringUtils::format("%d",spinWheel1Counter);
                text1->setString(msg.c_str());
                
            }
        }
    }
    for(int i = 0; i < 4; i++)
    {

        string name = StringUtils::format("item1%d",i);
        Sprite* item = franeSlot->getChildByName<Sprite*>(name);
        item->setPositionY(item->getPositionY()-spinSpeed);
        int delta = -54 - item->getPositionY();
        if(delta>0)
        {
            item->setPositionY(415 -delta);
            if(i==3)
            {
                spinWheel1Counter ++;
                auto text1 = mainLayer->getChildByName<Text*>("lbRound2");
                string msg = StringUtils::format("%d",spinWheel1Counter);
                text1->setString(msg.c_str());
                
            }
        }
    }
    for(int i = 0; i < 4; i++)
    {
        string name = StringUtils::format("item2%d",i);
        Sprite* item = franeSlot->getChildByName<Sprite*>(name);
        item->setPositionY(item->getPositionY()-spinSpeed);
        int delta = -54 - item->getPositionY();
        if(delta>0)
        {
            item->setPositionY(415 -delta);
            if(i==3)
            {
                spinWheel1Counter ++;
                auto text1 = mainLayer->getChildByName<Text*>("lbRound3");
                string msg = StringUtils::format("%d",spinWheel1Counter);
                text1->setString(msg.c_str());
                
            }
        }
    }
}
void GameScene::onStartSlot(float dt)
{
    spinCounter++;
    if(spinCounter>SPIN_ROUND + SLOT_ROW*3)
    {
        unschedule(schedule_selector(GameScene::onStartSlot));
        spinCounter = 0;
        return;
    }
    Layout* frameSlot = mainLayer->getChildByName<Layout*>("frameSlot");
    for(int i = 0; i < 3; i++)
    {
        string path = StringUtils::format("images/item_0%d.png",cocos2d::random()%5 +1);
        
        int id = (spinCounter-SPIN_ROUND -1)/3;
        if(spinCounter>SPIN_ROUND &&  id == i)
        {
            if(id<=i)
            {
                Sprite * sp = Sprite::create(path);
                sp->setPosition(Vec2(SLOT_ITEM_H/2 + i*SLOT_ITEM_H, SLOT_ITEM_H/2 + 4*SLOT_ITEM_H));
                frameSlot->addChild(sp);
                //int rowY = SPIN_ROUND + SLOT_ROW - spinCounter;
                int rowY =  3 - (spinCounter -SPIN_ROUND -id*3 -1);
                log("id:%d, rowY:%d",id,rowY);
                string name = StringUtils::format("item_%dx%d",id,rowY);
                sp->setName(name);
                MoveBy * moveByUp = MoveBy::create(DUR*(rowY), Vec2(0, -3/2*SLOT_ITEM_H) - Vec2(0,rowY*SLOT_ITEM_H +SLOT_ITEM_H/2));
                //MoveBy * moveByUp2 = MoveBy::create(DUR/3*(3-i), Vec2(0, SLOT_ITEM_H/3));
                //MoveBy * moveByUp = MoveBy::create(DUR*3, Vec2(0, -3/2*SLOT_ITEM_H) - Vec2(0,rowY*SLOT_ITEM_H +SLOT_ITEM_H/4));
                MoveBy * moveByUp2 = MoveBy::create(DUR*2, Vec2(0, SLOT_ITEM_H/2));
                CallFuncN* cal = CallFuncN::create([&, sp](Ref* sender)
                {
                });
                sp->runAction(Sequence::create(moveByUp, moveByUp2, DelayTime::create(0.2f), cal, nullptr));
            }

        }
        else
        {
            if(id<=i)
            {
                Sprite * sp = Sprite::create(path);
                sp->setPosition(Vec2(SLOT_ITEM_H/2 + i*SLOT_ITEM_H, SLOT_ITEM_H/2 + 4*SLOT_ITEM_H));
                frameSlot->addChild(sp);
                MoveBy * moveByUp = MoveBy::create(DUR*3, Vec2(0, -SLOT_ITEM_H*5));
                sp->runAction(Sequence::create(moveByUp, RemoveSelf::create(), nullptr));
            }
        }
        
    }
    
}
