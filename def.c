#include "Tetris.h"

#pragma region Initial Values
int reset_stage[] = 
{
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
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
    {0,0,0,0},
    {255,161,0,255},
    {0,121,241,255},
    {0,158,47,255},
    {230,41,55,255},
    {235,249,0,255},
    {200,122,255,255},
    {102,199,255,255},
    {200,200,200,200},
    {255,255,255,255},
    {0,0,0,255},
    {64,64,64,255},
    {255,255,255,255},
    {255,255,255,255},
    {255,255,255,255},
    {255,255,255,255},
    {255,255,255,255},
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


const int *tetromino_types[7][4] =
{
    {tetronimo_L_0, tetronimo_L_90, tetronimo_L_180, tetronimo_L_270},
    {tetronimo_J_0, tetronimo_J_90, tetronimo_J_180, tetronimo_J_270},
    {tetronimo_S_0, tetronimo_S_90, tetronimo_S_180, tetronimo_S_270},
    {tetronimo_Z_0, tetronimo_Z_90, tetronimo_Z_180, tetronimo_Z_270},
    {tetronimo_O_0, tetronimo_O_90, tetronimo_O_180, tetronimo_O_270},
    {tetronimo_T_0, tetronimo_T_90, tetronimo_T_180, tetronimo_T_270},
    {tetronimo_I_0, tetronimo_I_90, tetronimo_I_180, tetronimo_I_270}
};


// typedef struct Enemy{
    
//     float life;
//     int enemy_type;
//     int action_timer;
//     void(*attack)();
//     Texture2D mytexture;

// } Enemy;

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