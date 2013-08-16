//
//  TPMainScreen.h
//  Cocos2Dx
//
//  Created by Ace on 2013/07/23.
//
//

#ifndef __Cocos2Dx__TPMainScreen__
#define __Cocos2Dx__TPMainScreen__

#include "CCTableViewCell.h"
#include "CCTableView.h"
#include "CCScrollView.h"
#include "rapidjson.h"
#include "document.h"
#include "cocos-ext.h"
#include <iostream>
#include "cocos2d.h"
#include "TPItemObject.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::extension;

class Gamer:public CCObject {
private:
    CC_SYNTHESIZE(string,_name , Name);
    CC_SYNTHESIZE(int , _score, Score);
    CC_SYNTHESIZE(int, _reward, Reward);
public:
    Gamer(string name, int score);
};

class TPMainScreen : public CCLayer, CCTableViewDelegate, CCTableViewDataSource{
private:

    CCArray *listGamer = new CCArray();
    CCTableView *tableView;
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
    
    
    CCSprite *networkContainer;
    
    CCSprite *overContainer;
    
    CCSprite *itemContainer;
    CCSprite *item1, *item1Shade;
    CCSprite *item2, *item2Shade;
    CCSprite *item3, *item3Shade;
    CCSprite *item4, *item4Shade;
    CCSprite *item5, *item5Shade;
    CCSprite *item6, *item6Shade;
    CCSprite *item7, *item7Shade;
    CCSprite *item8, *item8Shade;
    CCSprite *item9, *item9Shade;
    CCSprite *item10, *item10Shade;
    CCArray *itemShadeArray;
    
    CCSprite *itemLabel;
    
    CCSprite *scoreContainer;
    CCSprite *scoreClose;
    CCSprite *scoreDancingTakasu;
    CCSprite *scoreBest;
    CCLabelTTF *scoreLabel;
    CCLabelBMFont *scoreBitMap;
    
    CCSprite *settingContainer;
    CCSprite *settingCancelBtn;
    CCSprite *settingContents;
    CCControlSlider *sfxSlider;
    CCControlSlider *bgmSlider;
    CCSprite *aboutBtn;
    CCSprite *tutorialBtn;
    
    
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
    
    bool settingOn;
    bool itemOn;
    
    bool item1On;
    bool item2On;
    bool item3On;
    int specialItemID;
    
    bool gameOverIsOn;
    int gameScoreOfNow;
public:
    ~TPMainScreen();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);
    
    void update(float dt);
    void menuCloseCallback(CCObject *pSender);
    
    void setTutorial();
    void setupHearts();
    void setCharge();
    void setSetting();
    void setItem();
    void setSpecialItemShade(CCSprite *selectedItemShade);
    void setCrystal(int decreasingAmount);
    
    CCRect boundingBoxWorldSpace(CCSprite *parentSprite, CCSprite *childSprite);
    
    void onHttpRequestCompleted(CCNode *sender, void *data);
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int index);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int index);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view);
    void convertName(char *str_name);
    long getTime();

    virtual bool init(bool isGameOver, int score);
    static TPMainScreen* create(bool isGameOver, int score);
    static CCScene* scene(bool isGameOver, int score);

};

#endif /* defined(__Cocos2Dx__TPMainScreen__) */