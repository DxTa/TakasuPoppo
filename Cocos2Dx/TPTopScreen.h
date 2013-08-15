//
//  TPTopScreen.h
//  Cocos2Dx
//
//  Created by macbook_017 on 8/15/13.
//
//

#ifndef __TPTOPSCREEN_H__
#define __TPTOPSCREEN_H__

#include <iostream>
#include "cocos2d.h"

using namespace  cocos2d;
USING_NS_CC;

class TPTopScreen :public CCLayer {
private:
    CCSize _screenSize;
    CCSprite *_topScreen;
    
public:
    virtual bool init();
    static CCScene * scene();
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *event);
    CREATE_FUNC(TPTopScreen);
};

#endif
