//
//  TP_Map.cpp
//  Cocos2Dx
//
//  Created by macbook_006 on 13/06/28.
//
//

#include "TakasuPoppo.h"
#pragma mark Tile Functions

void TakasuPoppo::addTileMap () {
    map = CCTMXTiledMap::create("AnotherMap.tmx");
    this->addChild(map, -1, -1);
    layer = map->layerNamed("Grids");
    TakasuPoppo::createFixture();
    
    CCArray *pChildrenArray = map->getChildren();
    CCObject *pObject = NULL;
    CCSpriteBatchNode *child = NULL;
    CCARRAY_FOREACH(pChildrenArray, pObject) {
        child = ((CCSpriteBatchNode *)pObject);
        if (!child) break;
        child->getTexture()->setAntiAliasTexParameters();
    }
}

void TakasuPoppo::createFixture() {
    CCSize layerSize = layer->getLayerSize();
    
    for (int y = 0; y < layerSize.height; y++) {
        for (int x = 0; x < layerSize.width; x++) {
            
            CCSprite *tileSprite = layer->tileAt(ccp(x, y));
            unsigned int m_gid = layer->tileGIDAt(ccp(x, y));
            
            char tileName[7][20];
            strcpy(tileName[0], "Candy");
            strcpy(tileName[1], "Candy2");
            strcpy(tileName[2], "Candy3");
            strcpy(tileName[3], "Candy4");
            strcpy(tileName[4], "Candy5");
            strcpy(tileName[5], "Candy6");
            strcpy(tileName[6], "Candy7");
            int randomTile = rand() % 7;
            char spriteName[100];
            
            while (TakasuPoppo::isTileMatched(m_gid, randomTile)) randomTile = rand() % 7;
            
            sprintf(spriteName, "%s.png", tileName[randomTile]);
            
            CCSprite *randomTileSprite = CCSprite::create(spriteName);
            CCPoint tilePosition = ccp(tileSprite->getPositionX() + tileSprite->getContentSize().width/2,
                                       tileSprite->getPositionY() + tileSprite->getContentSize().height/2);
            CCPoint tileCoordination = TakasuPoppo::tileCoorForPosition(tilePosition);
            randomTileSprite->setPosition(ccp(tilePosition.x, tilePosition.y + 10));
            CCObject *object = colorArray->objectAtIndex(m_gid - 1);
            TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
            TakasuPoppo::setValuesForExObj(exObj, randomTile, m_gid, randomTileSprite, tilePosition, tileCoordination, true);
            CCLog("Tile %i added - Color:%i; GID:%i, TileSprite:%s, TilePosition: X%i Y%i, Tile Coordination; X%i Y%i.",
                  colorArray->indexOfObject(exObj), randomTile, m_gid, spriteName, (int)tilePosition.x, (int)tilePosition.y,
                  (int)tileCoordination.x, (int)tileCoordination.y);
            
            this->addChild(randomTileSprite, 3, 300 + m_gid);
        }
    }
}

CCPoint TakasuPoppo::tileCoorForPosition(CCPoint position) {
    float x = position.x / map->getTileSize().width;
    float y = ((winSize.height - position.y)/(map->getTileSize().height)) -1;
    CCPoint transPos = ccp(floor(x), floor(y));
    return transPos;
}

void TakasuPoppo::swapColorID(TPObjectExtension *exObj, TPObjectExtension *swpObj) {
    int exID = exObj->getID();
    CCSprite *exSprite = exObj->getSprite();
    int swpID = swpObj->getID();
    CCSprite *swpSprite = swpObj->getSprite();
    
    exObj->setID(swpID);
    swpObj->setID(exID);
    exObj->setSprite(swpSprite);
    swpObj->setSprite(exSprite);
    CCLog("Tile %i's color %i got swaped with tile %i's color %i.",
          exObj->getGid(), exObj->getID(), swpObj->getGid(), swpObj->getID());
}

void TakasuPoppo::checkEmpty() {
    CCObject *object;
    CCARRAY_FOREACH_REVERSE(colorArray, object) {
        TPObjectExtension *exObj = dynamic_cast<TPObjectExtension*>(object);
        if (exObj->getID() == 7) {
            generateRandomBlock(exObj);
        }
    }
}

void TakasuPoppo::generateRandomBlock(TPObjectExtension *exObj) {
    char tileName[7][20];
    strcpy(tileName[0], "Candy");
    strcpy(tileName[1], "Candy2");
    strcpy(tileName[2], "Candy3");
    strcpy(tileName[3], "Candy4");
    strcpy(tileName[4], "Candy5");
    strcpy(tileName[5], "Candy6");
    strcpy(tileName[6], "Candy7");
    int randomTile = rand() % 7;
    char spriteName[100];
    
    sprintf(spriteName, "%s.png", tileName[randomTile]);
    
    CCSprite *randomTileSprite = CCSprite::create(spriteName);
    randomTileSprite->setPosition(ccp(exObj->getPosition().x, exObj->getPosition().y + 70));
    randomTileSprite->runAction(CCMoveTo::create(0.3, exObj->getPosition()));
    exObj->setSprite(randomTileSprite);
    exObj->setID(randomTile);
    this->addChild(randomTileSprite, 3, 300 + exObj->getGid());
}

