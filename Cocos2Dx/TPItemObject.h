//
//  TPItemObject.h
//  Cocos2Dx
//
//  Created by Nguyen The Vinh on 7/30/13.
//
//

#ifndef Cocos2Dx_TPItemObject_h
#define Cocos2Dx_TPItemObject_h
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;
USING_NS_CC;

class TPItemObject : public CCObject {
private:
    
    CC_SYNTHESIZE(bool, isFirstItemOn, IsFirstItemOn);
    CC_SYNTHESIZE(bool, isSecondItemOn, IsSecondItemOn);
    CC_SYNTHESIZE(bool, isThirdItemOn, IsThirdItemOn);
    CC_SYNTHESIZE(int, specialItemID, SpecialItemID);
    
public:
    TPItemObject(bool firstItem, bool secondItem, bool thirdItem, int spcialItemID);
    
};

#endif /* defined(__Cocos2Dx__TPItemObject__) */
