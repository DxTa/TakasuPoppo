//
//  TP_TakasuPoppo_Match.cpp
//  Cocos2Dx
//
//  Created by macbook_006 on 13/06/28.
//
//

#include "TakasuPoppo.h"
#include "TPBlockSet.h"
#pragma mark Matching Control

bool TakasuPoppo::isTileMatched(int gid, int typeID) {
    if (gid != 1 && gid != 2 &&
        gid != 8 && gid != 9 &&
        gid != 15 && gid != 16 &&
        gid != 22 && gid != 23 &&
        gid != 29 && gid != 30 &&
        gid != 36 && gid != 37 &&
        gid != 43 && gid != 44 ){
        CCObject *obj1 = colorArray->objectAtIndex(gid - 2);
        CCObject *obj2 = colorArray->objectAtIndex(gid - 3);
        TPObjectExtension *ex1 = dynamic_cast<TPObjectExtension*>(obj1);
        TPObjectExtension *ex2 = dynamic_cast<TPObjectExtension*>(obj2);
        if(ex1->getID() == typeID && ex2->getID() == typeID) return true;
    }
    if(gid >= 15){
        CCObject *obj1 = colorArray->objectAtIndex(gid - 8);
        CCObject *obj2 = colorArray->objectAtIndex(gid -15);
        TPObjectExtension *ex1 = dynamic_cast<TPObjectExtension*>(obj1);
        TPObjectExtension *ex2 = dynamic_cast<TPObjectExtension*>(obj2);
        if(ex1->getID() == typeID && ex2->getID() == typeID) return true;
    }
    return false;
}

