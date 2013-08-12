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
#include "TPItemObject.h"

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
    
    //===================== New UI =========================
    heartCount = 1;
    
    newBackground = CCSprite::create("poppo_background.png");
    newBackground->setPosition(ccp(winSize.width / 2,
                                   winSize.height / 2));
    this->addChild(newBackground, 100, 100);
    
    rankingContainer = CCSprite::create("poppo_ranking_container.png");
    rankingContainer->setPosition(ccp(winSize.width / 2,
                                      winSize.height / 2 + 50));
    this->addChild(rankingContainer, 101, 101);
    
    heartContainer = CCSprite::create("poppo_hearts_container.png");
    heartContainer->setPosition(ccp(rankingContainer->getContentSize().width / 2,
                                    rankingContainer->getContentSize().height - 50));
    rankingContainer->addChild(heartContainer, 102, 102);
    
    heartBox = CCSprite::create("poppo_heart_textbox.png");
    heartBox->setPosition(ccp(heartContainer->getContentSize().width - 250,
                              heartContainer->getContentSize().height - 50));
    heartContainer->addChild(heartBox, 103, 103);
    
    heartTP1 = CCSprite::create("poppo_heart_empty.png");
    heartTP1->setPosition(ccp(heartContainer->getContentSize().width - 585,
                              heartContainer->getContentSize().height - 50));
    heartContainer->addChild(heartTP1, 103, 104);
    
    heartTP2 = CCSprite::create("poppo_heart_empty.png");
    heartTP2->setPosition(ccp(heartContainer->getContentSize().width - 535,
                              heartContainer->getContentSize().height - 50));
    heartContainer->addChild(heartTP2, 103, 105);
    
    heartTP3 = CCSprite::create("poppo_heart_empty.png");
    heartTP3->setPosition(ccp(heartContainer->getContentSize().width - 485,
                              heartContainer->getContentSize().height - 50));
    heartContainer->addChild(heartTP3, 103, 105);
    
    heartTP4 = CCSprite::create("poppo_heart_empty.png");
    heartTP4->setPosition(ccp(heartContainer->getContentSize().width - 435,
                              heartContainer->getContentSize().height - 50));
    heartContainer->addChild(heartTP4, 103, 105);
    
    heartTP5 = CCSprite::create("poppo_heart_empty.png");
    heartTP5->setPosition(ccp(heartContainer->getContentSize().width - 385,
                              heartContainer->getContentSize().height - 50));
    heartContainer->addChild(heartTP5, 103, 105);
    
    TPMainScreen::setupHearts();
    
    heartPlus = CCSprite::create("poppo_heart_plus.png");
    heartPlus->setPosition(ccp(heartContainer->getContentSize().width - 160,
                               heartContainer->getContentSize().height - 45));
    heartContainer->addChild(heartPlus, 103, 109);
    
    heartChargeCount = 5 - heartCount;
    sprintf(heartViewChar, "%i", heartChargeCount);
    heartChargedLabel = CCLabelTTF::create(heartViewChar, "", 40);
    heartChargedLabel->setPosition(ccp(heartContainer->getContentSize().width - 200,
                                       heartContainer->getContentSize().height - 50));
    heartContainer->addChild(heartChargedLabel, 104, 144);
    
    //===================== New Rubies =========================
    
    rubyContainer = CCSprite::create("poppo_ruby_gauge.png");
    rubyContainer->setPosition(ccp(winSize.width / 4,
                                   winSize.height - 50));
    this->addChild(rubyContainer, 102, 110);
    
    rubyPlus = CCSprite::create("poppo_ruby_plus.png");
    rubyPlus->setPosition(ccp(rubyContainer->getContentSize().width,
                              rubyContainer->getContentSize().height - 40));
    rubyContainer->addChild(rubyPlus, 103, 111);
    
    rubyCount = 891998;
    sprintf(rubyCountChar, "%i", rubyCount);
    rubyCountLabel = CCLabelTTF::create(rubyCountChar, "Berlin Sans FB", 34);
    rubyCountLabel->setColor(ccc3(255, 255, 255));
    rubyCountLabel->setPosition(ccp(rubyContainer->getContentSize().width - 100,
                                    rubyContainer->getContentSize().height - 40));
    rubyContainer->addChild(rubyCountLabel, 104, 112);
    
    //===================== New Menu =========================
    
    
    settingBtn = CCSprite::create("poppo_setting.png");
    settingBtn->setPosition(ccp(winSize.width - 100,
                                winSize.height - 50));
    this->addChild(settingBtn, 102, 113);
    
    playBtn = CCSprite::create("poppo_play.png");
    playBtn->setPosition(ccp(winSize.width / 2,
                             winSize.height / 2 - 300));
    this->addChild(playBtn, 102, 113);
    
    darkenBg = CCSprite::create("poppo_darken.png");
    darkenBg->setPosition(ccp(winSize.width / 2,
                              winSize.height / 2));
    darkenBg->setVisible(false);
    this->addChild(darkenBg, 105, 114);
    
    
    //===================== New Tutorial =========================
    
    tutWin = CCSprite::create("poppo_tut_win.png");
    tutWin->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    tutWin->setVisible(false);
    
    this->addChild(tutWin, 110, 115);
    
    tutPrevBtn = CCSprite::create("poppo_tut_for_dis.png");
    tutPrevBtn->setPosition(ccp(tutWin->getContentSize().width / 2 - 100,
                                tutWin->getContentSize().height - 580));
    tutWin->addChild(tutPrevBtn, 111, 116);
    
    tutNextBtn = CCSprite::create("poppo_tut_for_ebl.png");
    tutNextBtn->setPosition(ccp(tutWin->getContentSize().width / 2 + 100,
                                tutWin->getContentSize().height - 580));
    tutWin->addChild(tutNextBtn, 111, 117);
    
    tutPageNo = 1;
    sprintf(tutPageChar, "%i / 6", tutPageNo);
    tutPageLbl = CCLabelTTF::create(tutPageChar, "Berlin Sans FB", 60);
    tutPageLbl->setPosition(ccp(tutWin->getContentSize().width / 2,
                                tutWin->getContentSize().height - 580));
    tutWin->addChild(tutPageLbl, 111, 118);
    
    tutContent1 = CCSprite::create("poppo_tut1.png");
    tutContent1->setPosition(ccp(tutWin->getContentSize().width / 2,
                                 tutWin->getContentSize().height / 2));
    tutWin->addChild(tutContent1, 111, 119);
    
    tutContent2 = CCSprite::create("poppo_tut2.png");
    tutContent2->setPosition(ccp(tutWin->getContentSize().width / 2,
                                 tutWin->getContentSize().height / 2));
    tutContent2->setVisible(false);
    tutWin->addChild(tutContent2, 111, 120);
    
    tutContent3 = CCSprite::create("poppo_tut3.png");
    tutContent3->setPosition(ccp(tutWin->getContentSize().width / 2,
                                 tutWin->getContentSize().height / 2));
    tutContent3->setVisible(false);
    tutWin->addChild(tutContent3, 111, 121);
    
    tutContent4 = CCSprite::create("poppo_tut4.png");
    tutContent4->setPosition(ccp(tutWin->getContentSize().width / 2,
                                 tutWin->getContentSize().height / 2));
    tutContent4->setVisible(false);
    tutWin->addChild(tutContent4, 111, 122);
    
    tutContent5 = CCSprite::create("poppo_tut5.png");
    tutContent5->setPosition(ccp(tutWin->getContentSize().width / 2,
                                 tutWin->getContentSize().height / 2));
    tutContent5->setVisible(false);
    tutWin->addChild(tutContent5, 111, 123);
    
    tutContent6 = CCSprite::create("poppo_tut6.png");
    tutContent6->setPosition(ccp(tutWin->getContentSize().width / 2,
                                 tutWin->getContentSize().height / 2));
    tutContent6->setVisible(false);
    tutWin->addChild(tutContent6, 111, 124);
    
    tutCancelBtn = CCSprite::create("poppo_charge_ccl.png");
    tutCancelBtn->setPosition(ccp(tutWin->getContentSize().width - 10,
                                  tutWin->getContentSize().height - 30));
    tutWin->addChild(tutCancelBtn, 111, 125);
    
    tutorialOn = false;
    
    
    //===================== New Charge =========================
    
    chargeWin = CCSprite::create("poppo_charge_win.png");
    chargeWin->setPosition(ccp(winSize.width / 2,
                               winSize.height / 2));
    this->addChild(chargeWin, 110, 130);
    chargeWin->setVisible(false);
    
    chargeCclBtn = CCSprite::create("poppo_charge_ccl.png");
    chargeCclBtn->setPosition(ccp(chargeWin->getContentSize().width - 10,
                                  chargeWin->getContentSize().height - 10));
    chargeWin->addChild(chargeCclBtn, 111, 131);
    
    chargeBtnScr1 = CCSprite::create("poppo_charge_btn.png");
    chargeBtnScr1->setPosition(ccp(chargeWin->getContentSize().width / 2,
                                   chargeWin->getContentSize().height / 2));
    chargeWin->addChild(chargeBtnScr1, 111, 132);
    
    chargeLblScr1 = CCSprite::create("poppo_charge_lbl1.png");
    chargeLblScr1->setPosition(ccp(chargeWin->getContentSize().width / 2,
                                   chargeWin->getContentSize().height / 2 - 100));
    chargeWin->addChild(chargeLblScr1, 111, 133);
    
    chargeLblScr2 = CCSprite::create("poppo_charge_lbl2.png");
    chargeLblScr2->setPosition(ccp(chargeWin->getContentSize().width - 500,
                                   chargeWin->getContentSize().height - 60));
    chargeWin->addChild(chargeLblScr2, 112, 134);
    chargeLblScr2->setVisible(false);
    
    chargeImgScr2 = CCSprite::create("poppo_charge_pag2.png");
    chargeImgScr2->setPosition(ccp(chargeWin->getContentSize().width / 2,
                                   chargeWin->getContentSize().height /2));
    chargeWin->addChild(chargeImgScr2, 111, 135);
    chargeImgScr2->setVisible(false);
    
    chargeBtnScr2 = CCSprite::create("poppo_charge_pag2btn.png");
    chargeBtnScr2->setPosition(ccp(chargeWin->getContentSize().width - 140,
                                   chargeWin->getContentSize().height - 390));
    chargeWin->addChild(chargeBtnScr2, 111, 136);
    chargeBtnScr2->setVisible(false);
    
    sprintf(heartCharChar, "x%i", heartChargeCount);
    heartChargeLabel = CCLabelTTF::create(heartCharChar, "Berlin Sans FB", 50);
    heartChargeLabel->setPosition(ccp(chargeWin->getContentSize().width - 445,
                                      chargeWin->getContentSize().height - 375));
    chargeWin->addChild(heartChargeLabel, 113, 137);
    heartChargeLabel->setVisible(false);
    
    crystalChargeCount = heartChargeCount;
    sprintf(crystalChargeChar, "x%i", crystalChargeCount);
    crystalChargeLabel = CCLabelTTF::create(crystalChargeChar, "Berlin Sans FB", 50);
    crystalChargeLabel->setPosition(ccp(chargeWin->getContentSize().width - 325,
                                        chargeWin->getContentSize().height - 375));
    chargeWin->addChild(crystalChargeLabel, 113, 138);
    crystalChargeLabel->setVisible(false);
    
    
    chargeWin3 = CCSprite::create("poppo_charge_win3.png");
    chargeWin3->setPosition(ccp(winSize.width / 2 + 5,
                                winSize.height / 2));
    this->addChild(chargeWin3, 120, 139);
    chargeWin3->setVisible(false);
    
    chargeCclBtn3 = CCSprite::create("poppo_charge_ccl.png");
    chargeCclBtn3->setPosition(ccp(chargeWin3->getContentSize().width - 30,
                                   chargeWin3->getContentSize().height - 30));
    chargeWin3->addChild(chargeCclBtn3, 121, 140);
    
    chargeLblScr3 = CCSprite::create("poppo_charge_lbl3.png");
    chargeLblScr3->setPosition(ccp(chargeWin3->getContentSize().width / 2,
                                   chargeWin3->getContentSize().height / 2));
    chargeWin3->addChild(chargeLblScr3, 121, 141);
    
    heartChargingLabel = CCLabelTTF::create(heartCharChar, "Berlin Sans FB", 30);
    heartChargingLabel->setPosition(ccp(chargeWin3->getContentSize().width / 2 - 10,
                                        chargeWin3->getContentSize().height / 2 + 2));
    heartChargingLabel->setColor(ccc3(106, 57, 6));
    chargeWin3->addChild(heartChargingLabel, 122, 142);
    
    chargeBtnScr3 = CCSprite::create("poppo_charge_yes_btn.png");
    chargeBtnScr3->setPosition(ccp(chargeWin3->getContentSize().width / 2 - 10,
                                   chargeWin3->getContentSize().height / 2 - 80));
    chargeWin3->addChild(chargeBtnScr3, 122, 143);
    
    
    
    chargeLblScr4 = CCSprite::create("poppo_charge_lbl4.png");
    chargeLblScr4->setPosition(ccp(chargeWin3->getContentSize().width / 2,
                                   chargeWin3->getContentSize().height / 2));
    chargeWin3->addChild(chargeLblScr4, 121, 141);
    chargeLblScr4->setVisible(false);
    
    chargeBtnScr4 = CCSprite::create("poppo_charge_return.png");
    chargeBtnScr4->setPosition(ccp(chargeWin3->getContentSize().width / 2 - 10,
                                   chargeWin3->getContentSize().height / 2 - 80));
    chargeWin3->addChild(chargeBtnScr4, 122, 143);
    chargeBtnScr4->setVisible(false);
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    this->scheduleUpdate();
    

    
    CCHttpRequest *request = new CCHttpRequest();
    request->setUrl((serverIP+":3000/users.json").c_str());
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(this, callfuncND_selector(TPMainScreen::onHttpRequestCompleted));
    CCHttpClient::getInstance()->send(request);
    request->release();
    return true;
}

