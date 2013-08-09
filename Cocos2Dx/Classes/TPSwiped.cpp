//
//  TP_takasuPoppo_Swiped.cpp
//  Cocos2Dx
//
//  Created by macbook_006 on 13/06/28.
//
//

#include "TakasuPoppo.h"

#pragma mark Swipe Actions

void TakasuPoppo::swipeSetup() {
    CCSwipeGestureRecognizer *swipe = CCSwipeGestureRecognizer::create();
    swipe->setTarget(this, callfuncO_selector(TakasuPoppo::didSwipe));
    
    swipe->setDirection(kSwipeGestureRecognizerDirectionDown | kSwipeGestureRecognizerDirectionLeft |
                        kSwipeGestureRecognizerDirectionRight | kSwipeGestureRecognizerDirectionUp);
    swipe->setCancelsTouchesInView(true);
    this->addChild(swipe);
}

void TakasuPoppo::didSwipe(int direction) {
    
}

void TakasuPoppo::swipedRight(TPObjectExtension *exObj) {
    if (!checkAllRunning() && exObj != NULL && exObj->getCoordination().x != 6 && exObj->getControlTrigger()) {
        unsigned int swapedGit = exObj->getGid() + 1;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

void TakasuPoppo::swipedLeft(TPObjectExtension *exObj) {
    if (!checkAllRunning() && exObj != NULL && exObj->getCoordination().x != 0  && exObj->getControlTrigger()) {
        unsigned int swapedGit = exObj->getGid() - 1;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

void TakasuPoppo::swipedUp(TPObjectExtension *exObj) {
    if (!checkAllRunning() && exObj != NULL && exObj->getCoordination().y != 0 && exObj->getControlTrigger()) {
        unsigned int swapedGit = exObj->getGid() - 7;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

void TakasuPoppo::swipedDown(TPObjectExtension *exObj) {
    if (!checkAllRunning() && exObj != NULL && exObj->getCoordination().y != 6 && exObj->getControlTrigger()) {
        unsigned int swapedGit = exObj->getGid() + 7;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

#pragma mark Tile Interactions
//void TakasuPoppo::swapTilesCheck(TPObjectExtension *exObj, int swpGid) {
//    TakasuPoppo::lookForMatches();
//    TPObjectExtension *swpObj = dynamic_cast<TPObjectExtension*>(colorArray->objectAtIndex(swpGid- 1)); //Out of range error
//    
//    if(swpObj->getBlockType() == HBC_BLOCK_TYPE)
//    {
//        //TakasuPoppo::swapColorID(exObj, swpObj);
//        cleanHyperBlockC(swpObj);
//        
//        return;
//    }
//    else if(exObj->getBlockType() == HBC_BLOCK_TYPE)
//    {
//        //TakasuPoppo::swapColorID(exObj, swpObj);
//        cleanHyperBlockC(exObj);
//        return;
//    }
//    
//    
//    
//    if (exObj != NULL &&
//        exObj->getControlTrigger() != false &&
//        swpObj != NULL &&
//        swpObj->getControlTrigger() != false &&
//        exObj->getID() != 7 &&
//        swpObj->getID() != 7) {
//
//        
//        TakasuPoppo::swapColorID(exObj, swpObj);
//        
//        
//        
//        
//
//        if (TakasuPoppo::matchAble(swpObj->getCoordination(), swpObj->getID()) == true ||
//            TakasuPoppo::matchAble(exObj->getCoordination(), exObj->getID()) == true) {
//            
//            moveCounter = 0;
//            this->schedule(schedule_selector(TakasuPoppo::movingBoolSwitch), MOVE_DELAY);
//            TakasuPoppo::checkPosition(exObj, swpObj);
//            if(TakasuPoppo::matchAble(swpObj->getCoordination(), swpObj->getID()) == true){
//                if(swpObj->getBlockType() == NORMAL_BLOCK_TYPE)
//                    swpObj->setBlockType(MOVED_NORMAL_BLOCK_TYPE);
//                if(swpObj->getBlockType() == HBA_BLOCK_TYPE)
//                    swpObj->setBlockType(MOVED_HBA_BLOCK_TYPE);
//                if(swpObj->getBlockType() == HBB_BLOCK_TYPE)
//                    swpObj->setBlockType(MOVED_HBB_BLOCK_TYPE);
//            }
//            if(TakasuPoppo::matchAble(exObj->getCoordination(), exObj->getID()) == true){
//                if(exObj->getBlockType() == NORMAL_BLOCK_TYPE)
//                    exObj->setBlockType(MOVED_NORMAL_BLOCK_TYPE);
//                if(exObj->getBlockType() == HBA_BLOCK_TYPE)
//                    exObj->setBlockType(MOVED_HBA_BLOCK_TYPE);
//                if(exObj->getBlockType() == HBB_BLOCK_TYPE)
//                    exObj->setBlockType(MOVED_HBB_BLOCK_TYPE);
//            }
//            
//        }
//        else {
//            TakasuPoppo::swapColorID(exObj, swpObj);
//            if(exObj->getSprite() != NULL && swpObj->getSprite() != NULL)
//                TakasuPoppo::swapTilesBack(exObj, swpObj);
//        }
//    }
//    //this->setTouchEnabled(true);
//
//}
void TakasuPoppo::swapTilesCheck(TPObjectExtension *exObj, int swpGid) {
    TakasuPoppo::lookForMatches();
    TPObjectExtension *swpObj = dynamic_cast<TPObjectExtension*>(colorArray->objectAtIndex(swpGid- 1)); //Out of range error
    
    if (exObj != NULL &&
        exObj->getControlTrigger() != false &&
        swpObj != NULL &&
        swpObj->getControlTrigger() != false &&
        exObj->getID() != 7 &&
        swpObj->getID() != 7) {
        
        if(swpObj->getBlockType() == HBC_BLOCK_TYPE)
        {
            swpObj->getSprite()->stopActionByTag(1210);
        }
        if(exObj->getBlockType() == HBC_BLOCK_TYPE)
        {
            exObj->getSprite()->stopActionByTag(1210);
        }
        TakasuPoppo::swapColorID(exObj, swpObj);
        
        if (TakasuPoppo::matchAble(swpObj->getCoordination(), swpObj->getID()) == true ||
            TakasuPoppo::matchAble(exObj->getCoordination(), exObj->getID()) == true) {
            TakasuPoppo::checkPosition(swpObj, exObj);
            moveCounter = 0;
            this->schedule(schedule_selector(TakasuPoppo::movingBoolSwitch), MOVE_DELAY);
            if(TakasuPoppo::matchAble(swpObj->getCoordination(), swpObj->getID()) == true){
                if(swpObj->getBlockType() == HBC_BLOCK_TYPE)
                {
                    makeBlockToBeHBC(swpObj);
                }
                if(exObj->getBlockType() == HBC_BLOCK_TYPE)
                {
                    makeBlockToBeHBC(exObj);
                }
                if(swpObj->getBlockType() == NORMAL_BLOCK_TYPE)
                    swpObj->setBlockType(MOVED_NORMAL_BLOCK_TYPE);
                if(swpObj->getBlockType() == HBA_BLOCK_TYPE)
                    swpObj->setBlockType(MOVED_HBA_BLOCK_TYPE);
                if(swpObj->getBlockType() == HBB_BLOCK_TYPE)
                    swpObj->setBlockType(MOVED_HBB_BLOCK_TYPE);
            }
            if(TakasuPoppo::matchAble(exObj->getCoordination(), exObj->getID()) == true){
                
                if(exObj->getBlockType() == HBC_BLOCK_TYPE)
                {
                    makeBlockToBeHBC(exObj);
                }
                if(swpObj->getBlockType() == HBC_BLOCK_TYPE)
                {
                    makeBlockToBeHBC(swpObj);
                }
                if(exObj->getBlockType() == NORMAL_BLOCK_TYPE)
                    exObj->setBlockType(MOVED_NORMAL_BLOCK_TYPE);
                if(exObj->getBlockType() == HBA_BLOCK_TYPE)
                    exObj->setBlockType(MOVED_HBA_BLOCK_TYPE);
                if(exObj->getBlockType() == HBB_BLOCK_TYPE)
                    exObj->setBlockType(MOVED_HBB_BLOCK_TYPE);
            }
            
        }
        else {
            TakasuPoppo::swapColorID(exObj, swpObj);
            if(exObj->getSprite() != NULL && swpObj->getSprite() != NULL)
            {
                TakasuPoppo::swapTilesBack(swpObj, exObj);
                if(swpObj->getBlockType() == HBC_BLOCK_TYPE)
                {
                    makeBlockToBeHBC(swpObj);
                }
                if(exObj->getBlockType() == HBC_BLOCK_TYPE)
                {
                    makeBlockToBeHBC(exObj);
                }
                
            }
        }
    }
    //this->setTouchEnabled(true);
    
}

void TakasuPoppo::swapColorID(TPObjectExtension *exObj, TPObjectExtension *swpObj) {
    int exID = exObj->getID();
    int swpID = swpObj->getID();
    exObj->setID(swpID);
    swpObj->setID(exID);

    
    
    //Vinh nt - Swap block type
    int exBlockId = exObj->getBlockType();
    int swpBlockId = swpObj->getBlockType();
    exObj->setBlockType(swpBlockId);
    swpObj->setBlockType(exBlockId);
    
    
    
    CCSprite *moveSprite = exObj->getSprite();
    CCSprite *swapSprite = swpObj->getSprite();
    exObj->setSprite(swapSprite);
    swpObj->setSprite(moveSprite);
}

void TakasuPoppo::swapTilesBack(TPObjectExtension *exObj, TPObjectExtension *swpObj) {
    CCPoint moveDes = swpObj->getPosition();
    CCPoint swapDes = exObj->getPosition();
    if(exObj != NULL && swpObj != NULL &&
       exObj->getSprite() != NULL &&
       exObj->getSprite()->numberOfRunningActions() == 0 &&
       swpObj->getSprite() != NULL &&
       swpObj->getSprite()->numberOfRunningActions() == 0)
    {
        CCBool* boolrun = new CCBool(true);
        exObj->getSprite()->runAction(CCSequence::create(
                                                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::runningSwap), (void*)boolrun),
                                                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable), (void*)swpObj),
                                                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable), (void*)exObj),
                                                    CCMoveTo::create(SWAP_TIME, moveDes),
                                                    CCMoveTo::create(SWAP_TIME, swapDes),
                                                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::notRunningSwap), (void*)boolrun),
                                                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable), (void*)swpObj),
                                                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable), (void*)exObj), NULL)
                                                        );
        swpObj->getSprite()->runAction(CCSequence::create(
                                                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::runningSwap), (void*)boolrun),
                                                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable), (void*)exObj),
                                                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable), (void*)swpObj),
                                                    CCMoveTo::create(SWAP_TIME, swapDes),
                                                    CCMoveTo::create(SWAP_TIME, moveDes),
                                                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::notRunningSwap), (void*)boolrun),
                                                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable), (void*)exObj),
                                                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable), (void*)swpObj), NULL));
        
    }
}

