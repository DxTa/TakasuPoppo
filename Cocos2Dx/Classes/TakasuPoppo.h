//  Created by MinhNT on 13/05/16.
//  Copyright FRAMGIA 2013年. All rights reserved.
//

#ifndef __TAKASUPOPPO_H__
#define __TAKASUPOPPO_H__


#include "cocos2d.h"
#include "TPObjectExtension.h"
#include "TPBlockSet.h"
#include "CCGestureRecognizer.h"
#include "CCSwipeGestureRecognizer.h"
#include "TPItemObject.h"
#include "TPDefinition.h"

USING_NS_CC;
class TakasuPoppo : public cocos2d::CCLayer {
private:
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint startSwipePoint;        //The starting point of swiping action
    CCPoint movingSwipePoint;       //The points that change during moving action
    CCPoint endSwipePoint;          //The points at the end of swiping action
    
    CCSprite *buttonSprite;         //A sprite for debug grid button
    CCSprite *refreshButton;        //A sprite for refresh grid button
    CCSprite *removeButton;         //A sprite for remove grid button
    
    CCSprite *firstTimeBar;
    CCSprite *middleTimeBar;
    CCSprite *lastTimeBar;
    
    CCProgressTimer *timerBar;
    CCProgressTimer *comboBar;
    
    CCTMXLayer *layer;              //The TMX Layer
    CCTMXTiledMap *map;             //The TMX Map
    
    CCArray *colorArray;            //Main blocks array, consist of TPObjectEx, stupidly named
    CCArray *toDestroyArray;        //To be removed blocks will be inserted to this array
    CCArray *pickedArray;           //The array of object to be moved with swipe button, 1 object only
    TPObjectExtension *mainSprite;
    
    CCArray *hintArray;             //An array consisting of possible matches
    
    TPObjectExtension *movedSprite; //The sprite to be moved with swipe button
    TPObjectExtension *swapedSprite;//The sprite to be swaped with moving sprite
    
    CCArray *debugTilesArray;       //The array consisting of debug objects
    
    float moveCounter;              //Counter time for move swipe action
    float fallCounter;              //Counter time for falling counter action
    
    float hbcComboTimer = 0;           //Timer for combos
    int hbcComboCounter = 0;           //Counter for combos
    
    float deltaTime;                //Public variable for delta time
    
    float executionTime = 3.5;
    
    float hintCounter = 3;          //Display hint after this counter
    
    float movingSpeed = AFTER_CLEAN_FALL_TIME;       //For all moving speed
    
    float gameTimer = PLAY_TIME;
    
    bool counterExist1 = false;
    bool counterExist2 = false;
    bool counterExist3 = false;
    
    bool spriteContained;           //Bool for the touch on sprite's trigger
    bool swiping;                   //Bool for swiping action
    bool swipeRecognized;           //Bool for swipe action recognized
    
    bool controlable;               //If the sprites are on the move, rends controlable false
    
    bool inTheMove;                 //True if there are sprites in moving action
//    bool inTheFall;                 //True if sprites are falling
    bool isLogicRunnning;
    bool inCleaning;
    
    bool swipeRight;                //True if swipe right action is recognized
    bool swipeLeft;                 //True if swipe left action is recognized
    bool swipeUp;                   //True if swipe up action is recognized
    bool swipeDown;                 //True if swipe down action is recognized
    
    bool hintDisplaying;            //Indicating that a hint is currently displayed
    int hintCount;
    
    bool gridOn = false;
    
    int debugRun = 0;
    
    char comboTimerString[20];
    char comboCounterString[20];
    
    
    CCLabelTTF *comboTimerLabel;
    CCLabelTTF *comboCounterLabel;
    
    //SCORE
    CCLabelTTF *lbScore;
    int score = 0;
    float ComboScoreRequired = 1;
    
    // Vinhnt - for fever time
    float feverTimer = 0;           //Timer for Fever Time
    float feverTimeLimit = 3;
    int feverCounter = 0;           //Counter for Fever Time
    bool isCreateFeverTime = false;
    bool isInFeverTime = false;
    
    int hyperC = 10;
    bool hyperBlockC = false;
    //Vinhnt - for Gauge Combo
    int gaugeComboCounter = 0;
    bool isCreateGaugeCombo = false;
    
    //item
    float timeBonus = 0;
    float increasedScore = 1;
    int doubleScore = 1;
    bool endLastScore = false;
    bool createThreeeHyper = false;
    float increaseComboTimes = 1;
    int lastScores = 0;
    int scoresBeforeLastBonus = 0;
    //moveto
    bool move =false;
    CCPoint mainPoint = CCPoint();
    bool swape = true;
    bool runningAfter = false;
    CCArray *boolMoveTo = new CCArray();
    CCArray *boolAfterClean = new CCArray();
    //time----
    bool endTime = false;
    // fixed hyper block C
    bool isHBCinBlockSet = false;
    float setCleanDelay();
    
