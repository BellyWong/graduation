#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

#include "HelloWorldScene.h"
#include "AngryBirdScene.h"
#include "AutomobileScene.h"
#include "CutTheRope.h"
#include "PulleyScene.h"
#include "GearScene.h"
#include "OneSidedPlatformScene.h"
#include "BuoyancyScene.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();
	//CCScene* pScene = AngryBirdScene::scene();
	//CCScene* pScene = AutomobileScene::scene();
	//CCScene* pScene = CutTheRopeScene::scene();
	//CCScene* pScene = PulleyScene::scene();
	//CCScene* pScene = GearScene::scene();
	//CCScene* pScene = OneSidedPlatformScene::scene();
	CCScene* pScene = BuoyancyScene::scene();

    // run
    pDirector->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
