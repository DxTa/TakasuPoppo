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
            
//            if (blockSet->getEx1() && blockSet->getEx1()->getBlockType() == 1) isHyper1 = true;
//            if (blockSet->getEx2() && blockSet->getEx2()->getBlockType() == 1) isHyper1 = true;           
//            if (blockSet->getEx3() && blockSet->getEx3()->getBlockType() == 1) isHyper1 = true;           
//            if (blockSet->getEx4() && blockSet->getEx4()->getBlockType() == 1) isHyper1 = true;     
//            if (blockSet->getEx5() && blockSet->getEx5()->getBlockType() == 1) isHyper1 = true;
//            
//            if (isHyper1) {
//                TakasuPoppo::cleanHyperBlockA(blockSet);
//            }
            
            if (!isHyper1) {
                if (blockSet->getEx1()->getSprite() != NULL) {
                    if (comboCounter != 4) {
                        TakasuPoppo::cleanSprite(blockSet->getEx1());
                    }
                    if (comboCounter == 4) {
                        blockSet->getEx1()->setBlockType(1);
                    }
//                    if (comboCounter == 5) {
//                        blockSet->getEx1()->setBlockType(2);
//                    }
//                    if (comboCounter == 8) {
//                        blockSet->getEx1()->setBlockType(3);
//                    }
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
                    //CCPoint movePos = exObj->getPosition();
                    CCSprite *toMoveSprite =  exObj2->getSprite();
                    //toMoveSprite->runAction(CCMoveTo::create(movingSpeed * blocksAway, movePos));
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
    TPObjectExtension *ex1U =
    TakasuPoppo::coorToExObj(ccp(blockSet->getEx1()->getCoordination().x,
                                 blockSet->getEx1()->getCoordination().y - 7));
    TPObjectExtension *ex1D =
    TakasuPoppo::coorToExObj(ccp(blockSet->getEx1()->getCoordination().x,
                                 blockSet->getEx1()->getCoordination().y + 7));
    TPObjectExtension *ex1L =
    TakasuPoppo::coorToExObj(ccp(blockSet->getEx1()->getCoordination().x - 1,
                                 blockSet->getEx1()->getCoordination().y));
    TPObjectExtension *ex1R =
    TakasuPoppo::coorToExObj(ccp(blockSet->getEx1()->getCoordination().x + 1,
                                 blockSet->getEx1()->getCoordination().y));
    
    TPObjectExtension *ex2U =
    TakasuPoppo::coorToExObj(ccp(blockSet->getEx2()->getCoordination().x,
                                 blockSet->getEx2()->getCoordination().y - 7));
    TPObjectExtension *ex2D =
    TakasuPoppo::coorToExObj(ccp(blockSet->getEx2()->getCoordination().x,
                                 blockSet->getEx2()->getCoordination().y + 7));
    TPObjectExtension *ex2L =
    TakasuPoppo::coorToExObj(ccp(blockSet->getEx2()->getCoordination().x - 1,
                                 blockSet->getEx2()->getCoordination().y));
    TPObjectExtension *ex2R =
    TakasuPoppo::coorToExObj(ccp(blockSet->getEx2()->getCoordination().x + 1,
                                 blockSet->getEx2()->getCoordination().y));
    
    TPObjectExtension *ex3U =
    TakasuPoppo::coorToExObj(ccp(blockSet->getEx3()->getCoordination().x,
                                 blockSet->getEx3()->getCoordination().y - 7));
    TPObjectExtension *ex3D =
    TakasuPoppo::coorToExObj(ccp(blockSet->getEx3()->getCoordination().x,
                                 blockSet->getEx3()->getCoordination().y + 7));
    TPObjectExtension *ex3L =
    TakasuPoppo::coorToExObj(ccp(blockSet->getEx3()->getCoordination().x - 1,
                                 blockSet->getEx3()->getCoordination().y));
    TPObjectExtension *ex3R =
    TakasuPoppo::coorToExObj(ccp(blockSet->getEx3()->getCoordination().x + 1,
                                 blockSet->getEx3()->getCoordination().y));
    
    if (blockSet->getEx4() != NULL) {
        TPObjectExtension *ex4U =
        TakasuPoppo::coorToExObj(ccp(blockSet->getEx4()->getCoordination().x,
                                     blockSet->getEx4()->getCoordination().y - 7));
        TPObjectExtension *ex4D =
        TakasuPoppo::coorToExObj(ccp(blockSet->getEx4()->getCoordination().x,
                                     blockSet->getEx4()->getCoordination().y + 7));
        TPObjectExtension *ex4L =
        TakasuPoppo::coorToExObj(ccp(blockSet->getEx4()->getCoordination().x - 1,
                                     blockSet->getEx4()->getCoordination().y));
        TPObjectExtension *ex4R =
        TakasuPoppo::coorToExObj(ccp(blockSet->getEx4()->getCoordination().x + 1,
                                     blockSet->getEx4()->getCoordination().y));
        
        if (ex4U != NULL && ex4U->getID() != 7) TakasuPoppo::cleanSprite(ex4U);
        if (ex4D != NULL && ex4D->getID() != 7) TakasuPoppo::cleanSprite(ex4D);
        if (ex4L != NULL && ex4D->getID() != 7) TakasuPoppo::cleanSprite(ex4L);
        if (ex4R != NULL && ex4R->getID() != 7) TakasuPoppo::cleanSprite(ex4R);
    }
    
    if (blockSet->getEx5() != NULL) {
        TPObjectExtension *ex5U =
        TakasuPoppo::coorToExObj(ccp(blockSet->getEx5()->getCoordination().x,
                                     blockSet->getEx5()->getCoordination().y - 7));
        TPObjectExtension *ex5D =
        TakasuPoppo::coorToExObj(ccp(blockSet->getEx5()->getCoordination().x,
                                     blockSet->getEx5()->getCoordination().y + 7));
        TPObjectExtension *ex5L =
        TakasuPoppo::coorToExObj(ccp(blockSet->getEx5()->getCoordination().x - 1,
                                     blockSet->getEx5()->getCoordination().y));
        TPObjectExtension *ex5R =
        TakasuPoppo::coorToExObj(ccp(blockSet->getEx5()->getCoordination().x + 1,
                                     blockSet->getEx5()->getCoordination().y));
        
        if (ex5U != NULL && ex5U->getID() != 7) TakasuPoppo::cleanSprite(ex5U);
        if (ex5D != NULL && ex5D->getID() != 7) TakasuPoppo::cleanSprite(ex5D);
        if (ex5L != NULL && ex5D->getID() != 7) TakasuPoppo::cleanSprite(ex5L);
        if (ex5R != NULL && ex5R->getID() != 7) TakasuPoppo::cleanSprite(ex5R);
    }
    
    
    if (ex1U != NULL && ex1U->getID() != 7) TakasuPoppo::cleanSprite(ex1U);
    if (ex1D != NULL && ex1D->getID() != 7) TakasuPoppo::cleanSprite(ex1D);
    if (ex1L != NULL && ex1D->getID() != 7) TakasuPoppo::cleanSprite(ex1L);
    if (ex1R != NULL && ex1R->getID() != 7) TakasuPoppo::cleanSprite(ex1R);
    
    if (ex2U != NULL && ex2U->getID() != 7) TakasuPoppo::cleanSprite(ex2U);
    if (ex2D != NULL && ex2D->getID() != 7) TakasuPoppo::cleanSprite(ex2D);
    if (ex2L != NULL && ex2D->getID() != 7) TakasuPoppo::cleanSprite(ex2L);
    if (ex2R != NULL && ex2R->getID() != 7) TakasuPoppo::cleanSprite(ex2R);
    
    if (ex3U != NULL && ex3U->getID() != 7) TakasuPoppo::cleanSprite(ex3U);
    if (ex3D != NULL && ex3D->getID() != 7) TakasuPoppo::cleanSprite(ex3D);
    if (ex3L != NULL && ex3D->getID() != 7) TakasuPoppo::cleanSprite(ex3L);
    if (ex3R != NULL && ex3R->getID() != 7) TakasuPoppo::cleanSprite(ex3R);
}

void TakasuPoppo::cleanSprite(TPObjectExtension *exObj) {
    exObj->setBlockType(0);
    CCSprite *exSprite = exObj->getSprite();
    exSprite->runAction(CCSequence::create(
                                           CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::spriteChange),
                                                                (void*)exObj),
                                           CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::changeID),
                                                                (void*)exObj),
                                           CCDelayTime::create(0.3),
                                           CCRemoveSelf::create(), NULL));
    
}