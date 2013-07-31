//
//  TPMainScreen.cpp
//  Cocos2Dx
//
//  Created by Ace on 2013/07/23.
//
//

#include "TPMainScreen.h"
#include "SimpleAudioEngine.h"
#include "TakasuPoppo.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene *TPMainScreen::scene() {
    CCScene *scene = CCScene::create();
    TPMainScreen *layer = TPMainScreen::create();
    scene->addChild(layer);
    return scene;
}

bool TPMainScreen::init() {
    if (!CCLayer::init()) return false;
    
    heartsCount = 0;
    heartAfterIncrease = heartsCount;
    
    menuBackground = CCSprite::create("BackgroundMenu.png");
    menuBackground->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(menuBackground, 0, 0);
    
    heartWindow = CCSprite::create("HeartsWindow.png");
    heartWindow->setPosition(ccp(winSize.width/2 + 9.5, winSize.height/2 + 300));
    this->addChild(heartWindow, 1, 1);
    
    rankingWindow = CCSprite::create("Tanking.png");
    rankingWindow->setPosition(ccp(winSize.width/2 + 9.5, winSize.height/2));
    this->addChild(rankingWindow, 2, 2);
    
    settingButton = CCSprite::create("Setting.png");
    settingButton->setPosition(ccp(540, winSize.height - 60));
    this->addChild(settingButton, 2, 3);
    
    startButton = CCSprite::create("Start.png");
    startButton->setPosition(ccp(winSize.width/2 + 9.5, 145));
    this->addChild(startButton, 3, 10);
    
    heartButton = CCSprite::create("HeartPlus.png");
    heartButton->setPosition(ccp(winSize.width/2 + 100, winSize.height/2 + 340));
    this->addChild(heartButton, 4, 12);
    
    heart1 = CCSprite::create("HeartEmpty.png");
    heart1->setPosition(ccp(winSize.width/2 - 70, winSize.height/2 + 330));
    this->addChild(heart1, 3, 4);
    
    heart2 = CCSprite::create("HeartEmpty.png");
    heart2->setPosition(ccp(winSize.width/2 - 40, winSize.height/2 + 330));
    this->addChild(heart2, 3, 5);
    
    heart3 = CCSprite::create("HeartEmpty.png");
    heart3->setPosition(ccp(winSize.width/2 - 10, winSize.height/2 + 330));
    this->addChild(heart3, 3, 6);
    
    heart4 = CCSprite::create("HeartEmpty.png");
    heart4->setPosition(ccp(winSize.width/2 + 20, winSize.height/2 + 330));
    this->addChild(heart4, 3, 7);
    
    heart5 = CCSprite::create("HeartEmpty.png");
    heart5->setPosition(ccp(winSize.width/2 + 50, winSize.height/2 + 330));
    this->addChild(heart5, 3, 8);
    TPMainScreen::setHearts();
    
    buyHeartWindow = CCSprite::create("BuyHeart.png");
    buyHeartWindow->setPosition(ccp(winSize.width/2 + 9.5, winSize.height + 200));
    this->addChild(buyHeartWindow, 4, 13);
    
    buyHeartPlus = CCSprite::create("Plus.png");
    buyHeartPlus->setPosition(ccp(130, 60));
    buyHeartWindow->addChild(buyHeartPlus, 4, 14);
    
    buyHeartMinus = CCSprite::create("Minus.png");
    buyHeartMinus->setPosition(ccp(190, 60));
    buyHeartWindow->addChild(buyHeartMinus, 4, 15);
    
    buyHeartCancelBtn = CCSprite::create("HeartBuyCancel.png");
    buyHeartCancelBtn->setPosition(ccp(400, 110));
    buyHeartWindow->addChild(buyHeartCancelBtn, 4, 16);
    
    buyHeartConfirmBtn = CCSprite::create("HeartBuyButton.png");
    buyHeartConfirmBtn->setPosition(ccp(330, 0));
    buyHeartWindow->addChild(buyHeartConfirmBtn, 4, 17);
    buyHeartConfirmBtn->setVisible(false);
    
    heartBuyInt = 0;
    sprintf(heartBuyChar, "%i", heartBuyInt);
    heartBuyLabel = CCLabelTTF::create(heartBuyChar, "Berlin Sans FB", 60);
    heartBuyLabel->setColor(ccc3(255, 255, 255));
    heartBuyLabel->setPosition(ccp(40, 66));
    buyHeartWindow->addChild(heartBuyLabel, 4, 18);
    
    rubyCost = 10 * heartBuyInt;
    sprintf(rubyCostChar, "%i", rubyCost);
    rubyCostLabel = CCLabelTTF::create(rubyCostChar, "Berlins Sans FB", 60);
    rubyCostLabel->setColor(ccc3(255, 255, 255));
    rubyCostLabel->setPosition(ccp(305, 66));
    buyHeartWindow->addChild(rubyCostLabel, 4, 19);
    
    itemWindow = CCSprite::create("Item Menu.png");
    itemWindow->setPosition(ccp(winSize.width/2 + 9.5, winSize.height/2 - 530));
    this->addChild(itemWindow, 4, 9);
    TPMainScreen::setItems();
    
    rubiesBar = CCSprite::create("Rubies.png");
    rubiesBar->setPosition(ccp(165, winSize.height - 60));
    this->addChild(rubiesBar, 2 ,3);
    
    rubyCount = 891998;
    sprintf(rubyCountChar, "%i", rubyCount);
    rubyCountLabel = CCLabelTTF::create(rubyCountChar, "Berlin Sans FB", 24);
    rubyCountLabel->setColor(ccc3(0, 0, 0));
    rubyCountLabel->setPosition(ccp(185, winSize.height - 63));
    this->addChild(rubyCountLabel, 4, 11);
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    this->scheduleUpdate();
    return true;
}

