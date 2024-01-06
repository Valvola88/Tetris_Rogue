#include "Tetris.h"

extern char* str_score;
extern int score;
extern char* str_max_score;
extern int max_score;

void MainMenuBeginPlay()
{
    current_game_loop.tick = MainMenuTick;
    current_game_loop.draw = MainMenuDraw;
    current_game_loop.post_draw = EmptyDraw;
    
    TetrisChangeMusic(MUSIC_MENU);
    
    current_game_loop.begin_play = EmptyBegin;

}

void MainMenuTick(const float delta_time)
{
    if (IsKeyPressed(KEY_D))
    {
        SpawnTile(250,250,0,RED);
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        current_game_loop.begin_play = MainBeginPlay;
    }
}

void MainMenuDraw()
{
    DrawTextCentral("TETRIS", 256, 100, 100, WHITE);
    DrawTextCentral("Press SPACE to rogue", 256, 200, 32, WHITE);
    
    if (max_score)
    {
        DrawTextCentral((char *)TextFormat("Max Score: %d", max_score), 256,300,40,WHITE);
    }
}

void EndMenuBeginPlay()
{

}

void EndMenuTick(const float delta_time)
{

}

void EndMenuDraw()
{

}
