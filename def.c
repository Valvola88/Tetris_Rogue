#include "Tetris.h"

#pragma region Initial Values
int reset_stage[] = 
{
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19,
    19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
};

#pragma region WallKiks
const int wk_0[8] = {-1, +0, -1, +1, +0, -2, -1, +2};
const int wk_1[8] = {+1, +0, +1, -1, +0, +2, +1, +2};
const int wk_2[8] = {+1, +0, +1, -1, +0, +2, +1, +2};
const int wk_3[8] = {-1, +0, -1, +1, +0, -2, -1, -2};
const int wk_4[8] = {+1, +0, +1, +1, +0, -2, +1, -2};
const int wk_5[8] = {-1, +0, -1, -1, +0, +2, -1, +2};
const int wk_6[8] = {-1, +0, -1, -1, +0, +2, -1, +2};
const int wk_7[8] = {+1, +0, +1, +1, +0, -2, +1, -2};

const int *wall_kick_offsets[8] =
{
    wk_0,
    wk_1,
    wk_2,
    wk_3,
    wk_4,
    wk_5,
    wk_6,
    wk_7
};

const int wki_0[8] = {-2,   0, +1, +0, -2, -1, +1, +2};
const int wki_1[8] = { 2,  0, -1,  0,  2,  1, -1, -2};
const int wki_2[8] = {-1,  0,  2,  0,  2,  1, -1, -2};
const int wki_3[8] = { 1,  0, -2,  0, -1,  2,  2, -1};
const int wki_4[8] = { 2,  0, -1,  0,  2,  1, -1, -2};
const int wki_5[8] = {-2,  0,  1,  0, -2, -1,  1,  2};
const int wki_6[8] = { 1,  0, -2,  0,  1, -2, -2,  1};
const int wki_7[8] = {-1,  0,  2,  0, -1,  2,  2, -1};

const int *wall_kick_I_offsets[8] =
{
    wki_0,
    wki_1,
    wki_2,
    wki_3,
    wki_4,
    wki_5,
    wki_6,
    wki_7
};

#pragma endregion

const Color colorTypes[20] =
{
    {0,0,0,0}, //0
    {255,161,0,255}, //1
    {0,121,241,255}, //2
    {0,158,47,255}, //3
    {230,41,55,255}, //4
    {235,249,0,255}, //5
    {200,122,255,255}, //6
    {102,199,255,255}, //7
    {42,255,0,255}, //8
    {255,0,203,255}, //9
    {142,94,48,255}, //10
    {64,64,64,255}, //11
    {255,255,255,255}, //12
    {255,255,255,255},
    {255,255,255,255},
    {255,255,255,255},
    {255,255,255,255},
    {255,255,255,255},
    {200,200,200,200},
    {255,255,255,255},
};

#pragma region //L PIECE
const int tetronimo_L_0 [] =
{
      0,  0,
     -1,  0,
      1,  0,
      1, -1
};
const int tetronimo_L_90 [] =
{
     0,  0,
     0, -1,
     0,  1,
     1,  1
};
const int tetronimo_L_180 [] =
{
     0,  0,
     1,  0,
    -1,  0,
    -1,  1
};
const int tetronimo_L_270 [] =
{
     0,   0,
     0,   1,
     0,  -1,
    -1,  -1
};
#pragma endregion

#pragma region //J PIECE
int tetronimo_J_0 [] =
{
      0,  0,
     -1,  0,
      1,  0,
     -1, -1
};
int tetronimo_J_90 [] =
{
     0,   0,
     0,   1,
     0,  -1,
     1,  -1
};
int tetronimo_J_180 [] =
{
     0,  0,
     1,  0,
    -1,  0,
     1,  1
};
int tetronimo_J_270 [] =
{
      0,  0,
      0, -1,
      0,  1,
     -1,  1
};
#pragma endregion

#pragma region //S PIECE
int tetronimo_S_0 [] =
{
      0,  0,
      0, -1,
      1,  -1,
      -1,  0
};
int tetronimo_S_90 [] =
{
      0,  0,
      1,  0,
      1,  1,
     0,  -1
};
int tetronimo_S_180 [] =
{
      0,  0,
      0,  1,
      -1,  1,
      1,  0
};
int tetronimo_S_270 [] =
{
      0,  0,
      -1,  0,
      -1,  -1,
      0,  1
};
#pragma endregion

#pragma region //Z PIECE
int tetronimo_Z_0 [] =
{
      0,  0,
      0, -1,
      -1,  -1,
      1,  0
};
int tetronimo_Z_90 [] =
{
      0,  0,
      1,  0,
      1,  -1,
      0,  1
};
int tetronimo_Z_180 [] =
{
      0,  0,
      0,  1,
      1,  1,
      -1,  0
};
int tetronimo_Z_270 [] =
{
      0,  0,
     -1,  0,
      -1,  1,
     0,  -1
};
#pragma endregion

