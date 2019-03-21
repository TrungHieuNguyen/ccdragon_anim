#include "BingoScreen.hpp"

BingoScreen::BingoScreen(){
}

BingoScreen::~BingoScreen(){
}

Scene* BingoScreen::createScene()
{
    return BingoScreen::create();
}
bool BingoScreen::init()
{
    if (!Scene::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    mainLayer = CSLoader::createNode("ScreenBingo.csb");
    mainLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    mainLayer->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2));
    this->addChild(mainLayer);
    showTopMenu();
    showBotMenu();
    auto btnStart = mainLayer->getChildByName("pnlControler")->getChildByName<Button*>("btnStart");
    btnStart->addClickEventListener([&, this](Ref* sender)
    {
        if(isPlaying)
        {
            isPlaying = false;
            stopGame();
        }
        else
        {
            isPlaying = true;
            startGame();
        }
    });
    auto btnA = mainLayer->getChildByName("pnlControler")->getChildByName<Button*>("btnA");
    btnA->addClickEventListener([&, this](Ref* sender)
    {
                                        
    });
    auto btnB = mainLayer->getChildByName("pnlControler")->getChildByName<Button*>("btnB");
    btnB->addClickEventListener([&, this](Ref* sender)
    {
        
    });
    return true;
}
void BingoScreen::resetGame()
{
    
}
void BingoScreen::startGame()
{
    schedule(schedule_selector(BingoScreen::updateGame),0.1f);
}

void BingoScreen::stopGame()
{
     unschedule(schedule_selector(BingoScreen::updateGame));
}
void BingoScreen::updateGame(float dt)
{
    log("updateGame...");
}
