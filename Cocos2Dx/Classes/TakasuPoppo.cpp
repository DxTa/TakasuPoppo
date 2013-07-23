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
    comboCounterLabel->setPosition(ccp(80, 850));
    
    sprintf(comboTimerString, "Timer: %f", comboTimer);
    comboTimerLabel = CCLabelTTF::create(comboTimerString, "Arial", FONT_SIZE);
    comboTimerLabel->setZOrder(15);
    comboTimerLabel->setColor(ccc3(225, 225, 225));
    comboTimerLabel->setPosition(ccp(330, 850));
    
    this->addChild(comboCounterLabel);
    this->addChild(comboTimerLabel);
    //===============================================================
    
    //======================== Interface ============================
    CCSprite *background = CCSprite::create("NewPrettyBackground.png");
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background, -3, -1);
    
    CCSprite *ideGauge = CCSprite::create("IdeGauge.png");
    ideGauge->setPosition(ccp(210, 780));
    this->addChild(ideGauge, 6, -2);
    
    CCSprite *comboGauge = CCSprite::create("ComboGauge.png");
    comboGauge->setPosition(ccp(400, 780));
    this->addChild(comboGauge, -2, -3);
    
    //===============================================================
    
    
    this->scheduleUpdate();
    
//    this->schedule(schedule_selector(TakasuPoppo::startGame));
    
    this->setTouchEnabled(true);
    
    this->schedule(schedule_selector(TakasuPoppo::fixedUpdate));
    
    this->scheduleOnce(schedule_selector(TakasuPoppo::timeSetup), 0);
    this->schedule(schedule_selector(TakasuPoppo::timeCounter));
    
    return true;
}

void TakasuPoppo::startGame() {
    hintCounter = 5;
    
    CCLOG("Timer %f", executionTime);
    executionTime -= deltaTime;
    
    CCSprite *counter3 = CCSprite::create("Counter3.png");
    CCSprite *counter2 = CCSprite::create("Counter2.png");
    CCSprite *counter1 = CCSprite::create("Counter1.png");
    
    counter3->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    counter2->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    counter1->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    
    counter3->setTag(403);
    counter2->setTag(402);
    counter1->setTag(401);
    
    if (executionTime < 3) {
        if (!counterExist3) this->addChild(counter3, 5);
        counterExist3 = true;
    }
    if (executionTime < 2) {
        if (counterExist3) this->removeChildByTag(403, true);
        counterExist3 = false;
        
        if (!counterExist2) this->addChild(counter2, 5);
        counterExist2 = true;
    }
    if (executionTime < 1) {
        if (counterExist2) this->removeChildByTag(402, true);
        counterExist2 = false;
        
        if (!counterExist1) this->addChild(counter1, 5);
        counterExist1 = true;
    }
    if (executionTime <= 0) { 
        if (counterExist1) this->removeChildByTag(401, true);
        counterExist1 = false;
    
        TakasuPoppo::swipeSetup();
        
        this->setTouchEnabled(true);
        
        this->schedule(schedule_selector(TakasuPoppo::fixedUpdate));
        
        this->scheduleOnce(schedule_selector(TakasuPoppo::timeSetup), 0);
        this->schedule(schedule_selector(TakasuPoppo::timeCounter));
        
        this->unschedule(schedule_selector(TakasuPoppo::startGame));
    }
}

void TakasuPoppo::update(float dt) {
    deltaTime = dt;
    
    //================== Combo related updates ======================
    sprintf(comboCounterString, "Combo: %i", comboCounter);
    comboCounterLabel->setString(comboCounterString);
    
    sprintf(comboTimerString, "Timer: %f", comboTimer);
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
    if (toDestroyArray->count() > 0 && !inTheMove && !inTheFall) {
        this->unschedule(schedule_selector(TakasuPoppo::fixedUpdate));
        this->scheduleOnce(schedule_selector(TakasuPoppo::logicExecution), 0);
        
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

void TakasuPoppo::scheduleClean() {
    debugRun += 1;
    CCLOG("Ran how many times_? - %i", debugRun);
    if (inCleaning == true) {
        this->scheduleOnce(schedule_selector(TakasuPoppo::cleanBlocks), 0.1);
        inCleaning = false;
    } 
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
    inCleaning = true;
    this->runAction(CCSequence::create(
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::scheduleClean)),
                                       CCDelayTime::create(CLEAN_DELAY),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::afterClean)),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::scheduleGenerate)),
                                       NULL));
    this->schedule(schedule_selector(TakasuPoppo::fallingBoolSwitch), FALL_TIME);
    this->schedule(schedule_selector(TakasuPoppo::fixedUpdate), LOGIC_DELAY);
}

void TakasuPoppo::timeSetup() {
    CCSprite *timer = CCSprite::create("Timer.png");
    timer->setAnchorPoint(ccp(0, 0));
    timerBar = CCProgressTimer::create(timer);
    
    timerBar->setType(kCCProgressTimerTypeBar);
    timerBar->setAnchorPoint(ccp(0, 0));
    
    timerBar->setPosition(30, 22);
    timerBar->setMidpoint(ccp(0, 0));
    timerBar->setBarChangeRate(ccp(1, 0));
    
    timerBar->setTag(405);
    this->addChild(timerBar, 5);
    
    CCSprite *combo = CCSprite::create("Combo.png");
    combo->setAnchorPoint(ccp(0, 0));
    comboBar = CCProgressTimer::create(combo);
    
    comboBar->setType(kCCProgressTimerTypeBar);
    comboBar->setAnchorPoint(ccp(0, 0));
    
    comboBar->setPosition(195, 760);
    comboBar->setMidpoint(ccp(0, 0));
    comboBar->setBarChangeRate(ccp(1, 0));
    
    comboBar->setTag(406);
    this->addChild(comboBar, 5);
}

void TakasuPoppo::timeCounter() {
    gameTimer -= deltaTime;
    if (gameTimer > 0) {
        timerBar->setPercentage(1.66 * gameTimer);
    }
    if (gameTimer < 0) {
        gameTimer = 60;
    }
//    else {
//        unschedule(schedule_selector(TakasuPoppo::timeCounter));
//    }
    
    if (comboCounter > 0 && comboCounter <= 5) {
        comboBar->setPercentage(comboCounter * 20);
    }
    if (comboCounter > 5) {
        comboBar->setPercentage(0);
    }
}

void TakasuPoppo::timeOver() {
    
}
