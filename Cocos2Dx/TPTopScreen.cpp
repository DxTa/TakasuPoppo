//
//  TPTopScreen.cpp
//  Cocos2Dx
//
//  Created by macbook_017 on 8/15/13.
//
//

#include "TPTopScreen.h"
#include "TPMainScreen.h"
#include "TPUser.h"

CCScene* TPTopScreen::scene()
{
    CCScene *scene = CCScene::create();
    TPTopScreen *layer = TPTopScreen::create();
    scene->addChild(layer);
    return scene;
}

bool TPTopScreen::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    _topScreen = CCSprite::create("poppo_start.png");
    _topScreen->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(_topScreen);
    this->setTouchEnabled(true);
    
    return true;
}

void TPTopScreen::ccTouchesBegan(CCSet *pTouches, CCEvent *event)
{    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    if (touch) {
        CCDirector::sharedDirector()->replaceScene(TPMainScreen::scene(false, 0));
        }
}


