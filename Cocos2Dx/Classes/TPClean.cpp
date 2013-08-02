//
//  TPClean.cpp
//  Cocos2Dx
//
//  Created by Ace on 2013/07/01.
//
//
#define SCORE_THREE  200
#define SCORE_FOUR  200
#define SCORE_FIVE 600
#define ONE_BLOCK 100

#include "TakasuPoppo.h"
#include "TPBlockSet.h"
void TakasuPoppo::cleanBlocks() {
    CCObject *object;
    if (toDestroyArray->count() != 0) {
        CCARRAY_FOREACH(toDestroyArray, object) {
            bool hyperA = false;
            bool hyperB = false;
            hintCounter = 3;
            TPBlockSet *blockSet = dynamic_cast<TPBlockSet*>(object);
            
            TakasuPoppo::plusAllComboCounter();
            // update current block set
            currentBlockSet = blockSet->getBlocksArray();
            
            //===============================
            if(blockSet->getEx3() != NULL)
            {
                score = score + (int)(increasedScore * SCORE_THREE * doubleScore);
                //hyperA = true;
            }
            if(blockSet->getEx4() != NULL)
            {
                score = score + (int)(increasedScore * SCORE_FOUR * doubleScore);
                hyperA = true;
            }
            if(blockSet->getEx5() != NULL)
            {
                score =score + (int)(increasedScore * SCORE_FIVE *doubleScore);
                hyperA = false;
                hyperB = true;
            }
            
            if (isValidEx(blockSet->getEx1())){
                TakasuPoppo::cleanOneBlock(blockSet->getEx1());
            }
            
            if (isValidEx(blockSet->getEx2())){
                if((!hyperA && !hyperB) || checkSwipe(blockSet)->getBlockType() >= 10)
                    TakasuPoppo::cleanOneBlock(blockSet->getEx2());
            }
            
            if (isValidEx(blockSet->getEx3())) {
                TakasuPoppo::cleanOneBlock(blockSet->getEx3());
            }
            
            if (isValidEx(blockSet->getEx4())) {
                TakasuPoppo::cleanOneBlock(blockSet->getEx4());
            }
            
            if (isValidEx(blockSet->getEx5())) {
                TakasuPoppo::cleanOneBlock(blockSet->getEx5());
            }
            
            if (isValidEx(blockSet->getEx6())) {
                TakasuPoppo::cleanOneBlock(blockSet->getEx6());
                
            }
            
            if (isValidEx(blockSet->getEx7())) {
                TakasuPoppo::cleanOneBlock(blockSet->getEx5());
            }
            
            if (checkSwipe(blockSet)->getBlockType() >= 10 && hyperA)
            {
                if(checkSwipe(blockSet)->getBlockType() == 11)
                    cleanA(checkSwipe(blockSet));
                if(checkSwipe(blockSet)->getBlockType() == 12)
                    cleanB(checkSwipe(blockSet));
                makeBlockToBeHBA(checkSwipe(blockSet));
                
            }
            else if(hyperA)
                makeBlockToBeHBA(blockSet->getEx2());
            else if (checkSwipe(blockSet)->getBlockType() >= 10 && hyperB)
            {
                if(checkSwipe(blockSet)->getBlockType() == 11)
                    cleanA(checkSwipe(blockSet));
                if(checkSwipe(blockSet)->getBlockType() == 12)
                    cleanB(checkSwipe(blockSet));
                makeBlockToBeHBB(checkSwipe(blockSet));
            }
            else if(hyperB)
                makeBlockToBeHBB(blockSet->getEx2());
            else {
                TakasuPoppo::cleanOneBlock(checkSwipe(blockSet));
            }
            // returm currentBlockSet to the default status
            currentBlockSet = NULL;
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
    score =score + (int)(increasedScore * ONE_BLOCK *doubleScore);
    CCSprite *exSprite = exObj->getSprite();
    if (exSprite != NULL) {
        exSprite->runAction(CCSequence::create(CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::changeID),(void*)exObj),CCDelayTime::create(CLEAN_DELAY),
                                               CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::popAnimation),
                                                                    (void*)exObj),
                                               CCRemoveSelf::create(), NULL));
        

    }
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
    
    // if this Hyper Block is not in current block, plus 1 to combo and fever Counter
    if (isInCurrentBlockSet(exObj)  == false) {
        TakasuPoppo::plusAllComboCounter();
    }
    
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
    
    if (bExObj != NULL && bExObj->getSprite() != NULL && bExObj->getID() != 7 && bExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(bExObj);
    }
    
    if (cExObj != NULL && cExObj->getSprite() != NULL && cExObj->getID() != 7 && cExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(cExObj);
    }
    
    if (dExObj != NULL && dExObj->getSprite() != NULL && dExObj->getID() != 7 && dExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(dExObj);
    }
    
    if (eExObj != NULL && eExObj->getSprite() != NULL && eExObj->getID() != 7 && eExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(eExObj);
    }
    
    if (gExObj != NULL && gExObj->getSprite() != NULL && gExObj->getID() != 7 && gExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(gExObj);
    }
    
    if (hExObj != NULL && hExObj->getSprite() != NULL && hExObj->getID() != 7 && hExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(hExObj);
    }
    
    if (iExObj != NULL && iExObj->getSprite() != NULL && iExObj->getID() != 7 && iExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(iExObj);
    }
    
    if (kExObj != NULL && kExObj->getSprite() != NULL && kExObj->getID() != 7 && kExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(kExObj);
    }
    
    if (exObj->getSprite() != NULL || exObj->getID() != 7) TakasuPoppo::cleanSprite(exObj);
    
}

