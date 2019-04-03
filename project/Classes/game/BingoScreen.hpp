
#pragma one

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameAbstract.h"
using namespace cocos2d;
using namespace std;
USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::extension;
using namespace std;
enum class PhysicsCategory {
    None = 0,
    Monster = (1 << 0),    // 1
    Projectile = (1 << 1), // 2
    All = PhysicsCategory::Monster | PhysicsCategory::Projectile // 3
};
class BingoScreen: public GameAbstract {
    //std::string sprites[] = { "banana.png", "cherries.png", "crate.png", "orange.png" };
    Sprite* _hero;
public:
    bool init();
    BingoScreen();
    virtual void resetGame() override;
    virtual void startGame() override;
    virtual void stopGame() override;
    virtual void updateGame(float dt) override;
    static cocos2d::Scene* createScene();
    virtual ~BingoScreen();
    CREATE_FUNC(BingoScreen);
    void addMonster(float dt);
    bool onTouchBegan(Touch *touch, Event *unused_event);
    bool onContactBegan(PhysicsContact &contact);
};

