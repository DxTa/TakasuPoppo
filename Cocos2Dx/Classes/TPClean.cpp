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
    createB = false;
    if (toDestroyArray->count() != 0) {
        
        
        CCARRAY_FOREACH(toDestroyArray, object) {            
            bool hyperA = false;
            bool hyperB = false;
            TPBlockSet *blockSet = dynamic_cast<TPBlockSet*>(object);
            if (blockSet->getType() == "hyperBlockC") {
                TakasuPoppo::cleanHyperBlockC(blockSet->getEx1());
            } else {
                hintCounter = 3;
                TakasuPoppo::plusAllComboCounter();
                // update current block set
                currentBlockSet = blockSet->getBlocksArray();
                
                //===============================
                
                if(blockSet->getEx3() != NULL)
                {
                    score = score + (int)(ComboScoreRequired * increasedScore * SCORE_THREE * doubleScore);
                }
                if(blockSet->getEx4() != NULL && blockSet->getEx4()->getID() != 7)
                {
                    score = score + (int)(ComboScoreRequired * increasedScore * SCORE_FOUR * doubleScore);
                    hyperA = true;
                }
                if(blockSet->getEx5() != NULL)
                {
                    score =score + (int)(ComboScoreRequired * increasedScore * SCORE_FIVE *doubleScore);
                    hyperA = false;
                    hyperB = true;
                }
                
                if (isValidEx(blockSet->getEx1())){
                    TakasuPoppo::cleanOneBlock(blockSet->getEx1());
                }
                
                if (isValidEx(blockSet->getEx2())){
                    if((!hyperA && !hyperB) || checkSwipe(blockSet)->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE)
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
                
                if(checkSwipe(blockSet)->getBlockType() == 13)
                {
                    createSpecialBlock(checkSwipe(blockSet), HBB_BLOCK_TYPE);
                }
                
                if(checkSwipe(blockSet)->getBlockType() >= 20)
                {
                    hyperA = false;
                    if (checkSwipe(blockSet)->getBlockType() == 21) {
                        cleanA(checkSwipe(blockSet));
                    }
                    if (checkSwipe(blockSet)->getBlockType() == 22) {
                        cleanB(checkSwipe(blockSet));
                    }
                    if(checkSwipe(blockSet)->getBlockType() == 26)
                        isCleanMB1 = true;
                    if(checkSwipe(blockSet)->getBlockType() == 27)
                        isCleanMB2 = true;
                    if(checkSwipe(blockSet)->getBlockType() == 28)
                        isCleanMB3 = true;
                    checkSwipe(blockSet)->setBlockType(13);

                }
                else if (checkSwipe(blockSet)->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE && hyperA)
                {
                    if(checkSwipe(blockSet)->getBlockType() == MOVED_HBA_BLOCK_TYPE)
                        cleanA(checkSwipe(blockSet));
                    if(checkSwipe(blockSet)->getBlockType() == MOVED_HBB_BLOCK_TYPE)
                        cleanB(checkSwipe(blockSet));
                    if(checkSwipe(blockSet)->getBlockType() == MB1_BLOCK_TYPE + 10)
                        isCleanMB1 = true;
                    if(checkSwipe(blockSet)->getBlockType() == MB2_BLOCK_TYPE + 10)
                        isCleanMB2 = true;
                    if(checkSwipe(blockSet)->getBlockType() == MB3_BLOCK_TYPE + 10)
                        isCleanMB3 = true;
                    createSpecialBlock(checkSwipe(blockSet), HBA_BLOCK_TYPE);
                    hyperA = false;
                    hyperB = false;
                }
                else if(hyperA)
                {
                    createSpecialBlock(blockSet->getEx2(), HBA_BLOCK_TYPE);
                    hyperA = false;
                    hyperB = false;
                }
                else if (checkSwipe(blockSet)->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE && hyperB)
                {
                    if(checkSwipe(blockSet)->getBlockType() == MOVED_HBA_BLOCK_TYPE)
                        cleanA(checkSwipe(blockSet));
                    if(checkSwipe(blockSet)->getBlockType() == MOVED_HBB_BLOCK_TYPE)
                        cleanB(checkSwipe(blockSet));
                    if(checkSwipe(blockSet)->getBlockType() == MB1_BLOCK_TYPE + 10)
                        isCleanMB1 = true;
                    if(checkSwipe(blockSet)->getBlockType() == MB2_BLOCK_TYPE + 10)
                        isCleanMB2 = true;
                    if(checkSwipe(blockSet)->getBlockType() == MB3_BLOCK_TYPE + 10)
                        isCleanMB3 = true;
                    
                    createSpecialBlock(checkSwipe(blockSet), HBB_BLOCK_TYPE);
                    hyperA = false;
                    hyperB = false;
                }
                else if(hyperB)
                {
                    createSpecialBlock(blockSet->getEx2(), HBB_BLOCK_TYPE);
                    hyperB = false;
                    hyperA = false;

                }
                else {
                    cleanOneBlock(checkSwipe(blockSet));
                }
                currentBlockSet = NULL;
            }
        }
    }
    // ===================== create    hyperB ===============

    CCObject* ox;
    CCARRAY_FOREACH(toDestroyArray, ox)
    {
        TPBlockSet *ex = dynamic_cast<TPBlockSet*>(ox);
        if(ex->getEx1() != NULL && ex->getEx1()->getBlockType() != 1 && ex->getEx1()->getBlockType() != 2 && ex->getEx1()->getBlockType() != 3 && ex->getEx1()->getBlockType() != 6 && ex->getEx1()->getBlockType() != 7 && ex->getEx1()->getBlockType() != 8)
            cleanOneBlock(ex->getEx1());
        if(ex->getEx2() != NULL && ex->getEx2()->getBlockType() != 1 && ex->getEx2()->getBlockType() != 2 && ex->getEx2()->getBlockType() != 3 && ex->getEx2()->getBlockType() != 6 && ex->getEx2()->getBlockType() != 7 && ex->getEx2()->getBlockType() != 8)
            cleanOneBlock(ex->getEx2());
        if(ex->getEx3() != NULL && ex->getEx3()->getBlockType() != 1 && ex->getEx3()->getBlockType() != 2 && ex->getEx3()->getBlockType() != 3 && ex->getEx3()->getBlockType() != 6 && ex->getEx3()->getBlockType() != 7 && ex->getEx3()->getBlockType() != 8)
            cleanOneBlock(ex->getEx3());
        if(ex->getEx4() != NULL && ex->getEx4()->getBlockType() != 1 && ex->getEx4()->getBlockType() != 2 && ex->getEx4()->getBlockType() != 3 && ex->getEx4()->getBlockType() != 6 && ex->getEx4()->getBlockType() != 7 && ex->getEx4()->getBlockType() != 8)
            cleanOneBlock(ex->getEx4());
        if(ex->getEx5() != NULL && ex->getEx5()->getBlockType() != 1 && ex->getEx5()->getBlockType() != 2 && ex->getEx5()->getBlockType() != 3 && ex->getEx5()->getBlockType() != 6 && ex->getEx5()->getBlockType() != 7 && ex->getEx5()->getBlockType() != 8)
            cleanOneBlock(ex->getEx5());
        
        if(ex->getEx6() != NULL && ex->getEx6()->getBlockType() != 1 && ex->getEx6()->getBlockType() != 2 && ex->getEx6()->getBlockType() != 3 && ex->getEx6()->getBlockType() != 6 && ex->getEx6()->getBlockType() != 7 && ex->getEx6()->getBlockType() != 8)
            cleanOneBlock(ex->getEx6());
        if(ex->getEx7() != NULL && ex->getEx7()->getBlockType() != 1 && ex->getEx7()->getBlockType() != 2 && ex->getEx7()->getBlockType() != 3 && ex->getEx7()->getBlockType() != 6 && ex->getEx7()->getBlockType() != 7 && ex->getEx7()->getBlockType() != 8)
            cleanOneBlock(ex->getEx7());
        

    }
    //=======================================================
    

    toDestroyArray->removeAllObjects();
    
}


