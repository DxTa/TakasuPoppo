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
    if (exObj->getCoordination().x != 6) {
        unsigned int swapedGit = exObj->getGid() + 1;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

void TakasuPoppo::swipedLeft(TPObjectExtension *exObj) {
    if (exObj->getCoordination().x != 0 ) {
        unsigned int swapedGit = exObj->getGid() - 1;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

void TakasuPoppo::swipedUp(TPObjectExtension *exObj) {
    if (exObj->getCoordination().y != 0) {
        unsigned int swapedGit = exObj->getGid() - 7;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

void TakasuPoppo::swipedDown(TPObjectExtension *exObj) {
    if (exObj->getCoordination().y != 6) {
        unsigned int swapedGit = exObj->getGid() + 7;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

#pragma mark Tile Interactions
void TakasuPoppo::swapTilesCheck(TPObjectExtension *exObj, int swpGid) {
    TakasuPoppo::lookForMatches();
    TPObjectExtension *swpObj = dynamic_cast<TPObjectExtension*>(colorArray->objectAtIndex(swpGid- 1)); //Out of range error
    if (exObj->getControlTrigger() != false && swpObj->getControlTrigger() != false &&
        exObj->getID() != 7 && swpObj->getID() != 7) {
        TakasuPoppo::swapColorID(exObj, swpObj);
        movedSprite = exObj;
        swapedSprite = swpObj;
        if (TakasuPoppo::matchAble(swpObj->getCoordination(), swpObj->getID()) == true ||
            TakasuPoppo::matchAble(exObj->getCoordination(), exObj->getID()) == true) {
            moveCounter = 0;
            this->schedule(schedule_selector(TakasuPoppo::movingBoolSwitch), MOVE_DELAY);
            TakasuPoppo::checkPosition();
            if(TakasuPoppo::matchAble(swpObj->getCoordination(), swpObj->getID()) == true){
                if(swpObj->getBlockType() == 0)
                    swpObj->setBlockType(10);
                if(swpObj->getBlockType() == 1)
                    swpObj->setBlockType(11);
                if(swpObj->getBlockType() == 2)
                    swpObj->setBlockType(12);
            }
            if(TakasuPoppo::matchAble(exObj->getCoordination(), exObj->getID()) == true){
                //if(exObj->getBlockType() == 3) cleanHyperBlockC(exObj);
                if(exObj->getBlockType() == 0)
                    exObj->setBlockType(10);
                if(exObj->getBlockType() == 1)
                    exObj->setBlockType(11);
                if(exObj->getBlockType() == 2)
                    exObj->setBlockType(12);
                
                
            }
            
            
                
    
        }
        else {
            TakasuPoppo::swapColorID(exObj, swpObj);
            TakasuPoppo::swapTilesBack();
        }
    }
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

void TakasuPoppo::swapTilesBack() {
    CCPoint moveDes = swapedSprite->getPosition();
    CCPoint swapDes = movedSprite->getPosition();
    
    movedSprite->getSprite()->runAction(CCSequence::create(
                                                           CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::switchControlable), (void*)movedSprite),
                                                           CCMoveTo::create(SWAP_TIME, moveDes),
                                                           CCMoveTo::create(SWAP_TIME, swapDes),
                                                           CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::switchControlable), (void*)movedSprite), NULL));
    
    swapedSprite->getSprite()->runAction(CCSequence::create(
                                                            CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::switchControlable), (void*)swapedSprite),
                                                            CCMoveTo::create(SWAP_TIME, swapDes),
                                                            CCMoveTo::create(SWAP_TIME, moveDes),
                                                            CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::switchControlable), (void*)swapedSprite), NULL));
}

//void TakasuPoppo::swapTilesBack() {
//    CCPoint moveDes = swapedSprite->getPosition();
//    CCPoint swapDes = movedSprite->getPosition();
//    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::switchControlable), (void*)movedSprite);
//    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::switchControlable), (void*)swapedSprite);
//    movedSprite->getSprite()->runAction(CCSequence::create(
//                                                           CCMoveTo::create(SWAP_TIME, moveDes),
//                                                           CCMoveTo::create(SWAP_TIME, swapDes),
//                                                           NULL)
//                                        );
//    
//    swapedSprite->getSprite()->runAction(CCSequence::create(
//                                                            
//                                                            CCMoveTo::create(SWAP_TIME, swapDes),
//                                                            CCMoveTo::create(SWAP_TIME, moveDes),
//                                                            NULL)
//                                         );
//    CCDelayTime::create(SWAP_TIME*2);
//    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::switchControlable), (void*)movedSprite);
//    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::switchControlable), (void*)swapedSprite);
//}


void TakasuPoppo::switchControlable(TPObjectExtension *exObj) {
    bool controlable = exObj->getControlTrigger();
    controlable = !controlable;
}

void TakasuPoppo::checkPosition() {
    if (swapedSprite->getSprite()->getPosition().x != swapedSprite->getPosition().x ||
        swapedSprite->getSprite()->getPosition().y != swapedSprite->getPosition().y ) {
        swapedSprite->getSprite()->runAction(CCMoveTo::create(SWAP_TIME, swapedSprite->getPosition()));
    }
    if (movedSprite->getSprite()->getPosition().x != movedSprite->getPosition().x ||
        movedSprite->getSprite()->getPosition().y != movedSprite->getPosition().y ) {
        movedSprite->getSprite()->runAction(CCMoveTo::create(SWAP_TIME, movedSprite->getPosition()));
    }
    
}

TPObjectExtension* TakasuPoppo::checkSwipe(TPBlockSet *blockSet){
    if (blockSet->getEx1() != NULL && blockSet->getEx1()->getBlockType() >= 10) return blockSet->getEx1();
    if (blockSet->getEx2() != NULL && blockSet->getEx2()->getBlockType() >= 10) return blockSet->getEx2();
    if (blockSet->getEx3() != NULL && blockSet->getEx3()->getBlockType() >= 10) return blockSet->getEx3();
    if (blockSet->getEx4() != NULL && blockSet->getEx4()->getBlockType() >= 10) return blockSet->getEx4();
    if (blockSet->getEx5() != NULL && blockSet->getEx5()->getBlockType() >= 10) return blockSet->getEx5();
    if (blockSet->getEx6() != NULL && blockSet->getEx6()->getBlockType() >= 10) return blockSet->getEx6();
    if (blockSet->getEx7() != NULL && blockSet->getEx7()->getBlockType() >= 10) return blockSet->getEx7();
    return blockSet->getEx2();
}