void TakasuPoppo::matchList() {
    for (int y = 0; y < 7; y++) {
        for (int x = 0; x < 5; x++) {
            CCArray *match = new CCArray;
            match->autorelease();
            CCPoint coor = ccp(x, y);
            int gid = layer->tileGIDAt(coor);
            int gidToIndex = gid - 1;
            CCObject *object = colorArray->objectAtIndex(gidToIndex);
            TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
            match->addObject(exObj);
            if (exObj != NULL && exObj->getCoordination().x == coor.x &&
                exObj->getCoordination().y == coor.y) {
                if (TakasuPoppo::getMatchHor(exObj)->count() >= 2) {
                    match->addObjectsFromArray(TakasuPoppo::getMatchHor(exObj));
                    x += getMatchHor(exObj)->count();
                    if (match->count() == 3) {
                        TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(1));
                        TPObjectExtension *exObj3 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(2));
                        exObj->setControlTrigger(false);
                        exObj2->setControlTrigger(false);
                        exObj3->setControlTrigger(false);
                        TPBlockSet *blockSet = new TPBlockSet(exObj, exObj2, exObj3,
                                                              NULL, NULL, NULL, NULL,
                                                              "TrioHor", exObj->getCoordination().x, exObj->getCoordination().y);
                        if (TakasuPoppo::destroyCheck(exObj)) toDestroyArray->addObject(blockSet);
                    }
                    if (match->count() == 4) {
                        TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(1));
                        TPObjectExtension *exObj3 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(2));
                        TPObjectExtension *exObj4 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(3));
                        exObj->setControlTrigger(false);
                        exObj2->setControlTrigger(false);
                        exObj3->setControlTrigger(false);
                        exObj4->setControlTrigger(false);
                        TPBlockSet *blockSet = new TPBlockSet(exObj, exObj2, exObj3, exObj4,
                                                              NULL, NULL, NULL,
                                                              "QuadHor", exObj->getCoordination().x, exObj->getCoordination().y);
                        if (TakasuPoppo::destroyCheck(exObj)) toDestroyArray->addObject(blockSet);
                    }
                    if (match->count() == 5) {
                        TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(1));
                        TPObjectExtension *exObj3 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(2));
                        TPObjectExtension *exObj4 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(3));
                        TPObjectExtension *exObj5 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(4));
                        exObj->setControlTrigger(false);
                        exObj2->setControlTrigger(false);
                        exObj3->setControlTrigger(false);
                        exObj4->setControlTrigger(false);
                        exObj5->setControlTrigger(false);
                        TPBlockSet *blockSet = new TPBlockSet(exObj, exObj2, exObj3, exObj4, exObj5,
                                                              NULL, NULL,
                                                              "PentaHor", exObj->getCoordination().x, exObj->getCoordination().y);
                        if (TakasuPoppo::destroyCheck(exObj)) toDestroyArray->addObject(blockSet);
                    }
                    if (match->count() == 6) {
                        TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(1));
                        TPObjectExtension *exObj3 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(2));
                        TPObjectExtension *exObj4 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(3));
                        TPObjectExtension *exObj5 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(4));
                        TPObjectExtension *exObj6 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(5));
                        exObj->setControlTrigger(false);
                        exObj2->setControlTrigger(false);
                        exObj3->setControlTrigger(false);
                        exObj4->setControlTrigger(false);
                        exObj5->setControlTrigger(false);
                        exObj6->setControlTrigger(false);
                        TPBlockSet *blockSet = new TPBlockSet(exObj, exObj2, exObj3, exObj4, exObj5,
                                                              exObj6, NULL,
                                                              "HexHor", exObj->getCoordination().x, exObj->getCoordination().y);
                        if (TakasuPoppo::destroyCheck(exObj)) toDestroyArray->addObject(blockSet);
                    }
                    if (match->count() == 7) {
                        TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(1));
                        TPObjectExtension *exObj3 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(2));
                        TPObjectExtension *exObj4 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(3));
                        TPObjectExtension *exObj5 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(4));
                        TPObjectExtension *exObj6 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(5));
                        TPObjectExtension *exObj7 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(6));
                        exObj->setControlTrigger(false);
                        exObj2->setControlTrigger(false);
                        exObj3->setControlTrigger(false);
                        exObj4->setControlTrigger(false);
                        exObj5->setControlTrigger(false);
                        exObj6->setControlTrigger(false);
                        exObj7->setControlTrigger(false);
                        TPBlockSet *blockSet = new TPBlockSet(exObj, exObj2, exObj3, exObj4, exObj5,
                                                              exObj6, exObj7,
                                                              "HeptaHor", exObj->getCoordination().x, exObj->getCoordination().y);
                        if (TakasuPoppo::destroyCheck(exObj)) toDestroyArray->addObject(blockSet);
                    }
                }
            }
        }
    }
    
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 5; y++) {
            CCArray *match = new CCArray;
            match->autorelease();
            CCPoint coor = ccp(x, y);
            int gid = layer->tileGIDAt(coor);
            int gidToIndex = gid - 1;
            CCObject *object = colorArray->objectAtIndex(gidToIndex);
            TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
            match->addObject(exObj);
            if (exObj != NULL && exObj->getCoordination().x == coor.x &&
                exObj->getCoordination().y == coor.y) {
                if (TakasuPoppo::getMatchVer(exObj)->count() >= 2) {
                    match->addObjectsFromArray(TakasuPoppo::getMatchVer(exObj));
                    y += getMatchVer(exObj)->count();
                    if (match->count() == 3) {
                        TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(1));
                        TPObjectExtension *exObj3 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(2));
                        exObj->setControlTrigger(false);
                        exObj2->setControlTrigger(false);
                        exObj3->setControlTrigger(false);
                        TPBlockSet *blockSet = new TPBlockSet(exObj, exObj2, exObj3,
                                                              NULL, NULL, NULL, NULL,
                                                              "TrioVer", exObj->getCoordination().x, exObj->getCoordination().y);
                        if (TakasuPoppo::destroyCheck(exObj)) toDestroyArray->addObject(blockSet);
                    }
                    if (match->count() == 4) {
                        TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(1));
                        TPObjectExtension *exObj3 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(2));
                        TPObjectExtension *exObj4 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(3));
                        exObj->setControlTrigger(false);
                        exObj2->setControlTrigger(false);
                        exObj3->setControlTrigger(false);
                        exObj4->setControlTrigger(false);
                        TPBlockSet *blockSet = new TPBlockSet(exObj, exObj2, exObj3, exObj4,
                                                              NULL, NULL, NULL,
                                                              "QuadVer", exObj->getCoordination().x, exObj->getCoordination().y);
                        if (TakasuPoppo::destroyCheck(exObj)) toDestroyArray->addObject(blockSet);
                    }
                    if (match->count() == 5) {
                        TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(1));
                        TPObjectExtension *exObj3 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(2));
                        TPObjectExtension *exObj4 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(3));
                        TPObjectExtension *exObj5 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(4));
                        exObj->setControlTrigger(false);
                        exObj2->setControlTrigger(false);
                        exObj3->setControlTrigger(false);
                        exObj4->setControlTrigger(false);
                        exObj5->setControlTrigger(false);
                        TPBlockSet *blockSet = new TPBlockSet(exObj, exObj2, exObj3, exObj4, exObj5,
                                                              NULL, NULL, 
                                                       "PentaVer", exObj->getCoordination().x, exObj->getCoordination().y);
                        if (TakasuPoppo::destroyCheck(exObj)) toDestroyArray->addObject(blockSet);
                    }
                    if (match->count() == 6) {
                        TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(1));
                        TPObjectExtension *exObj3 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(2));
                        TPObjectExtension *exObj4 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(3));
                        TPObjectExtension *exObj5 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(4));
                        TPObjectExtension *exObj6 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(5));
                        exObj->setControlTrigger(false);
                        exObj2->setControlTrigger(false);
                        exObj3->setControlTrigger(false);
                        exObj4->setControlTrigger(false);
                        exObj5->setControlTrigger(false);
                        exObj6->setControlTrigger(false);
                        TPBlockSet *blockSet = new TPBlockSet(exObj, exObj2, exObj3, exObj4, exObj5,
                                                              exObj6, NULL,
                                                              "HexVer", exObj->getCoordination().x, exObj->getCoordination().y);
                        if (TakasuPoppo::destroyCheck(exObj)) toDestroyArray->addObject(blockSet);
                    }
                    if (match->count() == 7) {
                        TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(1));
                        TPObjectExtension *exObj3 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(2));
                        TPObjectExtension *exObj4 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(3));
                        TPObjectExtension *exObj5 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(4));
                        TPObjectExtension *exObj6 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(5));
                        TPObjectExtension *exObj7 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(6));
                        exObj->setControlTrigger(false);
                        exObj2->setControlTrigger(false);
                        exObj3->setControlTrigger(false);
                        exObj4->setControlTrigger(false);
                        exObj5->setControlTrigger(false);
                        exObj6->setControlTrigger(false);
                        exObj7->setControlTrigger(false);
                        TPBlockSet *blockSet = new TPBlockSet(exObj, exObj2, exObj3, exObj4, exObj5,
                                                              exObj6, exObj7,
                                                              "HeptaVer", exObj->getCoordination().x, exObj->getCoordination().y);
                        if (TakasuPoppo::destroyCheck(exObj)) toDestroyArray->addObject(blockSet);
                    }
                }
            }
        }
    }
    //==================================check create B by Hor and Ver ====================
    CCObject *obj;
    if(toDestroyArray->count() != 0)
    {
        CCARRAY_FOREACH(toDestroyArray, obj)
        {
            TPBlockSet* blockset = dynamic_cast<TPBlockSet*>(obj);
            if(blockset->getEx1() != NULL && checkCreateHyperB(blockset->getEx1()->getCoordination(), blockset->getEx1()->getID()))
            {
                if (blockset->getEx1()->getBlockType() == 2 || blockset->getEx1()->getBlockType() == 12) {
                    blockset->getEx1()->setBlockType(22);
                }
                if (blockset->getEx1()->getBlockType() == 1 || blockset->getEx1()->getBlockType() == 11) {
                    blockset->getEx1()->setBlockType(21);
                }
                if (blockset->getEx1()->getBlockType() == 0 || blockset->getEx1()->getBlockType() == 10) {
                    blockset->getEx1()->setBlockType(20);
                }
            }
            if(blockset->getEx2() != NULL && checkCreateHyperB(blockset->getEx2()->getCoordination(), blockset->getEx2()->getID()))
            {
                if (blockset->getEx2()->getBlockType() == 2 || blockset->getEx2()->getBlockType() == 12) {
                    blockset->getEx2()->setBlockType(22);
                }
                if (blockset->getEx2()->getBlockType() == 1 || blockset->getEx2()->getBlockType() == 11) {
                    blockset->getEx2()->setBlockType(21);
                }
                if (blockset->getEx2()->getBlockType() == 0 || blockset->getEx2()->getBlockType() == 10) {
                    blockset->getEx2()->setBlockType(20);
                }
            }
            if(blockset->getEx3() != NULL && checkCreateHyperB(blockset->getEx3()->getCoordination(), blockset->getEx3()->getID()))
            {
                if (blockset->getEx3()->getBlockType() == 2 || blockset->getEx3()->getBlockType() == 12) {
                    blockset->getEx3()->setBlockType(22);
                }
                if (blockset->getEx3()->getBlockType() == 1 || blockset->getEx3()->getBlockType() == 11) {
                    blockset->getEx3()->setBlockType(21);
                }
                if (blockset->getEx3()->getBlockType() == 0 || blockset->getEx3()->getBlockType() == 10) {
                    blockset->getEx3()->setBlockType(20);
                }
            }
            if(blockset->getEx4() != NULL && checkCreateHyperB(blockset->getEx4()->getCoordination(), blockset->getEx4()->getID()))
            {
                if (blockset->getEx4()->getBlockType() == 2 || blockset->getEx4()->getBlockType() == 12) {
                    blockset->getEx4()->setBlockType(22);
                }
                if (blockset->getEx4()->getBlockType() == 1 || blockset->getEx4()->getBlockType() == 11) {
                    blockset->getEx4()->setBlockType(21);
                }
                if (blockset->getEx4()->getBlockType() == 0 || blockset->getEx4()->getBlockType() == 10) {
                    blockset->getEx4()->setBlockType(20);
                }
            }
            if(blockset->getEx5() != NULL && checkCreateHyperB(blockset->getEx5()->getCoordination(), blockset->getEx5()->getID()))
            {
                if (blockset->getEx5()->getBlockType() == 2 || blockset->getEx5()->getBlockType() == 12) {
                    blockset->getEx5()->setBlockType(22);
                }
                if (blockset->getEx5()->getBlockType() == 1 || blockset->getEx5()->getBlockType() == 11) {
                    blockset->getEx5()->setBlockType(21);
                }
                if (blockset->getEx5()->getBlockType() == 0 || blockset->getEx5()->getBlockType() == 10) {
                    blockset->getEx5()->setBlockType(20);
                }
            }
            if(blockset->getEx6() != NULL && checkCreateHyperB(blockset->getEx6()->getCoordination(), blockset->getEx6()->getID()))
            {
                if (blockset->getEx6()->getBlockType() == 2 || blockset->getEx6()->getBlockType() == 12) {
                    blockset->getEx6()->setBlockType(22);
                }
                if (blockset->getEx6()->getBlockType() == 1 || blockset->getEx6()->getBlockType() == 11) {
                    blockset->getEx6()->setBlockType(21);
                }
                if (blockset->getEx6()->getBlockType() == 0 || blockset->getEx6()->getBlockType() == 10) {
                    blockset->getEx6()->setBlockType(20);
                }
            }
            if(blockset->getEx7() != NULL && checkCreateHyperB(blockset->getEx7()->getCoordination(), blockset->getEx7()->getID()))
            {
                if (blockset->getEx7()->getBlockType() == 2 || blockset->getEx7()->getBlockType() == 12) {
                    blockset->getEx7()->setBlockType(22);
                }
                if (blockset->getEx7()->getBlockType() == 1 || blockset->getEx7()->getBlockType() == 11) {
                    blockset->getEx7()->setBlockType(21);
                }
                if (blockset->getEx7()->getBlockType() == 0 || blockset->getEx7()->getBlockType() == 10) {
                    blockset->getEx7()->setBlockType(20);
                }
            }
            
        }
    }
}

