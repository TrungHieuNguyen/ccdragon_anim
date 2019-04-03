#include "BingoScreen.hpp"

BingoScreen::BingoScreen(){
}

BingoScreen::~BingoScreen(){
}

Scene* BingoScreen::createScene()
{

    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = BingoScreen::create();
    scene->addChild(layer);
    return scene;
}
bool BingoScreen::init()
{
    if (!Scene::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto background = DrawNode::create();
    background->drawSolidRect(origin, visibleSize, Color4F(0.6,0.6,0.6,1.0));
    this->addChild(background);
    
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
    
 
     _hero = mainLayer->getChildByName<Sprite*>("MainCharacter");
    //_hero->setPosition(_positionX, _positionY);
    
    auto bodyBall= PhysicsBody::createCircle(_hero->getBoundingBox().size.height);      // 1
    bodyBall->getShape(0)->setRestitution(1.0f);
    bodyBall->getShape(0)->setFriction(0.0f);
    bodyBall->getShape(0)->setDensity(1.0f);
    bodyBall->setGravityEnable(true);                       // 2
    bodyBall->setDynamic(false);                            // 3
    //hero->setPhysicsBody(bodyBall);
    //bodyBall->setContactTestBitmask(0x000001);
    //hero->setTag(1);
    
    srand((unsigned int)time(nullptr));
    this->schedule(schedule_selector(BingoScreen::addMonster), 1.5);
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(BingoScreen::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, _hero);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(BingoScreen::onContactBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
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
void BingoScreen::addMonster(float dt) {
    auto monster = Sprite::create("monster.png");
    // 1
    auto monsterSize = monster->getContentSize();
    auto physicsBody = PhysicsBody::createBox(Size(monsterSize.width , monsterSize.height),
                                              PhysicsMaterial(0.1f, 1.0f, 0.0f));
    // 2
    physicsBody->setDynamic(true);
    // 3
    physicsBody->setCategoryBitmask((int)PhysicsCategory::Monster);
    physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
    physicsBody->setContactTestBitmask((int)PhysicsCategory::Projectile);
    
    monster->setPhysicsBody(physicsBody);
    // 1
    auto monsterContentSize = monster->getContentSize();
    auto selfContentSize = this->getContentSize();
    int minY = monsterContentSize.height/2;
    int maxY = selfContentSize.height - monsterContentSize.height/2;
    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY;
    
    monster->setPosition(Vec2(selfContentSize.width + monsterContentSize.width/2, randomY));
    this->addChild(monster);
    
    // 2
    int minDuration = 2.0;
    int maxDuration = 4.0;
    int rangeDuration = maxDuration - minDuration;
    int randomDuration = (rand() % rangeDuration) + minDuration;
    
    // 3
    auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width/2, randomY));
    auto actionRemove = RemoveSelf::create();
    monster->runAction(Sequence::create(actionMove,actionRemove, nullptr));
}

bool BingoScreen::onTouchBegan(Touch *touch, Event *unused_event) {
    // 1  - Just an example for how to get the  _player object
    //auto node = unused_event->getCurrentTarget();
    Vec2 touchLocation = touch->getLocation();
    Vec2 offset = touchLocation - _hero->getPosition();
    
    if (offset.x < 0) {
        return true;
    }
    
    auto projectile = Sprite::create("projectile.png");
    auto projectileSize = projectile->getContentSize();
    auto physicsBody = PhysicsBody::createCircle(projectileSize.width/2 );
    physicsBody->setDynamic(true);
    physicsBody->setCategoryBitmask((int)PhysicsCategory::Projectile);
    physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
    physicsBody->setContactTestBitmask((int)PhysicsCategory::Monster);
    projectile->setPhysicsBody(physicsBody);
    projectile->setPosition(_hero->getPosition());
    this->addChild(projectile);
    
    offset.normalize();
    auto shootAmount = offset * 1000;

    auto realDest = shootAmount + projectile->getPosition();
    
    auto actionMove = MoveTo::create(2.0f, realDest);
    auto actionRemove = RemoveSelf::create();
    projectile->runAction(Sequence::create(actionMove,actionRemove, nullptr));
    
    return true;
}
bool BingoScreen::onContactBegan(PhysicsContact &contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    if(nodeA)
        nodeA->removeFromParent();
    
    if(nodeB)
        nodeB->removeFromParent();
    return true;
}
