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
    
    hintCounter = 3;
    hintArray->removeAllObjects();
    if (this->getChildByTag(778)) this->removeChildByTag(778);
    hintDisplaying = false;
    
    CCTouch *touch = (CCTouch*)touches->anyObject();
    CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
    if (TakasuPoppo::touchPosValidation(touchLoc)) {
        CCPoint point = TakasuPoppo::tileCoorForPosition(touchLoc);
        if (point.x >= 0 || point.x <= 6 ||
            point.y >= 0 || point.y <= 6) {
            TPObjectExtension *exObject = TakasuPoppo::coorToExObj(TakasuPoppo::tileCoorForPosition(touchLoc));
            if (exObject != NULL && exObject->getSprite() != NULL && exObject->getID() != 7) {
                swipeRecognized = false;
                startSwipePoint = touchLoc;
                spriteContained = true;
                if(exObject != NULL)
                {
                    if(exObject->getID() != 7 && exObject->getBlockType() == HBC_BLOCK_TYPE && exObject->getSprite() && exObject->getSprite() != NULL && gameTimer > 0)
                    {
                        isHBCinBlockSet = true;
                        TPBlockSet* blockSet = new TPBlockSet(exObject, NULL, NULL, NULL, NULL, NULL, NULL, "hyperBlockC", exObject->getCoordination().x, exObject->getCoordination().y);
                        if(TakasuPoppo::destroyCheck(exObject, NULL)) toDestroyArray->addObject(blockSet);
                        move = false;
                        swape = false;
                        return;
                    }
                    else{
                        mainSprite = exObject;
                    }
                }
            }
            
            //============================ move by double click ===============
            
            if(move && !touchPosValidation(mainPoint)){
                TPObjectExtension *mainEx = TakasuPoppo::coorToExObj(mainPoint);
                CCPoint movePoint;
                movePoint.setPoint(point.x, point.y);
                if(mainEx != NULL && mainEx->getControlTrigger())
                {
                    if(movePoint.x == mainPoint.x - 1 && movePoint.y == mainPoint.y && mainPoint.x - 1 >= 0 && mainPoint.x - 1 < 7)
                    {
                        movedSprite = NULL;
                        swapedSprite = NULL;
                        move = false;
                        spriteContained = false;
                        swipeLeft = false;
                        swipeRight = false;
                        swipeUp = false;
                        swipeDown = false;
                        swipedLeft(mainEx);
                        swape = false;
                        return;
//                        goto tt;
                    }
                    if(movePoint.x == mainPoint.x + 1 && movePoint.y == mainPoint.y && mainPoint.x + 1 >= 0 && mainPoint.x + 1 < 7)
                    {
                        movedSprite = NULL;
                        swapedSprite = NULL;
                        move = false;
                        spriteContained = false;
                        swipeLeft = false;
                        swipeRight = false;
                        swipeUp = false;
                        swipeDown = false;

                        swipedRight(mainEx);
                        swape = false;
                        return;
//                        goto tt;
                    }
                    if(movePoint.x == mainPoint.x && movePoint.y == mainPoint.y - 1 && mainPoint.y - 1 >= 0 && mainPoint.y - 1 < 7)
                    {
                        movedSprite = NULL;
                        swapedSprite = NULL;
                        move = false;
                        spriteContained = false;
                        swipeLeft = false;
                        swipeRight = false;
                        swipeUp = false;
                        swipeDown = false;


                        swipedUp(mainEx);
                        swape = false;
                        return;
//                        goto tt;
                    }
                    if(movePoint.x == mainPoint.x && movePoint.y == mainPoint.y + 1 && mainPoint.y + 1 >= 0 && mainPoint.y + 1 < 7)
                    {
                        movedSprite = NULL;
                        swapedSprite = NULL;
                        move = false;
                        spriteContained = false;
                        swipeLeft = false;
                        swipeRight = false;
                        swipeUp = false;
                        swipeDown = false;


                        swipedDown(mainEx);
                        swape = false;
                        return;
//                        goto tt;
                    }
                    move = true;
                    swape = true;
                    mainPoint.setPoint(point.x, point.y);
                }
            }
            else {
                move = true;
                swape = true;
                mainPoint.setPoint(point.x, point.y);
            }
//            //=================================================================
            
        }
    }
//tt:
    
//    CCRect buttonRect = buttonSprite->boundingBox();
//    CCRect clearRect = removeButton->boundingBox();
//    CCRect refreshRect = refreshButton->boundingBox();
//    if (buttonRect.containsPoint(touchLoc) && !gridOn) TakasuPoppo::switchGrid();
//    if (clearRect.containsPoint(touchLoc) && gridOn) TakasuPoppo::remove();
//    if (refreshRect.containsPoint(touchLoc))
//    {
//        this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(TakasuPoppo::destroyAllBlocks)),
//                                           CCCallFunc::create(this, callfunc_selector(TakasuPoppo::createFixture)),NULL));
//    }
//    
    
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
            
            if ((movingSwipePoint.x - startSwipePoint.x > 8) && touchRect.intersectsRect(swipeRightRect)) {
                swipeRecognized = true;
                swipeRight = true;
            }
            else if ((startSwipePoint.x - movingSwipePoint.x > 8) && touchRect.intersectsRect(swipeLeftRect)) {
                swipeRecognized = true;
                swipeLeft = true;
            }
            else if ((movingSwipePoint.y - startSwipePoint.y > 8) && touchRect.intersectsRect(swipeUpRect)) {
                swipeRecognized = true;
                swipeUp = true;
            }
            else if ((startSwipePoint.y - movingSwipePoint.y > 8) && touchRect.intersectsRect(swipeDownRect)) {
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
        CCTMXLayer *layer = map->layerNamed("Layer");
        CCSize layerSize = layer->getLayerSize();
        CCSize tileSize = layer->getMapTileSize();
        CCPoint transPoint = TakasuPoppo::tileCoorForPosition(touchLoc);
        unsigned int m_gid = layer->tileGIDAt(transPoint);
        CCLog("Tile ID at position : %i", m_gid);
    }
}

bool TakasuPoppo::touchPosValidation(CCPoint touchLoc) {
    if (touchLoc.x < 0 ||
        touchLoc.y < 90 ||
        touchLoc.x >= map->getContentSize().width ||
        touchLoc.y >= map->getContentSize().height + 90)
        return false;
    else return true;
}
