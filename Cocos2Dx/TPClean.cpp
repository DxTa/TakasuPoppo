//
//  TPClean.cpp
//  Cocos2Dx
//
//  Created by Ace on 2013/07/01.
//
//
#define COMBO_HBA_COUNT  2
#define COMBO_HBB_COUNT  3
#define COMBO_HBC_COUNT  100


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
            
            if (comboCounter == COMBO_HBA_COUNT || comboCounter == COMBO_HBB_COUNT || comboCounter == COMBO_HBC_COUNT) {
                bool isCreateHyperBlock = false;
                
                if (blockSet->getEx1()->getBlockType() == 0) {
                    
                    isCreateHyperBlock = true;
                } else {
                    
                    if (blockSet->getEx1() && blockSet->getEx1() != NULL &&
                        blockSet->getEx1()->getID() != 7 &&
                        blockSet->getEx1()->getSprite() != NULL){
                        TakasuPoppo::cleanOneBlock(blockSet->getEx1());
                    }
                    
                }
                
                // clean from Ex2 - Ex5
                // we clean Ex2 - Ex5 first and after that, make Hyper Block if possible
                if (blockSet->getEx2() && blockSet->getEx2() != NULL &&
                    blockSet->getEx2()->getID() != 7 &&
                    blockSet->getEx2()->getSprite() != NULL){
                    
                    TakasuPoppo::cleanOneBlock(blockSet->getEx2());
                }
                
                if (blockSet->getEx3() && blockSet->getEx3() != NULL &&
                    blockSet->getEx3()->getID() != 7 &&
                    blockSet->getEx3()->getSprite() != NULL) {
                    
                    TakasuPoppo::cleanOneBlock(blockSet->getEx3());
                }
                
                if (blockSet->getEx4() && blockSet->getEx4() != NULL &&
                    blockSet->getEx4()->getID() != 7 &&
                    blockSet->getEx4()->getSprite() != NULL) {
                    
                    TakasuPoppo::cleanOneBlock(blockSet->getEx4());
                }
                
                if (blockSet->getEx5() && blockSet->getEx5() != NULL &&
                    blockSet->getEx5()->getID() != 7 &&
                    blockSet->getEx5()->getSprite() != NULL) {
                    
                    TakasuPoppo::cleanOneBlock(blockSet->getEx5());
                }
                
                // create Hyper block if possible (it have not been cleaned,..)
                if (isCreateHyperBlock == true) { 
                    if (blockSet->getEx1() != NULL && blockSet->getEx1()->getSprite() != NULL &&
                        blockSet->getEx1()->getID() != 7) { // neu block 1 da bi clean thi ko the tao Hyper Block
                        switch (comboCounter) {
                            case COMBO_HBA_COUNT:
                                TakasuPoppo::makeBlockToBeHBA(blockSet->getEx1());
                                break;
                                
                            case COMBO_HBB_COUNT:
                                TakasuPoppo::makeBlockToBeHBB(blockSet->getEx1());
                                break;
                                
                            case COMBO_HBC_COUNT:
                                TakasuPoppo::makeBlockToBeHBC(blockSet->getEx1());
                                break;
                                
                                
                            default:
                                break;
                        }
                        
                    }
                    
                }

            } else { // comboCounter is not HBA or HBB or HBC, we clean block by block
                
                if (blockSet->getEx1() != NULL && blockSet->getEx1()->getID() != 7 &&
                    blockSet->getEx1()->getSprite() != NULL){
                    TakasuPoppo::cleanOneBlock(blockSet->getEx1());
                }
                
                if (blockSet->getEx2() != NULL && blockSet->getEx2()->getID() != 7 &&
                    blockSet->getEx2()->getSprite() != NULL){
                    
                    TakasuPoppo::cleanOneBlock(blockSet->getEx2());
                }
                
                if (blockSet->getEx3() != NULL && blockSet->getEx3()->getID() != 7 &&
                    blockSet->getEx3()->getSprite() != NULL) {
                    
                    TakasuPoppo::cleanOneBlock(blockSet->getEx3());
                }
                
                if (blockSet->getEx4() && blockSet->getEx4() != NULL &&
                    blockSet->getEx4()->getID() != 7 &&
                    blockSet->getEx4()->getSprite() != NULL) {
                    
                    TakasuPoppo::cleanOneBlock(blockSet->getEx4());
                }
                
                if (blockSet->getEx5() && blockSet->getEx5() != NULL &&
                    blockSet->getEx5()->getID() != 7 &&
                    blockSet->getEx5()->getSprite() != NULL) {
                    
                    TakasuPoppo::cleanOneBlock(blockSet->getEx5());
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
                    
// this is the place that cause the bug "can not move the block"
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


void TakasuPoppo::cleanHyperBlockA(TPObjectExtension* exObj){
    
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
    

    exObj->setBlockType(0);
    
    TPObjectExtension *bExObj = TakasuPoppo::coorToExObj(bPoint);
    TPObjectExtension *cExObj = TakasuPoppo::coorToExObj(cPoint);
    TPObjectExtension *dExObj = TakasuPoppo::coorToExObj(dPoint);
    TPObjectExtension *eExObj = TakasuPoppo::coorToExObj(ePoint);
    TPObjectExtension *gExObj = TakasuPoppo::coorToExObj(gPoint);
    TPObjectExtension *hExObj = TakasuPoppo::coorToExObj(hPoint);
    TPObjectExtension *iExObj = TakasuPoppo::coorToExObj(iPoint);
    TPObjectExtension *kExObj = TakasuPoppo::coorToExObj(kPoint);
    
    if (bExObj != NULL && bExObj->getSprite() != NULL && bExObj->getID() != 7) {
    
        TakasuPoppo::cleanOneBlock(bExObj);
    }
    
    if (cExObj != NULL && cExObj->getSprite() != NULL && cExObj->getID() != 7) {

        TakasuPoppo::cleanOneBlock(cExObj);
    }
    
    if (dExObj != NULL && dExObj->getSprite() != NULL && dExObj->getID() != 7) {
    
        TakasuPoppo::cleanOneBlock(dExObj);
    }
    
    if (eExObj != NULL && eExObj->getSprite() != NULL && eExObj->getID() != 7) {
        
        TakasuPoppo::cleanOneBlock(eExObj);
    }
    
    if (gExObj != NULL && gExObj->getSprite() != NULL && gExObj->getID() != 7) {
    
        TakasuPoppo::cleanOneBlock(gExObj);
    }
    
    if (hExObj != NULL && hExObj->getSprite() != NULL && hExObj->getID() != 7) {
        
        TakasuPoppo::cleanOneBlock(hExObj);
    }
    
    if (iExObj != NULL && iExObj->getSprite() != NULL && iExObj->getID() != 7) {
        
        TakasuPoppo::cleanOneBlock(iExObj);
    }
    
    if (kExObj != NULL && kExObj->getSprite() != NULL && kExObj->getID() != 7) {
        
        TakasuPoppo::cleanOneBlock(kExObj);
    }
    
    if (exObj->getSprite() != NULL || exObj->getID() != 7) TakasuPoppo::cleanSprite(exObj);
    
}

void TakasuPoppo::cleanHyperBlockB(TPObjectExtension* exObj) {
    exObj->setBlockType(0);
    int x = exObj->getCoordination().x;
    int y = exObj->getCoordination().y;
    
    for (int i = 0; i < 7; i++) {
        TPObjectExtension* block1 = TakasuPoppo::coorToExObj(ccp(x, i));
        if (block1->getSprite() != NULL && block1->getID() != 7) TakasuPoppo::cleanOneBlock(block1);
        
        TPObjectExtension* block2 = TakasuPoppo::coorToExObj(ccp(i, y));
        if (block2->getSprite() != NULL && block2->getID() != 7) TakasuPoppo::cleanOneBlock(block2);
        
//        TakasuPoppo::cleanOneBlock(TakasuPoppo::coorToExObj(ccp(x, i)));
//        TakasuPoppo::cleanOneBlock(TakasuPoppo::coorToExObj(ccp(i, y)));
    }
    
    
    if (exObj->getID() != 7 || exObj->getSprite() != NULL) TakasuPoppo::cleanSprite(exObj);

}

void TakasuPoppo::cleanHyperBlockC(TPObjectExtension* exObj) {
    
    CCObject* obj;
    exObj->setBlockType(0);
    CCARRAY_FOREACH(colorArray, obj){
        TPObjectExtension* block = dynamic_cast<TPObjectExtension* >(obj);
        if (block != NULL && block->getID() == exObj->getID() &&
            block->getID() != 7 && exObj->getSprite() != NULL) {
            TakasuPoppo::cleanOneBlock(block);
        }
    }
    
}

void TakasuPoppo::cleanOneBlock(TPObjectExtension* exobj){
    switch (exobj->getBlockType()) {
        case 1:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockA(exobj);
            break;
            
        case 2:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;

        case 3:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockC(exobj);
            break;
            
        case 0:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;

            
        default:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;
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

void TakasuPoppo::makeBlockToBeHBB(TPObjectExtension* exObj){
    exObj->setBlockType(2);
    
    
    // change controlable
    exObj->setControlTrigger(true);
    
    // change sprite when the block be hyper
    int imageId = exObj->getID() + 1;
    CCImage *poppoB = new CCImage;
    char imagePath[15];
    sprintf(imagePath, "Poppo%dB2.png", imageId);
    poppoB->initWithImageFile(imagePath);
    CCTexture2D *poppoTexture = new CCTexture2D;
    poppoTexture->initWithImage(poppoB);
    CCSprite *poppoSprite = exObj->getSprite();
    poppoSprite->setTexture(poppoTexture);
    exObj->setSprite(poppoSprite);

}
void TakasuPoppo::makeBlockToBeHBC(TPObjectExtension *exobj){
    
}

//void TakasuPoppo::cleanBlockSetNormal(TPBlockSet *blockSet){
//    if (blockSet->getEx1() && blockSet->getEx1() != NULL && blockSet->getEx1()->getSprite() != NULL) {
//        TakasuPoppo::cleanSprite(blockSet->getEx1());
//    }
//    
//    if (blockSet->getEx2() && blockSet->getEx2() != NULL &&blockSet->getEx2()->getSprite() != NULL) {
//        TakasuPoppo::cleanSprite(blockSet->getEx2());
//    }
//    
//    if (blockSet->getEx3() && blockSet->getEx3() != NULL &&blockSet->getEx3()->getSprite() != NULL) {
//        TakasuPoppo::cleanSprite(blockSet->getEx3());
//    }
//    
//    if (blockSet->getEx4() && blockSet->getEx4() != NULL &&
//        blockSet->getEx4()->getSprite() != NULL) {
//        TakasuPoppo::cleanSprite(blockSet->getEx4());
//    }
//    if (blockSet->getEx5() && blockSet->getEx5() != NULL &&
//        blockSet->getEx5()->getSprite() != NULL) {
//        TakasuPoppo::cleanSprite(blockSet->getEx5());
//    }

//}