    bool createB = false;

public:
    CCArray* currentBlockSet = NULL;            // keep track of the current block set
    
#pragma mark Takasu Poppo
    
    
    virtual void update(float dt);
    void menuCloseCallback(CCObject* pSender);
    //Setup timer, preparing for the game
    void startGame();
    
    //Fixed update for executing game's logic
    void fixedUpdate(float time);
    
    //Scheduler for moving time delay
    void movingBoolSwitch(float time);
    //Scheduler for falling time delay
    void fallingBoolSwitch(float time);
    //Unschedule generation
    void scheduleGenerate();
    
    //Hint display
    void hintGeneration();
    // refresh the map if there is no combo can be make
    void refreshWhenNoCombo();
    //Logic execution
    void logicExecution();
    
    void timeSetup();
    
    void timeCounter();
    
    void timeOver();
    
#pragma mark Touch
    virtual void ccTouchesBegan(CCSet *touches, CCEvent *event);
    virtual void ccTouchesMoved(CCSet *touches, CCEvent *event);
    virtual void ccTouchesEnded(CCSet *touches, CCEvent *event);
    //Validate touch position, returns false if out of map
    bool touchPosValidation(CCPoint touchLoc);
    
    
#pragma mark Map
    //Creates TMX Map
    void addTileMap();
    //Add fixture to TMX Layer
    void createFixture();
    
    //Check if there is an empty block, not in use
    void checkEmpty();
    //Generate a random sprite on EX object
    void generateRandomBlock(TPObjectExtension *exObj, CCPoint fallCoor);
    //Generate a certain sprite on EX Object
    void generateBlock(TPObjectExtension *exObj1, int type, CCPoint fallCoor);
    
    //Returns a coordination for position
    CCPoint tileCoorForPosition(CCPoint position);
    
    //Inserts empty blocks to array, to be assigned in the next function
    void addBlocksToArray();
    //Set values for EX Object
    void setValuesForExObj(TPObjectExtension *exObj, int colorID, int gid, CCSprite *sprite,
                           CCPoint position, CCPoint coordination, bool trigger, int blockType);
    
#pragma mark Match
    //Check if there is matching pair in the begining, gotta rewrite it later
    bool isTileMatched(int gid, int typeID);
    
    //Check matching blocks and add them to destroy array
    void matchList();
    //Called in matchList function, to determinte Horizontal Matches
    CCArray *getMatchHor(TPObjectExtension *exObj);
    //Called in matchList function, to determinte Vertical Matches
    CCArray *getMatchVer(TPObjectExtension *exObj);
    
    //Returns a sum of possible matches
    int lookForMatches();
    //Returns true if match exists with objects
    bool sumOfMatches(TPObjectExtension *exA, TPObjectExtension *exB,
                      TPObjectExtension *ex1, TPObjectExtension *ex2, TPObjectExtension *ex3);
    
    //Returns an EX Object for coordination, awesome
    TPObjectExtension *coorToExObj(CCPoint);
    
    //Check before swapping a sprite if a match will be possible
    bool matchAble(CCPoint coor, int type);
    
    //Generate a match if there is a shortage
    void smartGeneration();
    
    bool destroyCheck(TPObjectExtension *ex1);
    
    CCPoint getFallPos(TPObjectExtension *exObj, CCPoint lastRowAtColumn0,
                       CCPoint lastRowAtColumn1, CCPoint lastRowAtColumn2,
                       CCPoint lastRowAtColumn3, CCPoint lastRowAtColumn4,
                       CCPoint lastRowAtColumn5, CCPoint lastRowAtColumn6);
    
#pragma mark Clean
    //Remove blocks from destroy array
    void cleanBlocks();
    //Move the blocks on the top of the destroyed blocks down
    void afterClean();
    
    //Clean with Hyper Block A
    void cleanHyperBlockA(TPObjectExtension* exObj);
    // Vinhnt - update: 1 more parametter for ferver time
    //Clean with Hyper Block B
    void cleanHyperBlockB(TPObjectExtension* exObj);
    //Clean with Hyper Block C
    void cleanHyperBlockC(TPObjectExtension* exObj);
    //Clean a sprite
    void cleanSprite(TPObjectExtension *exObj);
    
    void changeID(CCNode *sender, void* data);
    
    
#pragma mark Swiped
    //New swipe recognizer
    void swipeSetup();
    
    //New swpie action
    void didSwipe(int direction);
    //If swipe is recognizes, run into one of the followings
    void swipedUp(TPObjectExtension *exObj);
    void swipedDown(TPObjectExtension *exObj);
    void swipedLeft(TPObjectExtension *exObj);
    void swipedRight(TPObjectExtension *exObj);
    
    //Check the moving object and swapping object if action is possible, stupidly named
    void swapTilesCheck(TPObjectExtension *exObj, int swpGid);
    
