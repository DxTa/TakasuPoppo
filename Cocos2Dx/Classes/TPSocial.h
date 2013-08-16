//
//  TPSocial.h
//  Cocos2Dx
//
//  Created by Kien MetalRock on 8/16/13.
//
//

#ifndef __Cocos2Dx__TPSocial__
#define __Cocos2Dx__TPSocial__

#include <iostream>

#include "cocos2d.h"

using namespace  cocos2d;
USING_NS_CC;

class TPSocial :public CCLayer {
private:
    CCSize _screenSize;
    float w, h;
    
public:
    virtual bool init();
    static CCScene * scene();
    
    void Line();
    void Face();
    void Tweet();
    
    void Close();
    
    CREATE_FUNC(TPSocial);
};



#endif /* defined(__Cocos2Dx__TPSocial__) */
