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

CCScene* TakasuPoppo::scene(TPItemObject* itemObjectD) {
    CCScene *scene = CCScene::create();
    TakasuPoppo *layer = TakasuPoppo::create(itemObjectD);
    scene->addChild(layer);
    return scene;
}

bool TakasuPoppo::init(TPItemObject* itemObject) {
    srand(time(NULL));
    _itemObject = new TPItemObject(itemObject->getIsFirstItemOn(), itemObject->getIsSecondItemOn(), itemObject->getIsThirdItemOn(), itemObject->getSpecialItemID());

    if(_itemObject->getIsFirstItemOn())
        addTime();
    if(_itemObject->getIsSecondItemOn()) {
        increasedScores();
    }
    if(_itemObject->getIsThirdItemOn()){
        createThreeeHyper = true;
    }
    
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
    
    sprintf(comboCounterString, "Combo: %i", hbcComboCounter);
    comboCounterLabel = CCLabelTTF::create(comboCounterString, "Arial", FONT_SIZE);
    comboCounterLabel->setZOrder(15);
    comboCounterLabel->setColor(ccc3(225, 225, 225));
    comboCounterLabel->setPosition(ccp(80, 850));
    
    sprintf(comboTimerString, "Timer: %f", hbcComboTimer);
    comboTimerLabel = CCLabelTTF::create(comboTimerString, "Arial", FONT_SIZE);
    comboTimerLabel->setZOrder(15);
    comboTimerLabel->setColor(ccc3(225, 225, 225));
    comboTimerLabel->setPosition(ccp(330, 850));
    
    this->addChild(comboCounterLabel);
    this->addChild(comboTimerLabel);
    //===============================================================
    
    //==========================SCORE ===============================
    CCLabelTTF* lbScoreTitle = CCLabelTTF::create("Score :", "Arial", FONT_SIZE);
    lbScoreTitle->setZOrder(15);
    lbScoreTitle->setColor(ccc3(225, 225, 225));
    lbScoreTitle->setPosition(ccp(60, 890));
    this->addChild(lbScoreTitle);
    
    
    string str = static_cast<ostringstream*>( &(ostringstream() << score) )->str();
    lbScore = CCLabelTTF::create(str.c_str(), "Arial", FONT_SIZE);
    lbScore->setZOrder(15);
    lbScore->setColor(ccc3(225, 225, 225));
    lbScore->setPosition(ccp(160, 890));
    this->addChild(lbScore);
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
    
    //======================== Item Object ==========================
    
    _spcialItemID = _itemObject->getSpecialItemID() ;
    switch (_spcialItemID) {
        case 3:
            timeToCreateMB1 = rand() % 30 + 20;
            isCleanMB1 = false;
            isCreateMB1 = false;
            CCLog("time will create MB1: %i", timeToCreateMB1);
            break;
            
        case 4:
            timeToCreateMB2 = rand() % 60;
            isCleanMB2 = false;
            isCreateMB2 = false;
            isExistMB2 = false;
            countMB2 = 0;
            CCLog("time will create MB2: %i", timeToCreateMB2);
            break;
            
        case 6:
            doubleScoreStartTime = 0;
            isCleanMB3 = false;
            isCreateMB3 = false;
            timeToCreateMB3 = rand() % 30 + 30;
            CCLOG("Time to create MB2: %d", timeToCreateMB3);
            
        case 7:
            increaseComboTimes = 1.1;
            break;
            
        default:
            break;
    }
    
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
    sprintf(comboCounterString, "Combo: %i", hbcComboCounter);
    comboCounterLabel->setString(comboCounterString);
    
    sprintf(comboTimerString, "Timer: %f", hbcComboTimer);
    comboTimerLabel->setString(comboTimerString);
    
    
    if (hbcComboTimer > 0) {
        hbcComboTimer -= dt;
    }
    if (hbcComboTimer < 0) {
        hbcComboTimer = 0;
        hbcComboCounter = 0;
    }
    if (hbcComboCounter >= HBC_COMBO_MAXCOUNT) {
        hyperBlockC =true;
        hbcComboCounter = hbcComboCounter % HBC_COMBO_MAXCOUNT;
    }
    //===============================================================
    
    
    //=================== Really Combo updates ======================
    // ComboTimer is set to 3 if ComboCounter + 1 (user hit score)
    if (ComboTimer > 0) {
        ComboTimer -= dt;
    }
    if (ComboTimer < 0) {
        ComboTimer = 0;
        ComboCounter = 0;
    }
    CCLog("ComboTimer: %f", ComboTimer);
    CCLog("ComboCounter: %d", ComboCounter);

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
    
    
    
    //===================== Fever Time updates =======================
    
    if (feverCounter > 0) {
        
        if (feverCounter > FEVER_COMBO_REQUIRED ) {
            
            feverCounter = 0;
            feverTimer = 0;
        }

        else {
            feverTimer += dt;
            if (feverTimer > FEVER_TIME_REQUIRED) {
                feverTimer = 0;
                feverCounter = 0;
            } else {
                if (feverCounter == FEVER_COMBO_REQUIRED && isCreateFeverTime == false) {
                    isCreateFeverTime = true;
                }
            }
        }
    }
    
    if (isCreateFeverTime == true) {
        isInFeverTime = true;
        feverTimeLimit = 3;
        isCreateFeverTime = false;
    }
    
    if (isInFeverTime == true) {
        feverTimeLimit -= dt;

 //       CCLog("It is in ferver time now");

        if (feverTimeLimit < 0) {
            isInFeverTime = false;
            feverTimeLimit = 0;
            
  //          CCLog("It is not in fever Time");

        }
        
        
    }

//    CCLog("Fever Counter: %i", feverCounter);
//    CCLog("Fever Timer: %f", feverTimer);
    //================================================================

    //========================SCORE UPDATE ===========================
    string str = static_cast<ostringstream*>( &(ostringstream() << score) )->str();
    lbScore->setString(str.c_str());
    //================================================================
    
    //======================== Item Object ===========================
    switch (_spcialItemID) {
        case 3:
            if (gameTimer < timeToCreateMB1 && isCreateMB1 == false) {
                isCreateMB1 = true;
                CCLog("time will create MB1: %i", timeToCreateMB1);
            }
            if (isCreateMB1 == true) {
                timeToCreateMB1 = -1;
            }
            if (isCleanMB1 == true) {
                this->runAction(CCSequence::create(   CCCallFunc::create(this, callfunc_selector(TakasuPoppo::destroyAllBlocks)), CCCallFunc::create(this, callfunc_selector(TakasuPoppo::generateBlocksAfterCleanMB1)),NULL));
         }
            break;
            
        case 4:
            if ( ( (rand() % 60) == timeToCreateMB2) && isCreateMB2 == false && isExistMB2 == false && countMB2 < 10) {
                isCreateMB2 = true;
                countMB2 ++;
            }
            if (isCleanMB2 == true) {
                gameTimer += 2;
                isCleanMB2 = false;
            }
            break;
        
        case 6:
            
            if (gameTimer < timeToCreateMB3 && isCreateMB3 == false) {
                isCreateMB3 = true;
            }
            if (isCreateMB3 == true) {
                timeToCreateMB3 = -1;
            }
            if (isCleanMB3 == true) {
                doubleScoreStartTime = gameTimer;
                isCleanMB3 = false;
            }
            if (doubleScoreStartTime != 0) {
                if (gameTimer <= doubleScoreStartTime && gameTimer >= (doubleScoreStartTime - DOUBLE_SCORE_TIME) ) {
                    // do some code logic here
                    doubleScore = 2;
                    CCLog("gameTimer: %f", gameTimer);
                    CCLog("doubleScoreStartTime: %d", doubleScoreStartTime);
                    CCLog("The Score is double now");
                }
                else{
                    doubleScore = 1;
                    CCLog("The Score is not double anymore");
                }

            }
            break;
            
        case 5:
            modefiedLastBonus();
            break;

        default:
            break;
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
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::cleanBlocks)),
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
    
    gaugeComboCounter = 0;
    
    this->addChild(comboBar, 5);
}

