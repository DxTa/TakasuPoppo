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
            
            // count the combo to generate hyper block
            comboCounter += 1;
            
            // true if blockSet has a hyperblock A
            bool isHyper1 = false;
            if ((blockSet->getEx1() && blockSet->getEx1()->getBlockType() == 1) ||
                (blockSet->getEx2() && blockSet->getEx2()->getBlockType() == 1) ||
                (blockSet->getEx3() && blockSet->getEx3()->getBlockType() == 1) ||
                (blockSet->getEx4() && blockSet->getEx4()->getBlockType() == 1) ||
                (blockSet->getEx5() && blockSet->getEx5()->getBlockType() == 1) ) isHyper1 = true;

            if (existHyperBlockA == true) {
                
                if (isHyper1) {
                    TakasuPoppo::cleanHyperBlockA(blockSet);
                } else {
                    
                    TakasuPoppo::cleanBlockSetNormal(blockSet);
                }
                
            }
            
            else {
                
                if (comboCounter < 2) {
                    if (isHyper1) {
                        TakasuPoppo::cleanHyperBlockA(blockSet);
                    } else {
                        
                        TakasuPoppo::cleanBlockSetNormal(blockSet);
                    }
                    
                } else { // counterCombo >= 2 -> create new Hyper Bock A at Ex1
                    
                    if (isHyper1) {
                        TakasuPoppo::cleanHyperBlockA(blockSet);
                    } else {
                        
                        if (blockSet->getEx1()->getSprite() != NULL) {
                            existHyperBlockA = true;
                            TakasuPoppo::makeBlockToBeHBA(blockSet->getEx1());
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
            } // end of if else (existHyperBlockA == true)
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
                    
                    
                    //                    exObj->setControlTrigger(!exObj->getControlTrigger());
                    exObj2->setControlTrigger(!exObj2->getControlTrigger());
                    exObj->setControlTrigger(true);
                    //                    exObj2->setControlTrigger(true);
                    
                    break;
                }
            }
        }
    }
}

void TakasuPoppo::changeID(CCNode *sender, void* data) {
    TPObjectExtension *exObj = (TPObjectExtension*)data;
    exObj->setID(7);
    
    // change block type
    exObj->setBlockType(0);
}


void TakasuPoppo::cleanHyperBlockA(TPBlockSet *blockSet) {
    
    // clean block around
    
    if (blockSet->getEx1()->getBlockType() == 1 && blockSet->getEx1()->getSprite() != NULL) {
        findToCleanBlockAroundHBA(blockSet->getEx1());
        
    }
    if (blockSet->getEx2()->getBlockType() == 1 && blockSet->getEx2()->getSprite() != NULL) {
        findToCleanBlockAroundHBA(blockSet->getEx2());
        
    }
    if (blockSet->getEx3()->getBlockType() == 1 && blockSet->getEx3()->getSprite() != NULL) {
        findToCleanBlockAroundHBA(blockSet->getEx3());
        
    }
    if (blockSet->getEx4() && blockSet->getEx4() != NULL &&
        blockSet->getEx4()->getSprite() != NULL && blockSet->getEx4()->getBlockType() == 1) {
        findToCleanBlockAroundHBA(blockSet->getEx4());
        
    }
    if (blockSet->getEx5() && blockSet->getEx5() != NULL &&
        blockSet->getEx5()->getSprite() != NULL && blockSet->getEx5()->getBlockType() == 1) {
        findToCleanBlockAroundHBA(blockSet->getEx5());
        
    }
    
    // clean blockSet
    TakasuPoppo::cleanBlockSetNormal(blockSet);
}

void TakasuPoppo::cleanHyperBlockB(TPObjectExtension *ex) {
    
}

void TakasuPoppo::cleanHyperBlockC(TPObjectExtension *exo) {
    
    
}

void TakasuPoppo::cleanSprite(TPObjectExtension *exObj) {
    
    
    CCSprite *exSprite = exObj->getSprite();
    exSprite->runAction(CCSequence::create(
                                           CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::spriteChange),
                                                                (void*)exObj),
                                           CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::changeID),
                                                                (void*)exObj),
                                           CCDelayTime::create(CLEAN_DELAY),
                                           CCRemoveSelf::create(), NULL));
    
}



/*
 |======================================|
 |      findToCleanBlockAroundHB        |
 |======================================|
 |    |     -2  -1   0  +1  +2  +3      |
 |----|---------------------------------|
 | -3 |                                 |
 | -2 |                                 |
 | -1 |          k   b  c               |
 |  0 |          i  [a] d               |
 | +1 |          h   g  e               |
 | +2 |                                 |
 |======================================|
 */