void TPMainScreen::update(float dt) {
    
}

#pragma mark Touches

bool TPMainScreen::ccTouchBegan(CCTouch *touch, CCEvent *event) {
    
    return true;
}

void TPMainScreen::ccTouchEnded(CCTouch *touch, CCEvent *event) {
    CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
    
    if (!tutorialOn && !chargeOn) {
        CCRect settingBtnRect = settingBtn->boundingBox();
        if (settingBtnRect.containsPoint(touchLoc)) {
            tutorialOn = true;
            TPMainScreen::setTutorial();
            
        }
        
        CCPoint chargeBtnPnt = heartContainer->convertToWorldSpace(heartPlus->getPosition());
        CCRect chargeBtnRect = CCRectMake(chargeBtnPnt.x - heartPlus->getContentSize().width / 2,
                                          chargeBtnPnt.y - heartPlus->getContentSize().height / 2,
                                          heartPlus->getContentSize().width,
                                          heartPlus->getContentSize().height);
        
        if (chargeBtnRect.containsPoint(touchLoc)) {
            chargeOn = true;
            TPMainScreen::setCharge();
        }
        
        CCRect startRect = playBtn->boundingBox();
        if (startRect.containsPoint(touchLoc)) {
            //run into takasu
            TPItemObject* itemObject = new TPItemObject(true, true, true, 6);
            CCScene *gameScene = TakasuPoppo::scene(itemObject);
            CCDirector::sharedDirector()->setDepthTest(true);
            CCTransitionScene* transition = CCTransitionFadeUp::create(1, gameScene);
            CCDirector::sharedDirector()->replaceScene(transition);
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        }
    }
    
    //============== Tutorial Controls ================
    if (tutorialOn) {
        CCPoint tutNextBtnPnt = tutWin->convertToWorldSpace(tutNextBtn->getPosition());
        CCRect tutNextBtnRect = CCRectMake(tutNextBtnPnt.x - tutNextBtn->getContentSize().width / 2,
                                           tutNextBtnPnt.y - tutNextBtn->getContentSize().height / 2,
                                           tutNextBtn->getContentSize().width,
                                           tutNextBtn->getContentSize().height);
        
        CCPoint tutPrevBtnPnt = tutWin->convertToWorldSpace(tutPrevBtn->getPosition());
        CCRect tutPrevBtnRect = CCRectMake(tutPrevBtnPnt.x - tutPrevBtn->getContentSize().width / 2,
                                           tutPrevBtnPnt.y - tutPrevBtn->getContentSize().height / 2,
                                           tutPrevBtn->getContentSize().width,
                                           tutPrevBtn->getContentSize().height);
        
        CCPoint tutCancelBtnPnt = tutWin->convertToWorldSpace(tutCancelBtn->getPosition());
        CCRect tutCancelBtnRect = CCRectMake(tutCancelBtnPnt.x - tutCancelBtn->getContentSize().width / 2,
                                             tutCancelBtnPnt.y - tutCancelBtn->getContentSize().height / 2,
                                             tutCancelBtn->getContentSize().width,
                                             tutCancelBtn->getContentSize().height);
        
        if (tutNextBtnRect.containsPoint(touchLoc) && tutPageNo < 6) {
            tutPageNo += 1;
            sprintf(tutPageChar, "%i / 6", tutPageNo);
            tutPageLbl->setString(tutPageChar);
            TPMainScreen::setTutorial();
        }
        
        if (tutPrevBtnRect.containsPoint(touchLoc) && tutPageNo > 1) {
            tutPageNo -= 1;
            sprintf(tutPageChar, "%i / 6", tutPageNo);
            tutPageLbl->setString(tutPageChar);
            TPMainScreen::setTutorial();
        }
        
        if (tutCancelBtnRect.containsPoint(touchLoc)) {
            tutPageNo = 1;
            sprintf(tutPageChar, "%i / 6", tutPageNo);
            tutPageLbl->setString(tutPageChar);
            
            tutorialOn = false;
            TPMainScreen::setTutorial();
        }
    }
    
    //=============== Charge Controls =================
    
    if (chargeOn) {
        CCRect chargeBtn1Rect = TPMainScreen::boundingBoxWorldSpace(chargeWin, chargeBtnScr1);
        if (chargeBtn1Rect.containsPoint(touchLoc)) {
            charge2On = true;
            chargeOn = false;
            TPMainScreen::setCharge();
        }
        
        CCRect chargeCcl1Rect = TPMainScreen::boundingBoxWorldSpace(chargeWin, chargeCclBtn);
        if (chargeCcl1Rect.containsPoint(touchLoc)) {
            chargeExit = true;
            chargeOn = false;
            TPMainScreen::setCharge();
        }
    }
    
    if (charge2On) {
        CCRect chargeBtn2Rect = TPMainScreen::boundingBoxWorldSpace(chargeWin, chargeBtnScr2);
        if (chargeBtn2Rect.containsPoint(touchLoc)) {
            charge3On = true;
            charge2On = false;
            TPMainScreen::setCharge();
        }
        
        CCRect chargeCcl1Rect = TPMainScreen::boundingBoxWorldSpace(chargeWin, chargeCclBtn);
        if (chargeCcl1Rect.containsPoint(touchLoc)) {
            chargeExit = true;
            charge2On = false;
            TPMainScreen::setCharge();
        }
    }
    
    if (charge3On) {
        CCRect chargeBtn3Rect = TPMainScreen::boundingBoxWorldSpace(chargeWin3, chargeBtnScr3);
        if (chargeBtn3Rect.containsPoint(touchLoc)) {
            charge4On = true;
            charge3On = false;
            TPMainScreen::setCharge();
        }
        
        CCRect chargeCcl2Rect = TPMainScreen::boundingBoxWorldSpace(chargeWin3, chargeCclBtn3);
        if (chargeCcl2Rect.containsPoint(touchLoc)) {
            chargeBack = true;
            charge3On = false;
            TPMainScreen::setCharge();
            return;
        }
    }
    
    if (charge4On) {
        CCRect chargeBtn4Rect = TPMainScreen::boundingBoxWorldSpace(chargeWin3, chargeBtnScr4);
        if (chargeBtn4Rect.containsPoint(touchLoc)) {
            chargeExit = true;
            charge4On = false;
            TPMainScreen::setCharge();
            TPMainScreen::setCrystal(heartChargeCount);
            heartCount = 5;
            TPMainScreen::setupHearts();
        }
        
        CCRect chargeCcl2Rect = TPMainScreen::boundingBoxWorldSpace(chargeWin3, chargeCclBtn3);
        if (chargeCcl2Rect.containsPoint(touchLoc)) {
            chargeBack = true;
            charge4On = false;
            TPMainScreen::setCharge();
        }
    }
}

