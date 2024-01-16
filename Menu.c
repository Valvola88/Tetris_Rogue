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
    if (IsKeyPressed(KEY_A))
    {
        Vector2 v = {
            GetRandomValue(-20,20),
            GetRandomValue(-20,20)
            };
        ShoutStringExtra("HELLO!", 512/2, 512/2,2, 40, YELLOW, v,GetRandomValue(-20,20), EFFECT_COLOR_RANDOM);
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        current_game_loop.begin_play = MainBeginPlay;
    }


}

void MainMenuDraw()
{
    DrawTextCentral("TETRIS", 256, 64, 100, WHITE);
    DrawTextCentral("Press SPACE to rogue", 256, 160, 32, WHITE);
    
    Vector2 position;
    position.x = 100;
    position.y = 230;
    DrawTextureEx(GfxInputKeys[GFX_KEY_W], position, 0, 3, WHITE);
    position.x -= 28;
    position.y += 50;
    DrawTextureEx(GfxInputKeys[GFX_KEY_A], position, 0, 3, WHITE);
    position.x+= 50;
    DrawTextureEx(GfxInputKeys[GFX_KEY_S], position, 0, 3, WHITE);
    position.x+= 50;
    DrawTextureEx(GfxInputKeys[GFX_KEY_D], position, 0, 3, WHITE);
    DrawTextCentral("Move", position.x - 50 + 24, position.y + 52, 30, WHITE);

    position.x = 64;
    position.y += 100;
    DrawTextureEx(GfxInputKeys[GFX_KEY_1], position, 0, 3, WHITE);
    position.x+= 50;
    DrawTextureEx(GfxInputKeys[GFX_KEY_2], position, 0, 3, WHITE);
    position.x+= 50;
    DrawTextureEx(GfxInputKeys[GFX_KEY_3], position, 0, 3, WHITE);
    DrawTextCentral("Use Potion", position.x - 50 + 24, position.y + 52, 30, WHITE);


    position.x = 300;
    position.y = 210;
    DrawTextureEx(GfxInputKeys[GFX_KEY_Q], position, 0, 3, WHITE);
    position.x += 50;
    DrawTextureEx(GfxInputKeys[GFX_KEY_E], position, 0, 3, WHITE);
    DrawTextCentral("Rotate", position.x, position.y + 52, 30, WHITE);

    position.y += 92;
    position.x -= 25;
    DrawTextureEx(GfxInputKeys[GFX_KEY_SPACE], position, 0, 3, WHITE);
    DrawTextCentral("Store", position.x + 24, position.y + 52, 30, WHITE);

    position.y += 92;
    position.x -= 25;
    DrawTextureEx(GfxInputKeys[GFX_KEY_LEFT_SHIFT_LT], position, 0, 3, WHITE);
    position.x += 48;
    DrawTextureEx(GfxInputKeys[GFX_KEY_LEFT_SHIFT_RT], position, 0, 3, WHITE);
    DrawTextCentral("Activate", position.x, position.y + 52, 30, WHITE);


    if (max_score)
    {
        DrawTextCentral((char *)TextFormat("Max Score: %d", max_score), 256,20,40,WHITE);
    }

    DrawRectangle(256,256,2,2,BLUE);
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
