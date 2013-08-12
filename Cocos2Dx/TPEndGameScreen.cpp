//
//  TPEndGameScreen.cpp
//  Cocos2Dx
//
//  Created by macbook_017 on 8/12/13.
//
//

#include "TPEndGameScreen.h"
#include "CCString.h"
#include "TPMainScreen.h"

CCScene* TPEndGameScreen::scene() {
    CCScene *scene = CCScene::create();
    TPEndGameScreen *layer = TPEndGameScreen::create();
    scene->addChild(layer);
    return scene;
}

bool TPEndGameScreen::init()
{
    CCSize editBoxSize = CCSizeMake(winSize.width - 100, 60);
    
    CCLabelTTF *congrats = CCLabelTTF::create("BEST SCORE !!","BankGothic Md BT" , 60);
    congrats->setPosition(ccp(winSize.width /2, winSize.height * 6/8));
    this->addChild(congrats);
    
    //Email
    CCLabelTTF *emailLabel = CCLabelTTF::create("Please enter your Email", "BankGothic Md BT", 40);
    emailLabel->setPosition(ccp(winSize.width/2, winSize.height*5/8));
    this->addChild(emailLabel);
    
    editBoxUserEmail = CCEditBox::create(editBoxSize,CCScale9Sprite::create("GreenBox.png"));
    editBoxUserEmail->setPosition(ccp(winSize.width/2, 495));
    editBoxUserEmail->setFontSize(40);
    editBoxUserEmail->setFontColor(ccWHITE);
    editBoxUserEmail->setMaxLength(55);
    editBoxUserEmail->setReturnType(kKeyboardReturnTypeDone);
    editBoxUserEmail->setInputMode(kEditBoxInputModeEmailAddr);
    editBoxUserEmail->setDelegate(this);
    this->addChild(editBoxUserEmail);
    
    // Email Fail Message
    
    emailInvalidMsg = CCLabelTTF::create("Invalid Email !! Please try again !!", "BankGothic Md BT", 24);
    emailInvalidMsg->setPosition(ccp(editBoxUserEmail->getPosition().x,
                                     editBoxUserEmail->getPosition().y - 50));
    emailInvalidMsg->setColor(ccRED);
    emailInvalidMsg->setVisible(false);
    this->addChild(emailInvalidMsg);
     
    // name
    CCLabelTTF *nameLabel = CCLabelTTF::create("Please enter your name","BankGothic Md BT", 40);
    nameLabel->setPosition(ccp(winSize.width/2, winSize.height*3/8));
    this->addChild(nameLabel);
    editBoxUserName = CCEditBox::create(editBoxSize,CCScale9Sprite::create("GreenBox.png"));
    editBoxUserName->setPosition(ccp(winSize.width/2, nameLabel->getPositionY() - 60));
    editBoxUserName->setFontSize(40);
    editBoxUserName->setPlaceholderFontColor(ccWHITE);
    editBoxUserName->setMaxLength(15);
    editBoxUserName->setReturnType(kKeyboardReturnTypeDone);
    editBoxUserName->setInputMode(kEditBoxInputModeAny);
    editBoxUserName->setDelegate(this);
    this->addChild(editBoxUserName);
    
    nameInvalidMsg = CCLabelTTF::create("Invalid your name !! Please try again !", "BankGothic Md BT", 24);
    nameInvalidMsg->setPosition(ccp(editBoxUserName->getPosition().x, editBoxUserName->getPosition().y-50));
    nameInvalidMsg->setColor(ccRED);
    nameInvalidMsg->setVisible(false);
    this->addChild(nameInvalidMsg);
    
    CCMenuItemImage *sendMenuItem = CCMenuItemImage::create("SubmitButton.png",
                                                            "SubmitButtonOnClicked.png",
                                                            this, menu_selector(TPEndGameScreen::menuSendEmail));
    sendMenuItem->setPosition(ccp(winSize.width/2, 100));
    Menu = CCMenu::create(sendMenuItem, NULL);
    Menu->setPosition(CCPointZero);
    this->addChild(Menu, 1);
    
    return true;
}

void TPEndGameScreen::editBoxEditingDidBegin(CCEditBox* editBox)
{
}

void TPEndGameScreen:: editBoxEditingDidEnd(CCEditBox* editBox)
{
}

void TPEndGameScreen:: editBoxTextChanged(CCEditBox* editBox,const string& text)
{
}

void TPEndGameScreen:: editBoxReturn(CCEditBox* editBox)
{
    
}

