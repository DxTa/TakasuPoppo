//
//  TPSocial.cpp
//  Cocos2Dx
//
//  Created by Kien MetalRock on 8/16/13.
//
//

#include "TPSocialScreen.h"
#include "TPUser.h"

CCScene* TPSocialScreen::scene()
{
    CCScene *scene = CCScene::create();
    TPSocialScreen *layer = TPSocialScreen::create();
    scene->addChild(layer);
    return scene;
}

bool TPSocialScreen::init(){
    if (!CCLayer::init()) {
        return false;
    }
    this->setTouchEnabled(true);
    
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    w = _screenSize.width;
    h = _screenSize.height;
    
    CCSprite *background = CCSprite::create("SocialBG.png");
    background->setPosition(ccp(w/2, h/2));
    
    this->addChild(background);
    
    CCMenuItemImage *line = CCMenuItemImage::create("LineButton.png",
                                                    "LineButtonOnClicked.png",
                                                    this, menu_selector(TPSocialScreen::Line));
    line->setPosition(ccp(w*3/8 - 40, h/5));
    
    CCMenuItemImage *face = CCMenuItemImage::create("FbButton.png",
                                                    "FbButtonOnClicked.png",
                                                    this, menu_selector(TPSocialScreen::Face));
    face->setPosition(ccp(w*4/8, h/5));
    CCMenuItemImage *tweet = CCMenuItemImage::create("TweetButton.png",
                                                    "TweetButtonOnClicked.png",
                                                    this, menu_selector(TPSocialScreen::Tweet));
    tweet->setPosition(ccp(w*5/8 + 40, h/5));
    
    CCMenuItemImage *close = CCMenuItemImage::create("CloseButton.png",
                                                     "CloseButtonOnClicked.png",
                                                     this, menu_selector(TPSocialScreen::Close));
    close->setPosition(ccp(w/2, tweet->getPosition().y - close->getContentSize().height));
    
    CCMenu *socialMenu = CCMenu::create(line, face, tweet, close, NULL);
    socialMenu->setPosition(CCPointZero);
    this->addChild(socialMenu);
    
    
    int score = TPUser::shareTPUser()->getUserScore();
    char scoreBuf[20];
    sprintf(scoreBuf, "%d", score);
    
    CCLabelBMFont *scoreLabel = CCLabelBMFont::create(scoreBuf, "TakasuScore.fnt", 50, kCCTextAlignmentCenter);
    scoreLabel->setPosition(ccp(w/2, tweet->getPosition().y + 130));
    this->addChild(scoreLabel);
    
    return true;
}

void TPSocialScreen::Line() {
    
}

void TPSocialScreen::Face() {
    
}

void TPSocialScreen::Tweet() {
    
}

void TPSocialScreen::Close() {
    CCScene *mainScene = TPMainScreen::scene(true, TPUser::shareTPUser()->getUserScore());
    CCTransitionScene* transition = CCTransitionSlideInT::create(1, mainScene);
    CCDirector::sharedDirector()->replaceScene(transition);
}