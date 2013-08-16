//
//  TPDefinition.h
//  Cocos2Dx
//
//  Created by Nguyen The Vinh on 8/2/13.
//
//

#ifndef Cocos2Dx_TPDefinition_h
#define Cocos2Dx_TPDefinition_h

#define FONT_SIZE 30
// Combo and timer system
#define HBC_COMBO_MAXCOUNT 8
#define HBC_COMBO_MAXTIME 5

#define FEVER_COMBO_REQUIRED 5
#define FEVER_TIME_REQUIRED 3

#define GAUGE_COMBO_REQUIRED 10

#define COMBO_REQUIRED 50

// time and delay system
#define HINT_TIME 5
#define FALL_TIME 0.1
#define MOVE_TIME 0.05
#define SWAP_TIME 0.08

#define GENERATION_DELAY 0.05
#define CLEAN_DELAY 0.1
#define LOGIC_DELAY 0.7 // afterCleanspeed * 6 + generateSpeed *6 + scaleTime + swapTime*2
#define MOVE_DELAY 0.08

#define AFTER_CLEAN_FALL_TIME 0.05
#define GENERATE_FALL_TIME 0.05
#define POP_ANIMATION_DELAY 0.04

#define HBC_SCALE_DELAY 0.2

#define PLAY_TIME 600
#define GAUGE_PERIOD 2 // after this period, if no more combo is created, minus gauge combo by 1
// score system
#define SCORE_THREE  200
#define SCORE_FOUR  200
#define SCORE_FIVE 600
#define ONE_BLOCK 100

//Item System
#define DOUBLE_SCORE_TIME 20
#define MISSION_BLOCK2_MAX_AMOUNT 10

#define SPECIAL_ITEM_1_ID 1 // MISSION BLOCK 1 - ITEM 4
#define SPECIAL_ITEM_2_ID 2 // MISSION BLOCK 2 - ITEM 5
#define SPECIAL_ITEM_3_ID 3
#define SPECIAL_ITEM_4_ID 4 // MISSION BLOCK 3
#define SPECIAL_ITEM_5_ID 5

#define SWIPE_DISTANCE 15 //In pixels
// Block Type System
#define NORMAL_BLOCK_TYPE 0
#define HBA_BLOCK_TYPE 1
#define HBB_BLOCK_TYPE 2
#define HBC_BLOCK_TYPE 3
#define MB1_BLOCK_TYPE 6
#define MB2_BLOCK_TYPE 7
#define MB3_BLOCK_TYPE 8
#define MOVED_NORMAL_BLOCK_TYPE 10
#define MOVED_HBA_BLOCK_TYPE 11
#define MOVED_HBB_BLOCK_TYPE 12


USING_NS_CC;

#endif
