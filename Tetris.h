#include "raylib.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "time.h"

#define WINDOW_HEIGHT 512
#define WINDOW_WIDTH 512
#define START_POS_Y 1
#define START_MOVE_TILE_DOWN_TIMER 1.f
#define START_MOVE_TIME_HOLD_TIMER .5f
#define MOVE_HOLD_DOWN_DELAY .1f
#define VISIBLE_PIECES 5
#define START_OFFSET_X (WINDOW_WIDTH / 2) - (STAGE_WIDTH / 2 * TILE_SIZE)
#define START_OFFSET_Y (WINDOW_WIDTH / 2) - (STAGE_HEIGHT / 2 * TILE_SIZE)
#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22
#define TILE_SIZE 16
#define TETRONIMO_SIZE 4

#define MUSIC_MENU 0
#define MUSIC_MAIN 1
#define MUSIC_LOST 2
#define MUSIC_LAST 3

#define SFX_MOVE 0
#define SFX_ROTATE 1
#define SFX_LAND 2
#define SFX_HARDLAND 3
#define SFX_TETRIS 4
#define SFX_SINGLE 5
#define SFX_LVLUP 6
#define SFX_HOLD 7
#define SFX_GAME_OVER 8
#define SFX_LAST 9

#define STAGE_DIMENSION 264

#define WALLKICK_0_TO_90 0
#define WALLKICK_90_TO_180 2
#define WALLKICK_180_TO_270 4
#define WALLKICK_270_TO_0 6

#define WALLKICK_90_TO_0 1
#define WALLKICK_180_TO_90 3
#define WALLKICK_270_TO_180 5
#define WALLKICK_0_TO_270 7

#define TETRONIMO_I 6


extern int reset_stage[];
extern int stage[];
extern const int wall_kick_offsets[8][8];
extern const int wall_kick_I_offsets[8][8];
extern const Color colorTypes[10];
extern const int *tetromino_types[7][4];

struct game_loop
{
    void(*begin_play)();
    void(*tick)(const float delta_time);
    void(*draw)();
    void(*post_draw)();
    int play_begin;
};

extern struct game_loop current_game_loop;
typedef struct Tile Tile;

#pragma endregion

#pragma region Functions

//Sound relate functions
int TetrisLoadMusic();
int TetrisUnloadMusic();

int TetrisPlaySfx(const int sfx_num);
int TetrisLoopBgMusic();
int TetrisChangeMusic(const int music);


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

void DrawTextCentral(char* str, int x,  int y, int fonst_size, Color color);
void FormatScore(char* score_array, int score);

void EmptyBegin();
void EmptyTick(const float delta_time);
void EmptyDraw();

void MainMenuBeginPlay();
void MainMenuTick(const float delta_time);
void MainMenuDraw();

void MainDraw();
void MainOverlayDraw();
void MainBeginPlay();
void MainTick(const float delta_time);
void WaitForSpaceTick(const float delta_time);

void EndMenuDraw();
void EndMenuBeginPlay();
void EndMenuTick(const float delta_time);


void EffectBegin();
void EffectTick(const float delta_time);
void EffectDraw();
void SpawnTile(const int x, const int y, const int number, Color color);

int GetXPositionFromCellX(int cell_num);
int GetYPositionFromCellY(int cell_num);

#pragma endregion
