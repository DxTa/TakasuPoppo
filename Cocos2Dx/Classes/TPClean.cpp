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
                
                if (checkSwipe(blockSet)->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE && hyperA)
                {
                    if(checkSwipe(blockSet)->getBlockType() == MOVED_HBA_BLOCK_TYPE)
                        cleanA(checkSwipe(blockSet));
                    if(checkSwipe(blockSet)->getBlockType() == MOVED_HBB_BLOCK_TYPE)
                        cleanB(checkSwipe(blockSet));
                    createSpecialBlock(checkSwipe(blockSet), HBA_BLOCK_TYPE);
                    hyperA = false;
                    hyperB = false;
                    //break;
                }
                else if(hyperA)
                {
                    createSpecialBlock(blockSet->getEx2(), HBA_BLOCK_TYPE);
                    hyperA = false;
                    hyperB = false;
                    //break;
                }
                else if (checkSwipe(blockSet)->getBlockType() >= MOVED_NORMAL_BLOCK_TYPE && hyperB)
                {
                    if(checkSwipe(blockSet)->getBlockType() == MOVED_HBA_BLOCK_TYPE)
                        cleanA(checkSwipe(blockSet));
                    if(checkSwipe(blockSet)->getBlockType() == MOVED_HBB_BLOCK_TYPE)
                        cleanB(checkSwipe(blockSet));
                    createSpecialBlock(checkSwipe(blockSet), HBB_BLOCK_TYPE);
                    hyperA = false;
                    hyperB = false;
                    //break;
                }
                else if(hyperB)
                {
                    createSpecialBlock(blockSet->getEx2(), HBB_BLOCK_TYPE);
                    hyperB = false;
                    hyperA = false;
                   // break;

                }
                else {
                    TakasuPoppo::cleanOneBlock(checkSwipe(blockSet));
                }
                currentBlockSet = NULL;
                
            }
            
        }
    }
    toDestroyArray->removeAllObjects();
}


void TakasuPoppo::afterClean(){
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
                    if(checkAllRunning())
                    {
                        CCLOG("a sprite is running.....");
                        CCBool* boolrun = new CCBool(true);
                        TakasuPoppo::swapColorID(exObj, exObj2);
                        toMoveSprite->runAction(CCSequence::create(
                                                                   CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::afterCleanRunning), (void*)boolrun),
                                                                   CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable),(void*)exObj2),
                                                                   CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable),(void*)exObj),
                                                                   CCDelayTime::create(SWAP_TIME * 2),
                                                                   CCMoveBy::create(movingSpeed * blocksAway, ccp(0, - 90 * blocksAway)),
                                                                   CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::releaseAfterRunning), (void*)boolrun),
                                                                   CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable),(void*)exObj2),
                                                                   CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable),(void*)exObj), NULL));
                        break;

                    }
                    else{
                        CCBool* boolrun = new CCBool(true);
                        TakasuPoppo::swapColorID(exObj, exObj2);
                        toMoveSprite->runAction(CCSequence::create(
                                                                   CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::afterCleanRunning), (void*)boolrun),
                                                                   CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable),(void*)exObj2),
                                                                   CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setFalseControlable),(void*)exObj),
                                                                   CCMoveBy::create(movingSpeed * blocksAway, ccp(0, - 90 * blocksAway)),
                                                                   CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::releaseAfterRunning), (void*)boolrun),
                                                                   CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable),(void*)exObj2),
                                                                   CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::setTrueControlable),(void*)exObj), NULL));
  
                        break;
                    }
                }
            }
            exObj->setControlTrigger(true);
        }
    }
    toDestroyArray->removeAllObjects();
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
            
            break;
        case MB2_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            isCleanMB2 = true;
            isExistMB2 = false;

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
    
    TakasuPoppo::plusAllComboCounter();
    
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
            
            cloneSprite->runAction(CCSequence::create(CCScaleTo::create(0.2f, 1.5f),
                                                      CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::cleanOneBlock),(void*)block),
                                                      CCRemoveSelf::create(true),
                                                      NULL));
            
        }
    }
    
    isHBCinBlockSet = true;

}

