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
    unsigned int gid = exObj->getGid();
    if (gid != 7 && gid != 14 && gid != 21 && gid != 28 && gid != 35 && gid != 42 && gid != 49 ) {
        unsigned int swapedGit = exObj->getGid() + 1;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

void TakasuPoppo::swipedLeft(TPObjectExtension *exObj) {
    unsigned int gid = exObj->getGid();
    if (gid != 1 && gid != 8 && gid != 15 && gid != 22 && gid != 29 && gid != 36 && gid != 43 ) {
        unsigned int swapedGit = exObj->getGid() - 1;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

void TakasuPoppo::swipedUp(TPObjectExtension *exObj) {
    unsigned int gid = exObj->getGid();
    if (gid >= 7) {
        unsigned int swapedGit = exObj->getGid() - 7;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

void TakasuPoppo::swipedDown(TPObjectExtension *exObj) {
    unsigned int gid = exObj->getGid();
    if (gid < 43) {
        unsigned int swapedGit = exObj->getGid() + 7;
        TakasuPoppo::swapTilesCheck(exObj, swapedGit);
    }
}

#pragma mark Tile Interactions
void TakasuPoppo::swapTilesCheck(TPObjectExtension *exObj, int swpGid) {
    TakasuPoppo::lookForMatches();
    TPObjectExtension *swpObj = dynamic_cast<TPObjectExtension*>(colorArray->objectAtIndex(swpGid- 1)); //Out of range error
    if (exObj->getControlTrigger() != false && swpObj->getControlTrigger() != false &&
        exObj->getID() != 7 && swpObj->getID() != 7 &&
        exObj->getID() != 8 && swpObj->getID() != 8) {
        TakasuPoppo::swapColorID(exObj, swpObj);
        movedSprite = exObj;
        swapedSprite = swpObj;
        if (TakasuPoppo::matchAble(swpObj->getCoordination(), swpObj->getID()) == true ||
            TakasuPoppo::matchAble(exObj->getCoordination(), exObj->getID()) == true) {
            moveCounter = 0;
            this->schedule(schedule_selector(TakasuPoppo::movingBoolSwitch), 0.05);
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
                    CCMoveTo::create(0.09, moveDes),
                    CCMoveTo::create(0.09, swapDes),
                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::switchControlable), (void*)movedSprite), NULL));
    
    swapedSprite->getSprite()->runAction(CCSequence::create(
                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::switchControlable), (void*)swapedSprite),
                    CCMoveTo::create(0.09, swapDes),
                    CCMoveTo::create(0.09, moveDes),
                    CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::switchControlable), (void*)swapedSprite), NULL));
}

void TakasuPoppo::switchControlable(TPObjectExtension *exObj) {
    bool controlable = exObj->getControlTrigger();
    controlable = !controlable;
}

void TakasuPoppo::checkPosition() {
//    CCObject *object;
//    CCARRAY_FOREACH(colorArray, object) {
//        TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
//        if (exObj->getSprite() != NULL &&
//           (exObj->getSprite()->getPosition().x != exObj->getPosition().x ||
//            exObj->getSprite()->getPosition().y != exObj->getPosition().y) ) {
//            exObj->getSprite()->runAction(CCMoveTo::create(0.1, exObj->getPosition()));
//        }
//    }

    if (swapedSprite->getSprite()->getPosition().x != swapedSprite->getPosition().x ||
        swapedSprite->getSprite()->getPosition().y != swapedSprite->getPosition().y ) {
        swapedSprite->getSprite()->runAction(CCMoveTo::create(0.09, swapedSprite->getPosition()));
    }
    if (movedSprite->getSprite()->getPosition().x != movedSprite->getPosition().x ||
        movedSprite->getSprite()->getPosition().y != movedSprite->getPosition().y ) {
        movedSprite->getSprite()->runAction(CCMoveTo::create(0.09, movedSprite->getPosition()));
    }

}
