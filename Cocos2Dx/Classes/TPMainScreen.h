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
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    //===================== New UI =========================
    CCSprite *newBackground;
    CCSprite *rankingContainer;
    CCSprite *heartContainer;
    CCSprite *heartTP1;
    CCSprite *heartTP2;
    CCSprite *heartTP3;
    CCSprite *heartTP4;
    CCSprite *heartTP5;
    CCSprite *heartBox;
    CCSprite *heartPlus;
    CCSprite *rubyContainer;
    CCSprite *rubyPlus;
    CCSprite *settingBtn;
    CCSprite *playBtn;
    CCSprite *darkenBg;
    
    CCSprite *tutWin;
    CCSprite *tutPrevBtn;
    CCSprite *tutNextBtn;
    CCSprite *tutContent1;
    CCSprite *tutContent2;
    CCSprite *tutContent3;
    CCSprite *tutContent4;
    CCSprite *tutContent5;
    CCSprite *tutContent6;
    CCSprite *tutCancelBtn;
    
    CCSprite *chargeWin;
    CCSprite *chargeCclBtn;
    CCSprite *chargeBtnScr1;
    CCSprite *chargeLblScr1;
    
    CCSprite *chargeLblScr2;
    CCSprite *chargeImgScr2;
    CCSprite *chargeBtnScr2;
    CCSprite *chargeCclBtn2;
    
    CCSprite *chargeWin3;
    CCSprite *chargeBtnScr3;
    CCSprite *chargeLblScr3;
    CCSprite *chargeCclBtn3;
    
    CCSprite *chargeBtnScr4;
    CCSprite *chargeLblScr4;
    
    int tutPageNo;
    char tutPageChar[50];
    CCLabelTTF *tutPageLbl;
    
    int heartCount;
    int heartChargeCount;
    char heartViewChar[50];
    char heartCharChar[50];
    CCLabelTTF *heartChargedLabel;
    CCLabelTTF *heartChargeLabel;
    CCLabelTTF *heartChargingLabel;
    
    int crystalChargeCount;
    char crystalChargeChar[50];
    CCLabelTTF *crystalChargeLabel;
    
    int rubyCount;
    char rubyCountChar[50];
    CCLabelTTF *rubyCountLabel;
    
    bool tutorialOn;
    bool chargeOn;
    bool charge2On;
    bool charge3On;
    bool charge4On;
    bool chargeBack;
    bool chargeExit;
public:
    ~TPMainScreen();
    virtual bool init();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);
    
    void update(float dt);
    void menuCloseCallback(CCObject *pSender);
    
    void setTutorial();
    void setupHearts();
    void setCharge();
    
    void setCrystal(int decreasingAmount);
    
    CCRect boundingBoxWorldSpace(CCSprite *parentSprite, CCSprite *childSprite);
    
    static CCScene* scene();
    CREATE_FUNC(TPMainScreen);
};

#endif /* defined(__Cocos2Dx__TPMainScreen__) */