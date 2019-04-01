#include "BingoScreen.hpp"

BingoScreen::BingoScreen(){
}

BingoScreen::~BingoScreen(){
}

Scene* BingoScreen::createScene()
{
    // create the scene with physics enabled
    auto scene = Scene::createWithPhysics();
    
    // set gravity
    scene->getPhysicsWorld()->setGravity(Vec2(0, -900));
    
    // optional: set debug draw
    // scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
    
    auto layer = BingoScreen::create();
    scene->addChild(layer);
    return scene;
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
    //cocos2d::SpriteFrame *normalSpriteFrame;
    //btnStart->loadTextureNormal(normalSpriteFrame);
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
    auto emitter = ParticleSystemQuad::create("particles/particle_phaohoa_vang.plist");
    emitter->setPosition(0,0);
    //emitter->setAutoRemoveOnFinish(true);
    emitter->setSpeed(100);
    
    auto batch = ParticleBatchNode::createWithTexture(emitter->getTexture());
    
    batch->addChild(emitter);
    batch->setPosition(Vec2(100 , 100));
    batch->setScale(0.5f);
    

    //
    // Creates a 9-slice sprite with an sprite frame name.
//    Scale9Sprite * img = Scale9Sprite::create("images/btn_tuquay.png");
//    img->addChild(batch, 10);
    
    Scale9Sprite * img = Scale9Sprite::create("images/btn_tuquay.png");
    img->addChild(batch, 10);
    
//    Sprite * imghighlight = Sprite::create("images/card_main/homescreen/frame_recent.png");
//    img->addChild(imghighlight, 10);
//    auto stencil = Scale9Sprite::create("images/btn_tuquay.png");
//    ClippingNode *clipping = ClippingNode::create();
//    clipping->setAlphaThreshold(0.1f);
//    clipping->setContentSize(stencil->getContentSize());
//    clipping->addChild(imghighlight);
//    clipping->setPosition(100,100);
//    clipping->setStencil(stencil);
//    auto moveLeft = MoveBy::create(0.5f,Vec2(+250, 0));
//    auto moveRight = MoveBy::create(0.0f,Vec2(-250, 0));
//    auto seq1 = Sequence::create(moveLeft, DelayTime::create(2.0f), moveRight,nullptr);
//    imghighlight->runAction(RepeatForever::create(seq1));
//    //img->setContentSize(Size(70,150));
//    Label * label = Label::createWithTTF("Demo", "fonts/Marker Felt.ttf", 24);
//    ControlButton * startBtn = ControlButton::create(label,img);
//    //startBtn->setContentSize(Size(70,150));
//    startBtn->setAdjustBackgroundImage(false);
//    startBtn->setPosition(Vec2(200,200));
//    startBtn->setPreferredSize(Size(200,200));
//    startBtn->addChild(clipping,1);
//    //startBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MyClass::touch), CCControlEventTouchDownInside);
//    mainLayer->addChild(startBtn,100);
    
 
    auto hero = mainLayer->getChildByName<Sprite*>("MainCharacter");
    //hero->setPosition(_positionX, _positionY);
    
    auto bodyBall= PhysicsBody::createCircle(hero->getBoundingBox().size.height);      // 1
    bodyBall->getShape(0)->setRestitution(1.0f);
    bodyBall->getShape(0)->setFriction(0.0f);
    bodyBall->getShape(0)->setDensity(1.0f);
    bodyBall->setGravityEnable(true);                       // 2
    bodyBall->setDynamic(false);                            // 3
    hero->setPhysicsBody(bodyBall);
    //bodyBall->setContactTestBitmask(0x000001);
    hero->setTag(1);
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