void TakasuPoppo::cleanHyperBlockB(TPObjectExtension* exObj) {
    
    int x = exObj->getCoordination().x;
    int y = exObj->getCoordination().y;
        
    if (isInCurrentBlockSet(exObj) == false) {
        
        TakasuPoppo::plusAllComboCounter();
        
        exObj->setBlockType(0);
        for (int i = 0; i < 7; i++) {
            TPObjectExtension* block1 = TakasuPoppo::coorToExObj(ccp(x, i));
            if (block1->getSprite() != NULL && block1->getID() != 7 && block1->getBlockType() < 10) TakasuPoppo::cleanOneBlock(block1);
            
            TPObjectExtension* block2 = TakasuPoppo::coorToExObj(ccp(i, y));
            if (block2->getSprite() != NULL && block2->getID() != 7 && block2->getBlockType() < 10) TakasuPoppo::cleanOneBlock(block2);
            
        }
    }
    else { // this Hyper Block B is in the current Block, so dont plus the counter
        
        if (isInFeverTime == true) {
            exObj->setBlockType(1);
        }
        else {
            exObj->setBlockType(0);
        }
        
        for (int i = 0; i < 7; i++) {
            TPObjectExtension* block1 = TakasuPoppo::coorToExObj(ccp(x, i));
            if (block1->getSprite() != NULL && block1->getID() != 7  && block1->getBlockType() < 10) TakasuPoppo::cleanOneBlock(block1);
            
            TPObjectExtension* block2 = TakasuPoppo::coorToExObj(ccp(i, y));
            if (block2->getSprite() != NULL && block2->getID() != 7 && block2->getBlockType() < 10) TakasuPoppo::cleanOneBlock(block2);
            
        }

    }
    if (exObj->getID() != 7 || exObj->getSprite() != NULL) TakasuPoppo::cleanSprite(exObj);
    
}

//void TakasuPoppo::cleanHyperBlockC(TPObjectExtension* exObj) {
//    CCObject* obj;
//    
//    // if this Hyper Block is not in current block, plus 1 to combo and fever Counter
//    if (isInCurrentBlockSet(exObj) == false) {
//        // count the combo to generate hyper block
//        comboCounter += 1;
//        
//        // count the combo for the Fever Time
//        feverCounter += 1;
//        //count the combo for the Gauge Bar
//        gaugeComboCounter += 1;
//
//        exObj->setBlockType(0);
//        CCARRAY_FOREACH(colorArray, obj){
//            TPObjectExtension* block = dynamic_cast<TPObjectExtension* >(obj);
//            if (block != NULL && block->getID() == exObj->getID() &&
//                block->getID() != 7 && block->getSprite() != NULL) {
//                TakasuPoppo::cleanOneBlock(block);
//            }
//        }
//    }
//    else {
//        if (isInFeverTime == true) {
//            exObj->setBlockType(1);
//        }
//        else {
//            exObj->setBlockType(0);
//        }
//        
//        CCARRAY_FOREACH(colorArray, obj){
//            TPObjectExtension* block = dynamic_cast<TPObjectExtension* >(obj);
//            if (block != NULL && block->getID() == exObj->getID() &&
//                block->getID() != 7 && block->getSprite() != NULL) {
//                TakasuPoppo::cleanOneBlock(block);
//            }
//        }
//
//    }
//}

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
//            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
//                TakasuPoppo::cleanHyperBlockC(exobj);
            break;
        case 6:
            isCleanMB1 = true;
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;
        case 7:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            isCleanMB2 = true;
            isExistMB2 = false;

            break;
        case 8:
            isCleanMB3 = true;
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;
        case 11:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockA(exobj);
            break;
        case 12:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
        case 0:
            if (isInFeverTime == true) {
                // in fever time and this block is in currentBlockSet, we clean blocks around like Hyper Block A
                if (isInCurrentBlockSet(exobj)) {
                    currentBlockSet->removeObject(exobj);
                    if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                        TakasuPoppo::cleanHyperBlockA(exobj);

                }
                else {
                    TakasuPoppo::cleanSprite(exobj);
                }
                
            } else {
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
            }
            
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
    if(exObj->getID() != 7)
    {
        // change sprite when the block be hyper
        int imageId = exObj->getID() + 1;
        CCImage *poppoB = new CCImage;
        string str = static_cast<ostringstream*>( &(ostringstream() << imageId) )->str();
        str = "Poppo" + str + "HyperA.png";
        poppoB->initWithImageFile(str.c_str());
        CCTexture2D *poppoTexture = new CCTexture2D;
        poppoTexture->initWithImage(poppoB);
        CCSprite *poppoSprite = exObj->getSprite();
        poppoSprite->setTexture(poppoTexture);
        exObj->setSprite(poppoSprite);
    }
    
}

