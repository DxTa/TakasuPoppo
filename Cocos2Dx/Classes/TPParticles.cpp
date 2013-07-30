//
//  TPParticles.cpp
//  Cocos2Dx
//
//  Created by Ace on 2013/07/02.
//
//

#include "TakasuPoppo.h"

void TakasuPoppo::popParticles(CCPoint point) {
    //CCTexture2D *texture = CCTextureCache::sharedTextureCache()->textureForKey("Star.png");
    CCParticleSystemQuad *pop = new CCParticleSystemQuad;
    pop = CCParticleFireworks::create();
    pop->setTexture(CCTextureCache::sharedTextureCache()->addImage("Star.png"));
    pop->setPosition(point);
    pop->setGravity(CCPointZero);
    
    pop->setAngle(140);
    pop->setAngleVar(360);
    
    pop->setSpeed(80);
    //pop->setSpeedVar(360);
    
    pop->setStartSize(40);
    
    pop->setLife(0.1);
    pop->setPositionType(kCCPositionTypeRelative);
    
    pop->setRadialAccel(-50);
    //pop->setRadialAccelVar(-100);
    
    //pop->setTangentialAccel(-50);
    pop->setTotalParticles(9);
    //pop->setRotatePerSecond(0);
    pop->setAutoRemoveOnFinish(true);
    pop->setAtlasIndex(0);
    pop->setBlendAdditive(false);
    //pop->setOrderOfArrival(0);
    pop->setOpacityModifyRGB(false);
    pop->setDuration(0.5);
    pop->setEmissionRate(200);
    //pop->setEndRadius(50);
    this->addChild(pop, 5, 777);
}

void TakasuPoppo::remoteParticles() {
    this->removeChildByTag(777, true);
}

void TakasuPoppo::hintParticles(TPObjectExtension *exObj) {
    CCParticleSystemQuad *pop = new CCParticleSystemQuad;
    pop = CCParticleSpiral::create();
    pop->setTexture(CCTextureCache::sharedTextureCache()->addImage("Star.png"));
    pop->setPosition(exObj->getPosition());
    pop->setGravity(CCPointZero);
    
    pop->setAngle(140);
    pop->setAngleVar(360);
    
    pop->setSpeed(80);
    //pop->setSpeedVar(360);
    
    pop->setStartSize(40);
    
    //pop->setLife(0.1);
    pop->setPositionType(kCCPositionTypeRelative);
    
    pop->setRadialAccel(-50);
    //pop->setRadialAccelVar(-100);
    
    //pop->setTangentialAccel(-50);
    pop->setTotalParticles(9);
    //pop->setRotatePerSecond(0);
    //pop->setAutoRemoveOnFinish(true);
    pop->setAtlasIndex(0);
    pop->setBlendAdditive(false);
    //pop->setOrderOfArrival(0);
    pop->setOpacityModifyRGB(false);
    pop->setDuration(0.5);
    pop->setEmissionRate(200);
    //pop->setEndRadius(50);
    this->addChild(pop, 5, exObj->getGid() + 800);
}

void TakasuPoppo::sunParticles(TPObjectExtension *exObj) {
    CCParticleSystemQuad *pop = new CCParticleSystemQuad;
    pop = CCParticleSun::create();
    pop->setTexture(CCTextureCache::sharedTextureCache()->addImage("Star.png"));
    pop->setPosition(exObj->getPosition());
    pop->setGravity(CCPointZero);
    
    pop->setAngle(140);
    pop->setAngleVar(360);
    
    pop->setSpeed(80);
    //pop->setSpeedVar(360);
    
    pop->setStartSize(40);
    
    //pop->setLife(0.1);
    pop->setPositionType(kCCPositionTypeRelative);
    
    pop->setRadialAccel(-50);
    //pop->setRadialAccelVar(-100);
    
    //pop->setTangentialAccel(-50);
    pop->setTotalParticles(9);
    //pop->setRotatePerSecond(0);
    //pop->setAutoRemoveOnFinish(true);
    pop->setAtlasIndex(0);
    pop->setBlendAdditive(false);
    //pop->setOrderOfArrival(0);
    pop->setOpacityModifyRGB(false);
    pop->setDuration(0.5);
    pop->setEmissionRate(200);
    //pop->setEndRadius(50);
    this->addChild(pop, 5, 779);
}

