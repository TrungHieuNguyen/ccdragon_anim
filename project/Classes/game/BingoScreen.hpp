
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
class BingoScreen: public GameAbstract {
    //std::string sprites[] = { "banana.png", "cherries.png", "crate.png", "orange.png" };
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
};