void TakasuPoppo::makeBlockToBeHBB(TPObjectExtension* exObj){
    exObj->setBlockType(2);
    // change controlable
    exObj->setControlTrigger(true);
    if(exObj->getID() != 7)
    {
        // change sprite when the block be hyper
        int imageId = exObj->getID() + 1;
        CCImage *poppoB = new CCImage;
        string str = static_cast<ostringstream*>( &(ostringstream() << imageId) )->str();
        str = "Poppo" + str + "HyperB.png";
        poppoB->initWithImageFile(str.c_str());
        CCTexture2D *poppoTexture = new CCTexture2D;
        poppoTexture->initWithImage(poppoB);
        CCSprite *poppoSprite = exObj->getSprite();
        poppoSprite->setTexture(poppoTexture);
        exObj->setSprite(poppoSprite);
    }    
}
void TakasuPoppo::makeBlockToBeHBC(TPObjectExtension *exObj){
    exObj->setBlockType(3);
    exObj->setID(8);
    // change controlable
    exObj->setControlTrigger(true);
    
    CCAnimation *animation = CCAnimation::create();
    for (int i = 1; i < 8; i++) {
        char fileName[15] = {0};
        sprintf(fileName, "Poppo%dA.png", i);
        animation->addSpriteFrameWithFileName(fileName);
        
    }
    animation->setDelayPerUnit(0.05f);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(MAXFLOAT);
    CCAnimate* animate = CCAnimate::create(animation);
    //    animate->setTag(1210);
    
    exObj->getSprite()->runAction(animate);
}

bool TakasuPoppo::isInCurrentBlockSet(TPObjectExtension *exObj){
    // if this Hyper Block is not in current block, plus 1 to combo and fever Counter
    CCObject* obj;
    if (currentBlockSet != NULL && currentBlockSet->count() != 0) {
        CCARRAY_FOREACH(currentBlockSet, obj){
            if (obj != NULL ) {
                TPObjectExtension* block = dynamic_cast<TPObjectExtension*>(obj);
                if (block->getGid() == exObj->getGid()) {
                    return true;
                }
                
            }
        }        
    }
    
    return false;
    
}

bool TakasuPoppo::isValidEx(TPObjectExtension * ex){
    if(ex != NULL && ex->getID() != 7 && ex->getSprite() != NULL && ex->getBlockType() < 10)
            return true;
    else    return false;
}

void TakasuPoppo::cleanA(TPObjectExtension* exObj){
    
    // if this Hyper Block is not in current block, plus 1 to combo and fever Counter
    if (isInCurrentBlockSet(exObj)  == false) {
            TakasuPoppo::plusAllComboCounter();
    }
    
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
    
    
    //exObj->setBlockType(0);
    
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
}

void TakasuPoppo::cleanB(TPObjectExtension* exObj) {
    
    int x = exObj->getCoordination().x;
    int y = exObj->getCoordination().y;
    
    TakasuPoppo::plusAllComboCounter();
    
    for (int i = 6; i >= 0 ; i--) {
        TPObjectExtension* block1 = TakasuPoppo::coorToExObj(ccp(x, i));
        if (i != y && block1->getSprite() != NULL && block1->getID() != 7 && block1->getBlockType() < 10) TakasuPoppo::cleanOneBlock(block1);

        TPObjectExtension* block2 = TakasuPoppo::coorToExObj(ccp(i, y));
        if (i!=x && block2->getSprite() != NULL && block2->getID() != 7 && block2->getBlockType() < 10) TakasuPoppo::cleanOneBlock(block2);
        
    }

}

