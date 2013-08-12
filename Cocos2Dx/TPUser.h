//
//  TPUser.h
//  Cocos2Dx
//
//  Created by macbook_017 on 8/12/13.
//
//
#ifndef __TaKaSuPoppo__TPUser__
#define __TaKaSuPoppo__TPUser__

#define IP_SERVER "192.168.1.189"

#include "cocos2d.h"

using namespace  cocos2d;
using namespace std;

USING_NS_CC;

class TPUser :public CCObject {
private:
    string _serverIP;
//    string _userName;
//    string _userEmail;
//    int _userScore;
//    int _userReward;
//    int _heart;
//    int _lastTime;
//    int _crystal;
    
public:
    TPUser();
    static TPUser* shareTPUser();
    
    string getUserName();
    void setUserName(string name);
    
    string getUserEmail();
    void setUserEmail(string email);
    
    int getUserScore();
    void setUserScore(int score);
    
    int getUserReward();
    void setUserReward(int reward);
    
    string getServerIp();
    void setServerIp(string ip);
    
    int getUserHeart();
    void setUserHeart(int heart);
    
    int getLastTime();
    void setLastTime(int time);
    
    int getCrystal();
    void setCrystal(int crystal);
    
};

#endif