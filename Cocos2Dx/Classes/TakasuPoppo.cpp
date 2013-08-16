//  Created by MinhNT on 13/05/16.
//  Copyright FRAMGIA 2013年. All rights reserved.
//

#include "TakasuPoppo.h"
#include "SimpleAudioEngine.h"
#include "TPObjectExtension.h"
#include "TPBlockSet.h"
#include "CCGestureRecognizer.h"
#include "TPMainScreen.h"
#include "TPUser.h"

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
//    debugTilesArray = new CCArray;
//    TakasuPoppo::setupDebugButton();
//    
//    sprintf(comboCounterString, "Combo: %i", hbcComboCounter);
//    comboCounterLabel = CCLabelTTF::create(comboCounterString, "Arial", FONT_SIZE);
//    comboCounterLabel->setZOrder(15);
//    comboCounterLabel->setColor(ccc3(225, 225, 225));
//    comboCounterLabel->setPosition(ccp(80, 850));
//    
//    sprintf(comboTimerString, "Timer: %f", hbcComboTimer);
//    comboTimerLabel = CCLabelTTF::create(comboTimerString, "Arial", FONT_SIZE);
//    comboTimerLabel->setZOrder(15);
//    comboTimerLabel->setColor(ccc3(225, 225, 225));
//    comboTimerLabel->setPosition(ccp(330, 850));
//    
//    this->addChild(comboCounterLabel);
//    this->addChild(comboTimerLabel);
    //===============================================================
    
    //==========================SCORE ===============================
//    CCLabelTTF* lbScoreTitle = CCLabelTTF::create("SCORE", "Arial", FONT_SIZE);
//    lbScoreTitle->setZOrder(15);
//    lbScoreTitle->setColor(ccc3(225, 225, 225));
//    lbScoreTitle->setPosition(ccp(80, 920));
//    this->addChild(lbScoreTitle);
    
    
    string str = static_cast<ostringstream*>( &(ostringstream() << score) )->str();
    bmScore = CCLabelBMFont::create(str.c_str(), "TakasuScore.fnt", 30, kCCTextAlignmentLeft);
    bmScore->setZOrder(15);
    bmScore->setPosition(ccp(180, 920));
    this->addChild(bmScore);
    //===============================================================
    
    //======================== Interface ============================
    CCSprite *background = CCSprite::create("poppo_background2.png");
    background->setPosition(ccp(winSize.width / 2,
                                winSize.height / 2 + 33));
    this->addChild(background, -3, -1);
    
    CCSprite *upperCover = CCSprite::create("UpperCover.png");
    upperCover->setPosition(ccp(winSize.width / 2, winSize.height - 40));
    this->addChild(upperCover, 10, -4);
    
    CCSprite *ideGauge = CCSprite::create("ComboGaugeCircle.png");
    ideGauge->setPosition(ccp(330, 920));
    this->addChild(ideGauge, 13, -2);
    
    CCSprite *comboGauge = CCSprite::create("ComboBarOut.png");
    comboGauge->setPosition(ccp(440, 920));
    this->addChild(comboGauge, 11, -3);
    
    CCSprite *timerBar = CCSprite::create("TimeBarOut.png");
    timerBar->setPosition(ccp(winSize.width / 2 - 2, 136));
    this->addChild(timerBar, -2, -3);
    
    CCSprite *bottomCover = CCSprite::create("BottomCover.png");
    bottomCover->setPosition(ccp(winSize.width / 2, 40));
    this->addChild(bottomCover, -2);
    
    //===============================================================
    
    //======================== Item Object ==========================
    
    _spcialItemID = _itemObject->getSpecialItemID() ;
    switch (_spcialItemID) {
        case SPECIAL_ITEM_1_ID:
            timeToCreateMB1 = rand() % (PLAY_TIME/2) + (PLAY_TIME/3) ;
            isCleanMB1 = false;
            isCreateMB1 = false;
            CCLog("time will create MB1: %i", timeToCreateMB1);
            break;
            
        case SPECIAL_ITEM_2_ID:
            timeToCreateMB2 = rand() % PLAY_TIME;
            isCleanMB2 = false;
            isCreateMB2 = false;
            isExistMB2 = false;
            countMB2 = 0;
            CCLog("time will create MB2: %i", timeToCreateMB2);
            break;
            
        case SPECIAL_ITEM_4_ID:
            doubleScoreStartTime = 0;
            isCleanMB3 = false;
            isCreateMB3 = false;
            timeToCreateMB3 = rand() % (PLAY_TIME/2) + (PLAY_TIME/2);
            CCLOG("Time to create MB2: %d", timeToCreateMB3);
            
        case SPECIAL_ITEM_5_ID:
            increaseComboTimes = 1.1;
            break;
            
        default:
            break;
    }
    
    //===============================================================
    
    hintCount = TakasuPoppo::lookForMatches();
    
    this->scheduleUpdate();
    
    this->schedule(schedule_selector(TakasuPoppo::startGame));
    
