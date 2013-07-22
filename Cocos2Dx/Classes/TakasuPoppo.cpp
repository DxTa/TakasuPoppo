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
    
    //========================= Debugs =============================
    debugTilesArray = new CCArray;
    TakasuPoppo::setupDebugButton();
    
    sprintf(comboCounterString, "Combo: %i", comboCounter);
    comboCounterLabel = CCLabelTTF::create(comboCounterString, "Arial", FONT_SIZE);
    comboCounterLabel->setZOrder(15);
    comboCounterLabel->setColor(ccc3(225, 225, 225));
    comboCounterLabel->setPosition(ccp(100, 830));
    
    sprintf(comboTimerString, "Combo Timer: %f", comboTimer);
    comboTimerLabel = CCLabelTTF::create(comboTimerString, "Arial", FONT_SIZE);
    comboTimerLabel->setZOrder(15);
    comboTimerLabel->setColor(ccc3(225, 225, 225));
    comboTimerLabel->setPosition(ccp(200, 780));
    
    this->addChild(comboCounterLabel);
    this->addChild(comboTimerLabel);
    //===============================================================
    
    //======================== Interface ============================
    CCSprite *background = CCSprite::create("NewPrettyBackground.png");
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background, -3, -1);
    
    CCSprite *ideGauge = CCSprite::create("IdeGauge.png");
    ideGauge->setPosition(ccp(210, 780));
    this->addChild(ideGauge, -1, -2);
    
    CCSprite *comboGauge = CCSprite::create("ComboGauge.png");
    comboGauge->setPosition(ccp(400, 780));
    this->addChild(comboGauge, -2, -3);
    
    //===============================================================
    
    TakasuPoppo::swipeSetup();
    
    this->setTouchEnabled(true);
    
    this->scheduleUpdate();
    this->schedule(schedule_selector(TakasuPoppo::fixedUpdate));
    
    return true;
}

void TakasuPoppo::update(float dt) {
    
    
    deltaTime = dt;
    
    //================== Combo related updates ======================
    sprintf(comboCounterString, "Combo: %i", comboCounter);
    comboCounterLabel->setString(comboCounterString);
    
    sprintf(comboTimerString, "Combo Timer: %f", comboTimer);
    comboTimerLabel->setString(comboTimerString);
    
    
    if (comboTimer > 0) {
        comboTimer -= dt;
    }
    if (comboTimer < 0) {
        comboTimer = 0;
        comboCounter = 0;
        
        //Reset bools here
        existHyperBlockA = false;
        existHyperBlockB = false;
        existHyperBlockC = false;
    }
    if (comboCounter > COMBO_MAXCOUNT) {
        comboCounter = 0;
        
        //Reset here too
        // het 1 luot combo lai reset lai existHyperBlockA
        existHyperBlockA = false;
        existHyperBlockB = false;
        existHyperBlockC = false;
    }
    
    //===============================================================
    
    
    //=================== Hint related updates ======================
    if (hintCounter > 0) {
        hintCounter -= dt;
    }
    if (hintCounter <= 0 && hintDisplaying == false) {
        hintDisplaying = true;
        hintArray->removeAllObjects();
        TakasuPoppo::lookForMatches();
        this->scheduleOnce(schedule_selector(TakasuPoppo::hintGeneration), 0);
    }
    //================================================================
    
    
    
    //=================== Swipe related updates ======================
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
    //================================================================
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
    if (fallCounter > FALL_TIME) {
        inTheFall = false;
        this->unschedule(schedule_selector(TakasuPoppo::fallingBoolSwitch));
    }
}

void TakasuPoppo::movingBoolSwitch(float dt) {
    inTheMove = true;
    moveCounter += deltaTime;
    if (moveCounter > MOVE_TIME) {
        inTheMove = false;
        this->unschedule(schedule_selector(TakasuPoppo::movingBoolSwitch));
    }
}

void TakasuPoppo::scheduleGenerate() {
    this->schedule(schedule_selector(TakasuPoppo::smartGeneration), GENERATION_DELAY);
}

void TakasuPoppo::hintGeneration() {
    int hintCount = hintArray->count();
    if (hintCount > 0) {
        TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(hintArray->objectAtIndex(0));
        
        CCRenderTexture *tex = TakasuPoppo::outlineEffect(exObj->getSprite(), 10, ccc3(255, 255, 255), 90);
        this->addChild(tex, exObj->getSprite()->getZOrder() - 1, 778);
    }
}

void TakasuPoppo::logicExecution() {
    this->unschedule(schedule_selector(TakasuPoppo::smartGeneration));
    this->runAction(CCSequence::create(
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::cleanBlocks)),
                                       CCDelayTime::create(CLEAN_DELAY),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::afterClean)),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::scheduleGenerate)),
                                       NULL));
    this->schedule(schedule_selector(TakasuPoppo::fallingBoolSwitch), FALL_TIME);
    this->schedule(schedule_selector(TakasuPoppo::fixedUpdate), LOGIC_DELAY);
}

