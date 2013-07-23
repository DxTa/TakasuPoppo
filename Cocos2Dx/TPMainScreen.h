//
//  TPMainScreen.h
//  Cocos2Dx
//
//  Created by Ace on 2013/07/23.
//
//

#ifndef __Cocos2Dx__TPMainScreen__
#define __Cocos2Dx__TPMainScreen__

#include <iostream>


#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class TPMainScreen : public CCLayer{
private:
    CCSprite *background;

public:
    virtual bool init();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);
    //Selector callback
    void update(float dt);
    void menuCloseCallback(CCObject *pSender);
    
    static CCScene* scene();
    CREATE_FUNC(TPMainScreen);
};

#endif /* defined(__Cocos2Dx__TPMainScreen__) */