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

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include <vector>
#include <string>
#include "cocos2d.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::extension;
using namespace std;

enum GameState
{
    GAME_RESET,
    GAME_START,
    GAME_UPDATE,
    GAME_OVER,
};

typedef struct ItemsStruct
{
    ItemsStruct(): numEnd(-1), isHighLight(false)
    {
        
    }
    Point p;
    int numStart;
    int numEnd;
    int numTime;
    int idx;
    bool isRun;
    bool isHighLight;
} ItemsStruct;


class GameScene : public cocos2d::Scene
{
    Node* mainLayer;
    int spinSpeed;
    int spinWheel1Counter;
    ItemsStruct struct1;
    ItemsStruct struct2;
    ItemsStruct struct3;
    bool isRun;
    int spinCounter;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(GameScene);
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
};

#endif //
