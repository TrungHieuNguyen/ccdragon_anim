#include "AppDelegate.h"

#include "demo/HelloDragonBones.h"
#include "demo/AnimationBase.h"
#include "demo/DragonBonesEvent.h"
#include "demo/AnimationLayer.h"
#include "demo/BoneOffset.h"
#include "demo/InverseKinematics.h"
#include "demo/BoundingBox.h"
#include "demo/ReplaceSlotDisplay.h"
#include "demo/ReplaceSkin.h"
#include "demo/ReplaceAnimation.h"
#include "demo/CoreElement.h"
#include "demo/PerformanceTest.h"
#include "game/GameScrollingScreen.h"
#include "game/GameScene.h"
#include "game/BingoScreen.hpp"
// #include "DragonBonesTest.h"

USING_NS_CC;
static cocos2d::Size designResolutionSize = cocos2d::Size(480, 800);
AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Game2D", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Game2D");
#endif
        director->setOpenGLView(glview);
    }

    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60.f);
    FileUtils::getInstance()->addSearchPath("assets");
    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    auto scene = BingoScreen::createScene();
    // auto scene = AnimationBase::createScene();
    // auto scene = DragonBonesEvent::createScene();
    // auto scene = AnimationLayer::createScene();
    // auto scene = BoneOffset::createScene();
    // auto scene = InverseKinematics::createScene();
    // auto scene = BoundingBox::createScene();
    // auto scene = ReplaceSlotDisplay::createScene();
    // auto scene = ReplaceSkin::createScene();
    // auto scene = ReplaceAnimation::createScene();
    // auto scene = CoreElementGame::createScene();
    // auto scene = PerformanceTest::createScene();
    // auto scene = DragonBonesTest::createScene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
