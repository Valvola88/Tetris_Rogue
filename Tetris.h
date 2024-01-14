#ifndef _TETRIS_H
#define _TETRIS_H

#include "raylib.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "time.h"

#pragma region Defines

#define WINDOW_HEIGHT 512
#define WINDOW_WIDTH 512
#define START_POS_Y 1
#define START_MOVE_TILE_DOWN_TIMER 1.f
#define START_MOVE_TIME_HOLD_TIMER .5f
#define MOVE_HOLD_DOWN_DELAY .1f
#define VISIBLE_PIECES 5
#define START_OFFSET_X WINDOW_WIDTH / 2 - STAGE_WIDTH / 2 * TILE_SIZE
#define START_OFFSET_Y WINDOW_WIDTH / 2 - STAGE_HEIGHT / 2 * TILE_SIZE
#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22
#define TILE_SIZE 16
#define TETRONIMO_SIZE 4
#define REWARD_SIZE 48

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
#define SFX_ERROR 9
#define SFX_LAST 10

#define STAGE_DIMENSION 264

#define WALLKICK_0_TO_90 0
#define WALLKICK_90_TO_180 2
#define WALLKICK_180_TO_270 4
#define WALLKICK_270_TO_0 6

#define WALLKICK_90_TO_0 1
#define WALLKICK_180_TO_90 3
#define WALLKICK_270_TO_180 5
#define WALLKICK_0_TO_270 7

#define TETRONIMO_L 0
#define TETRONIMO_J 1
#define TETRONIMO_S 2
#define TETRONIMO_Z 3
#define TETRONIMO_O 4
#define TETRONIMO_T 5
#define TETRONIMO_I 6

#define ENEMY_SIMPLE 0
#define ENEMY_ADVANCED 1
#define ENEMY_BOSS 2
#define ENEMY_LAST 3

#define REWARD_TYPE_POTION 0
#define REWARD_TYPE_TRINKET 1

#define TRINKET_FALLER 0
#define TRINKET_MIRROR 1
#define TRINKET_GLASSES 2

#pragma endregion

#pragma region Extern
extern int reset_stage[];
extern int stage[];
extern const int* wall_kick_offsets[8];
extern const int* wall_kick_I_offsets[8];
extern const Color colorTypes[20];
extern const int *tetronimo_types[7][4];
#pragma endregion

#pragma region Struct

struct game_loop
{
    void(*begin_play)();
    void(*tick)(const float delta_time);
    void(*draw)();
    void(*post_draw)();
    int play_begin;
};

typedef struct Tile
{
    Color my_color;
    int index;
    int x;
    int y;
    void (*tick)(struct Tile *self, const float delta_time);
    void (*draw)(struct Tile *self);
    int velocity_x;
    int velocity_y;

    int isActive;

} Tile;

typedef struct Str_Tetronimo{
    int x;
    int y;
    int shape;
    int rotation;

    int *current_shape;

    Color color;
    int powerUpTile;

} Tetronimo;

typedef struct Reward{

    char* name; 
    char* tooltip; 

    int type;
    int subtype;

    Texture2D *textrue;

} Reward;

typedef struct Trinket{

    char* name; 

    int charge;
    int current_charge;

    Texture2D *textrue;

    int (*Activate)();

} Trinket;

typedef struct Enemy{
    
    int enemy_type;

    int life;
    int action_timer;

    void(*attack)();
    Texture2D mytexture;

} Enemy;

typedef struct Character{

    char* name;
    int damage;
    int life;
    Texture2D mytexture;

} Character;

typedef struct Clickable{

    char * name;
    int x;
    int y;
    int w;
    int h;

    int utils_value;

    Texture2D* texture;

    int(*Clicked)(int utils);
    void(*Hover)();

} Clickable;

extern struct game_loop current_game_loop;
extern Character main_character;
extern Enemy current_enemy;
extern Tetronimo mainTetronimo;

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


void FormatScore(char* score_array, int score);


void EndMenuDraw();
void EndMenuBeginPlay();
void EndMenuTick(const float delta_time);

void EffectBegin();
void EffectTick(const float delta_time);
void EffectDraw();
int DestroyTetronimoEffect(Tetronimo *tetronimo);


void RogueBegin();
void RoguePiecePlaced();
void RogueInputTick(const float delta_time);
void RogueDraw();
void RogueLineScored();
void RogueTetrisScored();
void RogueRewardTick(const float delta_time);
void RogueRewardDraw();
void RogueRewardBegin();

void SpawnTile(const int x, const int y, const int number, Color color);

int GetXPositionFromCellX(int cell_num);
int GetYPositionFromCellY(int cell_num);

int TetrisLoadImages();
int TetrisLoadTexture(Texture2D *texture, char* path, float scale);
int TetrisUnloadImages();

void TetrisDrawPowerUp(const int pu,const int x,const int y);

void TestWallKickRotateLeft(Tetronimo *myTetronimo, const int nextTetronimoRotation);
void TestWallKickRotateRight(Tetronimo *myTetronimo, const int nextTetronimoRotation);

void TetrisTileDraw(Tile *self);

void DrawTetromino2(Tetronimo *tetronimo);
void DrawTetromino(
    const int start_x,
    const int start_y,
    const int *tetronimo,
    const Color c);

void SetTetronimoRotation(Tetronimo *tetro, const int rotation);
int SetTetronimoShape(Tetronimo *tetro, const int shape);
void SpawnNewTetronimo(Tetronimo *tetro, const int shape);
int CreateBlockUnder(int position);
void PrintTetronimo(Tetronimo *t);

int MirrorMainTetronimo();
int FallTetronimo();

int TetrisSetTextureClickable(Clickable *click, Texture2D *texture);
int TetrisDrawClickable(Clickable *self);
int TetrisIsMouseInside(Clickable *self);
int TetrisClick(Clickable* self);

#pragma endregion

#endif