void TakasuPoppo::afterClean(){
    // when it run to afterClean, all block has ben clean and remove it from toDestroyArray, so we set isHBCinBlockSet = false
    isHBCinBlockSet = false;
    
    CCObject *object;
    CCARRAY_FOREACH_REVERSE(colorArray, object) {
        TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
        if (exObj != NULL && exObj->getID() == 7 && exObj->getCoordination().y != 0) {

            CCObject *object2;
            CCARRAY_FOREACH_REVERSE(colorArray, object2) {
                TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(object2);
                if (exObj2 != NULL && exObj2->getCoordination().x == exObj->getCoordination().x &&
                    exObj2->getCoordination().y < exObj->getCoordination().y &&
                    exObj2->getID() != 7 && exObj2->getSprite() && exObj2->getSprite() != NULL) {
                    int blocksAway = exObj->getCoordination().y - exObj2->getCoordination().y;
                    CCSprite *toMoveSprite =  exObj2->getSprite();

                    TakasuPoppo::swapColorID(exObj, exObj2);
                    exObj2->setControlTrigger(false);
                    toMoveSprite->runAction(CCSequence::create(
                                                               CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable),(void*)exObj2),
                                                               CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable),(void*)exObj),
                                                               CCMoveBy::create(movingSpeed * blocksAway, ccp(0, - 90 * blocksAway)),
                                                               CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable),(void*)exObj2),
                                                               CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable),(void*)exObj), NULL));
  
                    exObj2->setControlTrigger(false);
                    break;
                }
            }
            exObj->setControlTrigger(true);
        }
    }