//    this->setTouchEnabled(true);
    
    //this->schedule(schedule_selector(TakasuPoppo::fixedUpdate));
    
//    this->scheduleOnce(schedule_selector(TakasuPoppo::timeSetup), 0);
//    
//    this->schedule(schedule_selector(TakasuPoppo::timeCounter));
//    
//    this->schedule(schedule_selector(TakasuPoppo::refreshWhenNoCombo), 2);
    
    this->schedule(schedule_selector(TakasuPoppo::matchList));
    return true;
}

void TakasuPoppo::startGame() {
    hintCounter = 5;
    executionTime -= deltaTime;
    
    CCSprite *counter3 = CCSprite::create("Ready.png");
    CCSprite *counter2 = CCSprite::create("Counter2.png");
    CCSprite *counter1 = CCSprite::create("Go.png");
    
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
        
        counterExist2 = true;
    }
    if (executionTime < 1) {
        counterExist2 = false;
        
        if (!counterExist1) this->addChild(counter1, 5);
        counterExist1 = true;
    }
    if (executionTime <= 0) {
        if (counterExist1) this->removeChildByTag(401, true);
        counterExist1 = false;
        
        TakasuPoppo::swipeSetup();
        
        this->setTouchEnabled(true);
        
        //this->schedule(schedule_selector(TakasuPoppo::fixedUpdate));
        
        this->scheduleOnce(schedule_selector(TakasuPoppo::timeSetup), 0);
        this->schedule(schedule_selector(TakasuPoppo::timeCounter));        
        this->schedule(schedule_selector(TakasuPoppo::refreshWhenNoCombo), 2);
        
        this->unschedule(schedule_selector(TakasuPoppo::startGame));
    }
}

void TakasuPoppo::endGame() {
    endTimeCounter -= deltaTime;
    
    CCSprite *counter3 = CCSprite::create("TimeUp.png");
    CCSprite *counter1 = CCSprite::create("LastBonus.png");
    
    counter3->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    counter1->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    
    counter3->setTag(1406);
    counter1->setTag(1404);
    
    if (endTimeCounter < 4) {
        if (!timeOverOn) this->addChild(counter3, 5);
        timeOverOn = true;
    }
    if (endTimeCounter < 3) {
        if (timeOverOn) this->removeChildByTag(1406, true);
        timeOverOn = false;
    }
    if (endTimeCounter < 2) {
        if (!takasuBonusOn) this->addChild(counter1, 5);
        takasuBonusOn = true;
    }
    if (endTimeCounter < 1) {
        if (takasuBonusOn) this->removeChildByTag(1404, true);
        takasuBonusOn = false;
    }
    if (endTimeCounter <= 0) {
        TakasuPoppo::timeOver();
        this->unschedule(schedule_selector(TakasuPoppo::endGame));
    }
}


void TakasuPoppo::update(float dt) {
    deltaTime = dt;
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
//    sprintf(comboCounterString, "Combo: %i", hbcComboCounter);
//    comboCounterLabel->setString(comboCounterString);
//    
//    sprintf(comboTimerString, "Timer: %f", hbcComboTimer);
//    comboTimerLabel->setString(comboTimerString);
    
    
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
            
            //TPObjectExtension* exd = mainSprite;
            move =false;
            TakasuPoppo::swipedRight(mainSprite);
            swipeRight = false;
           // mainSprite = NULL;
            swipeLeft = false;
            swipeUp = false;
            swipeDown = false;
//            if(exd != NULL)
//            exd->release();

        }
        if (swipeLeft && swape && !runningAfter) {
            
            //TPObjectExtension* exd = mainSprite;
            move =false;
            TakasuPoppo::swipedLeft(mainSprite);
            swipeRight = false;
            //mainSprite = NULL;
            swipeLeft = false;
            swipeUp = false;
            swipeDown = false;
//            if(exd != NULL)
//                exd->release();

        }
        if (swipeUp && swape && !runningAfter) {
            
            //TPObjectExtension* exd = mainSprite;
            move =false;
            TakasuPoppo::swipedUp(mainSprite);
            swipeRight = false;
            //mainSprite = NULL;
            swipeLeft = false;
            swipeUp = false;
            swipeDown = false;
//            if(exd != NULL)
//            exd->release();
        }
        if (swipeDown && swape && !runningAfter) {
            
            //TPObjectExtension* exd = mainSprite;
            TakasuPoppo::swipedDown(mainSprite);
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
        
        if (!this->getChildByTag(888)) {
            burningTakasuOn = true;
            TakasuPoppo::burnOnTakasu();
        }
        
        if (feverTimeLimit < 0) {
            isInFeverTime = false;
            feverTimeLimit = 0;
            if (this->getChildByTag(888)) {
                burningTakasuOn = false;
                TakasuPoppo::burnOnTakasu();
            }
        }
        
    }
    //================================================================

    
    //========================SCORE UPDATE ===========================
    string str = static_cast<ostringstream*>( &(ostringstream() << score) )->str();
    bmScore->setString(str.c_str());
    //================================================================
    
    
    //======================== Item Object ===========================
    switch (_spcialItemID) {
        case SPECIAL_ITEM_1_ID:
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
            
        case SPECIAL_ITEM_2_ID:
            if ( ( (rand() % PLAY_TIME) == timeToCreateMB2) && isCreateMB2 == false && isExistMB2 == false && countMB2 < MISSION_BLOCK2_MAX_AMOUNT) {
                isCreateMB2 = true;
                countMB2 ++;
            }
            if (isCleanMB2 == true) {
                gameTimer += 2;
                isCleanMB2 = false;
            }
            break;
        
        case SPECIAL_ITEM_4_ID:
            
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

                }
                else{
                    doubleScore = 1;
                }

            }
            break;
            
        case SPECIAL_ITEM_3_ID:
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
    this->unschedule(schedule_selector(TakasuPoppo::matchList));
    inCleaning = true;
    this->runAction(CCSequence::create(
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::cleanBlocks)),
                                       CCDelayTime::create(setCleanDelay()),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::setFalseControl)),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::afterClean)),
                                       CCDelayTime::create(movingSpeed * fallDistance + SWAP_TIME*2),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::setControl)),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::scheduleGenerate))
                                       ,NULL));
    CCLog("Logic Delay Time: %f", logicDelayTime);
    logicCounter = 0;
    this->schedule(schedule_selector(TakasuPoppo::logicDelaySwitch), 0);
    
