//  Created by MinhNT on 13/05/16.
//  Copyright FRAMGIA 2013年. All rights reserved.
//
#ifndef Cocos2Dx_TPObjectExtension_h
#define Cocos2Dx_TPObjectExtension_h
#include "cocos2d.h"
using namespace std;
USING_NS_CC;
class TPObjectExtension : public CCObject{
private:
    int gid;
    int colorId;
    CCSprite *blockSprite;
    CCPoint position;
    CCPoint coordination;
    bool controlable;
    int blockType;
public:
    TPObjectExtension(int colorId ,int location, CCSprite *sprite,
                      CCPoint position, CCPoint coordination, bool controlable, int blockType);
    
    void setGid(int c);
    int getGid();
    
    int getID();
    void setID(int colorId);
    
    CCSprite *getSprite();
    void setSprite(CCSprite *sprite);
    
    CCPoint getPosition();
    void setPosition(CCPoint position);
    
    CCPoint getCoordination();
    void setCoordination(CCPoint position);
    
    bool getControlTrigger();
    void setControlTrigger(bool trigger);
    
    int getBlockType();
    void setBlockType(int blockType);
};
#endif