void TPEndGameScreen:: menuSendEmail(CCObject *pSender)
{
    
    int emailValid = false;
    int nameValid = false;
    
    CCFiniteTimeAction *showAction = CCFadeIn::create(0.5f);
    CCFiniteTimeAction *hideAction = CCFadeOut::create(2.0f);
    
    string email = editBoxUserEmail->getText();
    if (!TPEndGameScreen::isValidEmail(email)) {
        
        emailInvalidMsg->setVisible(true);
        emailInvalidMsg->runAction(CCSequence::create(showAction,hideAction,NULL));
        
    }
    else{
        emailValid = true;
    }
    
    if (strcmp(editBoxUserName->getText(), "") == 0) {
        nameInvalidMsg->setVisible(true);
        nameInvalidMsg->runAction(CCSequence::create(showAction,hideAction,NULL));
        
    }else
    {
        nameValid = true;
    }
    
    if (nameValid == true && emailValid == true) {
        
        char *strName = (char *)editBoxUserName->getText();
        TPEndGameScreen::standardSizeName(strName);
        
        TPUser::shareTPUser()->setUserName(strName);
        TPUser::shareTPUser()->setUserEmail(editBoxUserEmail->getText());
        TPUser::shareTPUser()->setUserReward(0);
        
        CCHttpRequest * request = new CCHttpRequest();
        
        string nameUser = TPUser::shareTPUser()->getUserName();
        TPEndGameScreen::removeSpace((char*)nameUser.c_str());
        int scoreUser = TPUser::shareTPUser()->getUserScore();
        //        CCLOG(" Diem %i",scoreUser);
        char strScore[100] = {0};
        sprintf(strScore, "%i", scoreUser);
        string emailUser  = TPUser::shareTPUser()->getUserEmail();
        string serverIP = TPUser::shareTPUser()->getServerIp();
        //    int rewardUser    = TPUser::shareTPUser()->getUserReward();
        string url    = serverIP + ":3000/users?name="+nameUser+"&point="+strScore+"&email="+emailUser;
        request->setUrl(url.c_str());
        request->setRequestType(CCHttpRequest::kHttpPost);
        CCHttpClient::getInstance()->send(request);
        request->release();
        
        //Return TPMainScreen affter to sent data to Server
        
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, TPMainScreen::scene()));
        
    }
}
void TPEndGameScreen::menuBack(cocos2d::CCObject *pSender) {
    //    CCDirector::sharedDirector()->replaceScene(RankingScene::scene());
}

void TPEndGameScreen::convertName(char *str) {
    int len = 0;
    int i = 0;
    len=strlen(str);
    for(i=0;i<len;i++)
    {
        if(str[i] == '_')
        {
            str[i] = ' ';
        }
    }
}

void TPEndGameScreen::insertChar(char *str,int index)
{
    for(int i=strlen(str)+1;i>index&&i>0;i--) str[i]=str[i-1];
    str[index]=' ';
}

void TPEndGameScreen:: standardSizeName(char *str)
{
    int i,j=0;
    for(i=0;i<strlen(str);i++)
    {
        if (j==0&&strchr(",.\!;:?",str[i])) continue;
        else if (i&&j&&strchr(",.\!;:?",str[i-1])&&str[i]!=' ') insertChar(str,i);
        
        if (j&&strchr(",.\!;:?",str[i])&&str[j-1]==' ')  str[j-1]=str[i],str[j]=' ';
        else if ((j==0&&str[i]!=' ')||(j&&str[j-1]==' '&&str[i]!=' ')) str[j++]=toupper(str[i]);
        else if ((j&&str[i]!=' ')||(j&&str[i-1]!=' '&&str[i]==' ')) str[j++]=str[i];
    }
    str[j-1*(j&&str[j-1]==' ')]=NULL;
}

// Change a space in a string by "_" char
void TPEndGameScreen:: removeSpace(char *str) {
    int len = 0;
    int i = 0;
    len=strlen(str);
    for(i=0;i<len;i++)
    {
        if(str[i] == ' ')
        {
            str[i] = '_';
        }
    }
}


bool TPEndGameScreen::isValidEmail(string email){
    int length = email.length();
    if (length >= 9 && ((email[0] > 64 && email[0] < 91) ||
                        (email[0] > 96 && email[0] < 123)) && email[length - 1] != '.') {
        int count1 = 0;
        int count2 = 0;
        int count3 = 0;
        int count4 = 0;
        for (int i = 0; i < length; i++) {
            if (email[i] == '@') {
                count3++;
            }
            if ((email[i] < 48 && email[i] != 46) || (email[i] > 57 && email[i] < 64) ||
                (email[i] >90 && email[i] < 97 && email[i] != 95) || (email[i] >122)) {
                count4++;
            }
            if (email[i] == '.') {
                if (i < email.find('@')) {
                    count1++;
                } else {
                    count2++;
                }
            }
        }
        if (count3 == 1 && count4 == 0 && count1 < 2 && count2 > 0 &&
            ( email.find('@') > 3 && email.find('@') < 32)) {
            return true;
        } else {
            return false;
        }
        
    } else {
        return false;
    }
    
}