CCArray *TakasuPoppo::getMatchHor(TPObjectExtension *exObj) {
    CCArray *matches = new CCArray;
    matches->autorelease();
    int colNum= exObj->getCoordination().x;
    for (int ct = 1; colNum + ct < 7; ct++) {
        CCPoint coor = ccp(colNum + ct, exObj->getCoordination().y);
        int gid = layer->tileGIDAt(coor);
        int gidToIndex = gid - 1;
        TPObjectExtension *checkObj = dynamic_cast<TPObjectExtension*>(colorArray->objectAtIndex(gidToIndex));
        if (exObj != NULL && checkObj != NULL && checkObj->getID() == exObj->getID() &&
            exObj->getID() < 7) {
            matches->addObject(checkObj);
        }
        else return matches;
    }
    return matches;
}

CCArray *TakasuPoppo::getMatchVer(TPObjectExtension *exObj) {
    CCArray *matches = new CCArray;
    matches->autorelease();
    int rowNum= exObj->getCoordination().y;
    for (int ct = 1; rowNum + ct < 7; ct++) {
        CCPoint coor = ccp(exObj->getCoordination().x, rowNum + ct);
        int gid = layer->tileGIDAt(coor);
        int gidToIndex = gid - 1;
        CCObject *object = colorArray->objectAtIndex(gidToIndex);
        TPObjectExtension *checkObj = dynamic_cast<TPObjectExtension*>(object);
        if (checkObj != NULL && checkObj->getID() == exObj->getID() &&
            exObj->getID() < 7) {
            matches->addObject(checkObj);
        }
        else return matches;
    }
    return matches;
}


