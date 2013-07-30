//
//  TP_Debug.cpp
//  Cocos2Dx
//
//  Created by macbook_006 on 13/06/28.
//
//

#include "TakasuPoppo.h"
#include "TPBlockSet.h"
#pragma mark Debug
void TakasuPoppo::setupDebugButton() {
    buttonSprite = CCSprite::create("ShowGridButton.png");
    buttonSprite->setPosition(ccp(buttonSprite->getContentSize().width/2 + 15, winSize.height - buttonSprite->getContentSize().height/2 - 15));
    this->addChild(buttonSprite, 3);
    
    refreshButton = CCSprite::create("RefreshButton.png");
    refreshButton->setPosition(ccp(refreshButton->getContentSize().width/2 + 230, winSize.height - refreshButton->getContentSize().height/2 - 15));
    this->addChild(refreshButton, 3);
    
    removeButton = CCSprite::create("ClearButton.png");
    removeButton->setPosition(ccp(removeButton->getContentSize().width/2 + 445, winSize.height - removeButton->getContentSize().height/2 - 15));
    this->addChild(removeButton, 3);
}

void TakasuPoppo::switchGrid() {
    if (!gridOn) {
        CCSize layerSize = layer->getLayerSize();
        CCObject *object = NULL;
        CCARRAY_FOREACH(colorArray, object) {
            TPObjectExtension *exObject = dynamic_cast<TPObjectExtension*>(object);
            CCPoint spritePos = exObject->getPosition();
            CCSprite *backgroundTile = CCSprite::create("Background.png");
            CCString *idString = CCString::createWithFormat("%i", exObject->getID());
            CCLabelTTF *stringLabel = CCLabelTTF::create(idString->getCString(), "Arial", 30);
            stringLabel->setPosition(spritePos);
            backgroundTile->setPosition(spritePos);
            
            this->addChild(backgroundTile, 3 , 801);
            this->addChild(stringLabel, 4 , 802);
            
            debugTilesArray->addObject(stringLabel);
            debugTilesArray->addObject(backgroundTile);
            gridOn = true;
        }
    }
}

void TakasuPoppo::remove() {
    CCObject *object;
    CCARRAY_FOREACH(debugTilesArray, object) {
        CCSprite *sprite = dynamic_cast<CCSprite*>(object);
        this->removeChild(sprite);
        gridOn = false;
    }
}

void TakasuPoppo::refresh() {
    TakasuPoppo::remove();
    TakasuPoppo::switchGrid();
}


void TakasuPoppo::destroyAllBlocks() {
    CCObject *object;
    CCARRAY_FOREACH(colorArray, object) {
        TPObjectExtension* exObj = dynamic_cast<TPObjectExtension*>(object);
        CCSprite *toRemoveSprite = exObj->getSprite();
        this->runAction(CCCallFuncND::create(this, callfuncND_selector(TakasuPoppo::popAnimation), (void*)exObj));
        this->removeChild(toRemoveSprite, true);
        exObj->setSprite(NULL);
        exObj->setID(7);
    }
}

void TakasuPoppo::menuCloseCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
