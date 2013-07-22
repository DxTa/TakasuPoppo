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
            CCPoint coor = ccp(x, y);
            int gid = layer->tileGIDAt(coor);
            int gidToIndex = gid - 1;
            CCObject *object = colorArray->objectAtIndex(gidToIndex);
            TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
            match->addObject(exObj);
            if (exObj->getCoordination().x == coor.x &&
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
                        TPBlockSet *blockSet = new TPBlockSet(exObj, exObj2, exObj3, NULL, NULL,
                                                              "TrioHor", exObj->getCoordination().x, exObj->getCoordination().y);
                        toDestroyArray->addObject(blockSet);
                        if (comboTimer <= 0) comboTimer = 5;
                        if (comboTimer > 0) comboCounter += 1;
                    }
                    if (match->count() == 4) {
                        TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(1));
                        TPObjectExtension *exObj3 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(2));
                        TPObjectExtension *exObj4 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(3));
                        exObj->setControlTrigger(false);
                        exObj2->setControlTrigger(false);
                        exObj3->setControlTrigger(false);
                        exObj4->setControlTrigger(false);
                        TPBlockSet *blockSet = new TPBlockSet(exObj, exObj2, exObj3, exObj4, NULL,
                                                              "QuadHor", exObj->getCoordination().x, exObj->getCoordination().y);
                        toDestroyArray->addObject(blockSet);
                        if (comboTimer <= 0) comboTimer = 5;
                        if (comboTimer > 0) comboCounter += 1;
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
                                                              "PentaHor", exObj->getCoordination().x, exObj->getCoordination().y);
                        toDestroyArray->addObject(blockSet);
                        if (comboTimer <= 0) comboTimer = 5;
                        if (comboTimer > 0) comboCounter += 1;
                    }
                }
            }
        }
    }
    
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 5; y++) {
            CCArray *match = new CCArray;
            CCPoint coor = ccp(x, y);
            int gid = layer->tileGIDAt(coor);
            int gidToIndex = gid - 1;
            CCObject *object = colorArray->objectAtIndex(gidToIndex);
            TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
            match->addObject(exObj);
            if (exObj->getCoordination().x == coor.x &&
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
                        TPBlockSet *blockSet = new TPBlockSet(exObj, exObj2, exObj3, NULL, NULL,
                                                              "TrioVer", exObj->getCoordination().x, exObj->getCoordination().y);
                        toDestroyArray->addObject(blockSet);
                        if (comboTimer <= 0) comboTimer = 5;
                        if (comboTimer > 0) comboCounter += 1;
                    }
                    if (match->count() == 4) {
                        TPObjectExtension *exObj2 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(1));
                        TPObjectExtension *exObj3 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(2));
                        TPObjectExtension *exObj4 = dynamic_cast<TPObjectExtension*>(match->objectAtIndex(3));
                        exObj->setControlTrigger(false);
                        exObj2->setControlTrigger(false);
                        exObj3->setControlTrigger(false);
                        exObj4->setControlTrigger(false);
                        TPBlockSet *blockSet = new TPBlockSet(exObj, exObj2, exObj3, exObj4, NULL,
                                                              "QuadVer", exObj->getCoordination().x, exObj->getCoordination().y);
                        toDestroyArray->addObject(blockSet);
                        if (comboTimer <= 0) comboTimer = 5;
                        if (comboTimer > 0) comboCounter += 1;
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
                                                              "PentaVer", exObj->getCoordination().x, exObj->getCoordination().y);
                        toDestroyArray->addObject(blockSet);
                        if (comboTimer <= 0) comboTimer = 5;
                        if (comboTimer > 0) comboCounter += 1;
                    }
                }
            }
        }
    }
    
}

CCArray *TakasuPoppo::getMatchHor(TPObjectExtension *exObj) {
    CCArray *matches = new CCArray;
    int colNum= exObj->getCoordination().x;
    for (int ct = 1; colNum + ct < 7; ct++) {
        CCPoint coor = ccp(colNum + ct, exObj->getCoordination().y);
        int gid = layer->tileGIDAt(coor);
        int gidToIndex = gid - 1;
        CCObject *object = colorArray->objectAtIndex(gidToIndex);
        TPObjectExtension *checkObj = dynamic_cast<TPObjectExtension*>(object);
        if (checkObj->getID() == exObj->getID() &&
            exObj->getID() != 7) {
            matches->addObject(checkObj);
        }
        else return matches;
    }
    return matches;
}