//    if (!inTheFall && !inTheMove) {        
//        this->schedule(schedule_selector(TakasuPoppo::fallingBoolSwitch), FALL_TIME);
//    }
}

void TakasuPoppo::timeSetup() {
    CCSprite *timer = CCSprite::create("TimeBarIn.png");
    timer->setAnchorPoint(ccp(0, 0));
    timerBar = CCProgressTimer::create(timer);
    
    timerBar->setType(kCCProgressTimerTypeBar);
    timerBar->setAnchorPoint(ccp(0, 0));
    
    timerBar->setPosition(30, 112);
    timerBar->setMidpoint(ccp(0, 0));
    timerBar->setBarChangeRate(ccp(1, 0));
    
    timerBar->setTag(405);
    this->addChild(timerBar, 5);
    
    CCSprite *combo = CCSprite::create("ComboBarIn.png");
    combo->setAnchorPoint(ccp(0, 0));
    comboBar = CCProgressTimer::create(combo);
    
    comboBar->setType(kCCProgressTimerTypeBar);
    comboBar->setAnchorPoint(ccp(0, 0));
    
    comboBar->setPosition(ccp(338, 900)); //-70 140
    comboBar->setMidpoint(ccp(0, 0));
    comboBar->setBarChangeRate(ccp(1, 0));
    
    comboBar->setTag(406);
    
    gaugeComboCounter = 0;
    
    this->addChild(comboBar, 12);
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
        if (!prepareToEnd) {
            executionTime = 3;
            this->schedule(schedule_selector(TakasuPoppo::endGame));
            prepareToEnd = true;
        }

    }

    //====================== Gauge Bar updates =======================
    if (gaugePeriod > 0) {
        gaugePeriod -= deltaTime;
    }
    if (gaugePeriod < 0) {
        if (gaugeComboCounter >= 0) {
            gaugeComboCounter -= deltaTime/2;
        }
        else gaugeComboCounter = 0;
    }

    if (gaugeComboCounter >= 0 && gaugeComboCounter <= GAUGE_COMBO_REQUIRED) {
        comboBar->setPercentage(gaugeComboCounter * 100/GAUGE_COMBO_REQUIRED);
    }

    
    if (gaugeComboCounter >= GAUGE_COMBO_REQUIRED) {
        isCreateGaugeCombo = true;
        
    }
    
    if (gaugeComboCounter >= GAUGE_COMBO_REQUIRED) {
        comboBar->setPercentage(0);
        gaugeComboCounter = gaugeComboCounter - GAUGE_COMBO_REQUIRED;
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
        
        if (TPUser::shareTPUser()->getUserScore() < score) {
            TPUser::shareTPUser()->setUserScore(score);
         }
        
        CCScene *mainScene = TPMainScreen::scene(true, score);
        CCTransitionScene* transition = CCTransitionSlideInT::create(1, mainScene);
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
//    this->unschedule(schedule_selector(TakasuPoppo::matchList));
    logicCounter += deltaTime;
    CCLog("logic counter: %f", logicCounter);
    if (logicCounter > logicDelayTime) {
        this->schedule(schedule_selector(TakasuPoppo::matchList));
        
        CCObject* obj;
        CCARRAY_FOREACH(colorArray, obj){
            TPObjectExtension* exObj = dynamic_cast<TPObjectExtension*>(obj);
            if (exObj->getID() != 7 && exObj->getSprite() != NULL && (exObj->getPosition().x == exObj->getSprite()->getPosition().x)) {
                exObj->setControlTrigger(true);
            }
            
        }
        controlable = true;
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
