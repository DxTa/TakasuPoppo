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
    
    long getStartedTime();
    void setStartedTime(long time);
    
    int getCrystal();
    void setCrystal(int crystal);
    
    bool ExistUser();
//    void setExistUser(bool existUser);
    
    float getBMG();
    void setBMG(float bmg);

    float getVolume();
    void setVolume(float volume);

    int getScoreLowestTopRanking();
    void setScoreLowestTopRanking(int scoreLowest);

};

#endif