CCRect TPMainScreen::boundingBoxWorldSpace(CCSprite *parentSprite, CCSprite *childSprite) {
    CCPoint toConvertPoint = parentSprite->convertToWorldSpace(childSprite->getPosition());
    CCRect worldBox = CCRectMake(toConvertPoint.x - childSprite->getContentSize().width / 2,
                                 toConvertPoint.y - childSprite->getContentSize().height / 2,
                                 childSprite->getContentSize().width,
                                 childSprite->getContentSize().height);
    return worldBox;
}

#pragma mark New Designs

void TPMainScreen::setTutorial() {
    if (tutorialOn) {
        darkenBg->setVisible(true);
        darkenBg->setZOrder(105);
        
        tutWin->setVisible(true);
        if (tutPageNo == 1) {
            tutContent1->setVisible(true);
            tutContent2->setVisible(false);
        }
        if (tutPageNo == 2) {
            tutContent1->setVisible(false);
            tutContent2->setVisible(true);
            tutContent3->setVisible(false);
        }
        if (tutPageNo == 3) {
            tutContent2->setVisible(false);
            tutContent3->setVisible(true);
            tutContent4->setVisible(false);
        }if (tutPageNo == 4) {
            tutContent3->setVisible(false);
            tutContent4->setVisible(true);
            tutContent5->setVisible(false);
        }
        if (tutPageNo == 5) {
            tutContent4->setVisible(false);
            tutContent5->setVisible(true);
            tutContent6->setVisible(false);
        }
        if (tutPageNo == 6) {
            tutContent5->setVisible(false);
            tutContent6->setVisible(true);
        }
    }
    else {
        darkenBg->setVisible(false);
        tutPageNo = 1;
        tutWin->setVisible(false);
        tutContent1->setVisible(true);
        tutContent2->setVisible(false);
        tutContent3->setVisible(false);
        tutContent4->setVisible(false);
        tutContent5->setVisible(false);
        tutContent6->setVisible(false);
    }
}

