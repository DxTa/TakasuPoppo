//
//  TPClean.cpp
//  Cocos2Dx
//
//  Created by Ace on 2013/07/01.
//
//

#include "TakasuPoppo.h"
#include "TPBlockSet.h"
void TakasuPoppo::cleanBlocks() {
    CCObject *object;
    if (toDestroyArray->count() != 0) {
        CCARRAY_FOREACH(toDestroyArray, object) {
            hintCounter = 3;
            TPBlockSet *blockSet = dynamic_cast<TPBlockSet*>(object);
            
            bool isHyper1 = false;

            if (!isHyper1) {
                if (blockSet->getEx1()->getSprite() != NULL) {
                    TakasuPoppo::cleanSprite(blockSet->getEx1());
                }
                
                if (blockSet->getEx2()->getSprite() != NULL) {
                    TakasuPoppo::cleanSprite(blockSet->getEx2());
                }
                
                if (blockSet->getEx3()->getSprite() != NULL) {
                    TakasuPoppo::cleanSprite(blockSet->getEx3());
                }
                
                if (blockSet->getEx4() && blockSet->getEx4() != NULL &&
                    blockSet->getEx4()->getSprite() != NULL) {
                    TakasuPoppo::cleanSprite(blockSet->getEx4());
                }
                if (blockSet->getEx5() && blockSet->getEx5() != NULL &&
                    blockSet->getEx5()->getSprite() != NULL) {
                    TakasuPoppo::cleanSprite(blockSet->getEx5());
                }
            }
        }
    }
    toDestroyArray->removeAllObjects();
}

void TakasuPoppo::afterClean() {
    CCObject *object;
    CCARRAY_FOREACH_REVERSE(colorArray, object) {
        TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
        if (exObj->getID() == 7 && exObj->getCoordination().y != 0) {
            CCObject *object2;
            CCARRAY_FOREACH_REVERSE(colorArray, object2) {
                TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(object2);
                if (exObj2->getCoordination().x == exObj->getCoordination().x &&
                    exObj2->getCoordination().y < exObj->getCoordination().y &&
                    exObj2->getID() != 7) {
                    int blocksAway = exObj->getCoordination().y - exObj2->getCoordination().y;
                    CCSprite *toMoveSprite =  exObj2->getSprite();
                    toMoveSprite->runAction(CCMoveBy::create(movingSpeed * blocksAway, ccp(0, - 90 * blocksAway)));
                    TakasuPoppo::swapColorID(exObj, exObj2);
                    exObj->setControlTrigger(!exObj->getControlTrigger());
                    exObj2->setControlTrigger(!exObj2->getControlTrigger());
                    break;
                }
            }
        }
    }    
}

void TakasuPoppo::changeID(CCNode *sender, void* data) {
    TPObjectExtension *exObj = (TPObjectExtension*)data;
    exObj->setID(7);
}

void TakasuPoppo::cleanHyperBlockA(TPBlockSet *blockSet) {

}

void TakasuPoppo::cleanSprite(TPObjectExtension *exObj) {
    exObj->setBlockType(0);
    CCSprite *exSprite = exObj->getSprite();
    exSprite->runAction(CCSequence::create(
                                           CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::spriteChange),
                                                                (void*)exObj),
                                           CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::changeID),
                                                                (void*)exObj),
                                           CCDelayTime::create(CLEAN_DELAY),
                                           CCRemoveSelf::create(), NULL));
    
}