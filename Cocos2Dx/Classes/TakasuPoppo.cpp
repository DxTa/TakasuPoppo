//  Created by MinhNT on 13/05/16.
//  Copyright FRAMGIA 2013年. All rights reserved.
//

#include "TakasuPoppo.h"
#include "SimpleAudioEngine.h"
#include "TPObjectExtension.h"
#include "TPBlockSet.h"
#include "CCGestureRecognizer.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

#pragma mark Default

CCScene* TakasuPoppo::scene() {
    CCScene *scene = CCScene::create();
    TakasuPoppo *layer = TakasuPoppo::create();
    scene->addChild(layer);
    return scene;
}

bool TakasuPoppo::init() {
    srand(time(NULL));
    if (!CCLayer::init()) return false;
    
    colorArray = new CCArray;
    toDestroyArray = new CCArray;
    pickedArray = new CCArray;
    hintArray = new CCArray;
    
    TakasuPoppo::addBlocksToArray();
    TakasuPoppo::addTileMap();
    TakasuPoppo::lookForMatches();
    
    controlable = true;

    //===============================================================
    debugTilesArray = new CCArray;
    TakasuPoppo::setupDebugButton();
    
    sprintf(comboCounterString, "Combo: %i", comboCounter);
    comboCounterLabel = CCLabelTTF::create(comboCounterString, "Arial", 30);
    comboCounterLabel->setZOrder(15);
    comboCounterLabel->setColor(ccc3(225, 225, 225));
    comboCounterLabel->setPosition(ccp(100, 830));
    
    sprintf(comboTimerString, "Combo Timer: %f", comboTimer);
    comboTimerLabel = CCLabelTTF::create(comboTimerString, "Arial", 30);
    comboTimerLabel->setZOrder(15);
    comboTimerLabel->setColor(ccc3(225, 225, 225));
    comboTimerLabel->setPosition(ccp(200, 780));
    
    this->addChild(comboCounterLabel);
    this->addChild(comboTimerLabel);
    //===============================================================
    
    CCSprite *background = CCSprite::create("NewBackground.png");
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background, -3, -1);
    
    TakasuPoppo::swipeSetup();
    
    this->setTouchEnabled(true);
    
    this->scheduleUpdate();
    this->schedule(schedule_selector(TakasuPoppo::fixedUpdate));
    
    return true;
}

void TakasuPoppo::update(float dt) {
    sprintf(comboCounterString, "Combo: %i", comboCounter);
    comboCounterLabel->setString(comboCounterString);
    
    sprintf(comboTimerString, "Combo Timer: %f", comboTimer);
    comboTimerLabel->setString(comboTimerString);
    
    deltaTime = dt;
    
    if (comboTimer > 0) comboTimer -= dt;
    if (comboTimer < 0) {
        comboTimer = 0;
        comboCounter = 0;
    }
    if (comboCounter > 8) comboCounter = 0;
    
    
//    if (hintCounter > 0) {
//        this->unschedule(schedule_selector(TakasuPoppo::hintGeneration));
//        hintCounter -= dt;
//    }
//    if (hintCounter <= 0 && hintDisplaying == false) {
//        hintArray->removeAllObjects();
//        TakasuPoppo::lookForMatches();
//        this->scheduleOnce(schedule_selector(TakasuPoppo::hintGeneration), 0);
//    }
    
    if (controlable) {
        if (swipeRight) {
            CCObject *object = NULL;
            CCARRAY_FOREACH(pickedArray, object) {
                TPObjectExtension *exObject = dynamic_cast<TPObjectExtension*>(object);
                TakasuPoppo::swipedRight(exObject);
                swipeRight = false;
                pickedArray->removeObject(object);
            }
        }
        if (swipeLeft) {
            CCObject *object = NULL;
            CCARRAY_FOREACH(pickedArray, object) {
                TPObjectExtension *exObject = dynamic_cast<TPObjectExtension*>(object);
                TakasuPoppo::swipedLeft(exObject);
                swipeLeft = false;
                pickedArray->removeObject(object);
            }
        }
        if (swipeUp) {
            CCObject *object = NULL;
            CCARRAY_FOREACH(pickedArray, object) {
                TPObjectExtension *exObject = dynamic_cast<TPObjectExtension*>(object);
                TakasuPoppo::swipedUp(exObject);
                swipeUp = false;
                pickedArray->removeObject(object);
            }
            
        }
        if (swipeDown) {
            CCObject *object = NULL;
            CCARRAY_FOREACH(pickedArray, object) {
                TPObjectExtension *exObject = dynamic_cast<TPObjectExtension*>(object);
                TakasuPoppo::swipedDown(exObject);
                swipeDown = false;
                pickedArray->removeObject(object);
            }
        }
    }
}

void TakasuPoppo::fixedUpdate(float time) {
    TakasuPoppo::matchList();
    if (toDestroyArray->count() != 0 && !inTheMove &&
        !inTheFall) {
        this->scheduleOnce(schedule_selector(TakasuPoppo::logicExecution), 0);
        this->unschedule(schedule_selector(TakasuPoppo::fixedUpdate));
    }
}

void TakasuPoppo::fallingBoolSwitch(float dt) {
    inTheFall = true;    
    fallCounter += deltaTime;
    if (fallCounter > 0.1) {
        inTheFall = false;
        this->unschedule(schedule_selector(TakasuPoppo::fallingBoolSwitch));
    }
}

void TakasuPoppo::movingBoolSwitch(float dt) {
    inTheMove = true;
    moveCounter += deltaTime;
    if (moveCounter > 0.1) {
        inTheMove = false;
        this->unschedule(schedule_selector(TakasuPoppo::movingBoolSwitch));
    }
}

void TakasuPoppo::scheduleGenerate() {
    this->schedule(schedule_selector(TakasuPoppo::smartGeneration), 0.3);
}

//void TakasuPoppo::hintGeneration() {
//    if (hintCounter <= 0 && !this->getChildByTag(778)) {
//        hintDisplaying = true;
//        int hintCount = hintArray->count();
//        int hintIndex = hintCount - 1;
//        int hintRandom = rand() %hintIndex;
//        
//        if (hintCount > 0) {
//            CCLog("Hint count: %i Index: %i", hintCount, hintRandom);
//            TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(hintArray->objectAtIndex(0));
//            CCLog("Object on coor X%iY%i ID %i has a chance for combo.", (int)exObj->getCoordination().x, (int)exObj->getCoordination().y, exObj->getID());
//            CCRenderTexture *tex = TakasuPoppo::outlineEffect(exObj->getSprite(), 10, ccc3(255, 255, 255), 90);
//            this->addChild(tex, exObj->getSprite()->getZOrder() - 1, 778);
//            this->unschedule(schedule_selector(TakasuPoppo::hintGeneration));
//        }
//    }
//}

void TakasuPoppo::logicExecution() {
    this->unschedule(schedule_selector(TakasuPoppo::smartGeneration));
    this->runAction(CCSequence::create(CCDelayTime::create(0.1),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::cleanBlocks)),
                                       CCDelayTime::create(0.3),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::afterClean)),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::scheduleGenerate)),
                                       NULL));
    this->schedule(schedule_selector(TakasuPoppo::fallingBoolSwitch), 0.1);
    this->schedule(schedule_selector(TakasuPoppo::fixedUpdate), 0.4);
}

