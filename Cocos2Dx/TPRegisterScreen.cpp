//
//  TPEndGameScreen.cpp
//  Cocos2Dx
//
//  Created by macbook_017 on 8/12/13.
//
//

#include "TPRegisterScreen.h"
#include "CCString.h"

CCScene* TPRegisterScreen::scene() {
    CCScene *scene = CCScene::create();
    TPRegisterScreen *layer = TPRegisterScreen::create();
    scene->addChild(layer);
    return scene;
}

bool TPRegisterScreen::init()
{
    
    w = winSize.width;
    h = winSize.height;
    CCSize editBoxSize = CCSizeMake((w - 250), 50);
    
    CCSprite *background = CCSprite::create("GetPresentBG.png");
    background->setPosition(ccp(w/2, h/2));
    this->addChild(background);

//    CCLabelTTF *congrats = CCLabelTTF::create("BEST SCORE !!","BankGothic Md BT" , 60);
//    congrats->setPosition(ccp(winSize.width /2, winSize.height * 6/8));
//    this->addChild(congrats);
    
    //Email
    CCLabelTTF *emailLabel = CCLabelTTF::create("メールアドレス", "BankGothic Md BT", 30);
    emailLabel->setPosition(ccp(w/2 - w/5, h*3.8f/8));
    this->addChild(emailLabel);
    
    editBoxUserEmail = CCEditBox::create(editBoxSize,CCScale9Sprite::create("WhiteBox.png"));
    editBoxUserEmail->setAnchorPoint(CCPointZero);
    editBoxUserEmail->setPosition(ccp(emailLabel->getPosition().x - emailLabel->getContentSize().width/2, emailLabel->getPositionY() - 80));
    editBoxUserEmail->setFontSize(40);
    editBoxUserEmail->setFontColor(ccBLUE);
    editBoxUserEmail->setMaxLength(55);
    editBoxUserEmail->setReturnType(kKeyboardReturnTypeDone);
    editBoxUserEmail->setInputMode(kEditBoxInputModeEmailAddr);
    editBoxUserEmail->setDelegate(this);
    this->addChild(editBoxUserEmail);
    
    // Email Fail Message
    
    emailInvalidMsg = CCLabelTTF::create(" Invalid Email !! Please try again !!", "BankGothic Md BT", 24);
    emailInvalidMsg->setAnchorPoint(CCPointZero);
    emailInvalidMsg->setPosition(ccp(editBoxUserEmail->getPosition().x,
                                     editBoxUserEmail->getPosition().y - 30));
    emailInvalidMsg->setColor(ccRED);
    emailInvalidMsg->setVisible(false);
    this->addChild(emailInvalidMsg);
     
    // name
    CCLabelTTF *nameLabel = CCLabelTTF::create("ニックネーム","BankGothic Md BT", 30);
    nameLabel->setPosition(ccp(w/2 - w/5 - 10, h*4.8/8));
    this->addChild(nameLabel);
    editBoxUserName = CCEditBox::create(editBoxSize,CCScale9Sprite::create("WhiteBox.png"));
    editBoxUserName->setAnchorPoint(CCPointZero);
    editBoxUserName->setPosition(ccp(nameLabel->getPosition().x - nameLabel->getContentSize().width/2, nameLabel->getPositionY() - 75));
    editBoxUserName->setFontSize(40);
    editBoxUserName->setPlaceholderFontColor(ccWHITE);
    editBoxUserName->setMaxLength(15);
    editBoxUserName->setFontColor(ccBLUE);
    editBoxUserName->setReturnType(kKeyboardReturnTypeDone);
    editBoxUserName->setInputMode(kEditBoxInputModeAny);
    editBoxUserName->setDelegate(this);
    this->addChild(editBoxUserName);
    
    nameInvalidMsg = CCLabelTTF::create("Invalid your name !! Please try again !", "BankGothic Md BT", 24);
    nameInvalidMsg->setAnchorPoint(CCPointZero);
    nameInvalidMsg->setPosition(ccp(editBoxUserName->getPosition().x, editBoxUserName->getPosition().y-30));
    nameInvalidMsg->setColor(ccRED);
    nameInvalidMsg->setVisible(false);
    this->addChild(nameInvalidMsg);
    
    CCMenuItemImage *sendMenuItem = CCMenuItemImage::create("SendButton.png",
                                                            "SendButtonOnClicked.png",
                                                            this, menu_selector(TPRegisterScreen::SendData));
    sendMenuItem->setPosition(ccp(winSize.width/2, 100));
    Menu = CCMenu::create(sendMenuItem, NULL);
    Menu->setPosition(CCPointZero);
    this->addChild(Menu, 1);
    
    return true;
}

