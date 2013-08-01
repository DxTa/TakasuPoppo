//
//  TPItemObject.cpp
//  Cocos2Dx
//
//  Created by Nguyen The Vinh on 7/30/13.
//
//

#include "TPItemObject.h"
using namespace cocos2d;
using namespace std;
USING_NS_CC;

TPItemObject::TPItemObject(bool firstItem, bool secondItem, bool thirdItem, int pSpcialItemID){
    this->isFirstItemOn = firstItem;
    this->isSecondItemOn = secondItem;
    this->isThirdItemOn = thirdItem;
    this->specialItemID = pSpcialItemID;
}