void TakasuPoppo::timeCounter() {
    
    if (gameTimer > 0) {
        gameTimer -= deltaTime;
        timerBar->setPercentage(1.66 * gameTimer);
    }
    if (gameTimer < 0) {
        timeBonus += deltaTime;
        hintCounter = 3;
        hintArray->removeAllObjects();
        if (this->getChildByTag(778)) this->removeChildByTag(778);
        hintDisplaying = false;
        this->unschedule(schedule_selector(TakasuPoppo::hintGeneration));
        TakasuPoppo::timeOver();

    }

    //====================== Gauge Bar updates =======================
    if (gaugeComboCounter >= 0 && gaugeComboCounter <= 10) {
        comboBar->setPercentage(gaugeComboCounter * 10);
    }

    
    if (gaugeComboCounter >= 10) {
        isCreateGaugeCombo = true;
        
    }
    
    if (gaugeComboCounter >= 10) {
        comboBar->setPercentage(0);
        gaugeComboCounter = gaugeComboCounter % 10;
    }
    
    //================================================================
    
}

void TakasuPoppo::timeOver() {
    if (lastScore()) {
        CCLOG("SCORE * %d",score);
        this->unschedule(schedule_selector(TakasuPoppo::timeCounter));
    }
}

//for Mission Block
TakasuPoppo* TakasuPoppo::create(TPItemObject* itemObject){
    TakasuPoppo *pRet = new TakasuPoppo();
    if (pRet && pRet->init(itemObject)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \

}