//==============================clean Block ===========
void TakasuPoppo::cleanHyperBlockA(CCNode* sender, void* data){
    
    // if this Hyper Block is not in current block, plus 1 to combo and fever Counter
    TPObjectExtension* exObj = (TPObjectExtension*)data;
    if (isInCurrentBlockSet(exObj)  == false) {
        
        TakasuPoppo::plusAllComboCounter();
    }
    
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
    
    if (bExObj != NULL && bExObj->getSprite() != NULL && bExObj->getID() != 7 && bExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(bExObj);
    }
    
    if (cExObj != NULL && cExObj->getSprite() != NULL && cExObj->getID() != 7 && cExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(cExObj);
    }
    
    if (dExObj != NULL && dExObj->getSprite() != NULL && dExObj->getID() != 7 && dExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(dExObj);
    }
    
    if (eExObj != NULL && eExObj->getSprite() != NULL && eExObj->getID() != 7 && eExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(eExObj);
    }
    
    if (gExObj != NULL && gExObj->getSprite() != NULL && gExObj->getID() != 7 && gExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(gExObj);
    }
    
    if (hExObj != NULL && hExObj->getSprite() != NULL && hExObj->getID() != 7 && hExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(hExObj);
    }
    
    if (iExObj != NULL && iExObj->getSprite() != NULL && iExObj->getID() != 7 && iExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(iExObj);
    }
    
    if (kExObj != NULL && kExObj->getSprite() != NULL && kExObj->getID() != 7 && kExObj->getBlockType() < 10) {
        
        TakasuPoppo::cleanOneBlock(kExObj);
    }
    
    if (exObj->getSprite() != NULL || exObj->getID() != 7) TakasuPoppo::cleanSprite(exObj);
    
}

void TakasuPoppo::cleanHyperBlockB(CCNode* sender, void* data) {
    TPObjectExtension* exObj = (TPObjectExtension*)data;
    
    int x = exObj->getCoordination().x;
    int y = exObj->getCoordination().y;
    
    if (isInCurrentBlockSet(exObj) == false) {
        
        TakasuPoppo::plusAllComboCounter();
        
        exObj->setBlockType(0);
        for (int i = 0; i < 7; i++) {
            TPObjectExtension* block1 = TakasuPoppo::coorToExObj(ccp(x, i));
            if (block1->getSprite() != NULL && block1->getID() != 7 && block1->getBlockType() < 10) TakasuPoppo::cleanOneBlock(block1);
            
            TPObjectExtension* block2 = TakasuPoppo::coorToExObj(ccp(i, y));
            if (block2->getSprite() != NULL && block2->getID() != 7 && block2->getBlockType() < 10) TakasuPoppo::cleanOneBlock(block2);
            
        }
    }
    else { // this Hyper Block B is in the current Block, so dont plus the counter
        
        if (isInFeverTime == true) {
            exObj->setBlockType(1);
        }
        else {
            exObj->setBlockType(0);
        }
        
        for (int i = 0; i < 7; i++) {
            TPObjectExtension* block1 = TakasuPoppo::coorToExObj(ccp(x, i));
            if (block1->getSprite() != NULL && block1->getID() != 7  && block1->getBlockType() < 10) TakasuPoppo::cleanOneBlock(block1);
            
            TPObjectExtension* block2 = TakasuPoppo::coorToExObj(ccp(i, y));
            if (block2->getSprite() != NULL && block2->getID() != 7 && block2->getBlockType() < 10) TakasuPoppo::cleanOneBlock(block2);
            
        }
        
    }
    if (exObj->getID() != 7 || exObj->getSprite() != NULL) TakasuPoppo::cleanSprite(exObj);
    
}

