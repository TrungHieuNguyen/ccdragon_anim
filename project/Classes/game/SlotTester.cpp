#include "SlotTester.hpp"



SlotTester::SlotTester(){
}

SlotTester::~SlotTester(){
}

Scene* SlotTester::createScene()
{
    return SlotTester::create();
}
bool SlotTester::init()
{
    if (!Scene::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    mainLayer = CSLoader::createNode("ScreenSlotTester.csb");
    mainLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    mainLayer->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2));
    this->addChild(mainLayer);
    auto btnStart = mainLayer->getChildByName<Button*>("btnStart");
    btnStart->addClickEventListener([&, this](Ref* sender)
    {
        //start();
        //testVirtualReel();
        schedule(schedule_selector(SlotTester::spinVirtualReel), 0.01);
    });
    spinCounter = 0;
    hitCounter = 0;
    //start();
    
//    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo( "dragonbones_export.xml" );
//    cocostudio::Armature *armature = cocostudio::Armature::create( "armature_name" );
    return true;
}

void SlotTester::start()
{
    long hit2Counter = 0;
    long hit3Counter = 0;
    string name = "S";
    long times = 1000;
    spinCounter = 0;
    //schedule(schedule_selector(SlotTester::updateSpin), 0.01);
    for(long  i =0; i< times; i++)
    {
        log("--------[%d]-------",i);
        generateResult();
        int hit = hits(name);
        if(hit > 0)
        {
            log("hit:%d",hit);
            hit3Counter+=hit;
        }
        if(hit == 2)
        {
            hit2Counter++;
        }
        
       
//        if(i>=times-1)
//        {
//            spinCounter = times;
//            unschedule(schedule_selector(SlotTester::updateSpin));
//        }
    }
    
    log("\n hit3s[%s]:%ld hit2s[%s]:%ld",name.c_str(),hit3Counter, name.c_str(), hit2Counter);
    float ratio = (float)hitCounter/spinCounter;
    log("\n Run times:%ld , Win3 : %ld Ratio: %2.6f Win2: %ld Ratio: %2.6f",times,hit3Counter, (float)hit3Counter/times, hit2Counter, (float)hit2Counter/times);
    
    auto label1 = mainLayer->getChildByName<Text*>("txtTimes");
    string msg1 = StringUtils::format("%ld",times);
    label1->setString(msg1.c_str());
    
    auto label2 = mainLayer->getChildByName<Text*>("txtHit3");
    string msg2 = StringUtils::format("%ld",hit3Counter);
    label2->setString(msg2.c_str());
    
    auto label3 = mainLayer->getChildByName<Text*>("txtHit2");
    string msg3 = StringUtils::format("%d",hit2Counter);
    label3->setString(msg3.c_str());
    
    auto txtTimesPrecent = mainLayer->getChildByName<Text*>("txtTimesPrecent");
    txtTimesPrecent->setString(StringUtils::format("%2.3f",times).c_str());
    txtTimesPrecent->setVisible(false);
    
    auto txtHit3Precent = mainLayer->getChildByName<Text*>("txtHit3Precent");
    txtHit3Precent->setString(StringUtils::format("%2.3f",(float)hit3Counter/times).c_str());
    
    auto txtHit2Precent = mainLayer->getChildByName<Text*>("txtHit2Precent");
    txtHit2Precent->setString(StringUtils::format("%2.3f",(float)hit2Counter/times).c_str());
    
}

int SlotTester::generateNumber(int min,int max)
{
    int random = cocos2d::RandomHelper::random_int(min, max);
    //log("random:%d",random);
    return random;
}

void  SlotTester::generateResult()
{
    vResultR1.clear();
    vResultR2.clear();
    vResultR3.clear();
    
    vector<string> reelTemp1 = vReelItem = REEL1;
    vector<string> reelTemp2 = vReelItem = REEL2;
    vector<string> reelTemp3 = vReelItem = REEL3;
    
    for(int i =0; i< 3; i++)
    {
        int random1 = generateNumber(0, reelTemp1.size()-1);
        vResultR1.push_back(reelTemp1.at(random1));
        reelTemp1.erase(reelTemp1.begin()+random1);
        
        int random2 = generateNumber(0, reelTemp2.size()-1);
        vResultR2.push_back(reelTemp2.at(random2));
        reelTemp2.erase(reelTemp2.begin()+random2);
        
        int random3 = generateNumber(0, reelTemp3.size()-1);
        vResultR3.push_back(reelTemp3.at(random3));
        reelTemp3.erase(reelTemp3.begin()+random3);
        
        log("[%s %s %s]",vResultR1.at(i).c_str(),vResultR2.at(i).c_str(),vResultR3.at(i).c_str());
    }
}


int SlotTester::hits(string name)
{
   
    int hit1 = 0;
    int hit2 = 0;
    int hit3 = 0;
    
    for(int i = 0; i< 3 ; i++)
    {
        if(!vResultR1.at(i).compare(name))
        {
             hit1++;
        }
    }
    
    if(hit1>0)
    {
        for(int j = 0; j< 3 ; j++)
        {
            
            if(!vResultR2.at(j).compare(name))
            {
                hit2++;
            }
        }
    }
    
    if(hit2>0)
    {
        for(int k = 0; k< 3 ; k++)
        {
            if(!vResultR3.at(k).compare(name))
            {
                hit3++;
            }
        }
    }
    
    return hit1*hit2*hit3;
}