#pragma region //O PIECE
int tetronimo_O_0 [] =
{
    0, 0,
    0, -1,
    -1, 0,
    -1, -1
};
int tetronimo_O_90 [] =
{
    0, 0,
    0, -1,
    -1, 0,
    -1, -1
};
int tetronimo_O_180 [] =
{
    0, 0,
    0, -1,
    -1, 0,
    -1, -1
};
int tetronimo_O_270 [] =
{
    0, 0,
    0, -1,
    -1, 0,
    -1, -1
};
#pragma endregion

#pragma region //T PIECE
int tetronimo_T_0 [] =
{
    0,  0,
    -1, 0,
    0,  -1,
    1,  0
};
int tetronimo_T_90 [] =
{
    0,  0,
    0, -1,
    1,  0,
    0,  1
};
int tetronimo_T_180 [] =
{
    0,  0,
    -1, 0,
    0,  1,
    1,  0
};
int tetronimo_T_270 [] =
{
    0,  0,
    0, -1,
    -1,  0,
    0,  1
};
#pragma endregion

#pragma region //I PIECE
int tetronimo_I_0 [] =
{
    -1,  -1,
    0,  -1,
    1,  -1,
    2,  -1
};
int tetronimo_I_90 [] =
{
    1, -2,
    1, -1,
    1,  0,
    1,  1
};
int tetronimo_I_180 [] =
{
    -1, 0,
    0,  0,
    1,  0,
    2,  0
};
int tetronimo_I_270 [] =
{
    0, -2,
    0, -1,
    0,  0,
    0,  1
};
#pragma endregion

#pragma region //I PIECE
int tetronimo_SMALL_I_0 [] =
{
    0,  0,
    0,  0,
    0,  0,
    0,  -1
};
int tetronimo_SMALL_I_90 [] =
{
    0,  0,
    0,  0,
    0,  0,
    1,  0
};
int tetronimo_SMALL_I_180 [] =
{
    0,  0,
    0,  0,
    0,  0,
    0,  1
};
int tetronimo_SMALL_I_270 [] =
{
    0,  0,
    0,  0,
    0,  0,
    -1,  0
};
#pragma endregion

#pragma region //I PIECE
int tetronimo_SMALL_L_0 [] =
{
    0,  0,
    0,  0,
    -1,  0,
    0,  -1
};
int tetronimo_SMALL_L_90 [] =
{
    0, 0,
    0, 0,
    0,  -1,
    1,  0
};
int tetronimo_SMALL_L_180 [] =
{
    0, 0,
    0,  0,
    1,  0,
    0,  1
};
int tetronimo_SMALL_L_270 [] =
{
    0,  0,
    0,  0,
    0,  1,
    -1,  0
};
#pragma endregion

#pragma region //I PIECE
int tetronimo_SMALL_O [] =
{
    0, 0,
    0, 0,
    0, 0,
    0, 0,
};
#pragma endregion


const int *tetronimo_types[10][4] =
{
    {tetronimo_L_0, tetronimo_L_90, tetronimo_L_180, tetronimo_L_270},
    {tetronimo_J_0, tetronimo_J_90, tetronimo_J_180, tetronimo_J_270},
    {tetronimo_S_0, tetronimo_S_90, tetronimo_S_180, tetronimo_S_270},
    {tetronimo_Z_0, tetronimo_Z_90, tetronimo_Z_180, tetronimo_Z_270},
    {tetronimo_O_0, tetronimo_O_90, tetronimo_O_180, tetronimo_O_270},
    {tetronimo_T_0, tetronimo_T_90, tetronimo_T_180, tetronimo_T_270},
    {tetronimo_I_0, tetronimo_I_90, tetronimo_I_180, tetronimo_I_270},

    //EXTRA SPECAIAL PIECES
    {tetronimo_SMALL_I_0, tetronimo_SMALL_I_90, tetronimo_SMALL_I_180, tetronimo_SMALL_I_270},
    {tetronimo_SMALL_L_0, tetronimo_SMALL_L_90, tetronimo_SMALL_L_180, tetronimo_SMALL_L_270},
    {tetronimo_SMALL_O, tetronimo_SMALL_O, tetronimo_SMALL_O, tetronimo_SMALL_O},

};



// typedef struct Reward{

//     char* name; 
//     char* tooltip; 

//     int type;
//     int subtype;

// } Reward;