// For new instance of Clean Hyper Block C with scale animation

void TakasuPoppo::scaleHyperBlockC(CCNode *sender, void* data){
    
    TPObjectExtension *exObj = (TPObjectExtension*)data;
    if (exObj->getSprite() != NULL && exObj->getID() != 7) {
        exObj->getSprite()->runAction(CCScaleTo::create(0.1f, 1.2f));
    }
}

void TakasuPoppo::cleanHyperBlockC(TPObjectExtension* exObj){
    
    isHBCinBlockSet = true;
    
    TakasuPoppo::plusAllComboCounter();
    
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
            
            cloneSprite->runAction(CCSequence::create(CCScaleTo::create(0.2f, 1.5f),
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
            
            break;
        case MB2_BLOCK_TYPE:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            isCleanMB2 = true;
            isExistMB2 = false;
            
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
            
            
        default:
            if (exobj != NULL && exobj->getSprite() != NULL && exobj->getID() != 7)
                TakasuPoppo::cleanSprite(exobj);
            break;
    }

}

float TakasuPoppo::setCleanDelay(){
    if (isHBCinBlockSet) {
        return HBC_CLEAN_DELAY;
    } else {
        return CLEAN_DELAY;
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
    
    // count the really combo
    ComboCounter += 1;
    if (ComboTimer != 3) ComboTimer = 3;
    
}
 void TakasuPoppo::afterCleanRunning(cocos2d::CCNode *sender, void *data)
{
    runningAfter = true;
    CCBool * boolMoving = (CCBool*)data;
    boolAfterClean->addObject(boolMoving);
    move = false;
    swape = false;
    
}
void TakasuPoppo::releaseAfterRunning(cocos2d::CCNode *sender, void *data)
{
    CCBool * boolMoving = (CCBool*)data;
    boolAfterClean->removeObject(boolMoving);
    
    move = false;
    swape = false;}
void TakasuPoppo::setFalseControl()
{
    move = false;
    swape = false;
    this->setTouchEnabled(false);
    runningAfter =true;
    swipeUp = false;
    swipeDown = false;
    swipeRight = false;
    swipeLeft = false;
}
void TakasuPoppo::setControl()
{
    this->setTouchEnabled(true);
    move = false;
    swape = false;
    runningAfter = false;
}

void TakasuPoppo::deleteMainSprite()
{
    mainSprite = NULL;
}
void TakasuPoppo::runningSwap(cocos2d::CCNode *sender, void *data)
{
    CCBool * boolMoving = (CCBool*)data;
    boolMoveTo->addObject(boolMoving);
    move = false;
    swape = false;
    
}
bool TakasuPoppo::checkAllRunning()
{
    CCObject* obj;
    CCARRAY_FOREACH(boolMoveTo, obj)
    {
        CCBool* boolMoving = dynamic_cast<CCBool*>(obj);
        if(boolMoving->getValue())
            return true;
    }
    return false;
}
bool TakasuPoppo::checkAfterCleanRunning()
{
    CCObject* obj;
    CCARRAY_FOREACH(boolAfterClean, obj)
    {
        CCBool* boolMoving = dynamic_cast<CCBool*>(obj);
        if(boolMoving->getValue())
        {
            boolAfterClean->removeAllObjects();
            return true;
        }
    }
    return false;
}

void TakasuPoppo::notRunningSwap(cocos2d::CCNode *sender, void *data)
{
    CCBool * boolMoving = (CCBool*)data;
    boolMoveTo->removeObject(boolMoving);
    move = false;
    swape = false;
}
void TakasuPoppo::refreshMoving()
{
    boolMoveTo->removeAllObjects();
    move = false;
    swape = false;
}