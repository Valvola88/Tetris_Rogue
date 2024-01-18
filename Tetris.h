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
#define START_OFFSET_X 160
#define START_OFFSET_Y 70
#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22
#define TILE_SIZE 16
#define TETRONIMO_SIZE 4
#define REWARD_SIZE 48
#define PIECE_QUEUE_SIZE 10



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


#define GFX_KEY_1 0
#define GFX_KEY_2 1
#define GFX_KEY_3 2
#define GFX_KEY_4 3
#define GFX_KEY_5 4
#define GFX_KEY_Q 5
#define GFX_KEY_W 6
#define GFX_KEY_E 7
#define GFX_KEY_SPACE 8
#define GFX_KEY_A 9
#define GFX_KEY_S 10
#define GFX_KEY_D 11
#define GFX_KEY_LEFT_SHIFT_LT 12
#define GFX_KEY_LEFT_SHIFT_RT 13
#define GFX_KEY_SHIFT 14
#define GFX_KEY_LAST 15

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
#define TETRONIMO_SMALL_I 7
#define TETRONIMO_SMALL_L 8
#define TETRONIMO_SMALL_O 9

#define ENEMY_SIMPLE 0
#define ENEMY_ADVANCED 1
#define ENEMY_BOSS 2
#define ENEMY_LAST 3

#define REWARD_TYPE_POTION 0
#define REWARD_TYPE_ACTIVE_TRINKET 1
#define REWARD_TYPE_PASSIVE_TRINKET 2

#define TRINKET_ACTIVE_FALLER 0
#define TRINKET_ACTIVE_MIRROR 1
#define TRINKET_ACTIVE_SHURIKEN 2
#define TRINKET_ACTIVE_TRASH 3

#define TRINKET_PASSIVE_GLOVE 0
#define TRINKET_PASSIVE_GLASSES 1
#define TRINKET_PASSIVE_TREASURE 2
#define TRINKET_PASSIVE_FLASK 3

#define EFFECT_NORMAL 0
#define EFFECT_COLOR_RANDOM 1
#define EFFECT_RAINBOW 2

#pragma endregion

#pragma region Extern
extern int reset_stage[];
extern int stage[];
extern const int* wall_kick_offsets[8];
extern const int* wall_kick_I_offsets[8];
extern const Color colorTypes[20];
extern const int *tetronimo_types[10][4];

extern Texture2D GfxInputKeys[];
extern Texture2D GfxActiveTrinket[];
extern Texture2D GfxPassiveTrinket[];
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

} Tetromino;

typedef struct Reward{

    char* name; 
    char* tooltip; 

    int type;
    int subtype;

    Texture2D *textrue;

} Reward;

typedef struct ActiveTrinket{

    char* name; 

    int charge;
    int current_charge;

    Texture2D *textrue;

    int (*Activate)();

} ActiveTrinket;

typedef struct PassiveTrinket{

    char* name;

    Texture2D *textrue;

    int utils_value;
    int (*OnPickup)(float utils);

} PassiveTrinket;

#define MAX_POSSIBLE_FRAME_IN_CLIP 8
typedef struct AnimationClip
{
    Texture2D *frames[MAX_POSSIBLE_FRAME_IN_CLIP];
    int max_frames;
    int current_frame;

    float FPS;
    float counter;

    void(*tick)(struct AnimationClip *self, float delta_time);
    Texture2D* (*GetCurrentTexture)(struct AnimationClip *self);
} AnimationClip;

typedef struct Enemy Enemy;

typedef struct Character{

    char* name;
    float damage;
    float life;
    Texture2D mytexture;

} Character;

typedef struct Clickable{

    char * name;
    int x;
    int y;
    int w;
    int h;

    int utils_value;
    float scale_dimension;

    Texture2D* texture;

    int(*Clicked)(int utils);
    void(*Hover)();

} Clickable;

typedef struct Action{

    char* name;
    float weight;
    int timer;
    void(*action)();

}Action;

#define MAX_ACTION_ENEMY 5
typedef struct Enemy{
    
    int enemy_type;
    char* name;
    
    float life;
    float max_life;

    int action_timer;
    int current_action_timer;

    Action *current_action;

    Action *attacks[5];
    int attack_number;

    void(*death)();

    AnimationClip *mytexture;

} Enemy;









extern struct game_loop current_game_loop;
extern Character main_character;
extern Enemy current_enemy;
extern Tetromino mainTetronimo;

extern AnimationClip GfxEnemiesClip[];
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

void DrawTextCentral(const char* str, int x,  int y, int fonst_size, Color color);
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
int DestroyTetronimoEffect(Tetromino *tetronimo);
void ShoutString(char* string, const int x, const int y, const float duration,const int fontSize, const Color color);
void ShoutStringExtra(char* string, const int x, const int y, const float duration,const int fontSize, const Color color, const Vector2 velocity, const float rotation, const int colorEffect);
void TetrisShotLinesDestroyed(const int lines);
int GetFontForContainer(char *string, Vector2 dimensions);

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


void TestWallKickRotateLeft(Tetromino *myTetronimo, const int nextTetronimoRotation);
void TestWallKickRotateRight(Tetromino *myTetronimo, const int nextTetronimoRotation);


#pragma region Draw Function
void TetrisTileDraw(Tile *self);
void TetrisDrawPowerUp(const int pu,const int x,const int y, float scale);
void DrawTetrominoOnWhiteCentered(const int up_left_x, const int up_left_y, int tetromino_shape);
void DrawTetrominoContainer(const int up_left_x, const int up_left_y, int tetromino_shape, const char* label);
void DrawTetromino2(Tetromino *tetronimo);

void DrawTetromino(
    const int tile_x,
    const int tile_y,
    const int *tetronimo,
    const Color c);

void DrawTetrominoAbsolute(
    const int start_x,
    const int start_y,
    const int *tetronimo,
    const Color c);
#pragma endregion


void SetTetronimoRotation(Tetromino *tetro, const int rotation);
int SetTetronimoShape(Tetromino *tetro, const int shape);
void SpawnNewTetronimo(Tetromino *tetro, const int shape);
void PrintTetronimo(Tetromino *t);


//ATTACK TYPE
void CreateBlockUnder(int *position, const int number_of_empty_block);
void TransformQueuedPieces(const int amount, const int shape);


//TRINKET ACTIVE
int MirrorMainTetronimo();
int FallTetronimo();
int DestroyTetronimo();
int RogueAttack();
int DealNonLethalDamage();

//TRINKET PASSIVE ON PICKUP
int AddPlayerDamage(float damage);
int AddPlayerVisibleReward(float _);
int AddPlayerPotionSlot(float _);
int AddPlayerVisibleTetromino(float _);

int TetrisSetTextureClickable(Clickable *click, Texture2D *texture);
int TetrisDrawClickable(Clickable *self);
int TetrisIsMouseInside(Clickable *self);
int TetrisClick(Clickable* self);


//ENEMIES AND ATTACK
void InitEnemies();
void ChangeRandomActionEnemy(Enemy *e);
void HealEnemy(float damage);
#pragma endregion

#endif