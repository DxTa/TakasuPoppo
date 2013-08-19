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
    return CCUserDefault::sharedUserDefault()->getStringForKey("UserName", "");
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
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("UserHeart", 2);
}

void TPUser::setUserHeart(int heart)
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("UserHeart", heart);
    CCUserDefault::sharedUserDefault()->flush();
}

int TPUser::getCrystal(){
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("UserCrystal",999999);
}

void TPUser::setCrystal(int crystal)
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("UserCrystal", crystal);
    CCUserDefault::sharedUserDefault()->flush();
}

float TPUser::getLastTime()
{
    return CCUserDefault::sharedUserDefault()->getFloatForKey("LastTime",0);
}

void TPUser::setLastTime(float lastTime)
{
    CCUserDefault::sharedUserDefault()->setFloatForKey("LastTime", lastTime);
    CCUserDefault::sharedUserDefault()->flush();
}

bool TPUser::ExistUser()
{
    string UserName = this->getUserName();
    return (!(UserName == ""));
}

//void TPUser::setExistUser(bool existUser)
//{
//  CCUserDefault::sharedUserDefault()->setBoolForKey("ExistUser", existUser);
//  CCUserDefault::sharedUserDefault()->flush();
//}

float TPUser::getBMG()
{
    return CCUserDefault::sharedUserDefault()->getFloatForKey("BMG");

}

void TPUser::setBMG(float bmg)
{
    CCUserDefault::sharedUserDefault()->setFloatForKey("BMG", bmg);
    CCUserDefault::sharedUserDefault()->flush();

}

float TPUser::getVolume()
{
    return CCUserDefault::sharedUserDefault()->getFloatForKey("Volume");
}

void TPUser::setVolume(float volume)
{
    CCUserDefault::sharedUserDefault()->setFloatForKey("Volume", volume);
    CCUserDefault::sharedUserDefault()->flush();
}

int TPUser::getScoreLowestTopRanking()
{
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("LowestTopRanking",0);
}

void TPUser::setScoreLowestTopRanking(int scoreLowest)
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("LowestTopRanking", scoreLowest);
    CCUserDefault::sharedUserDefault()->flush();
}

string TPUser::getServerIp()
{
    return this->_serverIP;
}

void TPUser::setServerIp(string ip){
    this->_serverIP = ip;
}