void TPMainScreen::update(float dt) {
    if (itemWindowMoving == true || heartWindowMoving == true) {
        itemWindowMoveTimer -= dt;
    }
    if (itemWindowMoveTimer <= 0) {
        itemWindowMoving = false;
        heartWindowMoving = false;
    }
}

bool TPMainScreen::ccTouchBegan(CCTouch *touch, CCEvent *event) {
    CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
    
    itemWindowRect = itemWindow->boundingBox();
    heartButtonRect = heartButton->boundingBox();
    
    CCPoint item1Point = itemWindow->convertToWorldSpace(item1->getPosition());
    item1Rect = CCRectMake(item1Point.x - item1->getContentSize().width / 2,
                           item1Point.y - item1->getContentSize().height / 2,
                           item1->getContentSize().width,
                           item1->getContentSize().height);
    
    CCPoint itemChosenPoint = itemWindow->convertToWorldSpace(itemChosen->getPosition());
    itemChosenRect = CCRectMake(itemChosenPoint.x - itemChosen->getContentSize().width / 2,
                                itemChosenPoint.y - itemChosen->getContentSize().height / 2,
                                itemChosen->getContentSize().width,
                                itemChosen->getContentSize().height);
    
    if (!itemWindowMoving && !itemWindowMoved && itemWindowRect.containsPoint(touchLoc)) {
        itemWindow->runAction(CCMoveBy::create(0.5, ccp(0, 600)));
        itemWindowMoved = true;
        itemWindowMoving = true;
        itemWindowMoveTimer = 1;
        if (heartWindowMoved) {
            buyHeartWindow->runAction(CCMoveBy::create(0.5, ccp(0, 600)));
            heartWindowMoved = false;
            heartWindowMoving = true;
            itemWindowMoveTimer = 1;
        }
    }
    if (!itemWindowMoving  && itemWindowMoved && !itemWindowRect.containsPoint(touchLoc)) {
        itemWindow->runAction(CCMoveBy::create(0.5, ccp(0, -600)));
        itemWindowMoved = false;
        itemWindowMoving = true;
        itemWindowMoveTimer = 1;
    }
    
    if (!itemWindowMoving && itemWindowMoved && item1Rect.containsPoint(touchLoc)) {
        itemChosen->setTexture(CCTextureCache::sharedTextureCache()->addImage("ItemA.png"));
        itemChosenOn = true;
    }
    
    if (!itemWindowMoving && itemWindowMoved && itemChosenOn && itemChosenRect.containsPoint(touchLoc)) {
        itemChosen->setTexture(CCTextureCache::sharedTextureCache()->addImage("NoItem.png"));
        itemChosenOn = false;
    }
    
    if (!heartWindowMoving && !heartWindowMoved && heartButtonRect.containsPoint(touchLoc)) {
        if (heartsCount != 5) {
            buyHeartWindow->runAction(CCMoveBy::create(0.5, ccp(0, - 600)));
            heartWindowMoved = true;
            heartWindowMoving = true;
            itemWindowMoveTimer = 1;
        }
    }
    return true;
}