//    toDestroyArray->removeAllObjects();
}

void TakasuPoppo::changeID(CCNode *sender, void* data) {
    TPObjectExtension *exObj = (TPObjectExtension*)data;
    exObj->setID(7);
    
    // change block type
    exObj->setBlockType(NORMAL_BLOCK_TYPE);
}

void TakasuPoppo::cleanSprite(TPObjectExtension *exObj) {
    score =score + (int)(ComboScoreRequired * increasedScore * ONE_BLOCK *doubleScore);
    CCSprite *exSprite = exObj->getSprite();
    if (exSprite != NULL && exObj != NULL && exObj->getID() != 7 && exObj->getSprite() != NULL) {
        exSprite->stopActionByTag(1210);
        CCPoint *spritePosition = new CCPoint(exObj->getPosition());
        exSprite->runAction(CCSequence::create(
                CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::changeID), (void*)exObj),
                CCDelayTime::create(CLEAN_DELAY),
                CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::popAnimation), (void*)spritePosition),
//                CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::removeSprite), (void*)exSprite),
                                               CCRemoveSelf::create(true),
                                               NULL));
        

    }
}

void TakasuPoppo::removeSprite(CCNode* sender, void* data)
{
    if(data != NULL)
    {
        CCSprite *exSprite = (CCSprite*)data;
        this->removeChild(exSprite);
    }
}