/*
 |======================================|
 |        Grid Variables Mapping        |
 |======================================|
 |    |     -2  -1   0  +1  +2  +3      |
 |----|---------------------------------|
 | -3 |              j                  |
 | -2 |          y   h   i              |
 | -1 |      k   l   e   f   g          |
 |  0 |      m   n  [a]  b   c   d      |
 | +1 |          s   o   p   t          |
 | +2 |          x   q   r              |
 |======================================|
 */

int TakasuPoppo::lookForMatches() {
    int match = 0;
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 7; y++) {
            CCPoint aPoint = ccp(x, y);
            CCPoint bPoint = ccp(x + 1, y);
            CCPoint cPoint = ccp(x + 2, y);
            CCPoint dPoint = ccp(x + 3, y);
            CCPoint ePoint = ccp(x, y - 1);
            CCPoint fPoint = ccp(x + 1, y - 1);
            CCPoint gPoint = ccp(x + 2, y - 1);
            CCPoint hPoint = ccp(x, y - 2);
            CCPoint iPoint = ccp(x + 1, y - 2);
            CCPoint jPoint = ccp(x, y - 3);
            CCPoint lPoint = ccp(x - 1, y - 1);
            CCPoint mPoint = ccp(x - 2, y);
            CCPoint pPoint = ccp(x + 1, y + 1);
            CCPoint qPoint = ccp(x, y + 2);
            CCPoint sPoint = ccp(x - 1, y + 1);
            CCPoint tPoint = ccp(x + 2, y + 1);
            CCPoint yPoint = ccp(x - 1, y - 2);
            
            TPObjectExtension *aExObj = TakasuPoppo::coorToExObj(aPoint);
            TPObjectExtension *bExObj = TakasuPoppo::coorToExObj(bPoint);
            TPObjectExtension *cExObj = TakasuPoppo::coorToExObj(cPoint);
            TPObjectExtension *dExObj = TakasuPoppo::coorToExObj(dPoint);
            TPObjectExtension *eExObj = TakasuPoppo::coorToExObj(ePoint);
            TPObjectExtension *fExObj = TakasuPoppo::coorToExObj(fPoint);
            TPObjectExtension *gExObj = TakasuPoppo::coorToExObj(gPoint);
            TPObjectExtension *hExObj = TakasuPoppo::coorToExObj(hPoint);
            TPObjectExtension *iExObj = TakasuPoppo::coorToExObj(iPoint);
            TPObjectExtension *jExObj = TakasuPoppo::coorToExObj(jPoint);
            TPObjectExtension *lExObj = TakasuPoppo::coorToExObj(lPoint);
            TPObjectExtension *mExObj = TakasuPoppo::coorToExObj(mPoint);
            TPObjectExtension *pExObj = TakasuPoppo::coorToExObj(pPoint);
            TPObjectExtension *qExObj = TakasuPoppo::coorToExObj(qPoint);
            TPObjectExtension *sExObj = TakasuPoppo::coorToExObj(sPoint);
            TPObjectExtension *tExObj = TakasuPoppo::coorToExObj(tPoint);
            TPObjectExtension *yExObj = TakasuPoppo::coorToExObj(yPoint);
            
            if(aExObj != NULL)
            {
                if (aExObj->getBlockType() == HBC_BLOCK_TYPE) {
                    match++;
                }
                //Horizontal 3 matches
                if (bExObj != NULL && bExObj->getID() == aExObj->getID()) {
                    if (TakasuPoppo::sumOfMatches(aExObj, bExObj, lExObj, sExObj, mExObj)) match++;
                    if (TakasuPoppo::sumOfMatches(aExObj, bExObj, gExObj, tExObj, dExObj)) match++;
                    
                }
                
                //Vertical 3 matches
                if (eExObj != NULL && eExObj->getID() == aExObj->getID()) {
                    if (TakasuPoppo::sumOfMatches(aExObj, eExObj, iExObj, jExObj, yExObj))match++;
                    if (TakasuPoppo::sumOfMatches(aExObj, eExObj, pExObj, qExObj, sExObj))match++;
                }
                
                //Middle Vertical Top
                if (hExObj != NULL && hExObj->getID() == aExObj->getID()) {
                    if (TakasuPoppo::sumOfMatches(aExObj, hExObj, lExObj, fExObj, NULL)) match++;
                }
                
                //Middle Vertical Bottom
                if (qExObj != NULL && qExObj->getID() == aExObj->getID()) {
                    if (TakasuPoppo::sumOfMatches(aExObj, qExObj, pExObj, sExObj, NULL)) match++;
                }
                
                //Middle Horizontal Left
                if (mExObj != NULL && mExObj->getID() == aExObj->getID()) {
                    if (TakasuPoppo::sumOfMatches(aExObj, mExObj, lExObj, sExObj, NULL)) match++;
                }
                
                //Middle Horizontal Right
                if (cExObj != NULL && cExObj->getID() == aExObj->getID()) {
                    if (TakasuPoppo::sumOfMatches(aExObj, cExObj, fExObj, pExObj, NULL)) match++;
                }
            }
        }
    }
    //    CCLog("There are %i possible matches", match);
    return match;
}

