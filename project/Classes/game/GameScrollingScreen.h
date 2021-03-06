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

#pragma one
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include <vector>
#include <string>
#include "cocos2d.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::extension;
using namespace std;

class GameScrollingScreen : public cocos2d::Scene
{
    Node* mainLayer;
    int spinSpeed;
    int spinWheel1Counter;
    bool isRun;
    int spinCounter;
    Node* _nodeTrees;
    Node* _nodeBuilding01;
    Node* _nodeBuilding02;
    Node* _nodeBuilding03;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(GameScrollingScreen);
    int tickCounter;
    int stateGame;
    void timeTick(float dt);
    void resetGame();
    void startGame();
    void updateGame();
    void update(float) override;
    void updateGameState(int state);
    void spinColumn(float dt);
    void onStartSlot(float);
    
private:
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
};