extern Texture2D GfxPotions[];
const Reward REWARDS[]= 
{
    {"POTION L", "\nCHANGE YOUR TETRONIMO INTO L SHAPE", REWARD_TYPE_POTION, TETRONIMO_L, &GfxPotions[TETRONIMO_L]},
    {"POTION J", "\nCHANGE YOUR TETRONIMO INTO J SHAPE", REWARD_TYPE_POTION, TETRONIMO_J, &GfxPotions[TETRONIMO_J]},
    {"POTION S", "\nCHANGE YOUR TETRONIMO INTO S SHAPE", REWARD_TYPE_POTION, TETRONIMO_S, &GfxPotions[TETRONIMO_S]},
    {"POTION Z", "\nCHANGE YOUR TETRONIMO INTO Z SHAPE", REWARD_TYPE_POTION, TETRONIMO_Z, &GfxPotions[TETRONIMO_Z]},
    {"POTION T", "\nCHANGE YOUR TETRONIMO INTO T SHAPE", REWARD_TYPE_POTION, TETRONIMO_T, &GfxPotions[TETRONIMO_T]},
    {"POTION O", "\nCHANGE YOUR TETRONIMO INTO O SHAPE", REWARD_TYPE_POTION, TETRONIMO_O, &GfxPotions[TETRONIMO_O]},
    {"POTION I", "\nCHANGE YOUR TETRONIMO INTO I SHAPE", REWARD_TYPE_POTION, TETRONIMO_I, &GfxPotions[TETRONIMO_I]},
    {"POTION HALF I", "\nCHANGE INTO HALF I SHAPE", REWARD_TYPE_POTION, TETRONIMO_SMALL_I, &GfxPotions[TETRONIMO_SMALL_I]},
    {"POTION SMALL L", "\nCHANGE INTO SMALL L SHAPE", REWARD_TYPE_POTION, TETRONIMO_SMALL_L, &GfxPotions[TETRONIMO_SMALL_L]},
    {"POTION MINI O", "\nCHANGE INTO MINI O SHAPE", REWARD_TYPE_POTION, TETRONIMO_SMALL_O, &GfxPotions[TETRONIMO_SMALL_O]},
    //9 ↑
    //10 ↓
    {"FALLER", "\nCOLLAPSE YOUR TETRONIMO\nCHARGE 4", REWARD_TYPE_ACTIVE_TRINKET, TRINKET_ACTIVE_FALLER, &GfxActiveTrinket[TRINKET_ACTIVE_FALLER]},
    {"MIRROR", "\nMIRRORS YOUR TETRONIMO\nCHARGE 2", REWARD_TYPE_ACTIVE_TRINKET, TRINKET_ACTIVE_MIRROR, &GfxActiveTrinket[TRINKET_ACTIVE_MIRROR]},
    {"SHURIKEN", "\nDEAL DAMAGE TO ENEMY\nCHARGE 6", REWARD_TYPE_ACTIVE_TRINKET, TRINKET_ACTIVE_SHURIKEN, &GfxActiveTrinket[TRINKET_ACTIVE_SHURIKEN]},
    {"TRASH CAN", "\nDESTROY YOUR CURRENT TETRONIMO\n CHARGE 3", REWARD_TYPE_ACTIVE_TRINKET, TRINKET_ACTIVE_TRASH, &GfxActiveTrinket[TRINKET_ACTIVE_TRASH]},
    //14 ↓
    {"TOUGH GLOVE", "\nUPGRADES YOUR DAMAGE", REWARD_TYPE_PASSIVE_TRINKET, TRINKET_PASSIVE_GLOVE, &GfxPassiveTrinket[TRINKET_PASSIVE_GLOVE]},
    {"GLASSES", "\nSHOW AN EXTRA TETROMINO (MAX 5)", REWARD_TYPE_PASSIVE_TRINKET, TRINKET_PASSIVE_GLASSES, &GfxPassiveTrinket[TRINKET_PASSIVE_GLASSES]},
    {"TREASURE", "\nSHOW AN EXTRA REWARD (MAX 5)", REWARD_TYPE_PASSIVE_TRINKET, TRINKET_PASSIVE_TREASURE, &GfxPassiveTrinket[TRINKET_PASSIVE_TREASURE]},

};

// typedef struct Trinket{

//     char* name; 

//     int charge;
//     int current_charge;

//     Texture2D *textrue;

// } Trinket;

const ActiveTrinket TemplateActiveTrinkets[]=
{
    {"FALLER", 4, 4, &GfxActiveTrinket[0], FallTetronimo},
    {"MIRROR", 2, 2, &GfxActiveTrinket[1], MirrorMainTetronimo},
    {"SHURIKEN", 6, 6, &GfxActiveTrinket[2], RogueAttack},
    {"TRASH", 3, 3, &GfxActiveTrinket[3], DestroyTetronimo},
};

// typedef struct PassiveTrinket{

//     char* name;

//     Texture2D *textrue;
//     int utils_value;
//     int (*OnPickup)(int utils);

// } PassiveTrinket;
const PassiveTrinket TemplatePassiveTrinkets[] =
{
    {"TOUGH GLOVE", &GfxPassiveTrinket[0], 5, AddPlayerDamage},
    {"GLASSES", &GfxPassiveTrinket[1], 0, AddPlayerVisibleTetromino},
    {"TREASURE", &GfxPassiveTrinket[2], 0, AddPlayerVisibleReward},
};

const int EnemiesHealth[ENEMY_LAST] =
{
    1,
    15,
    30
};

const int EnemiesTimer[ENEMY_LAST] =
{
    5,
    4,
    6
};