//
//  Touches.cpp
//  Cocos2Dx
//
//  Created by macbook_006 on 13/06/27.
//
//

#include "TakasuPoppo.h"
#pragma mark Touches

void TakasuPoppo::ccTouchesBegan(CCSet *touches, CCEvent *event) {
    CCTouch *touch = (CCTouch*)touches->anyObject();
    CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
    
    if (TakasuPoppo::touchPosValidation(touchLoc)) {
        TPObjectExtension *exObject = TakasuPoppo::coorToExObj(TakasuPoppo::tileCoorForPosition(touchLoc));
        if (exObject->getSprite()) {
            swipeRecognized = false;
            startSwipePoint = touchLoc;
            pickedArray->addObject(exObject);
            spriteContained = true;
        }
    }
    
    CCRect buttonRect = buttonSprite->boundingBox();
    CCRect clearRect = removeButton->boundingBox();
    CCRect refreshRect = refreshButton->boundingBox();
    if (buttonRect.containsPoint(touchLoc) && !gridOn)TakasuPoppo::switchGrid();
    if (clearRect.containsPoint(touchLoc) && gridOn)TakasuPoppo::remove();
    if (refreshRect.containsPoint(touchLoc))
        this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(TakasuPoppo::destroyAllBlocks)),
                                           CCCallFunc::create(this, callfunc_selector(TakasuPoppo::createFixture)),NULL));
}

void TakasuPoppo::ccTouchesMoved (CCSet *touches, CCEvent *event) {
    CCTouch *touch = (CCTouch*)touches->anyObject();
    if (spriteContained) {
        CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
        movingSwipePoint = touchLoc;
        
        if (!swipeRecognized) swiping = true;
        else swiping = false;
        
        if (swiping == true) {
            CCRect touchRect = CCRect(touchLoc.x, touchLoc.y, 70, 70);
            
            CCRect swipeRightRect = CCRectMake((startSwipePoint.x + 40), startSwipePoint.y, 80, 20);
            CCRect swipeLeftRect = CCRectMake((startSwipePoint.x - 40), startSwipePoint.y, 80, 20);
            CCRect swipeUpRect = CCRectMake(startSwipePoint.x, startSwipePoint.y + (40), 20, 80);
            CCRect swipeDownRect = CCRectMake(startSwipePoint.x, startSwipePoint.y - (40), 20, 80);
            
            if ((movingSwipePoint.x - startSwipePoint.x > 10) && touchRect.intersectsRect(swipeRightRect)) {
                swipeRecognized = true;
                swipeRight = true;
            }
            else if ((startSwipePoint.x - movingSwipePoint.x > 10) && touchRect.intersectsRect(swipeLeftRect)) {
                swipeRecognized = true;
                swipeLeft = true;
            }
            else if ((movingSwipePoint.y - startSwipePoint.y > 10) && touchRect.intersectsRect(swipeUpRect)) {
                swipeRecognized = true;
                swipeUp = true;
            }
            else if ((startSwipePoint.y - movingSwipePoint.y > 10) && touchRect.intersectsRect(swipeDownRect)) {
                swipeRecognized = true;
                swipeDown = true;
            }
            else if (!touchRect.intersectsRect(swipeRightRect) && !touchRect.intersectsRect(swipeLeftRect)
                     && !touchRect.intersectsRect(swipeUpRect) && !touchRect.intersectsRect(swipeDownRect)) swipeRecognized = true;
        }
    }
}

void TakasuPoppo::ccTouchesEnded(CCSet *touches, CCEvent *event) {
    CCTouch *touch = (CCTouch*)touches->anyObject();
    CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
    swiping = false;
    
    if (TakasuPoppo::touchPosValidation(touchLoc)) {
        CCTMXLayer *layer = map->layerNamed("Grids");
        CCSize layerSize = layer->getLayerSize();
        CCSize tileSize = layer->getMapTileSize();
        CCPoint transPoint = TakasuPoppo::tileCoorForPosition(touchLoc);
        unsigned int m_gid = layer->tileGIDAt(transPoint);
        CCLog("Tile ID at position : %i", m_gid);
        
    }
    pickedArray->removeAllObjects();
    
}

bool TakasuPoppo::touchPosValidation(CCPoint touchLoc) {
    if (touchLoc.x < 0 ||
        touchLoc.y < 0 ||
        touchLoc.x >= map->getContentSize().width ||
        touchLoc.y >= map->getContentSize().height)
        return false;
    else return true;
}