void TPMainScreen::ccTouchEnded(CCTouch *touch, CCEvent *event) {
    CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
    
    CCPoint buyHeartCancelPnt = buyHeartWindow->convertToWorldSpace(buyHeartCancelBtn->getPosition());
    buyHeartCancelRect = CCRectMake(buyHeartCancelPnt.x - buyHeartCancelBtn->getContentSize().width / 2,
                                    buyHeartCancelPnt.y - buyHeartCancelBtn->getContentSize().height / 2,
                                    buyHeartCancelBtn->getContentSize().width,
                                    buyHeartCancelBtn->getContentSize().height);
    
    CCPoint buyHeartPlusPnt = buyHeartWindow->convertToWorldSpace(buyHeartPlus->getPosition());
    buyHeartPlusRect = CCRectMake(buyHeartPlusPnt.x - buyHeartPlus->getContentSize().width / 2,
                                  buyHeartPlusPnt.y - buyHeartPlus->getContentSize().height / 2,
                                  buyHeartPlus->getContentSize().width,
                                  buyHeartPlus->getContentSize().height);
    
    CCPoint buyHeartMinusPnt = buyHeartWindow->convertToWorldSpace(buyHeartMinus->getPosition());
    buyHeartMinusRect = CCRectMake(buyHeartMinusPnt.x - buyHeartMinus->getContentSize().width / 2,
                                   buyHeartMinusPnt.y - buyHeartMinus->getContentSize().height / 2,
                                   buyHeartMinus->getContentSize().width,
                                   buyHeartMinus->getContentSize().height);
    
    CCPoint buyHeartConfirmPnt = buyHeartWindow->convertToWorldSpace(buyHeartConfirmBtn->getPosition());
    buyHeartConfirmRect = CCRectMake(buyHeartConfirmPnt.x - buyHeartConfirmBtn->getContentSize().width / 2,
                                     buyHeartConfirmPnt.y - buyHeartConfirmBtn->getContentSize().height / 2,
                                     buyHeartConfirmBtn->getContentSize().width,
                                     buyHeartConfirmBtn->getContentSize().height);
    
    CCRect startRect = startButton->boundingBox();
    
    if (!heartWindowMoving && heartWindowMoved && buyHeartCancelRect.containsPoint(touchLoc)) {
        buyHeartWindow->runAction(CCMoveBy::create(0.5, ccp(0, 600)));
        heartWindowMoved = false;
        heartWindowMoving = true;
        itemWindowMoveTimer = 1;
    }
    
    if (!heartWindowMoving && heartWindowMoved && buyHeartPlusRect.containsPoint(touchLoc)) {
        if (heartsCount != 5) TPMainScreen::setPlusHeart();
    }
    
    if (!heartWindowMoving && heartWindowMoved && buyHeartMinusRect.containsPoint(touchLoc)) {
        if (heartsCount != 5) TPMainScreen::setMinusHeart();
    }
    
    if (!heartWindowMoving && heartWindowMoved && buyHeartConfirmRect.containsPoint(touchLoc)) {
        TPMainScreen::setNewHeartCount();
        
    }
    
    if (startRect.containsPoint(touchLoc)) {
        //run into takasu
        CCScene *gameScene = TakasuPoppo::scene(3);
        CCDirector::sharedDirector()->setDepthTest(true);
        CCTransitionScene* transition = CCTransitionFadeUp::create(1, gameScene);
        CCDirector::sharedDirector()->replaceScene(transition);
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
//        CCDirector::sharedDirector()->replaceScene(gameScene);

//        CCDirector::sharedDirector()->setDepthTest(true);
//        CCTransitionScene *transition = CCTransitionPageTurn::create(1.0f, gameScene, false);
//        CCDirector::sharedDirector()->replaceScene(transition);

        
        
    }
    
}

void TPMainScreen::setPlusHeart() {
    if (heartAfterIncrease != 5) {
        heartAfterIncrease += 1;
        
        heartBuyInt += 1;
        sprintf(heartBuyChar, "%i", heartBuyInt);
        heartBuyLabel->setString(heartBuyChar);
        
        rubyCost = 10 * heartBuyInt;
        sprintf(rubyCostChar, "%i", rubyCost);
        rubyCostLabel->setString(rubyCostChar);
    }
    
    if (heartBuyInt > 0) {
        buyHeartConfirmBtn->setVisible(true);
    }
}

void TPMainScreen::setMinusHeart() {
    if (heartBuyInt != 0) {
        heartAfterIncrease -=1;
        
        heartBuyInt -=1;
        sprintf(heartBuyChar, "%i", heartBuyInt);
        heartBuyLabel->setString(heartBuyChar);
        
        rubyCost = 10 * heartBuyInt;
        sprintf(rubyCostChar, "%i", rubyCost);
        rubyCostLabel->setString(rubyCostChar);
    }
    
    if (heartBuyInt == 0) {
        buyHeartConfirmBtn->setVisible(false);
    }
}

void TPMainScreen::setNewHeartCount() {
    if (rubyCost < rubyCount) {
        rubyCountAfterPay = rubyCount - rubyCost;
        
        heartsCount += heartBuyInt;
        TPMainScreen::setHearts();
        
        heartBuyInt = 0;
        sprintf(heartBuyChar, "%i", heartBuyInt);
        heartBuyLabel->setString(heartBuyChar);
        
        rubyCost = 0;
        sprintf(rubyCostChar, "%i", rubyCost);
        rubyCostLabel->setString(rubyCostChar);
        
        buyHeartConfirmBtn->setVisible(false);
        
        this->schedule(schedule_selector(TPMainScreen::setRubyCount));
        rubyPaid = false;
    }
}

