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
#include "TPUser.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene *TPMainScreen::scene(bool isGameOver, int score) {
    CCScene *scene = CCScene::create();
    TPMainScreen *layer = TPMainScreen::create(isGameOver, score);
    scene->addChild(layer);
    return scene;
}

bool TPMainScreen::init(bool isGameOver, int score) {
    if (!CCLayer::init()) return false;
    
    if (isGameOver) {
        gameOverIsOn = isGameOver;
        gameScoreOfNow = score;
        CCLog("Score: %i", gameScoreOfNow);
    }
    
    //===================== New UI =========================
    heartCount = 1;
    itemShadeArray = new CCArray;
    
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
    
    
    //===================== New Setting =========================
    settingContainer = CCSprite::create("poppo_tut_win.png");
    settingContainer->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    this->addChild(settingContainer, 130, 144);
    
    settingCancelBtn = CCSprite::create("poppo_charge_ccl.png");
    settingCancelBtn->setPosition(ccp(settingContainer->getContentSize().width - 10,
                                      settingContainer->getContentSize().height - 30));
    settingContainer->addChild(settingCancelBtn, 131, 145);
    
    settingContents = CCSprite::create("SettingContents.png");
    settingContents->setPosition(ccp(settingContainer->getContentSize().width / 2 + 20,
                                     settingContainer->getContentSize().height - 170));
    settingContainer->addChild(settingContents, 132, 145);
    
    bgmSlider = CCControlSlider::create("SliderBody.png", "Slider1Progress.png", "Slider2Mark.png");
    bgmSlider->setPosition(ccp(settingContainer->getContentSize().width / 2,
                               settingContainer->getContentSize().height - 240));
    bgmSlider->setEnabled(true);
    bgmSlider->setMinimumValue(0);
    bgmSlider->setMaximumValue(100);
    bgmSlider->setValue(40);
    settingContainer->addChild(bgmSlider, 133, 146);
    
    sfxSlider = CCControlSlider::create("SliderBody.png", "Slider2Progress.png", "Slider1Mark.png");
    sfxSlider->setPosition(ccp(settingContainer->getContentSize().width / 2,
                               settingContainer->getContentSize().height - 345));
    sfxSlider->setEnabled(true);
    sfxSlider->setMinimumValue(0);
    sfxSlider->setMaximumValue(100);
    sfxSlider->setValue(60);
    settingContainer->addChild(sfxSlider, 133, 147);
    
    
    aboutBtn = CCSprite::create("AboutButton.png");
    aboutBtn->setPosition(ccp(settingContainer->getContentSize().width / 2 - 130,
                              settingContainer->getContentSize().height - 490));
    
    settingContainer->addChild(aboutBtn, 133, 148);
    
    tutorialBtn = CCSprite::create("HowToPlayButton.png");
    tutorialBtn->setPosition(ccp(settingContainer->getContentSize().width / 2 + 130,
                              settingContainer->getContentSize().height - 490));
    
    settingContainer->addChild(tutorialBtn, 133, 149);
    settingContainer->setVisible(false);
    
    //===================== NewItem =========================
    
    itemContainer = CCSprite::create("poppo_empty_container.png");
    itemContainer->setPosition(ccp(rankingContainer->getContentSize().width / 2,
                                    rankingContainer->getContentSize().height - 50));
    this->addChild(itemContainer, 101, 155);
    
    item1 = CCSprite::create("poppoItem1.png");
    item1->setPosition(ccp(itemContainer->getContentSize().width / 2 - 150,
                           itemContainer->getContentSize().height / 2 + 130));
    itemContainer->addChild(item1, 102, 156);
    
    item2 = CCSprite::create("poppoItem2.png");
    item2->setPosition(ccp(itemContainer->getContentSize().width / 2 - 25,
                           itemContainer->getContentSize().height / 2 + 130));
    itemContainer->addChild(item2, 102, 157);
    
    item3 = CCSprite::create("poppoItem3.png");
    item3->setPosition(ccp(itemContainer->getContentSize().width / 2 + 100,
                           itemContainer->getContentSize().height / 2 + 130));
    itemContainer->addChild(item3, 102, 158);
    
    item4 = CCSprite::create("poppoItem4.png");
    item4->setPosition(ccp(itemContainer->getContentSize().width / 2 + 225,
                           itemContainer->getContentSize().height / 2 + 130));
    itemContainer->addChild(item4, 102, 159);
    
    item5 = CCSprite::create("poppoItem5.png");
    item5->setPosition(ccp(itemContainer->getContentSize().width / 2 - 150,
                           itemContainer->getContentSize().height / 2 + 10));
    itemContainer->addChild(item5, 102, 160);
    
    item6 = CCSprite::create("poppoItem6.png");
    item6->setPosition(ccp(itemContainer->getContentSize().width / 2 - 25,
                           itemContainer->getContentSize().height / 2 + 10));
    itemContainer->addChild(item6, 102, 161);
    
    item7 = CCSprite::create("poppoItem7.png");
    item7->setPosition(ccp(itemContainer->getContentSize().width / 2 + 100,
                           itemContainer->getContentSize().height / 2 + 10));
    itemContainer->addChild(item7, 102, 162);
    
    item8 = CCSprite::create("poppoItem8.png");
    item8->setPosition(ccp(itemContainer->getContentSize().width / 2 + 225,
                           itemContainer->getContentSize().height / 2 + 10));
    itemContainer->addChild(item8, 102, 163);
    
    item9 = CCSprite::create("itemNotAvailable.png");
    item9->setPosition(ccp(itemContainer->getContentSize().width / 2 - 150,
                           itemContainer->getContentSize().height / 2 - 110));
    itemContainer->addChild(item9, 102, 164);
    
    item10 = CCSprite::create("itemNotAvailable.png");
    item10->setPosition(ccp(itemContainer->getContentSize().width / 2 - 25,
                            itemContainer->getContentSize().height / 2 - 110));
    itemContainer->addChild(item10, 102, 165);
    
    itemLabel = CCSprite::create("poppoItemLabel.png");
    itemLabel->setPosition(ccp(itemContainer->getContentSize().width / 2 + 160,
                    itemContainer->getContentSize().height / 2 - 110));
    itemContainer->addChild(itemLabel, 102);
    
    item1Shade = CCSprite::create("ItemShade.png");
    item1Shade->setPosition(ccp(itemContainer->getContentSize().width / 2 - 150,
                           itemContainer->getContentSize().height / 2 + 130));
    itemContainer->addChild(item1Shade, 103, 166);
    item1Shade->setVisible(false);

    item2Shade = CCSprite::create("ItemShade.png");
    item2Shade->setPosition(ccp(itemContainer->getContentSize().width / 2 - 25,
                           itemContainer->getContentSize().height / 2 + 130));
    itemContainer->addChild(item2Shade, 103, 167);
    item2Shade->setVisible(false);
    
    item3Shade = CCSprite::create("ItemShade.png");
    item3Shade->setPosition(ccp(itemContainer->getContentSize().width / 2 + 100,
                           itemContainer->getContentSize().height / 2 + 130));
    itemContainer->addChild(item3Shade, 103, 168);
    item3Shade->setVisible(false);
    
    item4Shade = CCSprite::create("ItemShade.png");
    item4Shade->setPosition(ccp(itemContainer->getContentSize().width / 2 + 225,
                           itemContainer->getContentSize().height / 2 + 130));
    itemContainer->addChild(item4Shade, 103, 169);
    item4Shade->setVisible(false);
    itemShadeArray->addObject(item4Shade);
    
    item5Shade = CCSprite::create("ItemShade.png");
    item5Shade->setPosition(ccp(itemContainer->getContentSize().width / 2 - 150,
                           itemContainer->getContentSize().height / 2 + 10));
    itemContainer->addChild(item5Shade, 103, 170);
    item5Shade->setVisible(false);
    itemShadeArray->addObject(item5Shade);
    
    item6Shade = CCSprite::create("ItemShade.png");
    item6Shade->setPosition(ccp(itemContainer->getContentSize().width / 2 - 25,
                           itemContainer->getContentSize().height / 2 + 10));
    itemContainer->addChild(item6Shade, 103, 171);
    item6Shade->setVisible(false);
    itemShadeArray->addObject(item6Shade);
    
    item7Shade = CCSprite::create("ItemShade.png");
    item7Shade->setPosition(ccp(itemContainer->getContentSize().width / 2 + 100,
                           itemContainer->getContentSize().height / 2 + 10));
    itemContainer->addChild(item7Shade, 103, 172);
    item7Shade->setVisible(false);
    itemShadeArray->addObject(item7Shade);
    
    item8Shade = CCSprite::create("ItemShade.png");
    item8Shade->setPosition(ccp(itemContainer->getContentSize().width / 2 + 225,
                           itemContainer->getContentSize().height / 2 + 10));
    itemContainer->addChild(item8Shade, 103, 173);
    item8Shade->setVisible(false);
    itemShadeArray->addObject(item8Shade);
    
    item9Shade = CCSprite::create("itemNotAvailable.png");
    item9Shade->setPosition(ccp(itemContainer->getContentSize().width / 2 - 150,
                           itemContainer->getContentSize().height / 2 - 110));
    itemContainer->addChild(item9Shade, 103, 174);
    item9Shade->setVisible(false);
    itemShadeArray->addObject(item9Shade);
    
    item10Shade = CCSprite::create("itemNotAvailable.png");
    item10Shade->setPosition(ccp(itemContainer->getContentSize().width / 2 - 25,
                            itemContainer->getContentSize().height / 2 - 110));
    itemContainer->addChild(item10Shade, 103, 175);
    item10Shade->setVisible(false);
    itemShadeArray->addObject(item10Shade);
    
    itemContainer->setVisible(false);
    
    //===================== Request =========================
    CCHttpRequest *request = new CCHttpRequest();
    string serverIP = TPUser::shareTPUser()->getServerIp();
    request->setUrl((serverIP+":3000/users.json").c_str());
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(this, httpresponse_selector(TPMainScreen::onHttpRequestCompleted));
    CCHttpClient::getInstance()->send(request);
    request->release();
    
    networkContainer = CCSprite::create("poppo_empty_container.png");
    networkContainer->setPosition(ccp(winSize.width / 2,
                                      winSize.height / 2 + 50));
    this->addChild(networkContainer, 101, 150);
    
    //===================== Gameover ======================
    
    
    if (gameOverIsOn) {
        networkContainer->setVisible(false);
        playBtn->setVisible(false);
        
        scoreContainer = CCSprite::create("poppo_empty_container.png");
        scoreContainer->setPosition(ccp(winSize.width / 2,
                                        winSize.height - 50));
        this->addChild(scoreContainer, 101, 176);
        
        scoreDancingTakasu = CCSprite::create("poppo_overImage.png");
        scoreDancingTakasu->setPosition(ccp(scoreContainer->getContentSize().width - 140,
                                            -200));
        scoreContainer->addChild(scoreDancingTakasu, 105, 178);
        
        string str = static_cast<ostringstream*>( &(ostringstream() << gameScoreOfNow) )->str();
        scoreBitMap = CCLabelBMFont::create(str.c_str(), "TakasuScore.fnt", 150, kCCTextAlignmentCenter);
        scoreBitMap->setPosition(ccp(scoreContainer->getContentSize().width / 2 - 100,
                                     - 80));
        scoreContainer->addChild(scoreBitMap, 105, 177);
        
        scoreBest = CCSprite::create("BestScore.png");
        scoreBest->setPosition(ccp(scoreContainer->getContentSize().width / 2 - 140,
                                   - 140));
        scoreContainer->addChild(scoreBest, 105, 180);
        
        scoreLabel = CCLabelTTF::create(str.c_str(), "Berlin Sans FB", 30);
        scoreLabel->setPosition(ccp(scoreContainer->getContentSize().width / 2 - 20,
                                    - 140));
        scoreContainer->addChild(scoreLabel, 105, 181);
        
        scoreClose = CCSprite::create("poppo_scoreClose.png");
        scoreClose->setPosition(ccp(scoreContainer->getContentSize().width / 2,
                                    - 500));
        scoreContainer->addChild(scoreClose, 103, 179);
    }
    
    return true;
}