    //Swap 2 blocks sprites and type IDs
    void swapColorID(TPObjectExtension *exObj, TPObjectExtension *swpObj);
    //Turn on or off controlable bool
    void switchControlable(TPObjectExtension *exObj);
    
    //Check if swapedSprite and movedSprite are in their position
    void checkPosition(TPObjectExtension *exObj, TPObjectExtension *swpObj);
    //Runs and return, for when moving is not possible
    void swapTilesBack(TPObjectExtension *exObj, TPObjectExtension *swpObj);
    
    TPObjectExtension* checkSwipe(TPBlockSet *blockSet);
    
#pragma mark Particles
    //Pop particles
    void popParticles(CCPoint position);
    //Remote particles run function, not available yet
    void remoteParticles();
    //Spark particles for hint
    void hintParticles(TPObjectExtension *exObj);
    //Shine particles, gives a shine for a set of blocks
    void comboParticles(TPObjectExtension *exObj);
    //Shine effect applies on Hyper Block A
    void sunParticles(TPObjectExtension *exObj);
    
    //Rends an outline effect on a sprite
    CCRenderTexture *outlineEffect(CCSprite *label, int size, ccColor3B color, GLubyte opacity);
    //Change sprite
    void spriteChange(CCNode *sender, void* data);
    
    void popAnimation(CCNode *sender, void* data);
#pragma mark Debug
    void setupDebugButton();
    void switchGrid();
    void remove();
    void refresh();
    void destroyAllBlocks();
    
    
    //Vinhnt - for HyperBlock
    void makeBlockToBeHBC(TPObjectExtension* exobj);
    void cleanOneBlock(TPObjectExtension* exobj);
    bool isInCurrentBlockSet(TPObjectExtension* exobj);
        
    bool isValidEx(TPObjectExtension * ex);
    void randomBlockC();
    
    void cleanA(TPObjectExtension* exObj);
    void cleanB(TPObjectExtension* exObj);
    void scaleHyperBlockC(CCNode *sender, void* data);
    void cleanOneBlock(CCNode *sender, void* data);
    void createSpecialBlock(TPObjectExtension* exObj, int blockType);
    
    int _spcialItemID;
    TPItemObject* _itemObject;
    // Vinhnt - for Mission Block 1
    bool isCleanMB1;
    bool isCreateMB1;
    int timeToCreateMB1;
    void generateBlocksAfterCleanMB1();
    
    // Vinhnt - for Mission Block 2:
    bool isCleanMB2;
    bool isCreateMB2;
    bool isExistMB2;
    int timeToCreateMB2;
    int countMB2;
    
    // Vinhnt - for Mission Block 3 (Item 6 – double score)
    bool isCleanMB3;
    bool isCreateMB3;
    int timeToCreateMB3;
    int doubleScoreStartTime;
    
    //Vinhnt - reWrite the init function
    virtual bool init(TPItemObject* itemObject);
    static TakasuPoppo* create(TPItemObject* itemObject);
    static CCScene* scene(TPItemObject* itemObject);
    
    // Vinhnt - for the really combo
    float ComboTimer = 0;           //Timer for combos
    int ComboCounter = 0;           //Counter for combos
    
    //Vinhnt - plus combo just in 1 function
    void plusAllComboCounter();
    
    //Vinhnt - logic Delay
    void logicDelaySwitch();
    bool executingLogic = false;
    float logicCounter = 0;
    float logicDelayTime = LOGIC_DELAY;
    
    //ITEM function
    bool lastScore();
    void addTime();
    void increasedScores();
    void cleanHyperBlockA(CCNode* sender, void* data);
    void cleanHyperBlockB(CCNode* sender, void* data);
    void cleanHyperBlockC(CCNode* sender, void* data);
    void createMapWithHyperBlock();
    void modefiedLastBonus();
    
    //moveto
    void setControl();
    void afterCleanRunning(cocos2d::CCNode *sender, void *data);
    void releaseAfterRunning(cocos2d::CCNode *sender, void *data);
    void setFalseControl();
    void setTrueControlable(CCNode *sender, void* data);
    void setFalseControlable(CCNode *sender, void* data);
    void deleteMainSprite();
    
    void runningSwap(cocos2d::CCNode *sender, void *data);
    bool swapruning = false;
    void notRunningSwap(cocos2d::CCNode *sender, void *data);
    bool checkAllRunning();
    void refreshMoving();
    bool checkAfterCleanRunning();
    //remove sprite
    void removeSprite(CCNode* sender, void* data);
    bool checkUpdate();
    //checkResetMap
    void checkResetMap();
    //checkB
    bool checkCreateHyperB(CCPoint coor , int type);
    bool checkVerMatch(CCPoint coor , int type);
    bool checkHorMatch(CCPoint coor , int type);
};

#endif