CCRenderTexture *TakasuPoppo::outlineEffect(CCSprite *sprite, int size, ccColor3B color, GLubyte opacity) {
    CCRenderTexture *outline = CCRenderTexture::create(sprite->getTexture()->getContentSize().width + size * 2,
                                                       sprite->getTexture()->getContentSize().height + size * 2);
    CCPoint originalPos = sprite->getPosition();
    ccColor3B originalColor = sprite->getColor();
    GLubyte originalOpacity = sprite->getOpacity();
    bool originalVisibility = sprite->isVisible();
    
    sprite->setColor(color);
    sprite->setOpacity(opacity);
    sprite->setVisible(true);
    
    ccBlendFunc originalBlend = sprite->getBlendFunc();
    ccBlendFunc bf = {GL_SRC_ALPHA, GL_ONE};
    
    sprite->setBlendFunc(bf);
    
    CCPoint bottomLeft = ccp(sprite->getContentSize().width * sprite->getAnchorPoint().x + size,
                             sprite->getContentSize().height * sprite->getAnchorPoint().y + size);
    
    CCPoint positionOffset = ccp(0, 0);
    
    CCPoint position = ccpSub(originalPos, positionOffset);
    
    outline->begin();
    
    for (int i = 0; i < 360; i += 15) {
        sprite->setPosition(ccp(bottomLeft.x + sin(CC_DEGREES_TO_RADIANS(i)) * size,
                                bottomLeft.y + cos(CC_DEGREES_TO_RADIANS(i)) * size));
        sprite->visit();
    }
    
    outline->end();
    
    sprite->setPosition(originalPos);
    sprite->setColor(originalColor);
    sprite->setBlendFunc(originalBlend);
    sprite->setVisible(originalVisibility);
    sprite->setOpacity(originalOpacity);
    
    outline->setPosition(position);
    outline->getSprite()->getTexture()->setAntiAliasTexParameters();
    
    return outline;
}

void TakasuPoppo::popAnimation(CCNode* sender, void* data) {
    TPObjectExtension *exObj = (TPObjectExtension*)data;
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("starPop.plist");
    CCArray* animFrames = new CCArray;
    char str[100] = {0};
    for(int i = 0; i < 5; i++) {
        sprintf(str, "StarPop%d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        frame->setOriginalSizeInPixels(CCSizeMake(300, 300));
        animFrames->addObject(frame);
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.05f);
    CCSprite *popSprite = CCSprite::create();
    popSprite->setPosition(exObj->getPosition());
    this->addChild(popSprite, 4);
    popSprite->runAction(CCSequence::create(CCAnimate::create(animation),
                                            CCRemoveSelf::create(),
                                            NULL));
}

//void TakasuPoppo::spriteChange(CCNode *sender, void* data) {
//    TPObjectExtension *exObj = (TPObjectExtension*)data;
//    if (exObj->getID() == 0) {
//        CCImage *poppoB = new CCImage;
//        poppoB->initWithImageFile("Poppo1B.png");
//        CCTexture2D *poppoTexture = new CCTexture2D;
//        poppoTexture->initWithImage(poppoB);
//        CCSprite *poppoSprite = exObj->getSprite();
//        poppoSprite->setTexture(poppoTexture);
//    }
//    if (exObj->getID() == 1) {
//        CCImage *poppoB = new CCImage;
//        poppoB->initWithImageFile("Poppo2B.png");
//        CCTexture2D *poppoTexture = new CCTexture2D;
//        poppoTexture->initWithImage(poppoB);
//        CCSprite *poppoSprite = exObj->getSprite();
//        poppoSprite->setTexture(poppoTexture);
//    }
//    if (exObj->getID() == 2) {
//        CCImage *poppoB = new CCImage;
//        poppoB->initWithImageFile("Poppo3B.png");
//        CCTexture2D *poppoTexture = new CCTexture2D;
//        poppoTexture->initWithImage(poppoB);
//        CCSprite *poppoSprite = exObj->getSprite();
//        poppoSprite->setTexture(poppoTexture);
//    }
//    if (exObj->getID() == 3) {
//        CCImage *poppoB = new CCImage;
//        poppoB->initWithImageFile("Poppo4B.png");
//        CCTexture2D *poppoTexture = new CCTexture2D;
//        poppoTexture->initWithImage(poppoB);
//        CCSprite *poppoSprite = exObj->getSprite();
//        poppoSprite->setTexture(poppoTexture);
//    }
//    if (exObj->getID() == 4) {
//        CCImage *poppoB = new CCImage;
//        poppoB->initWithImageFile("Poppo5B.png");
//        CCTexture2D *poppoTexture = new CCTexture2D;
//        poppoTexture->initWithImage(poppoB);
//        CCSprite *poppoSprite = exObj->getSprite();
//        poppoSprite->setTexture(poppoTexture);
//    }
//    if (exObj->getID() == 5) {
//        CCImage *poppoB = new CCImage;
//        poppoB->initWithImageFile("Poppo6B.png");
//        CCTexture2D *poppoTexture = new CCTexture2D;
//        poppoTexture->initWithImage(poppoB);
//        CCSprite *poppoSprite = exObj->getSprite();
//        poppoSprite->setTexture(poppoTexture);
//    }
//    if (exObj->getID() == 6) {
//        CCImage *poppoB = new CCImage;
//        poppoB->initWithImageFile("Poppo7B.png");
//        CCTexture2D *poppoTexture = new CCTexture2D;
//        poppoTexture->initWithImage(poppoB);
//        CCSprite *poppoSprite = exObj->getSprite();
//        poppoSprite->setTexture(poppoTexture);
//    }
//}

