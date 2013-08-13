//  Created by MinhNT on 13/05/16.
//  Copyright FRAMGIA 2013年. All rights reserved.
//

#include "TakasuPoppo.h"
#include "SimpleAudioEngine.h"
#include "TPObjectExtension.h"
#include "TPBlockSet.h"
#include "CCGestureRecognizer.h"
#include "TPMainScreen.h"

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
            timeToCreateMB1 = rand() % (PLAY_TIME/2) + (PLAY_TIME/3) ;
            isCleanMB1 = false;
            isCreateMB1 = false;
            CCLog("time will create MB1: %i", timeToCreateMB1);
            break;
            
        case 4:
            timeToCreateMB2 = rand() % PLAY_TIME;
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
            timeToCreateMB3 = rand() % (PLAY_TIME/2) + (PLAY_TIME/2);
            CCLOG("Time to create MB2: %d", timeToCreateMB3);
            
        case 7:
            increaseComboTimes = 1.1;
            break;
            
        default:
            break;
    }
    
    //===============================================================
    
    hintCount = TakasuPoppo::lookForMatches();
    
    this->scheduleUpdate();
    
    //    this->schedule(schedule_selector(TakasuPoppo::startGame));
    
    this->setTouchEnabled(true);
    
    //this->schedule(schedule_selector(TakasuPoppo::fixedUpdate));
    
    this->scheduleOnce(schedule_selector(TakasuPoppo::timeSetup), 0);
    
    this->schedule(schedule_selector(TakasuPoppo::timeCounter));
    
    this->schedule(schedule_selector(TakasuPoppo::refreshWhenNoCombo), 2);
    return true;
}

void TakasuPoppo::startGame() {
    hintCounter = 5;
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
        
        //this->setTouchEnabled(true);
        
        //this->schedule(schedule_selector(TakasuPoppo::fixedUpdate));
        
        this->scheduleOnce(schedule_selector(TakasuPoppo::timeSetup), 0);
        this->schedule(schedule_selector(TakasuPoppo::timeCounter));
        
        this->unschedule(schedule_selector(TakasuPoppo::startGame));
    }
}

