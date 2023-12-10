#include "raylib.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "time.h"

#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22
#define TILE_SIZE 16
#define TETRONIMO_SIZE 4

#define SFX_MOVE 0
#define SFX_ROTATE 1
#define SFX_LAND 2
#define SFX_HARDLAND 3
#define SFX_TETRIS 4
#define SFX_SINGLE 5
#define SFX_LVLUP 6
#define SFX_HOLD 7
#define SFX_LAST 8


extern int stage[];
extern const Color colorTypes[10];
extern const int *tetromino_types[7][4];



#pragma endregion

#pragma region Functions

//Sound relate functions
int TetrisLoadMusic();
int TetrisUnloadMusic();

int TetrisPlaySfx(const int sfx_num);
int TetrisLoopBgMusic();

void MainDeleteEffectTick(const float delta_time);

int CheckDownCollision(
    const int grid_pos_x,
    const int grid_pos_y,
    const int *tetronimo);

int CheckSideCollision(
    const int grid_pos_x,
    const int grid_pos_y,
    const int side_offset,
    const int *tetronimo);

int CheckRotateCollision(
    const int grid_pos_x,
    const int grid_pos_y,
    const int *tetronimo);

int GetLowestPiecePosition(
    const int grid_pos_x,
    const int grid_pos_y,
    const int *tetronimo
);
#pragma endregion