void SlotTester::updateSpin(float dt)
{
    log("updateSpin:%ld",spinCounter);
    spinCounter++;
    auto txtTimes = mainLayer->getChildByName<Text*>("txtTimes");
    txtTimes->setString(StringUtils::format("%ld",spinCounter).c_str());
}
void SlotTester::spinRamdomReel()
{
    vector<string> reelSymbol[3] = {REEL_SYMBOLS_01,REEL_SYMBOLS_02,REEL_SYMBOLS_03};
    for(int i = 0; i < 3; i++)
    {
        reelResult[i].clear();
    }
    
    for(int i = 0; i < 3; i++)
    {
        for(int j =0; j < 3; j++)
        {
            int rand =  RandomHelper::random_int(0, int(reelSymbol[j].size()-1));
            //int rand =  arc4random()%(reelSymbol[j].size()-1);
            reelResult[j].push_back(reelSymbol[j].at(rand));
            reelSymbol[j].erase(reelSymbol[j].begin()+rand);
            
        }
    }
}
void SlotTester::spinVirtualReel()
{
    vector<string> reelSymbol[3] = {REEL_SYMBOLS_01, REEL_SYMBOLS_01, REEL_SYMBOLS_01};
    for(int i = 0; i < 3; i++)
    {
        virtualReelResult[i].clear();
    }
    for(int i = 0; i < 3 ; i++)
    {
        int size = reelSymbol[i].size()-1;
        //int rand =  RandomHelper::random_int(0, 1000)%size;
        int rand =  RandomHelper::random_int(0, size);
        //int rand =  arc4random()%(size);
        //log("rand=%d",rand);
        for(int j = 0; j < 3; j++)
        {
            string symbol = reelSymbol[i].at((rand+j)%reelSymbol[i].size());
            virtualReelResult[i].push_back(symbol);
        }
    }
    
    string verifyStr = "S";
    for(int i = 0; i < 3; i++)
    {
        log("%s  %s  %s", virtualReelResult[0].at(i).c_str(),virtualReelResult[1].at(i).c_str(),virtualReelResult[2].at(i).c_str());
        
    }
    
    
    
    
}
int SlotTester::hitSymbol(string verifyStr)
{
    
    int counter[3] = {0};
    for(int i = 0; i < 3; i++)
    {
        if(virtualReelResult[0].at(i).compare(verifyStr)==0)
        {
            counter[0]++;
            arrHitCounter[0]++;
        }
        if(virtualReelResult[1].at(i).compare(verifyStr)==0)
        {
            counter[1]++;
            arrHitCounter[1]++;
        }
        if(virtualReelResult[2].at(i).compare(verifyStr)==0)
        {
            counter[2]++;
            arrHitCounter[2]++;
        }
        
        
    }
    return counter[0]*counter[1]*counter[2];
}
void SlotTester::testRamdomReel()
{
    
}
void SlotTester::testVirtualReel()
{
    const long SPIN_NUM =100000;
    long scatCounter = 0;
    for(long i = 0; i < 3; i++)
        arrHitCounter[i]=0;
    
    for(long i = 0; i < SPIN_NUM; i++)
    {
        log("----------------[%ld]",i);
        spinVirtualReel();
        int counter = hitSymbol("S");
        if(counter>0)
        {
            log("Found %ld JACKPOT",counter);
            scatCounter+= counter;
        }
    }
    float rate = (float)scatCounter/SPIN_NUM;
    for(long i = 0; i < 3; i++)
        log("Found %ld SCATTER in Reel[%d]", arrHitCounter[i],i );
    log("Found %ld JACKPOT Rate:%2.6f",scatCounter,rate );
}
 void SlotTester::spinVirtualReel(float dt)
{
    spinCounter++;
    if(spinCounter > SPIN_NUM)
    {
        unschedule(schedule_selector(SlotTester::spinVirtualReel));
        float rate = (float)scatCounter/SPIN_NUM;
        for(long i = 0; i < 3; i++)
            log("Found %ld SCATTER in Reel[%d]", arrHitCounter[i],i );
        log("Found %ld JACKPOT Rate:%2.6f",scatCounter,rate );
        spinCounter = 0;
        scatCounter = 0;
    }
    else
    {
        log("----------------[%ld]",spinCounter);
        spinVirtualReel();
        int counter = hitSymbol("S");
        if(counter>0)
        {
            log("Found %ld JACKPOT",counter);
            scatCounter+= counter;
        }
        
        auto label1 = mainLayer->getChildByName<Text*>("txtTimes");
        string msg1 = StringUtils::format("%ld",spinCounter);
        label1->setString(msg1.c_str());
        
        auto label2 = mainLayer->getChildByName<Text*>("txtHit3");
        string msg2 = StringUtils::format("%ld",scatCounter);
        label2->setString(msg2.c_str());
        
//        auto label3 = mainLayer->getChildByName<Text*>("txtHit2");
//        string msg3 = StringUtils::format("%d",hit2Counter);
//        label3->setString(msg3.c_str());
        
//        auto txtTimesPrecent = mainLayer->getChildByName<Text*>("txtTimesPrecent");
//        txtTimesPrecent->setString(StringUtils::format("%2.3f",times).c_str());
//        txtTimesPrecent->setVisible(false);
        
        auto txtHit3Precent = mainLayer->getChildByName<Text*>("txtHit3Precent");
        txtHit3Precent->setString(StringUtils::format("%2.3f",(float)scatCounter/spinCounter).c_str());
        
//        auto txtHit2Precent = mainLayer->getChildByName<Text*>("txtHit2Precent");
//        txtHit2Precent->setString(StringUtils::format("%2.3f",(float)hit2Counter/times).c_str());
        
    }
}