bool TakasuPoppo::sumOfMatches(TPObjectExtension *exA, TPObjectExtension *exB,
                               TPObjectExtension *ex1, TPObjectExtension *ex2, TPObjectExtension *ex3) {
    // Vinh nt - change the condination in if: && exA->getID() != 7
    if (ex1 != NULL && ex1->getID() == exA->getID()  && exA->getID() != 7) {
        if (hintArray->count() < 5) hintArray->addObject(ex1);
        return true;
    }
    if (ex2 != NULL && ex2->getID() == exA->getID() && exA->getID() != 7) {
        if (hintArray->count() < 5) hintArray->addObject(ex2);
        return true;
    }
    if (ex3 != NULL && ex3->getID() == exA->getID() && exA->getID() != 7) {
        if (hintArray->count() < 5) hintArray->addObject(ex3);
        return true;
    }
    return false;
}

TPObjectExtension *TakasuPoppo::coorToExObj(CCPoint coor) {
    if ((coor.x >= 0 && coor.x < 7) && (coor.y >= 0 && coor.y < 7)) {
        int gid = layer->tileGIDAt(coor);
        int gidToIndex = gid - 1;
        CCObject *object = colorArray->objectAtIndex(gidToIndex);
        TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
        return exObj;
    }
    return NULL;
}

/*
 |======================================|
 |           Check Matchable            |
 |======================================|
 |    |     -2  -1   0  +1  +2  +3      |
 |----|---------------------------------|
 | -3 |                                 |
 | -2 |              h                  |
 | -1 |              e                  |
 |  0 |      m   n  [a]  b   c          |
 | +1 |              o                  |
 | +2 |              q                  |
 |======================================|
 */

