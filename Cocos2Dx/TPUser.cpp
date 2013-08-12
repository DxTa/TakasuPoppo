//
//  TPUser.cpp
//  Cocos2Dx
//
//  Created by macbook_017 on 8/12/13.
//
//

#include "TPUser.h"
#include "TPUser.h"

TPUser::TPUser()
{
    this->setServerIp(IP_SERVER);
}

TPUser* TPUser::shareTPUser()
{
    return new TPUser();
}

string TPUser::getUserName(){
    return CCUserDefault::sharedUserDefault()->getStringForKey("UserName");
}

void TPUser::setUserName(string name){
    CCUserDefault::sharedUserDefault()->setStringForKey("UserName", name);
    CCUserDefault::sharedUserDefault()->flush();
}

string TPUser::getUserEmail(){
    return CCUserDefault::sharedUserDefault()->getStringForKey("UserEmail");
}

void TPUser::setUserEmail(string email)
{
    CCUserDefault::sharedUserDefault()->setStringForKey("UserEmail", email);
    CCUserDefault::sharedUserDefault()->flush();
}

int TPUser::getUserScore(){
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("UserScore");
}

void TPUser::setUserScore(int score){
    CCUserDefault::sharedUserDefault()->setIntegerForKey("UserScore", score);
    CCUserDefault::sharedUserDefault()->flush();
}

int TPUser::getUserReward(){
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("UserReward");
}

void TPUser::setUserReward(int reward){
    CCUserDefault::sharedUserDefault()->setIntegerForKey("UserReward", reward);
    CCUserDefault::sharedUserDefault()->flush();
}

int TPUser::getUserHeart(){
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("UserHeart");
}

void TPUser::setUserHeart(int heart)
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("UserHeart", heart);
    CCUserDefault::sharedUserDefault()->flush();
}

int TPUser::getLastTime(){
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("UserLastTime");
}

void TPUser::setLastTime(int time)
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("UserLastTime", time);
    CCUserDefault::sharedUserDefault()->flush();
}

int TPUser::getCrystal(){
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("UserCrystal");
}

void TPUser::setCrystal(int crystal)
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("UserCrystal", crystal);
    CCUserDefault::sharedUserDefault()->flush();
}

string TPUser::getServerIp()
{
    return this->_serverIP;
}

void TPUser::setServerIp(string ip){
    this->_serverIP = ip;
}
