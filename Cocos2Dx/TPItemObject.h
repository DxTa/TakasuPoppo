//
//  TPItemObject.h
//  Cocos2Dx
//
//  Created by Nguyen The Vinh on 7/30/13.
//
//

#ifndef Cocos2Dx_TPObjectExtension_h
#define Cocos2Dx_TPObjectExtension_h
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class TPItemObject : public CCObject {
private:
    int itemID;
    
public:
    void    setItemID(int itemID);
    int     getItemID();
    
};

#endif /* defined(__Cocos2Dx__TPItemObject__) */