void TPMainScreen::setCharge() {
    if (chargeOn) {
        darkenBg->setVisible(true);
        darkenBg->setZOrder(105);
        chargeWin->setVisible(true);
    }
    if (charge2On) {
        chargeBtnScr1->setVisible(false);
        chargeLblScr1->setVisible(false);
        
        chargeLblScr2->setVisible(true);
        chargeImgScr2->setVisible(true);
        chargeBtnScr2->setVisible(true);
        
        heartChargeLabel->setString(heartCharChar);
        heartChargeLabel->setVisible(true);
        
        crystalChargeLabel->setString(crystalChargeChar);
        crystalChargeLabel->setVisible(true);
    }
    if (charge3On) {
        darkenBg->setZOrder(119);
        chargeWin3->setVisible(true);
    }
    
    if (charge4On) {
        chargeBtnScr3->setVisible(false);
        chargeLblScr3->setVisible(false);
        heartChargingLabel->setVisible(false);
        
        chargeBtnScr4->setVisible(true);
        chargeLblScr4->setVisible(true);
    }
    
    if (chargeBack) {
        darkenBg->setZOrder(105);
        chargeWin3->setVisible(false);
        chargeBtnScr3->setVisible(true);
        chargeLblScr3->setVisible(true);
        chargeCclBtn3->setVisible(true);
        heartChargingLabel->setVisible(true);
        
        chargeBtnScr4->setVisible(false);
        chargeLblScr4->setVisible(false);
        
        charge2On = true;
        chargeBack = false;
    }
    
    if (chargeExit) {
        darkenBg->setVisible(false);
        darkenBg->setZOrder(-1);
        
        chargeWin->setVisible(false);
        chargeBtnScr1->setVisible(true);
        chargeLblScr1->setVisible(true);
        
        chargeLblScr2->setVisible(false);
        chargeImgScr2->setVisible(false);
        chargeBtnScr2->setVisible(false);
        heartChargeLabel->setVisible(false);
        crystalChargeLabel->setVisible(false);
        
        chargeWin3->setVisible(false);
        chargeBtnScr3->setVisible(true);
        chargeLblScr3->setVisible(true);
        chargeCclBtn3->setVisible(true);
        heartChargingLabel->setVisible(true);
        
        chargeBtnScr4->setVisible(false);
        chargeLblScr4->setVisible(false);
        
        chargeExit = false;
    }
}