void TakasuPoppo::update(float dt) {
    deltaTime = dt;
    //if(runningAfter) this->setTouchEnabled(false);
//    if(lookForMatches() == 0)
//        //reset
//    {
//        this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(TakasuPoppo::destroyAllBlocks)),
//                                               CCCallFunc::create(this, callfunc_selector(TakasuPoppo::createFixture)),NULL));
//  
//    }
    
    
    TakasuPoppo::matchList();
//    bool c = checkUpdate();
    if (toDestroyArray->count() > 0 && !inTheMove /*&& !inTheFall*/)
    {
        TakasuPoppo::fixedUpdate(0.013);
        //this->scheduleOnce(schedule_selector(TakasuPoppo::fixedUpdate), 0);
    }else
    {
        //this->unschedule(schedule_selector(TakasuPoppo::fixedUpdate));
        //setControl();
        //releaseAfterRunning();
    }
    

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
//    CCLog("ComboTimer: %f", ComboTimer);

    //===============================================================
    
    
    //=================== Hint related updates ======================

    if (hintCounter > 0) {
        hintCounter -= dt;
    }
    
    if (hintCounter <= 0 && hintDisplaying == false) {
        hintDisplaying = true;
        hintArray->removeAllObjects();
        hintCount = TakasuPoppo::lookForMatches();
        this->scheduleOnce(schedule_selector(TakasuPoppo::hintGeneration), 0);
        if (hintCount == 0) {
            this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(TakasuPoppo::destroyAllBlocks)),
                                               CCCallFunc::create(this, callfunc_selector(TakasuPoppo::createFixture)),NULL));

        }
    }
    //================================================================
    
    
    
    //=================== Swipe related updates ======================
    if (controlable) {
        if (swipeRight && swape && !runningAfter) {
            
            TPObjectExtension* exd = mainSprite;
            move =false;
            TakasuPoppo::swipedRight(exd);
            swipeRight = false;
           // mainSprite = NULL;
            swipeLeft = false;
            swipeUp = false;
            swipeDown = false;
//            if(exd != NULL)
//            exd->release();

        }
        if (swipeLeft && swape && !runningAfter) {
            
            TPObjectExtension* exd = mainSprite;
            move =false;
            TakasuPoppo::swipedLeft(exd);
            swipeRight = false;
            //mainSprite = NULL;
            swipeLeft = false;
            swipeUp = false;
            swipeDown = false;
//            if(exd != NULL)
//                exd->release();

        }
        if (swipeUp && swape && !runningAfter) {
            
            TPObjectExtension* exd = mainSprite;
            move =false;
            TakasuPoppo::swipedUp(exd);
            swipeRight = false;
            //mainSprite = NULL;
            swipeLeft = false;
            swipeUp = false;
            swipeDown = false;
//            if(exd != NULL)
//            exd->release();
        }
        if (swipeDown && swape && !runningAfter) {
            
            TPObjectExtension* exd = mainSprite;
            TakasuPoppo::swipedDown(exd);
            move =false;
            swipeRight = false;
           // mainSprite = NULL;
            swipeLeft = false;
            swipeUp = false;
            swipeDown = false;
//            if(exd != NULL)
//                exd->release();
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
        if (feverTimeLimit < 0) {
            isInFeverTime = false;
            feverTimeLimit = 0;
        }
        
    }
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
            if ( ( (rand() % PLAY_TIME) == timeToCreateMB2) && isCreateMB2 == false && isExistMB2 == false && countMB2 < MISSION_BLOCK2_MAX_AMOUNT) {
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
//                    CCLog("gameTimer: %f", gameTimer);
//                    CCLog("doubleScoreStartTime: %d", doubleScoreStartTime);
//                    CCLog("The Score is double now");
                }
                else{
                    doubleScore = 1;
//                    CCLog("The Score is not double anymore");
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

void TakasuPoppo::fixedUpdate(float time){
    //TakasuPoppo::matchList();
    if (toDestroyArray->count() > 0 && !inTheMove /*&& !inTheFall*/) {
        //count = 0;
        if (executingLogic == false) {
            executingLogic = true;
            this->scheduleOnce(schedule_selector(TakasuPoppo::logicExecution), 0);
            //TakasuPoppo::logicExecution();
        }

        //TakasuPoppo::logicExecution();
    }
}

//void TakasuPoppo::fallingBoolSwitch(float dt) {
//    inTheFall = true;
//    fallCounter += deltaTime;
//    if (fallCounter > FALL_TIME) {
//        inTheFall = false;
//        this->unschedule(schedule_selector(TakasuPoppo::fallingBoolSwitch));
//    }
//}

void TakasuPoppo::movingBoolSwitch(float dt) {
    inTheMove = true;
    moveCounter += deltaTime;
    if (moveCounter > MOVE_TIME) {
        inTheMove = false;
        this->unschedule(schedule_selector(TakasuPoppo::movingBoolSwitch));
    }
}

void TakasuPoppo::scheduleGenerate() {
    //this->scheduleOnce(schedule_selector(TakasuPoppo::smartGeneration), GENERATION_DELAY);
    TakasuPoppo::smartGeneration();
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
    if(ComboCounter >= COMBO_REQUIRED)
    {
        ComboScoreRequired = 1 + ((int)(ComboCounter/COMBO_REQUIRED)) / 10;
//        CCLOG("SSSSSSSSS %d",ComboCounter);
    }
    //this->unschedule(schedule_selector(TakasuPoppo::smartGeneration));
    inCleaning = true;
    this->runAction(CCSequence::create(
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::cleanBlocks)),
//                                       CCDelayTime::create(0.2f),
                                       CCDelayTime::create(setCleanDelay()),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::setFalseControl)),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::afterClean)),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::refreshMoving)),
                                       CCDelayTime::create(movingSpeed * 6),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::setControl)),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::scheduleGenerate))
                                       ,NULL));
    logicCounter = 0;
    this->schedule(schedule_selector(TakasuPoppo::logicDelaySwitch), 0);
    
