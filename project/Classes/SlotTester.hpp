#ifndef SlotTester_hpp
#define SlotTester_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace std;
USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::extension;
using namespace std;
class SlotTester: public Scene {
    int idx;
    Node* mainLayer;
    long spinCounter = 0;
    long hitCounter = 0;
    const long SPIN_NUM =1000;
    long scatCounter = 0;
    std::vector<string> vResultR1;
    std::vector<string> vResultR2;
    std::vector<string> vResultR3;
    std::vector<std::string> vReelItem;
    std::vector<std::string> REEL1 = { "X", "X", "X", "X", "X", "X", "X", "X", "X", "S" };
    std::vector<std::string> REEL2 = { "X", "X", "X", "X", "X", "X", "X", "X", "X", "S" };
    std::vector<std::string> REEL3 = { "S", "X", "X", "X", "X", "X", "X", "X", "X", "S" };
    
    vector<string> REEL_SYMBOLS_01 {"7","8","9","X","J","Q","K","A","W","S"};
    vector<string> REEL_SYMBOLS_02 {"7","8","9","X","J","Q","S","K","A","W"};
    vector<string> REEL_SYMBOLS_03 {"7","8","9","X","J","Q","S","K","A","W"};
    
    vector<string> reelResult[3];
    vector<string> virtualReelResult[3];
    long arrHitCounter[3];
    
public:
    bool init();
    SlotTester();
    static cocos2d::Scene* createScene();
    virtual ~SlotTester();
    CREATE_FUNC(SlotTester);
    int generateNumber(int min,int max);
    void generateResult();
    int hits(string name);
    int checkHit3(string name);
    void start();
    void updateSpin(float dt);
    int hitSymbol(string);
    void spinRamdomReel();
    void spinVirtualReel();
    void testRamdomReel();
    void testVirtualReel();
    void spinVirtualReel(float dt);
    
};
#endif /* SlotTester_hpp */