void TPMainScreen::setupHearts() {
    heartChargeCount = 5 - heartCount;
    //Set texture only works if the sprite is created with some texture already
    if (heartCount == 5) {
        heartTP1->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
        heartTP2->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
        heartTP3->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
        heartTP4->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
        heartTP5->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
    }
    if (heartCount == 4) {
        heartTP1->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
        heartTP2->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
        heartTP3->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
        heartTP4->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
        heartTP5->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
    }
    if (heartCount == 3) {
        heartTP1->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
        heartTP2->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
        heartTP3->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
        heartTP4->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
        heartTP5->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
    }
    if (heartCount == 2) {
        heartTP1->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
        heartTP2->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
        heartTP3->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
        heartTP4->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
        heartTP5->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
    }
    if (heartCount == 1) {
        heartTP1->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart.png"));
        heartTP2->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
        heartTP3->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
        heartTP4->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
        heartTP5->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
    }
    if (heartCount == 0) {
        heartTP1->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
        heartTP2->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
        heartTP3->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
        heartTP4->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
        heartTP5->setTexture(CCTextureCache::sharedTextureCache()->addImage("poppo_heart_empty.png"));
    }
}

void TPMainScreen::setCrystal(int decreasingAmount) {
    rubyCount -= decreasingAmount;
    sprintf(rubyCountChar, "%i", rubyCount);
    rubyCountLabel->setString(rubyCountChar);
    
    heartChargeCount = 5 - heartCount;
    sprintf(heartViewChar, "%i", heartChargeCount);
    heartChargedLabel->setString(heartViewChar);
}

