//  Created by MinhNT on 13/05/16.
//  Copyright FRAMGIA 2013年. All rights reserved.
//
#include "TPObjectExtension.h"

using namespace cocos2d;
using namespace std;
USING_NS_CC;

TPObjectExtension::TPObjectExtension(int id, int gid, CCSprite* sprite,
                                     CCPoint position, CCPoint coordination, bool controlable, int blockType) {
    this->colorId = id;
    this->gid = gid;
    this->blockSprite = sprite;
    this->position = position;
    this->coordination = coordination;
    this->controlable = controlable;
    this->blockType = blockType;
}

int TPObjectExtension::getID() {
    return this->colorId;
}

void TPObjectExtension::setID(int id) {
    this->colorId=id;
}

int TPObjectExtension::getGid() {
    return gid;
}

void TPObjectExtension::setGid(int c) {
    this->gid = c;
}

CCSprite *TPObjectExtension::getSprite() {
    return blockSprite;
}

void TPObjectExtension::setSprite(CCSprite *sprite) {
    this->blockSprite = sprite;
}

CCPoint TPObjectExtension::getPosition() {
    return position;
}

void TPObjectExtension::setPosition(CCPoint position) {
    this->position = position;
}

CCPoint TPObjectExtension::getCoordination() {
    return coordination;
}

void TPObjectExtension::setCoordination(CCPoint coordination) {
    this->coordination = coordination;
}

bool TPObjectExtension::getControlTrigger() {
    return controlable;
}

void TPObjectExtension::setControlTrigger(bool trigger) {
    this->controlable = trigger;
}

int TPObjectExtension::getBlockType() {
    return blockType;
}

void TPObjectExtension::setBlockType(int blockType) {
    this->blockType = blockType;
}