/*
 |======================================|
 |         clean Hyper BLock A          |
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
    if (gameTimer > 0) {
        if (isInCurrentBlockSet(exObj)  == false) {
            TakasuPoppo::plusAllComboCounter();
        }

    }
    else{
        
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
    
    
    exObj->setBlockType(NORMAL_BLOCK_TYPE);
    
    TPObjectExtension *bExObj = TakasuPoppo::coorToExObj(bPoint);
    TPObjectExtension *cExObj = TakasuPoppo::coorToExObj(cPoint);
    TPObjectExtension *dExObj = TakasuPoppo::coorToExObj(dPoint);
    TPObjectExtension *eExObj = TakasuPoppo::coorToExObj(ePoint);
    TPObjectExtension *gExObj = TakasuPoppo::coorToExObj(gPoint);
    TPObjectExtension *hExObj = TakasuPoppo::coorToExObj(hPoint);
    TPObjectExtension *iExObj = TakasuPoppo::coorToExObj(iPoint);
    TPObjectExtension *kExObj = TakasuPoppo::coorToExObj(kPoint);
    
    if (bExObj != NULL && bExObj->getSprite() != NULL && bExObj->getID() != 7 && bExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(bExObj);
    }
    
    if (cExObj != NULL && cExObj->getSprite() != NULL && cExObj->getID() != 7 && cExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(cExObj);
    }
    
    if (dExObj != NULL && dExObj->getSprite() != NULL && dExObj->getID() != 7 && dExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(dExObj);
    }
    
    if (eExObj != NULL && eExObj->getSprite() != NULL && eExObj->getID() != 7 && eExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(eExObj);
    }
    
    if (gExObj != NULL && gExObj->getSprite() != NULL && gExObj->getID() != 7 && gExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(gExObj);
    }
    
    if (hExObj != NULL && hExObj->getSprite() != NULL && hExObj->getID() != 7 && hExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(hExObj);
    }
    
    if (iExObj != NULL && iExObj->getSprite() != NULL && iExObj->getID() != 7 && iExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(iExObj);
    }
    
    if (kExObj != NULL && kExObj->getSprite() != NULL && kExObj->getID() != 7 && kExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(kExObj);
    }
    
    if (exObj->getSprite() != NULL || exObj->getID() != 7) TakasuPoppo::cleanSprite(exObj);
    
}

void TakasuPoppo::cleanHyperBlockB(TPObjectExtension* exObj) {
    
    int x = exObj->getCoordination().x;
    int y = exObj->getCoordination().y;
    
    if (isInCurrentBlockSet(exObj) == false) {
        
        exObj->setBlockType(NORMAL_BLOCK_TYPE);
        
        TakasuPoppo::plusAllComboCounter();
    }
    else { // this Hyper Block B is in the current Block, so dont plus the counter
        
        if (isInFeverTime == true) {
            exObj->setBlockType(HBA_BLOCK_TYPE);
        }
        else {
            exObj->setBlockType(NORMAL_BLOCK_TYPE);
        }
    }
    
    for (int i = 6; i >= 0 ; i--) {
        TPObjectExtension* block1 = TakasuPoppo::coorToExObj(ccp(x, i));
        if (i != y && block1->getSprite() != NULL && block1->getID() != 7 && block1->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) TakasuPoppo::cleanOneBlock(block1);
        
        TPObjectExtension* block2 = TakasuPoppo::coorToExObj(ccp(i, y));
        if (i!=x && block2->getSprite() != NULL && block2->getID() != 7 && block2->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) TakasuPoppo::cleanOneBlock(block2);
        
    }
    

    if (exObj->getID() != 7 || exObj->getSprite() != NULL) TakasuPoppo::cleanSprite(exObj);
    
}

void TakasuPoppo::cleanOneBlock(TPObjectExtension* exobj){
    switch (exobj->getBlockType()) {
        case HBA_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockA(exobj);
            break;
            
        case HBB_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
            
        case HBC_BLOCK_TYPE:
//            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
//                TakasuPoppo::cleanHyperBlockC(exobj);
            break;
        case MB1_BLOCK_TYPE:
            if (gameTimer >= 0) {
                isCleanMB1 = true;
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
            }
            else TakasuPoppo::cleanSprite(exobj);
            
            break;
        case MB2_BLOCK_TYPE:
            if (gameTimer >= 0) {
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
                isCleanMB2 = true;
                isExistMB2 = false;

            } else {
                TakasuPoppo::cleanSprite(exobj);
            }

            break;
        case MB3_BLOCK_TYPE:
            isCleanMB3 = true;
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;
        case MOVED_HBA_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockA(exobj);
            break;
        case MOVED_HBB_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
        case NORMAL_BLOCK_TYPE:
            if (isInFeverTime == true) {
                // in fever time and this block is in currentBlockSet, we clean blocks around like Hyper Block A
                if (isInCurrentBlockSet(exobj)) {
                    currentBlockSet->removeObject(exobj);
                    if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                        TakasuPoppo::cleanHyperBlockA(exobj);

                }
                else {
                    if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
                }
                
            } else {
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
            }
            
            break;
        case MOVED_NORMAL_BLOCK_TYPE + 10:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
            
        case (MOVED_HBA_BLOCK_TYPE + 10):
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
        case (MOVED_HBB_BLOCK_TYPE + 10):
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;

            
        default:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;
    }
}

void TakasuPoppo::makeBlockToBeHBC(TPObjectExtension *exObj){
    exObj->setBlockType(HBC_BLOCK_TYPE);
    exObj->setID(8);

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
    animate->setTag(1210);
    exObj->getSprite()->runAction(animate);
}

bool TakasuPoppo::isInCurrentBlockSet(TPObjectExtension *exObj){
    // if this Hyper Block is not in current block, plus 1 to combo and fever Counter
    CCObject* obj;
    if (currentBlockSet != NULL && currentBlockSet->count() > 0) {
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
//    if (ex != NULL && (checkCreateHyperB(ex->getCoordination(), ex->getID()) || ex->getBlockType() == 13)) {
//        return false;
//    }
    if(ex != NULL && ex->getID() != 7 && ex->getSprite() && ex->getSprite() != NULL && ex->getBlockType() < MOVED_NORMAL_BLOCK_TYPE)
            return true;
    else    return false;
}

void TakasuPoppo::cleanA(TPObjectExtension* exObj){
    
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
    
    for (int i = 6; i >= 0 ; i--) {
        TPObjectExtension* block1 = TakasuPoppo::coorToExObj(ccp(x, i));
        if (i != y && block1->getSprite() != NULL && block1->getID() != 7 && block1->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) TakasuPoppo::cleanOneBlock(block1);

        TPObjectExtension* block2 = TakasuPoppo::coorToExObj(ccp(i, y));
        if (i!=x && block2->getSprite() != NULL && block2->getID() != 7 && block2->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) TakasuPoppo::cleanOneBlock(block2);
        
    }

}

//==============================clean Block ===========
// call when time out
void TakasuPoppo::cleanHyperBlockA(CCNode* sender, void* data){
    
    TPObjectExtension* exObj = (TPObjectExtension*)data;
    plusAllComboCounter();
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
    
    
    exObj->setBlockType(NORMAL_BLOCK_TYPE);
    
    TPObjectExtension *bExObj = TakasuPoppo::coorToExObj(bPoint);
    TPObjectExtension *cExObj = TakasuPoppo::coorToExObj(cPoint);
    TPObjectExtension *dExObj = TakasuPoppo::coorToExObj(dPoint);
    TPObjectExtension *eExObj = TakasuPoppo::coorToExObj(ePoint);
    TPObjectExtension *gExObj = TakasuPoppo::coorToExObj(gPoint);
    TPObjectExtension *hExObj = TakasuPoppo::coorToExObj(hPoint);
    TPObjectExtension *iExObj = TakasuPoppo::coorToExObj(iPoint);
    TPObjectExtension *kExObj = TakasuPoppo::coorToExObj(kPoint);
    
    if (bExObj != NULL && bExObj->getSprite() != NULL && bExObj->getID() != 7 && bExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(bExObj);
    }
    
    if (cExObj != NULL && cExObj->getSprite() != NULL && cExObj->getID() != 7 && cExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(cExObj);
    }
    
    if (dExObj != NULL && dExObj->getSprite() != NULL && dExObj->getID() != 7 && dExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(dExObj);
    }
    
    if (eExObj != NULL && eExObj->getSprite() != NULL && eExObj->getID() != 7 && eExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(eExObj);
    }
    
    if (gExObj != NULL && gExObj->getSprite() != NULL && gExObj->getID() != 7 && gExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(gExObj);
    }
    
    if (hExObj != NULL && hExObj->getSprite() != NULL && hExObj->getID() != 7 && hExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(hExObj);
    }
    
    if (iExObj != NULL && iExObj->getSprite() != NULL && iExObj->getID() != 7 && iExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(iExObj);
    }
    
    if (kExObj != NULL && kExObj->getSprite() != NULL && kExObj->getID() != 7 && kExObj->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) {
        
        TakasuPoppo::cleanOneBlock(kExObj);
    }
    
    if (exObj->getSprite() != NULL || exObj->getID() != 7) TakasuPoppo::cleanSprite(exObj);
    
}

void TakasuPoppo::cleanHyperBlockB(CCNode* sender, void* data) {
    TPObjectExtension* exObj = (TPObjectExtension*)data;
    
    int x = exObj->getCoordination().x;
    int y = exObj->getCoordination().y;

    TakasuPoppo::plusAllComboCounter();

    if (isInFeverTime == true) {
        exObj->setBlockType(HBA_BLOCK_TYPE);
    }
    else {
        exObj->setBlockType(NORMAL_BLOCK_TYPE);
    }
    
    for (int i = 0; i < 7; i++) {
        TPObjectExtension* block1 = TakasuPoppo::coorToExObj(ccp(x, i));
        if (block1->getSprite() != NULL && block1->getID() != 7  && block1->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) TakasuPoppo::cleanOneBlock(block1);
        
        TPObjectExtension* block2 = TakasuPoppo::coorToExObj(ccp(i, y));
        if (block2->getSprite() != NULL && block2->getID() != 7 && block2->getBlockType() < MOVED_NORMAL_BLOCK_TYPE) TakasuPoppo::cleanOneBlock(block2);
    }

    if (exObj->getID() != 7 || exObj->getSprite() != NULL) TakasuPoppo::cleanSprite(exObj);
}


void TakasuPoppo::cleanHyperBlockC(CCNode* sender, void* data) {
    TPObjectExtension* exObj = (TPObjectExtension*)data;
    plusAllComboCounter();
    
    exObj->setBlockType(NORMAL_BLOCK_TYPE);
    // random an ID and clean all block with this ID
    exObj->getSprite()->stopActionByTag(1210);
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
            CCSprite *cloneSprite = CCSprite::createWithTexture(poppoTexture);
            
            cloneSprite->setPosition(block->getSprite()->getPosition());
            cloneSprite->setZOrder(500);
            this->addChild(cloneSprite);
            
            cloneSprite->runAction(CCSequence::create(CCScaleTo::create(HBC_SCALE_DELAY, 1.5f),
                                                      CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::cleanOneBlock),(void*)block),
                                                      CCRemoveSelf::create(true),
                                                      NULL));
            
        }
    }
    
    isHBCinBlockSet = true;

}

void TakasuPoppo::cleanHyperBlockC(TPObjectExtension* exObj){
    plusAllComboCounter();
    
    isHBCinBlockSet = true;
    exObj->setBlockType(NORMAL_BLOCK_TYPE);
    // random an ID and clean all block with this ID
    exObj->getSprite()->stopActionByTag(1210);
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
            CCSprite *cloneSprite = CCSprite::createWithTexture(poppoTexture);
            
            cloneSprite->setPosition(block->getSprite()->getPosition());
            cloneSprite->setZOrder(500);
            this->addChild(cloneSprite);
            
            cloneSprite->runAction(CCSequence::create(CCScaleTo::create(HBC_SCALE_DELAY, 1.5f),
                                                      CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::cleanOneBlock),(void*)block),
                                                      CCRemoveSelf::create(true),
                                                      NULL));
            
        }
    }
    


}
void TakasuPoppo::cleanOneBlock(cocos2d::CCNode *sender, void *data){
    TPObjectExtension *exobj = (TPObjectExtension*)data;
    switch (exobj->getBlockType()) {
        case HBA_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockA(exobj);
            break;
            
        case HBB_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
            
        case HBC_BLOCK_TYPE:
            //            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
            //                TakasuPoppo::cleanHyperBlockC(exobj);
            break;
        case MB1_BLOCK_TYPE:
            if (gameTimer >= 0) {
                isCleanMB1 = true;
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
            }
            else TakasuPoppo::cleanSprite(exobj);
            
            break;
        case MB2_BLOCK_TYPE:
            if (gameTimer >= 0) {
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
                isCleanMB2 = true;
                isExistMB2 = false;
                
            } else {
                TakasuPoppo::cleanSprite(exobj);
            }
            
            break;
        case MB3_BLOCK_TYPE:
            isCleanMB3 = true;
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;
        case MOVED_HBA_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockA(exobj);
            break;
        case MOVED_HBB_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
        case NORMAL_BLOCK_TYPE:
            if (isInFeverTime == true) {
                // in fever time and this block is in currentBlockSet, we clean blocks around like Hyper Block A
                if (isInCurrentBlockSet(exobj)) {
                    currentBlockSet->removeObject(exobj);
                    if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                        TakasuPoppo::cleanHyperBlockA(exobj);
                    
                }
                else {
                    if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                        TakasuPoppo::cleanSprite(exobj);
                }
                
            } else {
                if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                    TakasuPoppo::cleanSprite(exobj);
            }
            
            break;
        case MOVED_NORMAL_BLOCK_TYPE + 10:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
            
        case (MOVED_HBA_BLOCK_TYPE + 10):
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
        case (MOVED_HBB_BLOCK_TYPE + 10):
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanHyperBlockB(exobj);
            break;
            
            
        default:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;
    }
}

float TakasuPoppo::setCleanDelay(){
    if (isHBCinBlockSet) {
        logicDelayTime = AFTER_CLEAN_FALL_TIME*6 + GENERATE_FALL_TIME*6 + SWAP_TIME*2 + CLEAN_DELAY + POP_ANIMATION_DELAY + HBC_SCALE_DELAY;
        return (HBC_SCALE_DELAY + CLEAN_DELAY + POP_ANIMATION_DELAY);
    } else {
        logicDelayTime = AFTER_CLEAN_FALL_TIME*6 + GENERATE_FALL_TIME*6 + SWAP_TIME*2 + CLEAN_DELAY + POP_ANIMATION_DELAY;
        return (CLEAN_DELAY + POP_ANIMATION_DELAY);
    }
}

void TakasuPoppo::plusAllComboCounter(){
    // count the combo to generate hyper block
    hbcComboCounter += 1;
    if (hbcComboTimer <= 0) hbcComboTimer = HBC_COMBO_MAXTIME * increaseComboTimes;

    // count the combo for the Fever Time
    feverCounter += 1;
    
    //count the combo for the Gauge Bar
    gaugeComboCounter += 1;
    if (gaugePeriod != GAUGE_PERIOD) {
        gaugePeriod = GAUGE_PERIOD;
    }
    
    // count the really combo
    ComboCounter += 1;
    if (ComboTimer != 3) ComboTimer = 3;
    
}

void TakasuPoppo::setFalseControl()
{
    
//    move = false;
//    swape = false;
////    this->setTouchEnabled(false);
//    runningAfter =true;
//    swipeUp = false;
//    swipeDown = false;
//    swipeRight = false;
//    swipeLeft = false;
}
void TakasuPoppo::setControl()
{
//    this->setTouchEnabled(true);
//    move = false;
//    swape = false;
//    runningAfter = false;
}

void TakasuPoppo::deleteMainSprite()
{
    mainSprite = NULL;
}

bool TakasuPoppo::checkHorMatch(CCPoint coor , int type)
{
    if(type == 8)
        return false;
    int x = coor.x;
    int y = coor.y;
    
    CCPoint ePoint = ccp(x, y - 1);
    CCPoint hPoint = ccp(x, y - 2);
    CCPoint oPoint = ccp(x, y + 1);
    CCPoint qPoint = ccp(x, y + 2);
    TPObjectExtension *eExObj = TakasuPoppo::coorToExObj(ePoint);
    TPObjectExtension *hExObj = TakasuPoppo::coorToExObj(hPoint);
    TPObjectExtension *oExObj = TakasuPoppo::coorToExObj(oPoint);
    TPObjectExtension *qExObj = TakasuPoppo::coorToExObj(qPoint);
    
    if (eExObj != NULL && eExObj->getID() == type &&
        hExObj != NULL && hExObj->getID() == type) {
        return true;
    }
    
    if (oExObj != NULL && oExObj->getID() == type &&
        qExObj != NULL && qExObj->getID() == type) {
        return true;
    }
    
    if (oExObj != NULL && oExObj->getID() == type &&
        eExObj != NULL && eExObj->getID() == type) {
        return true;
    }
    return false;
}

bool TakasuPoppo::checkVerMatch(CCPoint coor , int type)
{
    if(type == 8)
        return false;
    int x = coor.x;
    int y = coor.y;
    
    CCPoint bPoint = ccp(x + 1, y);
    CCPoint cPoint = ccp(x + 2, y);
    CCPoint mPoint = ccp(x - 2, y);
    CCPoint nPoint = ccp(x - 1, y);
    
    TPObjectExtension *bExObj = TakasuPoppo::coorToExObj(bPoint);
    TPObjectExtension *cExObj = TakasuPoppo::coorToExObj(cPoint);
    TPObjectExtension *mExObj = TakasuPoppo::coorToExObj(mPoint);
    TPObjectExtension *nExObj = TakasuPoppo::coorToExObj(nPoint);

    
    if (bExObj != NULL && bExObj->getID() == type &&
        cExObj != NULL && cExObj->getID() == type) {
        return true;
    }
    
    if (nExObj != NULL && nExObj->getID() == type &&
        mExObj != NULL && mExObj->getID() == type) {
        return true;
    }
    
    if (nExObj != NULL && nExObj->getID() == type &&
        bExObj != NULL && bExObj->getID() == type) {
        return true;
    }
    return false;
}

bool TakasuPoppo::checkCreateHyperB(CCPoint coor , int type)
{
    if(checkVerMatch(coor, type) && checkHorMatch(coor, type))
    {
        CCLOG( "True Cmnr");
        return true;
    }
    return false;
}