bool TakasuPoppo::matchAble(CCPoint coor, int type) {
    if(type == 8)
        return false;
    int x = coor.x;
    int y = coor.y;
    
    CCPoint bPoint = ccp(x + 1, y);
    CCPoint cPoint = ccp(x + 2, y);
    CCPoint ePoint = ccp(x, y - 1);
    CCPoint hPoint = ccp(x, y - 2);
    CCPoint mPoint = ccp(x - 2, y);
    CCPoint nPoint = ccp(x - 1, y);
    CCPoint oPoint = ccp(x, y + 1);
    CCPoint qPoint = ccp(x, y + 2);
    
    TPObjectExtension *bExObj = TakasuPoppo::coorToExObj(bPoint);
    TPObjectExtension *cExObj = TakasuPoppo::coorToExObj(cPoint);
    TPObjectExtension *eExObj = TakasuPoppo::coorToExObj(ePoint);
    TPObjectExtension *hExObj = TakasuPoppo::coorToExObj(hPoint);
    TPObjectExtension *mExObj = TakasuPoppo::coorToExObj(mPoint);
    TPObjectExtension *nExObj = TakasuPoppo::coorToExObj(nPoint);
    TPObjectExtension *oExObj = TakasuPoppo::coorToExObj(oPoint);
    TPObjectExtension *qExObj = TakasuPoppo::coorToExObj(qPoint);
    
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

/*
 |======================================|
 |        Smart Generation Chart        |
 |======================================|
 |    |     -2  -1   0  +1  +2  +3      |
 |----|---------------------------------|
 | -3 |                                 |
 | -2 |              h                  |
 | -1 |              e       g          |
 |  0 |          n  [a]  b   c          |
 | +1 |          s   o   p   t          |
 | +2 |                                 |
 |======================================|
 */

void TakasuPoppo::smartGeneration() {
    
    int randomGID = rand() % 3;
    int i = 0;
    CCObject *object;
    
    CCPoint lastRowAtColumn6;
    CCPoint lastRowAtColumn5;
    CCPoint lastRowAtColumn4;
    CCPoint lastRowAtColumn3;
    CCPoint lastRowAtColumn2;
    CCPoint lastRowAtColumn1;
    CCPoint lastRowAtColumn0;
    
    
    for (int yCoor = 6; yCoor > 0; yCoor--) {
        for (int xCoor = 6 ; xCoor > 0; xCoor--) {
            CCPoint coor = ccp(xCoor, yCoor);
            int gid = layer->tileGIDAt(coor);
            int gidToIndex = gid - 1;
            CCObject *object = colorArray->objectAtIndex(gidToIndex);
            TPObjectExtension *checkObj = dynamic_cast<TPObjectExtension*>(object);
            if (checkObj->getID() == 7) {
                if (checkObj->getCoordination().x == 6)lastRowAtColumn6 = CCPoint(xCoor, yCoor);
                if (checkObj->getCoordination().x == 5)lastRowAtColumn5 = CCPoint(xCoor, yCoor);
                if (checkObj->getCoordination().x == 4)lastRowAtColumn4 = CCPoint(xCoor, yCoor);
                if (checkObj->getCoordination().x == 3)lastRowAtColumn3 = CCPoint(xCoor, yCoor);
                if (checkObj->getCoordination().x == 2)lastRowAtColumn2 = CCPoint(xCoor, yCoor);
                if (checkObj->getCoordination().x == 1)lastRowAtColumn1 = CCPoint(xCoor, yCoor);
                if (checkObj->getCoordination().x == 0)lastRowAtColumn0 = CCPoint(xCoor, yCoor);
                break;
            }
        }
    }
    
    CCARRAY_FOREACH(colorArray, object) {
        TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
        if (exObj != NULL && exObj->getID() == 7) {
            i ++;
            switch (_spcialItemID) {
                case SPECIAL_ITEM_1_ID:
                    // create Mission Block 1
                    if (isCreateMB1 == true) {
                        TakasuPoppo::generateRandomBlock(exObj, TakasuPoppo::getFallPos(exObj, lastRowAtColumn0,
                                                                                        lastRowAtColumn1,lastRowAtColumn2,
                                                                                        lastRowAtColumn3,lastRowAtColumn4,
                                                                                        lastRowAtColumn5, lastRowAtColumn6));
                        TakasuPoppo::createSpecialBlock(exObj, MB1_BLOCK_TYPE);
                        isCreateMB1 = false;
                    } else {
                        if (isCreateGaugeCombo == true && (i % 3 == randomGID)) { // gauge combo: create new Hyper Block B
                            TakasuPoppo::generateRandomBlock(exObj, TakasuPoppo::getFallPos(exObj, lastRowAtColumn0,
                                                                                            lastRowAtColumn1,lastRowAtColumn2,
                                                                                            lastRowAtColumn3,lastRowAtColumn4,
                                                                                            lastRowAtColumn5, lastRowAtColumn6));
                            exObj->setControlTrigger(false);
                            TakasuPoppo::makeBlockToBeHBC(exObj);
                            isCreateGaugeCombo = false;
                            
                        } else {
                            TakasuPoppo::generateRandomBlock(exObj, TakasuPoppo::getFallPos(exObj, lastRowAtColumn0,
                                                                                            lastRowAtColumn1,lastRowAtColumn2,
                                                                                            lastRowAtColumn3,lastRowAtColumn4,
                                                                                            lastRowAtColumn5, lastRowAtColumn6));
                            exObj->setControlTrigger(false);
                        }
                    }

                    break;
                    
                case SPECIAL_ITEM_2_ID:
                    // create Mission Block 2
                    if (isCreateMB2 == true) {
                        TakasuPoppo::generateRandomBlock(exObj, TakasuPoppo::getFallPos(exObj, lastRowAtColumn0,
                                                                                        lastRowAtColumn1,lastRowAtColumn2,
                                                                                        lastRowAtColumn3,lastRowAtColumn4,
                                                                                        lastRowAtColumn5, lastRowAtColumn6));
                        TakasuPoppo::createSpecialBlock(exObj, MB2_BLOCK_TYPE);
                        isCreateMB2 = false;
                        isExistMB2 = true;
                    } else {
                        if (isCreateGaugeCombo == true && (i % 3 == randomGID)) { // gauge combo: create new Hyper Block B
                            TakasuPoppo::generateRandomBlock(exObj, TakasuPoppo::getFallPos(exObj, lastRowAtColumn0,
                                                                                            lastRowAtColumn1,lastRowAtColumn2,
                                                                                            lastRowAtColumn3,lastRowAtColumn4,
                                                                                            lastRowAtColumn5, lastRowAtColumn6));
                            exObj->setControlTrigger(false);
                            TakasuPoppo::makeBlockToBeHBC(exObj);
                            isCreateGaugeCombo = false;
                            
                        } else {
                            TakasuPoppo::generateRandomBlock(exObj, TakasuPoppo::getFallPos(exObj, lastRowAtColumn0,
                                                                                            lastRowAtColumn1,lastRowAtColumn2,
                                                                                            lastRowAtColumn3,lastRowAtColumn4,
                                                                                            lastRowAtColumn5, lastRowAtColumn6));
                            exObj->setControlTrigger(false);
                        }
                    }
                    break;
                    
                case SPECIAL_ITEM_4_ID:
                    // create Mission Block 3
                    if (isCreateMB3 == true) {
                        TakasuPoppo::generateRandomBlock(exObj, TakasuPoppo::getFallPos(exObj, lastRowAtColumn0,
                                                                                        lastRowAtColumn1,lastRowAtColumn2,
                                                                                        lastRowAtColumn3,lastRowAtColumn4,
                                                                                        lastRowAtColumn5, lastRowAtColumn6));
                        TakasuPoppo::createSpecialBlock(exObj, MB3_BLOCK_TYPE);
                        isCreateMB3 = false;
                    } else {
                        if (isCreateGaugeCombo == true && (i % 3 == randomGID)) { // gauge combo: create new Hyper Block B
                            TakasuPoppo::generateRandomBlock(exObj, TakasuPoppo::getFallPos(exObj, lastRowAtColumn0,
                                                                                            lastRowAtColumn1,lastRowAtColumn2,
                                                                                            lastRowAtColumn3,lastRowAtColumn4,
                                                                                            lastRowAtColumn5, lastRowAtColumn6));
                            exObj->setControlTrigger(false);
                            TakasuPoppo::makeBlockToBeHBC(exObj);
                            isCreateGaugeCombo = false;
                            
                        } else {
                            TakasuPoppo::generateRandomBlock(exObj, TakasuPoppo::getFallPos(exObj, lastRowAtColumn0,
                                                                                            lastRowAtColumn1,lastRowAtColumn2,
                                                                                            lastRowAtColumn3,lastRowAtColumn4,
                                                                                            lastRowAtColumn5, lastRowAtColumn6));
                            exObj->setControlTrigger(false);
                        }
                    }
                    break;

                    
                default:
                    if (isCreateGaugeCombo == true && (i % 3 == randomGID)) { // gauge combo: create new Hyper Block B
                        TakasuPoppo::generateRandomBlock(exObj, TakasuPoppo::getFallPos(exObj, lastRowAtColumn0,
                                                                                        lastRowAtColumn1,lastRowAtColumn2,
                                                                                        lastRowAtColumn3,lastRowAtColumn4,
                                                                                        lastRowAtColumn5, lastRowAtColumn6));
                        exObj->setControlTrigger(false);
                        TakasuPoppo::makeBlockToBeHBC(exObj);
                        isCreateGaugeCombo = false;
                        
                    } else {
                        TakasuPoppo::generateRandomBlock(exObj, TakasuPoppo::getFallPos(exObj, lastRowAtColumn0,
                                                                                        lastRowAtColumn1,lastRowAtColumn2,
                                                                                        lastRowAtColumn3,lastRowAtColumn4,
                                                                                        lastRowAtColumn5, lastRowAtColumn6));
                        exObj->setControlTrigger(false);
                    }

                    break;
            }
            
        }
        
    }
    
    if(hyperBlockC){
        randomBlockC();
    }
    
    return;
}

CCPoint TakasuPoppo::getFallPos(TPObjectExtension *exObj, CCPoint lastRowAtColumn0,
                                CCPoint lastRowAtColumn1, CCPoint lastRowAtColumn2,
                                CCPoint lastRowAtColumn3, CCPoint lastRowAtColumn4,
                                CCPoint lastRowAtColumn5, CCPoint lastRowAtColumn6) {
    
    CCPoint presentCoor = exObj->getCoordination();
    int yDifference;
    CCPoint presentPos = exObj->getPosition();
    CCPoint fallPos;
    
    if (presentCoor.x == lastRowAtColumn6.x) {
        yDifference = (int)lastRowAtColumn6.y - (int)presentCoor.y;
        fallPos = ccp(presentPos.x, 675 + 90 + yDifference * 90);
        return fallPos;
    }
    if (presentCoor.x == lastRowAtColumn5.x) {
        yDifference = (int)lastRowAtColumn5.y - (int)presentCoor.y;
        fallPos = ccp(presentPos.x, 675 + 90 + yDifference * 90);
        return fallPos;
    }
    if (presentCoor.x == lastRowAtColumn4.x) {
        yDifference = (int)lastRowAtColumn4.y - (int)presentCoor.y;
        fallPos = ccp(presentPos.x, 675 + 90 + yDifference * 90);
        return fallPos;
    }
    if (presentCoor.x == lastRowAtColumn3.x) {
        yDifference = (int)lastRowAtColumn3.y - (int)presentCoor.y;
        fallPos = ccp(presentPos.x, 675 + 90 + yDifference * 90);
        return fallPos;
    }
    if (presentCoor.x == lastRowAtColumn2.x) {
        yDifference = (int)lastRowAtColumn2.y - (int)presentCoor.y;
        fallPos = ccp(presentPos.x, 675 + 90 + yDifference * 90);
        return fallPos;
    }
    if (presentCoor.x == lastRowAtColumn1.x) {
        yDifference = (int)lastRowAtColumn1.y - (int)presentCoor.y;
        fallPos = ccp(presentPos.x, 675 + 90 + yDifference * 90);
        return fallPos;
    }
    if (presentCoor.x == lastRowAtColumn0.x) {
        yDifference = (int)lastRowAtColumn0.y - (int)presentCoor.y;
        fallPos = ccp(presentPos.x, 675 + 90 + yDifference * 90);
        return fallPos;
    }
    return exObj->getPosition();
}

bool TakasuPoppo::destroyCheck(TPObjectExtension *ex1) {
    if (toDestroyArray->count() != 0) {
        CCObject *object;
        CCARRAY_FOREACH(toDestroyArray, object) {
            TPBlockSet *blockSet = dynamic_cast<TPBlockSet*>(object);
            if (blockSet->getEx1()->getGid() == ex1->getGid()) {
                return false;
            }
        }
    }
    return true;
}

void TakasuPoppo::randomBlockC()
{
    CCObject* obj = new CCObject;
    CCARRAY_FOREACH(colorArray, obj){
        TPObjectExtension* exObj = dynamic_cast<TPObjectExtension* >(obj);
        if (exObj->getBlockType() == NORMAL_BLOCK_TYPE && (rand() % (int)gameTimer) == 0 && exObj->getSprite() != NULL) {
            makeBlockToBeHBC(exObj);
            exObj->setControlTrigger(false);
            hyperBlockC = false;
            break;
        }
    }

}

// intead of many function make block to be special block
void TakasuPoppo::createSpecialBlock(TPObjectExtension *exObj, int blockType){
    // change controlable
    if(exObj->getID() != 7 && exObj->getID() != 8)
    {
        exObj->setBlockType(blockType);
        // change sprite when the block be hyper
        int imageId = exObj->getID() + 1;
        CCImage *poppoB = new CCImage;
        string str = static_cast<ostringstream*>( &(ostringstream() << imageId) )->str();
        switch (blockType) {
            case HBA_BLOCK_TYPE:
                str = "Poppo" + str + "HyperA.png";
                break;
            case HBB_BLOCK_TYPE:
                str = "Poppo" + str + "HyperB.png";
                break;
            case MB1_BLOCK_TYPE:
                str = "Poppo" + str + "Mission1.png";
                break;
            case MB2_BLOCK_TYPE:
                str = "Poppo" + str + "Mission2.png";
                break;
            case MB3_BLOCK_TYPE:
                str = "Poppo" + str + "Mission3.png";
                break;

            default:
                break;
        }
        
        poppoB->initWithImageFile(str.c_str());
        CCTexture2D *poppoTexture = new CCTexture2D;
        poppoTexture->initWithImage(poppoB);
        CCSprite *poppoSprite = exObj->getSprite();
        poppoSprite->setTexture(poppoTexture);
        exObj->setSprite(poppoSprite);
    }

}

void TakasuPoppo::generateBlocksAfterCleanMB1() {
    CCSize layerSize = layer->getLayerSize();
    int colorId1 = rand() % 7;
    int colorId2;
    do {
        colorId2 = rand() % 7;
    } while (colorId2 == colorId1);
    int randomTile;
    char tileName[7][20];
    strcpy(tileName[0], "Poppo1A");
    strcpy(tileName[1], "Poppo2A");
    strcpy(tileName[2], "Poppo3A");
    strcpy(tileName[3], "Poppo4A");
    strcpy(tileName[4], "Poppo5A");
    strcpy(tileName[5], "Poppo6A");
    strcpy(tileName[6], "Poppo7A");

    
    for (int y = 0; y < layerSize.height; y++) {
        for (int x = 0; x < layerSize.width; x++) {
            
            CCSprite *tileSprite = layer->tileAt(ccp(x, y));
            unsigned int m_gid = layer->tileGIDAt(ccp(x, y));
            
                        
            if (m_gid % 2 == 1) {
                randomTile = colorId1;
            } else {
                randomTile = colorId2;
            }
            
            char spriteName[100];
            
            sprintf(spriteName, "%s.png", tileName[randomTile]);
            
            CCSprite *randomTileSprite = CCSprite::create(spriteName);
            CCPoint tilePosition = ccp(tileSprite->getPositionX() + tileSprite->getContentSize().width/2,
                                       tileSprite->getPositionY() + 90 + tileSprite->getContentSize().height/2);
            CCPoint tileCoordination = TakasuPoppo::tileCoorForPosition(tilePosition);
            randomTileSprite->setPosition(ccp(tilePosition.x, tilePosition.y + 10));
            CCObject *object = colorArray->objectAtIndex(m_gid - 1);
            TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
            TakasuPoppo::setValuesForExObj(exObj, randomTile, m_gid, randomTileSprite, tilePosition, tileCoordination, true, 0);
            
            this->addChild(randomTileSprite, 3, 300 + m_gid);
        }
    }
    
    isCleanMB1 = false;
}