void TakasuPoppo::switchControlable(TPObjectExtension *exObj) {
//    bool controlable = exObj->getControlTrigger();
//    controlable = !controlable;
    exObj->setControlTrigger(!exObj->getControlTrigger());
    
}

void TakasuPoppo::setTrueControlable(CCNode *sender, void* data)
{
    move = false;
    swape = false;
    if(data != NULL)
    {
        TPObjectExtension * exObj = (TPObjectExtension*)data;
        if(exObj != NULL)
        exObj->setControlTrigger(true);
    }
}
void TakasuPoppo::setFalseControlable(CCNode *sender, void* data)
{
    //runningAfter = true;
    //move = false;
    //swape = false;
    TPObjectExtension* exObj = (TPObjectExtension*)data;
    if(exObj != NULL)
        exObj->setControlTrigger(false);
}

void TakasuPoppo::checkPosition(TPObjectExtension *exObj, TPObjectExtension *swpObj) {
    CCPoint moveDes = swpObj->getPosition();
    CCPoint swapDes = exObj->getPosition();
    if(swpObj->getSprite()->numberOfRunningActions() == 0 && exObj->getSprite()->numberOfRunningActions() == 0)
    {
        if (swpObj->getSprite()->getPosition().x != swpObj->getPosition().x ||
            swpObj->getSprite()->getPosition().y != swpObj->getPosition().y ) {
            CCBool* boolrun = new CCBool(true);
            swpObj->getSprite()->runAction(CCSequence::create(
                                                              CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::runningSwap), (void*)boolrun),
                                                              CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable), (void*)swpObj),
                                                              CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable), (void*)exObj),
                                                              CCMoveTo::create(SWAP_TIME, moveDes),
                                                              CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::notRunningSwap), (void*)boolrun),
                                                              CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable), (void*)exObj),
                                                              CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable), (void*)swpObj),
                                                               NULL));
        }
        if (exObj->getSprite()->getPosition().x != exObj->getPosition().x ||
            exObj->getSprite()->getPosition().y != exObj->getPosition().y ) {
            CCBool* boolrun = new CCBool(true);
            exObj->getSprite()->runAction(CCSequence::create(
                                                             CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::runningSwap), (void*)boolrun),
                                                             CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable), (void*)exObj),
                                                             CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable), (void*)swpObj),
                                                             CCMoveTo::create(SWAP_TIME, swapDes),
                                                             CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::notRunningSwap), (void*)boolrun),
                                                             CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable), (void*)exObj),
                                                             CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable), (void*)swpObj),
                                                             NULL));
        }
    }
}
TPObjectExtension* TakasuPoppo::checkSwipe(TPBlockSet *blockSet){
    if (blockSet->getEx1() != NULL && blockSet->getEx1()->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE) return blockSet->getEx1();
    if (blockSet->getEx2() != NULL && blockSet->getEx2()->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE) return blockSet->getEx2();
    if (blockSet->getEx3() != NULL && blockSet->getEx3()->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE) return blockSet->getEx3();
    if (blockSet->getEx4() != NULL && blockSet->getEx4()->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE) return blockSet->getEx4();
    if (blockSet->getEx5() != NULL && blockSet->getEx5()->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE) return blockSet->getEx5();
    if (blockSet->getEx6() != NULL && blockSet->getEx6()->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE) return blockSet->getEx6();
    if (blockSet->getEx7() != NULL && blockSet->getEx7()->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE) return blockSet->getEx7();
    return blockSet->getEx2();
}

