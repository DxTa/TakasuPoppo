//
//  TPItem.cpp
//  Cocos2Dx
//
//  Created by macbook_006 on 13/07/31.
//
//

#include "TPBlockSet.h"
#include "TPObjectExtension.h"
#include "TakasuPoppo.h"

bool TakasuPoppo::lastScore()
{
    this->runAction(CCDelayTime::create(5));
    CCObject* obj;
    int t = (int)(timeBonus/1.5);
    CCARRAY_FOREACH(colorArray, obj){
        this->runAction(CCDelayTime::create(4));
        TPObjectExtension* exObj = dynamic_cast<TPObjectExtension*>(obj);
        
        if(t==2){
            timeBonus = 0;
            if(exObj != NULL && exObj->getSprite() && exObj->getSprite() != NULL &&
               (exObj->getBlockType() == HBA_BLOCK_TYPE || exObj->getBlockType() == MOVED_HBA_BLOCK_TYPE))
            {
                this->getParent()->runAction(CCSequence::create(
                                                                CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::cleanHyperBlockA),(void*)exObj),
                                                                CCCallFunc::create(this, callfunc_selector(TakasuPoppo::logicExecution)),
                                                                NULL));
                return false;
            }
            if(exObj != NULL && exObj->getSprite() && exObj->getSprite() != NULL &&
               (exObj->getBlockType() == HBB_BLOCK_TYPE || exObj->getBlockType() == MOVED_HBB_BLOCK_TYPE))
            {
                this->getParent()->runAction(CCSequence::create(
                                                                CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::cleanHyperBlockB),(void*)exObj),
                                                                CCCallFunc::create(this, callfunc_selector(TakasuPoppo::logicExecution)),
                                                                NULL));
                return false;
            }
            if(exObj != NULL && exObj->getSprite() && exObj->getSprite() != NULL && exObj->getBlockType() == HBC_BLOCK_TYPE)
            {
                this->getParent()->runAction(CCSequence::create(
                                                                CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::cleanHyperBlockC),(void*)exObj),
                                                                CCCallFunc::create(this, callfunc_selector(TakasuPoppo::logicExecution)),
                                                                NULL));
                return false;
            }
            if (exObj->getGid() == 49 && exObj->getBlockType() == NORMAL_BLOCK_TYPE && gameTimer < 0) {
                endLastScore = true;
                //this->unschedule(schedule_selector(TakasuPoppo::fixedUpdate));
                lastScores = score - scoresBeforeLastBonus;
                return true;
            }
            
        }
    }
    return false;
}
void TakasuPoppo::addTime(){
    gameTimer = gameTimer + 5;
}

void TakasuPoppo::increasedScores()
{
    increasedScore = 1.1;
}

void TakasuPoppo::createMapWithHyperBlock()
{
    int gidA = rand() % 49;
    int gidB = rand() % 49;
    int gidC = rand() % 49;
    while(gidA == gidB || gidB == gidC || gidC == gidA){
        gidA = rand() % 49;
        gidB = rand() % 49;
        gidC = rand() % 49;
    }
    TPObjectExtension* exA = dynamic_cast<TPObjectExtension*>(colorArray->objectAtIndex(gidA));
    if(exA != NULL && exA->getSprite() && exA->getSprite() != NULL &&
       exA->getID() != 7 && exA->getBlockType() == NORMAL_BLOCK_TYPE)
        makeBlockToBeHBA(exA);
    
    TPObjectExtension* exB = dynamic_cast<TPObjectExtension*>(colorArray->objectAtIndex(gidB));
    if(exB != NULL && exB->getSprite() && exB->getSprite() != NULL && exB->getID() != 7 &&
       exB->getBlockType() == NORMAL_BLOCK_TYPE)
        makeBlockToBeHBB(exB);

    TPObjectExtension* exC = dynamic_cast<TPObjectExtension*>(colorArray->objectAtIndex(gidC));
    if(exC != NULL && exC->getSprite() && exC->getSprite() != NULL && exC->getID() != 7 &&
       exC->getBlockType() == NORMAL_BLOCK_TYPE)
        makeBlockToBeHBC(exC);
}

void TakasuPoppo::modefiedLastBonus()
{
    if(endLastScore && gameTimer < 0)
    {
        score = score + lastScores ;
        endLastScore = false;
    }
}