void TakasuPoppo::cleanHyperBlockC(CCNode* sender, void* data) {
    TPObjectExtension* exObj = (TPObjectExtension*)data;
    
    TakasuPoppo::plusAllComboCounter();
    
    exObj->setBlockType(0);
    // random an ID and clean all block with this ID
    exObj->getSprite()->stopAllActions();
    int a = rand() % 7;
    exObj->setID(a);
    int imageId = exObj->getID() + 1;
    CCImage *poppoC = new CCImage;
    string str = static_cast<ostringstream*>( &(ostringstream() << imageId) )->str();
    str = "Poppo" + str + "A.png";
    poppoC->initWithImageFile(str.c_str());
    CCTexture2D *poppoTexture = new CCTexture2D;
    poppoTexture->initWithImage(poppoC);
    CCSprite *poppoSprite = exObj->getSprite();
    poppoSprite->setTexture(poppoTexture);
    exObj->setSprite(poppoSprite);
    
    CCObject* obj;
    CCARRAY_FOREACH(colorArray, obj){
        TPObjectExtension* block = dynamic_cast<TPObjectExtension* >(obj);
        if (block != NULL && block->getID() == exObj->getID() &&
            block->getID() != 7 && block->getSprite() != NULL) {
            CCSprite *exSprite = block->getSprite();
            exSprite->runAction(CCSequence::create(CCDelayTime::create(0.3f), CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::scaleHyperBlockC),(void*)block),CCDelayTime::create(0.75f), CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::newCleanOneBlock),(void*)block), NULL));
        }
    }
}

// For new instance of Clean Hyper Block C with scale animation

void TakasuPoppo::scaleHyperBlockC(CCNode *sender, void* data){
    TPObjectExtension *exObj = (TPObjectExtension*)data;
    exObj->getSprite()->runAction(CCScaleTo::create(0.1f, 1.2f));
}

void TakasuPoppo::cleanHyperBlockC(TPObjectExtension* exObj){
    
    TakasuPoppo::plusAllComboCounter();
    
    exObj->setBlockType(0);
    // random an ID and clean all block with this ID
    exObj->getSprite()->stopAllActions();
    int a = rand() % 7;
    exObj->setID(a);
    int imageId = exObj->getID() + 1;
    CCImage *poppoC = new CCImage;
    string str = static_cast<ostringstream*>( &(ostringstream() << imageId) )->str();
    str = "Poppo" + str + "A.png";
    poppoC->initWithImageFile(str.c_str());
    CCTexture2D *poppoTexture = new CCTexture2D;
    poppoTexture->initWithImage(poppoC);
    CCSprite *poppoSprite = exObj->getSprite();
    poppoSprite->setTexture(poppoTexture);
    exObj->setSprite(poppoSprite);
    
    CCObject* obj;
    CCARRAY_FOREACH(colorArray, obj){
        TPObjectExtension* block = dynamic_cast<TPObjectExtension* >(obj);
        if (block != NULL && block->getID() == exObj->getID() &&
            block->getID() != 7 && block->getSprite() != NULL) {
            CCSprite *exSprite = block->getSprite();
            exSprite->runAction(CCSequence::create(CCDelayTime::create(0.1f), CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::scaleHyperBlockC),(void*)block),CCDelayTime::create(0.2f), CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::newCleanOneBlock),(void*)block), NULL));
        }
    }
}

void TakasuPoppo::newCleanOneBlock(cocos2d::CCNode *sender, void *data){
    
    TPObjectExtension *exobj = (TPObjectExtension*)data;
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
//            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
//                TakasuPoppo::cleanHyperBlockC(exobj);
            break;
        case 6:
            isCleanMB1 = true;
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;
        case 7:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            isCleanMB2 = true;
            isExistMB2 = false;
            
            break;
        case 8:
            isCleanMB3 = true;
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;

        case 11:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockA(exobj);
            break;
        case 12:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
        case 0:
            if (isInFeverTime == true) {
                // in fever time and this block is in currentBlockSet, we clean blocks around like Hyper Block A
                if (isInCurrentBlockSet(exobj)) {
                    currentBlockSet->removeObject(exobj);
                    if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                        TakasuPoppo::cleanHyperBlockA(exobj);
                    
                }
                else {
                    TakasuPoppo::cleanSprite(exobj);
                }
                
            } else {
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
            }
            
            break;
            
            
        default:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;
    }
    this->unschedule(schedule_selector(TakasuPoppo::smartGeneration));
    inCleaning = true;
    this->runAction(CCSequence::create(
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::cleanBlocks)),
                                       CCDelayTime::create(CLEAN_DELAY),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::afterClean)),
                                       CCCallFunc::create(this, callfunc_selector(TakasuPoppo::scheduleGenerate)),
                                       NULL));
//    this->schedule(schedule_selector(TakasuPoppo::fallingBoolSwitch), FALL_TIME);
}

void TakasuPoppo::plusAllComboCounter(){
    // count the combo to generate hyper block
    hbcComboCounter += 1;
    if (hbcComboTimer <= 0) hbcComboTimer = 5 * increaseComboTimes;

    // count the combo for the Fever Time
    feverCounter += 1;
    
    //count the combo for the Gauge Bar
    gaugeComboCounter += 1;
    
    // count the really combo
    ComboCounter += 1;
    if (ComboTimer != 3) ComboTimer = 3;
    
}