//============== Recieve data from Server and put into listGamer Array ================
void TPMainScreen::onHttpRequestCompleted(CCNode *sender, void *data) {
    CCHttpResponse *response = (CCHttpResponse*)data;

    if (!response) {
        return;
    }
    
    if (!response->isSucceed()) {
        CCLabelTTF *notConnectLabel = CCLabelTTF::create("現在ランキングは閉じています", "Time New Roman", 30);
        notConnectLabel->setPosition(ccp(winSize.width/2, winSize.height/2));
        notConnectLabel->setColor(ccYELLOW);
        
//        CCLabelTTF *checkInternetMsg = CCLabelTTF::create("Please check your internet connection !!", "Time New Roman", 30);
//        checkInternetMsg->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 40));
//        checkInternetMsg->setColor(ccYELLOW);
//       
//        this->addChild(checkInternetMsg,150);
        this->addChild(notConnectLabel, 150);
        return;
    }
    
    //dump data recieve
    std::vector<char> *buffer = response->getResponseData();
    char *data1 = (char*)(malloc(buffer->size()* sizeof(char)));
    int d = 0;
    for ( ; d < buffer->size(); d++) {
        data1[d] = (*buffer)[d];
    }
    data1[d+1]='\0';
    rapidjson::Document document;
    if(data1 != NULL && !document.Parse<0>(data1).HasParseError())
    {
        for (rapidjson::SizeType  i = 0; i < document.Size(); i++)
        {
            string name = document[i]["name"].GetString();
            TPMainScreen::convertName((char*)name.c_str());
            
            Gamer *gamer = new Gamer(name,document[i]["point"].GetInt());
            listGamer->addObject(gamer);
        }

    } else {
       
    }
    free(data1);
    CCLOG(" so luong gamer:%i",listGamer->count());
    tableView = CCTableView::create(this, CCSizeMake(700, 400));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setAnchorPoint(ccp(0, 0));
    tableView->setPosition(ccp(winSize.width / 8, 300));
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->addChild(tableView, 150);
    tableView->reloadData();
    
}