void TPMainScreen::update(float dt) {
   
}

#pragma mark Touches

bool TPMainScreen::ccTouchBegan(CCTouch *touch, CCEvent *event) {
    if (bgmSlider->isTouchInside(touch)) {
        
    }
    
    return true;
}

void TPMainScreen::ccTouchEnded(CCTouch *touch, CCEvent *event) {
    CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
    
    if (!tutorialOn && !chargeOn && !settingOn) {
        CCRect settingBtnRect = settingBtn->boundingBox();
        if (settingBtnRect.containsPoint(touchLoc)) {
            settingOn = true;
            TPMainScreen::setSetting();
        }
        
        CCRect chargeBtnRect = TPMainScreen::boundingBoxWorldSpace(heartContainer, heartPlus);
        if (chargeBtnRect.containsPoint(touchLoc)) {
            chargeOn = true;
            TPMainScreen::setCharge();
        }
        
        CCRect startRect = playBtn->boundingBox();
        if (startRect.containsPoint(touchLoc) && !itemOn && !settingOn && !chargeOn && !tutorialOn && !gameOverIsOn) {
            itemOn = true;
            TPMainScreen::setItem();
            networkContainer->setVisible(false);
            return;
        }
    }
    
    if (gameOverIsOn) {
        CCRect closeButtonRect = TPMainScreen::boundingBoxWorldSpace(scoreContainer, scoreClose);
        if (closeButtonRect.containsPoint(touchLoc)) {
            scoreContainer->setVisible(false);
            
            playBtn->setVisible(true);
            networkContainer->setVisible(true);
            
            gameOverIsOn = false;
            return;
        }
    }
    //============== Tutorial Controls ================
    if (tutorialOn) {
        CCRect tutNextBtnRect = TPMainScreen::boundingBoxWorldSpace(tutWin, tutNextBtn);
        CCRect tutPrevBtnRect = TPMainScreen::boundingBoxWorldSpace(tutWin, tutPrevBtn);
        CCRect tutCancelBtnRect = TPMainScreen::boundingBoxWorldSpace(tutWin, tutCancelBtn);
        
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
    
    //=============== Tut Controls =================
    if (settingOn) {
        CCRect howToRect = TPMainScreen::boundingBoxWorldSpace(settingContainer, tutorialBtn);
        if (howToRect.containsPoint(touchLoc)) {
            tutorialOn = true;
            settingOn = false;
            TPMainScreen::setSetting();
            TPMainScreen::setTutorial();
        }
        
        CCRect cancelSettingRect = TPMainScreen::boundingBoxWorldSpace(settingContainer, settingCancelBtn);
        if (cancelSettingRect.containsPoint(touchLoc)) {
            settingOn = false;
            TPMainScreen::setSetting();
        }
    }
    
    //=============== Item Controls =================
    if (itemOn) {
        CCRect startRect = playBtn->boundingBox();
        if (startRect.containsPoint(touchLoc) && itemOn && !settingOn && !tutorialOn && !chargeOn) {
            TPItemObject* itemObject = new TPItemObject(item1On, item2On, item3On, specialItemID);
            CCScene *gameScene = TakasuPoppo::scene(itemObject);
            CCTransitionScene* transition = CCTransitionSlideInT::create(1, gameScene);
            CCDirector::sharedDirector()->replaceScene(transition);
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        }
        
        CCRect item1Rect = TPMainScreen::boundingBoxWorldSpace(itemContainer, item1);
        if (item1Rect.containsPoint(touchLoc) && !item1On) {
            item1On = true;
            TPMainScreen::setItem();
            return;
        }
        if (item1Rect.containsPoint(touchLoc) && item1On) {
            item1On = false;
            TPMainScreen::setItem();
            return;
        }
        
        CCRect item2Rect = TPMainScreen::boundingBoxWorldSpace(itemContainer, item2);
        if (item2Rect.containsPoint(touchLoc) && !item2On) {
            item2On = true;
            TPMainScreen::setItem();
            return;
        }
        if (item2Rect.containsPoint(touchLoc) && item2On) {
            item2On = false;
            TPMainScreen::setItem();
            return;
        }
        
        CCRect item3Rect = TPMainScreen::boundingBoxWorldSpace(itemContainer, item3);
        if (item3Rect.containsPoint(touchLoc) && !item3On) {
            item3On = true;
            TPMainScreen::setItem();
            return;
        }
        if (item3Rect.containsPoint(touchLoc) && item3On) {
            item3On = false;
            TPMainScreen::setItem();
            return;
        }
        
        CCRect item4Rect = TPMainScreen::boundingBoxWorldSpace(itemContainer, item4);
        if (item4Rect.containsPoint(touchLoc) && specialItemID != 1) {
            specialItemID = SPECIAL_ITEM_1_ID;
            TPMainScreen::setItem();
            return;
        }
        if (item4Rect.containsPoint(touchLoc) && specialItemID == 1) {
            specialItemID = 0;
            TPMainScreen::setItem();
            return;
        }
        
        CCRect item5Rect = TPMainScreen::boundingBoxWorldSpace(itemContainer, item5);
        if (item5Rect.containsPoint(touchLoc) && specialItemID != 2) {
            specialItemID = SPECIAL_ITEM_2_ID;
            TPMainScreen::setItem();
            return;
        }
        if (item5Rect.containsPoint(touchLoc) && specialItemID == 2) {
            specialItemID = 0;
            TPMainScreen::setItem();
            return;
        }
        
        CCRect item6Rect = TPMainScreen::boundingBoxWorldSpace(itemContainer, item6);
        if (item6Rect.containsPoint(touchLoc) && specialItemID != 3) {
            specialItemID = SPECIAL_ITEM_3_ID;
            TPMainScreen::setItem();
            return;
        }
        if (item6Rect.containsPoint(touchLoc) && specialItemID == 3) {
            specialItemID = 0;
            TPMainScreen::setItem();
            return;
        }
        
        CCRect item7Rect = TPMainScreen::boundingBoxWorldSpace(itemContainer, item7);
        if (item7Rect.containsPoint(touchLoc) && specialItemID != 4) {
            specialItemID = SPECIAL_ITEM_4_ID;
            TPMainScreen::setItem();
            return;
        }
        if (item7Rect.containsPoint(touchLoc) && specialItemID == 4) {
            specialItemID = 0;
            TPMainScreen::setItem();
            return;
        }
        
        CCRect item8Rect = TPMainScreen::boundingBoxWorldSpace(itemContainer, item8);
        if (item8Rect.containsPoint(touchLoc) && specialItemID != 5) {
            specialItemID = SPECIAL_ITEM_5_ID;
            TPMainScreen::setItem();
            return;
        }
        if (item8Rect.containsPoint(touchLoc) && specialItemID == 5) {
            specialItemID = 0;
            TPMainScreen::setItem();
            return;
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

void TPMainScreen::setItem() {
    if (itemOn) {
        networkContainer->setVisible(false);
        itemContainer->setVisible(true);
        if (item1On) item1Shade->setVisible(true);
        if (!item1On) item1Shade->setVisible(false);
        
        if (item2On) item2Shade->setVisible(true);
        if (!item2On) item2Shade->setVisible(false);
        
        if (item3On) item3Shade->setVisible(true);
        if (!item3On) item3Shade->setVisible(false);
        
        if (specialItemID == 1) TPMainScreen::setSpecialItemShade(item4Shade);
        if (specialItemID == 2) TPMainScreen::setSpecialItemShade(item5Shade);
        if (specialItemID == 3) TPMainScreen::setSpecialItemShade(item6Shade);
        if (specialItemID == 4) TPMainScreen::setSpecialItemShade(item7Shade);
        if (specialItemID == 5) TPMainScreen::setSpecialItemShade(item8Shade);
        if (specialItemID == 0) {
            CCObject *object;
            CCARRAY_FOREACH(itemShadeArray, object) {
                CCSprite *shadeSprite = dynamic_cast<CCSprite*>(object);
                shadeSprite->setVisible(false);
            }
        }
    }
    if (!itemOn) {
        itemContainer->setVisible(false);
        networkContainer->setVisible(true);
    }
}

void TPMainScreen::setSpecialItemShade(CCSprite *selectedItemShade) {
    CCObject *object;
    CCARRAY_FOREACH(itemShadeArray, object) {
        CCSprite *shadeSprite = dynamic_cast<CCSprite*>(object);
        shadeSprite->setVisible(false);
    }
    selectedItemShade->setVisible(true);
}

void TPMainScreen::setSetting() {
    if (settingOn) {
        darkenBg->setVisible(true);
        darkenBg->setZOrder(129);

        settingContainer->setVisible(true);
    }
    if (!settingOn) {
        darkenBg->setVisible(false);
        settingContainer->setVisible(false);
    }
}

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
        notConnectLabel->setPosition(ccp(networkContainer->getContentSize().width / 2,
                                         networkContainer->getContentSize().height / 2));
        notConnectLabel->setColor(ccYELLOW);
        networkContainer->addChild(notConnectLabel, 107);
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
    tableView = CCTableView::create(this, CCSizeMake(700, 400));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setAnchorPoint(ccp(0, 0));
    tableView->setPosition(ccp(networkContainer->getContentSize().width / 2 - 200,
                               networkContainer->getContentSize().height / 2 - 200));
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    networkContainer->addChild(tableView, 102, 151);
    tableView->reloadData();
    
}

void TPMainScreen::tableCellTouched(CCTableView* table, CCTableViewCell* cell) {
    
}

CCSize TPMainScreen::tableCellSizeForIndex(CCTableView *table, unsigned int index) {
    return CCSizeMake(600, 80);
}

CCTableViewCell* TPMainScreen::tableCellAtIndex(CCTableView *table, unsigned int index) {
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

TPMainScreen* TPMainScreen::create(bool isGameOver, int score){
    TPMainScreen *pRet = new TPMainScreen();
    if (pRet && pRet->init(isGameOver, score)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
    
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