CCArray *TakasuPoppo::getMatchVer(TPObjectExtension *exObj) {
    CCArray *matches = new CCArray;
    int rowNum= exObj->getCoordination().y;
    for (int ct = 1; rowNum + ct < 7; ct++) {
        CCPoint coor = ccp(exObj->getCoordination().x, rowNum + ct);
        int gid = layer->tileGIDAt(coor);
        int gidToIndex = gid - 1;
        CCObject *object = colorArray->objectAtIndex(gidToIndex);
        TPObjectExtension *checkObj = dynamic_cast<TPObjectExtension*>(object);
        if (checkObj->getID() == exObj->getID() &&
            exObj->getID() != 7) {
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
//    CCLog("There are %i possible matches", match);
    return match;
}

bool TakasuPoppo::sumOfMatches(TPObjectExtension *exA, TPObjectExtension *exB,
                               TPObjectExtension *ex1, TPObjectExtension *ex2, TPObjectExtension *ex3) {
        if (ex1 != NULL && ex1->getID() == exA->getID()) {
            if (hintArray->count() < 5) hintArray->addObject(ex1);
            return true;
        }
        if (ex2 != NULL && ex2->getID() == exA->getID()) {
            if (hintArray->count() < 5) hintArray->addObject(ex2);
            return true;
        }
        if (ex3 != NULL && ex3->getID() == exA->getID()) {
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
    if (TakasuPoppo::lookForMatches() > 0) {
        CCObject *object;
        CCARRAY_FOREACH(colorArray, object) {
            TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
            if (exObj->getID() == 7) {
                TakasuPoppo::generateRandomBlock(exObj);
            }
        }
        controlable = true;
        return;
    }
    
    if (TakasuPoppo::lookForMatches() == 0) {
        CCObject *object;
        CCARRAY_FOREACH_REVERSE(colorArray, object) {
            TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
            int x = exObj->getCoordination().x;
            int y = exObj->getCoordination().y;
            CCPoint aPoint = ccp(x, y);
            CCPoint bPoint = ccp(x + 1, y);
            CCPoint ePoint = ccp(x, y - 1);
            CCPoint hPoint = ccp(x, y - 2);
            CCPoint nPoint = ccp(x - 1, y);
            CCPoint u1Point = ccp(x -2, y);
            CCPoint oPoint = ccp(x, y + 1);
            CCPoint xPoint = ccp(x, y + 2);
            CCPoint sPoint = ccp(x - 1, y + 1);
            CCPoint h1Point = ccp(x - 2, y + 2);
            CCPoint jPoint = ccp(x, y +2);
            
            
            TPObjectExtension *aExObj = TakasuPoppo::coorToExObj(aPoint);
            TPObjectExtension *bExObj = TakasuPoppo::coorToExObj(bPoint);
            TPObjectExtension *u1ExObj = TakasuPoppo::coorToExObj(u1Point);
            TPObjectExtension *eExObj = TakasuPoppo::coorToExObj(ePoint);
            TPObjectExtension *hExObj = TakasuPoppo::coorToExObj(hPoint);
            TPObjectExtension *nExObj = TakasuPoppo::coorToExObj(nPoint);
            TPObjectExtension *oExObj = TakasuPoppo::coorToExObj(oPoint);
            TPObjectExtension *xExObj = TakasuPoppo::coorToExObj(xPoint);
            TPObjectExtension *sExObj = TakasuPoppo::coorToExObj(sPoint);
            TPObjectExtension *h1ExObj = TakasuPoppo::coorToExObj(h1Point);
            TPObjectExtension *jExObj = TakasuPoppo::coorToExObj(jPoint);
            
            if(aExObj != NULL && aExObj->getID() == 7){
                
                if (eExObj != NULL && eExObj->getID() == 7) {
                    if (hExObj != NULL && hExObj->getID() == 7) {
                        if(aExObj->getGid() <= 42 && oExObj != NULL && oExObj->getID() !=7)
                        {
                            generateRandomBlock(aExObj);
                            generateBlock(hExObj, oExObj->getID());
                            generateBlock(eExObj, oExObj->getID());
                            aExObj->setControlTrigger(true);
                            hExObj->setControlTrigger(true);
                            eExObj->setControlTrigger(true);
                            controlable = true ;
                            continue;
                        }
                        else if(aExObj->getGid() <= 35 && xExObj != NULL && xExObj->getGid() != 7)
                        {
                            generateRandomBlock(hExObj);
                            generateBlock(aExObj, xExObj->getID());
                            generateBlock(eExObj, xExObj->getID());
                            aExObj->setControlTrigger(true);
                            hExObj->setControlTrigger(true);
                            eExObj->setControlTrigger(true);
                            controlable =true ;
                            continue;
                        }
                        else if (aExObj->getGid()%7 != 0 &&  bExObj != NULL && bExObj->getID() != 7)
                        {
                            generateRandomBlock(aExObj);
                            generateBlock(hExObj, bExObj->getID());
                            generateBlock(eExObj, bExObj->getID());
                            aExObj->setControlTrigger(true);
                            hExObj->setControlTrigger(true);
                            eExObj->setControlTrigger(true);
                            controlable =true ;
                            continue;
                        }
                        else if (aExObj->getGid() % 7 !=1 && (nExObj != NULL && nExObj->getID() != 7))
                        {
                            generateRandomBlock(aExObj);
                            generateBlock(hExObj, nExObj->getID());
                            generateBlock(eExObj, nExObj->getID());
                            aExObj->setControlTrigger(true);
                            hExObj->setControlTrigger(true);
                            eExObj->setControlTrigger(true);
                            controlable = true ;
                            continue;
                        }
                    }
                    else
                        if(aExObj->getGid() >= 8 && aExObj->getGid() <= 42 && oExObj != NULL && oExObj->getID() !=7)
                        {
                            generateBlock(aExObj, oExObj->getID());
                            generateBlock(eExObj, oExObj->getID());
                            aExObj->setControlTrigger(true);
                            eExObj->setControlTrigger(true);
                            controlable = true ;
                            continue;
                        }
                }
                if(aExObj->getGid() % 7 !=1 && nExObj != NULL && nExObj->getID() == 7)
                {
                    
                    if(u1ExObj != NULL && u1ExObj->getID() ==7)
                    {
                        if((aExObj->getGid()-1)%7 >= 2 && aExObj->getGid() <= 35)
                        {
                            if(sExObj != NULL && xExObj != NULL && sExObj->getID() == xExObj->getID() && sExObj->getID() != 7)
                            {
                                generateRandomBlock(u1ExObj);
                                generateBlock(aExObj, sExObj->getID());
                                generateRandomBlock(nExObj);
                                aExObj->setControlTrigger(true);
                                u1ExObj->setControlTrigger(true);
                                nExObj->setControlTrigger(true);
                                controlable = true ;
                                continue;
                            }
                            if(sExObj != NULL && h1ExObj != NULL && sExObj->getID() == h1ExObj->getID() && sExObj->getID() != 7)
                            {
                                generateRandomBlock(u1ExObj);
                                generateBlock(nExObj, sExObj->getID());
                                generateRandomBlock(aExObj);
                                aExObj->setControlTrigger(true);
                                u1ExObj->setControlTrigger(true);
                                nExObj->setControlTrigger(true);
                                controlable = true ;
                                continue;
                            }
                            if(sExObj != NULL && hExObj != NULL && sExObj->getID() == hExObj->getID() && sExObj->getID() != 7)
                            {
                                generateRandomBlock(aExObj);
                                generateBlock(u1ExObj, sExObj->getID());
                                generateRandomBlock(nExObj);
                                aExObj->setControlTrigger(true);
                                u1ExObj->setControlTrigger(true);
                                nExObj->setControlTrigger(true);
                                controlable = true ;
                                continue;
                            }
                            if(sExObj != NULL && jExObj != NULL && sExObj->getID() == jExObj->getID() && sExObj->getID() != 7)
                            {
                                generateRandomBlock(u1ExObj);
                                generateBlock(nExObj, sExObj->getID());
                                generateRandomBlock(aExObj);
                                aExObj->setControlTrigger(true);
                                u1ExObj->setControlTrigger(true);
                                nExObj->setControlTrigger(true);
                                controlable = true ;
                                continue;
                            }
                        }
                        
                        if((aExObj->getGid()-1)%7 <= 5 && bExObj != NULL && bExObj->getID() != 7)
                        {
                            generateRandomBlock(aExObj);
                            generateBlock(u1ExObj, bExObj->getID());
                            generateBlock(nExObj, bExObj->getID());
                            aExObj->setControlTrigger(true);
                            u1ExObj->setControlTrigger(true);
                            nExObj->setControlTrigger(true);
                            controlable = true ;
                            continue;
                        }
                        if(aExObj->getGid()<= 42 && oExObj != NULL && oExObj->getID() != 7){
                            generateRandomBlock(aExObj);
                            generateBlock(u1ExObj, oExObj->getGid());
                            generateBlock(nExObj, oExObj->getID());
                            aExObj->setControlTrigger(true);
                            u1ExObj->setControlTrigger(true);
                            nExObj->setControlTrigger(true);
                            controlable = true ;
                            continue;
                        }
                    }
                    else {
                        if((aExObj->getGid() <= 42 && oExObj != NULL && oExObj->getID() != 7)){
                            generateBlock(aExObj, oExObj->getID());
                            generateBlock(nExObj, oExObj->getID());
                            aExObj->setControlTrigger(true);
                            nExObj->setControlTrigger(true);
                            controlable = true ;
                            continue;
                        }
                    }
                }
                else{
                    generateRandomBlock(aExObj);
                    aExObj->setControlTrigger(true);
                    controlable = true ;
                    continue;
                }
            }
            //exObj->setControlTrigger(true);
        }
        controlable = true;
        return;
    }
}