void TPRegisterScreen::editBoxEditingDidBegin(CCEditBox* editBox)
{
}

void TPRegisterScreen:: editBoxEditingDidEnd(CCEditBox* editBox)
{
}

void TPRegisterScreen:: editBoxTextChanged(CCEditBox* editBox,const string& text)
{
}

void TPRegisterScreen:: editBoxReturn(CCEditBox* editBox)
{
    
}

void TPRegisterScreen:: SendData(CCObject *pSender)
{
    
    int emailValid = false;
    int nameValid = false;
    
    CCFiniteTimeAction *showAction = CCFadeIn::create(0.5f);
    CCFiniteTimeAction *hideAction = CCFadeOut::create(2.0f);
    
    string email = editBoxUserEmail->getText();
    if (!TPRegisterScreen::isValidEmail(email)) {
        
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
        TPRegisterScreen::standardSizeName(strName);
        
        TPUser::shareTPUser()->setUserName(strName);
        TPUser::shareTPUser()->setUserEmail(editBoxUserEmail->getText());
        
        CCHttpRequest * request = new CCHttpRequest();
        
        string nameUser = TPUser::shareTPUser()->getUserName();
        TPRegisterScreen::removeSpace((char*)nameUser.c_str());
        int scoreUser = TPUser::shareTPUser()->getUserScore();

        char strScore[100] = {0};
        sprintf(strScore, "%i", scoreUser);
        string emailUser  = TPUser::shareTPUser()->getUserEmail();
        string serverIP = TPUser::shareTPUser()->getServerIp();

        string url    = serverIP + ":3000/users?name="+nameUser+"&point="+strScore+"&email="+emailUser;
        request->setUrl(url.c_str());
        request->setRequestType(CCHttpRequest::kHttpPost);
        CCHttpClient::getInstance()->send(request);
        request->release();
        
        //Return TPMainScreen affter to sent data to Server
        
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,TPSocialScreen::scene()));
        
    }
}


void TPRegisterScreen::convertName(char *str) {
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

void TPRegisterScreen::insertChar(char *str,int index)
{
    for(int i=strlen(str)+1;i>index&&i>0;i--) str[i]=str[i-1];
    str[index]=' ';
}

void TPRegisterScreen:: standardSizeName(char *str)
{
    int i,j=0;
    for(i=0;i<strlen(str);i++)
    {
        if (j==0&&strchr(",.\\!;:?",str[i])) continue;
        else if (i&&j&&strchr(",.\\!;:?",str[i-1])&&str[i]!=' ') insertChar(str,i);
        
        if (j&&strchr(",.\\!;:?",str[i])&&str[j-1]==' ')  str[j-1]=str[i],str[j]=' ';
        else if ((j==0&&str[i]!=' ')||(j&&str[j-1]==' '&&str[i]!=' ')) str[j++]=toupper(str[i]);
        else if ((j&&str[i]!=' ')||(j&&str[i-1]!=' '&&str[i]==' ')) str[j++]=str[i];
    }
    str[j-1*(j&&str[j-1]==' ')]=NULL;
}

// Change a space in a string by "_" char
void TPRegisterScreen:: removeSpace(char *str) {
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


bool TPRegisterScreen::isValidEmail(string email){
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