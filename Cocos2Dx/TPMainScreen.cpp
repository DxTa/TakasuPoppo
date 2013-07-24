//
//  TPMainScreen.cpp
//  Cocos2Dx
//
//  Created by Ace on 2013/07/23.
//
//

#include "TPMainScreen.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene *TPMainScreen::scene() {
    cocos2d::CCScene *scene = CCScene::create();
    TPMainScreen *layer = TPMainScreen::create();
    scene->addChild(layer);
    return scene;
}

bool TPMainScreen::init() {
    if (!CCLayer::init()) return false;
    
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    return true;
}

void TPMainScreen::update(float dt) {
    
}

bool TPMainScreen::ccTouchBegan(CCTouch *touch, CCEvent *event) {
    return true;
}

void TPMainScreen::ccTouchEnded(CCTouch *touch, CCEvent *event) {

}



void TPMainScreen::menuCloseCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}