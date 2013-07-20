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