void TPMainScreen::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    
}

CCSize TPMainScreen::tableCellSizeForIndex(CCTableView *table, unsigned int index)
{
    return CCSizeMake(600, 80);
}

CCTableViewCell* TPMainScreen::tableCellAtIndex(CCTableView *table, unsigned int index)
{
    CCTableViewCell *cell = table->dequeueCell();
    cell = new CCTableViewCell();
    cell->autorelease();
    //
    Gamer *gamer = (Gamer*)listGamer->objectAtIndex(index);
    CCString *scoreGamer = CCString::createWithFormat("%d",gamer->getScore());
    CCLabelTTF *scoreLabel = CCLabelTTF::create(scoreGamer->getCString(), "Helvetica", 30.0);
    scoreLabel->setColor(ccYELLOW);
    scoreLabel->setAnchorPoint(ccp(1, 0));
    scoreLabel->setPosition(ccp(300,0));
    scoreLabel->setTag(150);
    cell->addChild(scoreLabel);
    
    CCLabelTTF *nameLabel = CCLabelTTF::create(gamer->getName().c_str(), "Helvetica", 30.0);
    nameLabel->setAnchorPoint(CCPointZero);
    nameLabel->setColor(ccYELLOW);
    nameLabel->setPosition(CCPointZero);
    cell->addChild(nameLabel,150);
//    CCLOG("Name:%s Diem:%d",gamer->getName().c_str(),gamer->getScore());
    return cell;
}

unsigned int TPMainScreen::numberOfCellsInTableView(CCTableView *table)
{
    return listGamer->count();
}

void TPMainScreen::scrollViewDidScroll(CCScrollView *view){
}

void TPMainScreen::scrollViewDidZoom(CCScrollView *view){
}

void TPMainScreen::convertName(char *str_name)
{
    int len = 0;
    int i = 0;
    len=strlen(str_name);
    for(i=0;i<len;i++)
    {
        if(str_name[i] == '_')
        {
            str_name[i] = ' ';
        }
    }
}

long TPMainScreen::getTime(){
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_sec / 1000);
    
}

Gamer::Gamer(string name, int score)
{
    this->_score = score;
    this->_name = name;
}

#pragma mark Another

void TPMainScreen::menuCloseCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

TPMainScreen::~TPMainScreen(){
    
}