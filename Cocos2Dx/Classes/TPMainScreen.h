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
#include "TPItemObject.h"

USING_NS_CC;
using namespace std;

class TPMainScreen : public CCLayer{
private:
    CCSprite *background;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *menuBackground;
    CCSprite *heartWindow;
    CCSprite *rankingWindow;
    CCSprite *rubiesBar;
    CCSprite *settingButton;
    
    CCSprite *startButton;
    
    CCSprite *heartButton;
    CCRect heartButtonRect;
    
    CCSprite *heart1;
    CCSprite *heart2;
    CCSprite *heart3;
    CCSprite *heart4;
    CCSprite *heart5;
    
    CCSprite *itemWindow;
    CCRect itemWindowRect;
    
    CCSprite *item1;
    CCRect item1Rect;
    
    CCSprite *item2;
    CCRect item2Rect;
    
    CCSprite *item3;
    CCRect item3Rect;
    
    CCSprite *item4;
    CCRect item4Rect;
    
    CCSprite *item5;
    CCRect item5Rect;
    
    CCSprite *item6;
    CCRect item6Rect;
    
    CCSprite *item7;
    CCRect item7Rect;
    
    CCSprite *item8;
    CCRect item8Rect;
    
    CCSprite *item9;
    CCRect item9Rect;
    
    CCSprite *item10;
    CCRect item10Rect;
    
    CCSprite *itemChosen;
    CCRect itemChosenRect;
    
    CCSprite *buyHeartWindow;
    
    CCSprite *buyHeartPlus;
    CCRect buyHeartPlusRect;
    
    CCSprite *buyHeartMinus;
    CCRect buyHeartMinusRect;
    
    CCSprite *buyHeartCancelBtn;
    CCRect buyHeartCancelRect;
    
    CCSprite *buyHeartConfirmBtn;
    CCRect buyHeartConfirmRect;
    
    CCLabelTTF *buyHeartHrtLabel;
    CCLabelTTF *buyHeartRbyLabel;
    
    CCLabelTTF *rubyCountLabel;
    int rubyCount;
    char rubyCountChar[100];
    
    CCLabelTTF *rubyCostLabel;
    int rubyCost;
    char rubyCostChar[100];
    
    CCLabelTTF *heartBuyLabel;
    int heartBuyInt;
    char heartBuyChar[100];
    
    int rubyCountAfterPay;
    bool rubyPaid;
    
    int heartAfterIncrease;
    bool heartIncreased;
    
    float itemWindowMoveTimer = 1;
    
    bool itemWindowMoved = false;
    bool itemWindowMoving = false;
    bool itemChosenOn = false;
    
    bool heartWindowMoved = false;
    bool heartWindowMoving = false;
    bool heartChanged = false;
    
    int heartsCount;
    
public:
    ~TPMainScreen();
    virtual bool init();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);
    
    void update(float dt);
    void menuCloseCallback(CCObject *pSender);
    
    void setHearts();
    
    void setItems();
    
    void setPlusHeart();
    void setMinusHeart();
    void setNewHeartCount();
    void setRubyCount();
    
    float itemSizeY(CCSprite * itemSprite);
    
    CCSprite setHeartSprite(CCSprite *heart);
    
    static CCScene* scene();
    CREATE_FUNC(TPMainScreen);
};

#endif /* defined(__Cocos2Dx__TPMainScreen__) */