//    if (!inTheFall && !inTheMove) {        
//        this->schedule(schedule_selector(TakasuPoppo::fallingBoolSwitch), FALL_TIME);
//    }
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
        scoresBeforeLastBonus = score;
    }
//=================================RESET GAME =====================
    
//    if(gameTimer < 5)
//        checkResetMap();

// ===============================================================
    if (gameTimer < 0) {
        timeBonus += deltaTime;
        hintCounter = 3;
        hintArray->removeAllObjects();
        if (this->getChildByTag(778)) this->removeChildByTag(778);
        hintDisplaying = false;
        //this->setTouchEnabled(false);
        this->unschedule(schedule_selector(TakasuPoppo::hintGeneration));
        TakasuPoppo::timeOver();

    }

    //====================== Gauge Bar updates =======================
    if (gaugeComboCounter >= 0 && gaugeComboCounter <= GAUGE_COMBO_REQUIRED) {
        comboBar->setPercentage(gaugeComboCounter * 100/GAUGE_COMBO_REQUIRED);
    }

    
    if (gaugeComboCounter >= GAUGE_COMBO_REQUIRED) {
        isCreateGaugeCombo = true;
        
    }
    
    if (gaugeComboCounter >= GAUGE_COMBO_REQUIRED) {
        comboBar->setPercentage(0);
        gaugeComboCounter = gaugeComboCounter % GAUGE_COMBO_REQUIRED;
    }
    
    //================================================================
    
}

void TakasuPoppo::timeOver() {
    
    CCObject *obj;
    CCARRAY_FOREACH(colorArray, obj){
        TPObjectExtension* exObj = dynamic_cast<TPObjectExtension*>(obj);
        exObj->setControlTrigger(false);
    }
    move = false;
    endTime = true;
    runningAfter = true;
    swape = false;
    CCBool * boolMoving = new CCBool(true);
    boolMoveTo->addObject(boolMoving);

    if (lastScore()) {
        CCLOG("SCORE * %d",score);
        CCScene *mainScene = TPMainScreen::scene();
        CCDirector::sharedDirector()->setDepthTest(true);
        CCTransitionScene* transition = CCTransitionFadeUp::create(1, mainScene);
        CCDirector::sharedDirector()->replaceScene(transition);
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

        //this->unscheduleUpdate();
    }

    
    this->unschedule(schedule_selector(TakasuPoppo::fixedUpdate));

   // this->unschedule(schedule_selector(TakasuPoppo::timeCounter));


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

bool TakasuPoppo::checkUpdate()
{
    CCObject* obj;
    CCARRAY_FOREACH(colorArray, obj)
    {
        TPObjectExtension* exObj = dynamic_cast<TPObjectExtension*>(obj);
        if(exObj->getID() == 7)
            return true;
    }
    return false;
}

void TakasuPoppo::logicDelaySwitch(){
    logicCounter += deltaTime;
    CCLog("logic counter: %f", logicCounter);
    if (logicCounter > logicDelayTime) {
        CCObject* obj;
        CCARRAY_FOREACH(colorArray, obj){
            TPObjectExtension* exObj = dynamic_cast<TPObjectExtension*>(obj);
            if (exObj->getID() != 7 && exObj->getSprite() != NULL && (exObj->getPosition().x == exObj->getSprite()->getPosition().x)) {
                exObj->setControlTrigger(true);
            }
            
        }
        executingLogic = false;
        this->unschedule(schedule_selector(TakasuPoppo::logicDelaySwitch));
    }

    
}

void TakasuPoppo::refreshWhenNoCombo(){
    hintCount = TakasuPoppo::lookForMatches();
    if (hintCount == 0) {
        this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(TakasuPoppo::destroyAllBlocks)),
                                           CCCallFunc::create(this, callfunc_selector(TakasuPoppo::createFixture)),NULL));
    }
}