void TPMainScreen::setRubyCount() {
    CCLog("Ruby Cost %i", rubyCost);
    CCLog("Ruby Count %i", rubyCount);
    CCLog("Ruby Count after pay %i", rubyCountAfterPay);
    if (rubyCountAfterPay < rubyCount) {
        rubyCount -= 1;
        sprintf(rubyCountChar, "%i", rubyCount);
        rubyCountLabel->setString(rubyCountChar);
    }
    
    if (rubyCountAfterPay == rubyCount) {
        this->unschedule(schedule_selector(TPMainScreen::setRubyCount));
        rubyPaid = true;
    }
}

void TPMainScreen::setHearts() {
    //Set texture only works if the sprite is created with some texture already
    if (heartsCount == 5) {
        heart1->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heart2->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heart3->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heart4->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heart5->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heartButton->setVisible(false);
    }
    if (heartsCount == 4) {
        heart1->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heart2->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heart3->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heart4->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heart5->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heartButton->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartPlus.png"));
        heartButton->setVisible(true);
    }
    if (heartsCount == 3) {
        heart1->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heart2->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heart3->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heart4->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heart5->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heartButton->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartPlus.png"));
        heartButton->setVisible(true);
    }
    if (heartsCount == 2) {
        heart1->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heart2->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heart3->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heart4->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heart5->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heartButton->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartPlus.png"));
        heartButton->setVisible(true);
    }
    if (heartsCount == 1) {
        heart1->setTexture(CCTextureCache::sharedTextureCache()->addImage("Heart.png"));
        heart2->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heart3->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heart4->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heart5->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heartButton->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartPlus.png"));
        heartButton->setVisible(true);
    }
    if (heartsCount == 0) {
        heart1->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heart2->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heart3->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heart4->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heart5->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartEmpty.png"));
        heartButton->setTexture(CCTextureCache::sharedTextureCache()->addImage("HeartPlus.png"));
        heartButton->setVisible(true);
    }
}

void TPMainScreen::setItems() {
    itemChosen = CCSprite::create("NoItem.png");
    
    item1 = CCSprite::create("ItemA.png");
    item2 = CCSprite::create("NoItem.png");
    item3 = CCSprite::create("NoItem.png");
    item4 = CCSprite::create("NoItem.png");
    item5 = CCSprite::create("NoItem.png");
    item6 = CCSprite::create("NoItem.png");
    item7 = CCSprite::create("NoItem.png");
    item8 = CCSprite::create("NoItem.png");
    item9 = CCSprite::create("NoItem.png");
    item10 = CCSprite::create("NoItem.png");
    
    itemChosen = CCSprite::create("NoItem.png");
    
    item1->setPosition(ccp(80, TPMainScreen::itemSizeY(item1)));
    item2->setPosition(ccp(180, TPMainScreen::itemSizeY(item2)));
    item3->setPosition(ccp(280, TPMainScreen::itemSizeY(item3)));
    item4->setPosition(ccp(380, TPMainScreen::itemSizeY(item4)));
    item5->setPosition(ccp(480, TPMainScreen::itemSizeY(item5)));
    
    item6->setPosition(ccp(80, TPMainScreen::itemSizeY(item6) - 90));
    item7->setPosition(ccp(180, TPMainScreen::itemSizeY(item7) - 90));
    item8->setPosition(ccp(280, TPMainScreen::itemSizeY(item8) - 90));
    item9->setPosition(ccp(380, TPMainScreen::itemSizeY(item9) - 90));
    item10->setPosition(ccp(480, TPMainScreen::itemSizeY(item10) - 90));
    
    itemChosen->setPosition(ccp(480, TPMainScreen::itemSizeY(itemChosen) + 95));
    
    itemWindow->addChild(item1, 5);
    itemWindow->addChild(item2, 5);
    itemWindow->addChild(item3, 5);
    itemWindow->addChild(item4, 5);
    itemWindow->addChild(item5, 5);
    
    itemWindow->addChild(item6, 5);
    itemWindow->addChild(item7, 5);
    itemWindow->addChild(item8, 5);
    itemWindow->addChild(item9, 5);
    itemWindow->addChild(item10, 5);
    
    itemWindow->addChild(itemChosen, 5);
}

float TPMainScreen::itemSizeY(CCSprite *itemSprite) {
    float contentSizeY;
    if (itemSprite->getContentSize().height >= 78) {
        contentSizeY = 200 - itemSprite->getContentSize().height / 2;
        return contentSizeY;
    }
    else {
        contentSizeY = 200 - itemSprite->getContentSize().height / 2 - 2;
        return contentSizeY;
    }
}

void TPMainScreen::menuCloseCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

TPMainScreen::~TPMainScreen(){
    
}