void TakasuPoppo::findToCleanBlockAroundHBA(TPObjectExtension* exObj){
    
    CCPoint aPoint = exObj->getCoordination();
    int x = aPoint.x;
    int y = aPoint.y;
    
    CCPoint bPoint = ccp( x, y - 1);
    CCPoint cPoint = ccp(x + 1, y - 1);
    CCPoint dPoint = ccp(x + 1, y);
    CCPoint ePoint = ccp(x + 1, y + 1);
    CCPoint gPoint = ccp(x, y + 1);
    CCPoint hPoint = ccp(x - 1, y + 1);
    CCPoint iPoint = ccp(x - 1, y);
    CCPoint kPoint = ccp(x - 1, y - 1);
    
    TakasuPoppo::cleanSprite(exObj);
    exObj->setBlockType(0);
    
    TPObjectExtension *bExObj = TakasuPoppo::coorToExObj(bPoint);
    TPObjectExtension *cExObj = TakasuPoppo::coorToExObj(cPoint);
    TPObjectExtension *dExObj = TakasuPoppo::coorToExObj(dPoint);
    TPObjectExtension *eExObj = TakasuPoppo::coorToExObj(ePoint);
    TPObjectExtension *gExObj = TakasuPoppo::coorToExObj(gPoint);
    TPObjectExtension *hExObj = TakasuPoppo::coorToExObj(hPoint);
    TPObjectExtension *iExObj = TakasuPoppo::coorToExObj(iPoint);
    TPObjectExtension *kExObj = TakasuPoppo::coorToExObj(kPoint);
    
    if (bExObj != NULL && bExObj->getID() != 7) {
        
        
        if (bExObj->getBlockType() == 1) {

            findToCleanBlockAroundHBA(bExObj);
        }
        else{
            TakasuPoppo::cleanSprite(bExObj);
        }
        
    }
    if (cExObj != NULL && cExObj->getID() != 7) {

        if (cExObj->getBlockType() == 1) {

            findToCleanBlockAroundHBA(cExObj);
        }
        else{
            TakasuPoppo::cleanSprite(cExObj);
        }
        
        
    }
    if (dExObj != NULL && dExObj->getID() != 7) {
        
        if (dExObj->getBlockType() == 1) {

            findToCleanBlockAroundHBA(dExObj);
        }
        else{
            TakasuPoppo::cleanSprite(dExObj);
        }
        
        
    }
    if (eExObj != NULL && eExObj->getID() != 7) {
        
        if (eExObj->getBlockType() == 1) {

            findToCleanBlockAroundHBA(eExObj);
        } else{
            TakasuPoppo::cleanSprite(eExObj);
        }
        
        
    }
    if (gExObj != NULL && gExObj->getID() != 7) {
        
        
        if (gExObj->getBlockType() == 1) {

            findToCleanBlockAroundHBA(gExObj);
        }
        else{
            TakasuPoppo::cleanSprite(gExObj);
        }
        
        
    }
    if (hExObj != NULL && hExObj->getID() != 7) {
        
        
        if (hExObj->getBlockType() == 1) {

            findToCleanBlockAroundHBA(hExObj);
        }
        else {
            TakasuPoppo::cleanSprite(hExObj);
        }
        

    }
    if (iExObj != NULL && iExObj->getID() != 7) {
        
        
        if (iExObj->getBlockType() == 1) {

            findToCleanBlockAroundHBA(iExObj);
        }else {
            TakasuPoppo::cleanSprite(iExObj);
        }
        
        
    }
    if (kExObj != NULL && kExObj->getID() != 7) {
        
        
        if (kExObj->getBlockType() == 1) {

            findToCleanBlockAroundHBA(kExObj);
        } else {
            TakasuPoppo::cleanSprite(kExObj);
        }
        
        
    }
}

void TakasuPoppo::makeBlockToBeHBA(TPObjectExtension* exObj){
    exObj->setBlockType(1);
    
    
    // change controlable
    exObj->setControlTrigger(true);
    
    // change sprite when the block be hyper
    int imageId = exObj->getID() + 1;
    CCImage *poppoB = new CCImage;
    char imagePath[15];
    sprintf(imagePath, "Poppo%dB.png", imageId);
    poppoB->initWithImageFile(imagePath);
    CCTexture2D *poppoTexture = new CCTexture2D;
    poppoTexture->initWithImage(poppoB);
    CCSprite *poppoSprite = exObj->getSprite();
    poppoSprite->setTexture(poppoTexture);
    exObj->setSprite(poppoSprite);
    
}

void TakasuPoppo::cleanBlockSetNormal(TPBlockSet *blockSet){
    if (blockSet->getEx1() && blockSet->getEx1() != NULL && blockSet->getEx1()->getSprite() != NULL) {
        TakasuPoppo::cleanSprite(blockSet->getEx1());
    }
    
    if (blockSet->getEx2() && blockSet->getEx2() != NULL &&blockSet->getEx2()->getSprite() != NULL) {
        TakasuPoppo::cleanSprite(blockSet->getEx2());
    }
    
    if (blockSet->getEx3() && blockSet->getEx3() != NULL &&blockSet->getEx3()->getSprite() != NULL) {
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