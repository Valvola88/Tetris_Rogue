#include "Tetris.h"

#pragma region Initial Values
int stage[] = 
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

const Color colorTypes[10] =
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
    {255,255,255,255}
};

#pragma region //L PIECE
const int tetronimo_L_0 [] =
{
     0,  0,
     0, -1,
     0,  1,
     1,  1
};
const int tetronimo_L_90 [] =
{
     0,  0,
     1,  0,
    -1,  0,
    -1,  1
};
const int tetronimo_L_180 [] =
{
     0,   0,
     0,   1,
     0,  -1,
    -1,  -1
};
const int tetronimo_L_270 [] =
{
      0,  0,
     -1,  0,
      1,  0,
      1, -1
};
#pragma endregion

#pragma region //J PIECE
int tetronimo_J_0 [] =
{
      0,  0,
      0, -1,
      0,  1,
     -1,  1
};
int tetronimo_J_90 [] =
{
     0,  0,
     1,  0,
    -1,  0,
     1,  1
};
int tetronimo_J_180 [] =
{
     0,   0,
     0,   1,
     0,  -1,
     1,  -1
};
int tetronimo_J_270 [] =
{
      0,  0,
     -1,  0,
      1,  0,
     -1, -1
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
     -1,  0,
      -1,  1,
     0,  -1
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
      1,  0,
      1,  -1,
      0,  1
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
    0, -1,
    1,  0,
    0,  1
};
int tetronimo_T_90 [] =
{
    0,  0,
    -1, 0,
    0,  -1,
    1,  0
};
int tetronimo_T_180 [] =
{
    0,  0,
    0, -1,
    -1,  0,
    0,  1
};
int tetronimo_T_270 [] =
{
    0,  0,
    -1, 0,
    0,  1,
    1,  0
};
#pragma endregion

#pragma region //I PIECE
int tetronimo_I_0 [] =
{
    0,  0,
    0, -1,
    0,  1,
    0,  2
};
int tetronimo_I_90 [] =
{
    0,  0,
    -1, 0,
     1, 0,
     2,  0
};
int tetronimo_I_180 [] =
{
    0,  0,
    0, -1,
    0,  1,
    0,  2
};
int tetronimo_I_270 [] =
{
    0,  0,
    -1, 0,
     1, 0,
     2,  0
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