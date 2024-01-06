#include "Tetris.h"

int potions[5] = {6,-1,-1, -1, -1};
Reward rewards[4];

Character main_character;
Enemy current_enemy;
Clickable visible_rewards[3];

int visible_potions = 3;

extern Texture2D PowerUps[];
extern int EnemiesHealth[];
extern int EnemiesTimer[];

extern int showRewardBox;

int green_rect;

void SetEnemy(int enemy_type)
{
    current_enemy.enemy_type = enemy_type;

    main_character.damage = 1;

    current_enemy.life = EnemiesHealth[enemy_type];
    current_enemy.action_timer = EnemiesTimer[enemy_type];
}

void RogueBegin()
{
    TetrisLoadTexture(&(main_character.mytexture), "resources/texture/character.png", 2);
    TetrisLoadTexture(&(current_enemy.mytexture), "resources/texture/enemy.png", 2);

    green_rect = 100;
    SetEnemy(ENEMY_SIMPLE);
}

void UsePotion(int potion_number)
{
    if (potion_number >= visible_potions)
        return;

    if (potions[potion_number] < 0)
        return;


    if(!CheckRotateCollision(mainTetronimo.x, mainTetronimo.y, tetromino_types[potions[potion_number]][mainTetronimo.rotation]))
    {
        DestroyTetronimoEffect(&mainTetronimo);
        SetTetronimoShape(&mainTetronimo, potions[potion_number]);
        TetrisPlaySfx(SFX_LVLUP);
        potions[potion_number] = -1;
    }
    else
    {
        TetrisPlaySfx(SFX_ERROR);
    }
}

void RoguePiecePlaced()
{
    current_enemy.action_timer--;

    if (current_enemy.action_timer == 0)
    {   
        CreateBlockUnder(GetRandomValue(1,11));

        current_enemy.action_timer = 5;
    }
}

void RogueLineScored()
{
    //printf("Attack");
    current_enemy.life -= main_character.damage;
    float percent = ((float)(current_enemy.life) / (float)(EnemiesHealth[current_enemy.enemy_type]));
    green_rect = 100 * percent;

    if (current_enemy.life <= 0)
    {
        showRewardBox = 1;
    }
}

void RogueTetrisScored()
{

}

void RogueInputTick(const float delta_time)
{
    if (IsKeyPressed(KEY_ONE))
    {
        UsePotion(0);
    }
    if (IsKeyPressed(KEY_TWO))
    {
        UsePotion(1);
    }
        if (IsKeyPressed(KEY_THREE))
    {
        UsePotion(2);
    }
        if (IsKeyPressed(KEY_FOUR))
    {
        UsePotion(3);
    }
        if (IsKeyPressed(KEY_FIVE))
    {
        UsePotion(4);
    }
}

void RogueDraw()
{
    for(int i = 0; i< visible_potions; i++)
    {
        if (potions[i] > -1)
        {
            TetrisDrawPowerUp(potions[i],16 + ((48 + 2) * i ),450);
        }
    }

    DrawTexture(main_character.mytexture, 16,16, WHITE);
    DrawTexture(current_enemy.mytexture, 400,16, WHITE);

    DrawText(TextFormat("%i", current_enemy.action_timer), 360,24,32,WHITE);
    //DrawText(TextFormat("%f", current_enemy.life), 380, 78,16,WHITE);

    DrawRectangle(372,68,104,14,BLACK);
    DrawRectangle(374,70,green_rect,10,GREEN);
}

void RogueRewardDraw()
{
    DrawRectangle(64,64,384, 150, WHITE);

    DrawTextCentral(rewards[0].name, 132,140,10,BLACK);
    TetrisDrawClickable(&visible_rewards[0]);
    // TetrisDrawPowerUp(rewards[0].subtype, 100,150);
    // DrawTextCentral(rewards[1].name, 232,140,10,BLACK);
    // TetrisDrawPowerUp(rewards[1].subtype, 200,150);
    // DrawTextCentral(rewards[2].name, 332,140,10,BLACK);
    // TetrisDrawPowerUp(rewards[2].subtype, 300,150);
}

void RogueRewardTick(const float delta_time)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        int valid_click = 0;
        for(int i = 0; i < 1;i++)
        {
            {
                valid_click = valid_click + TetrisClick(&visible_rewards[i]);
            }
        }

        if (valid_click)
        {
            current_game_loop.post_draw = EmptyDraw;
            current_game_loop.tick = MainTick;
        }
    } 
}

int AddPotion(int potion_number){

    for(int i = 0; i< visible_potions; i++)
    {
        if (potions[i] > -1)
            continue;

        potions[i] = potion_number;
        break;
    }
    return 0;
}

void RogueRewardBegin()
{
    showRewardBox  = 0;
    current_game_loop.tick = RogueRewardTick;
    current_game_loop.post_draw = RogueRewardDraw;
    current_game_loop.begin_play = EmptyBegin;

    rewards[0].name = "I Potion";
    rewards[0].type = REWARD_TYPE_POTION;
    rewards[0].subtype = TETRONIMO_I;
    
    TetrisSetTextureClickable(&visible_rewards[0], &PowerUps[TETRONIMO_I]);
    visible_rewards[0].x = 100;
    visible_rewards[0].y = 150;
    visible_rewards[0].Clicked = AddPotion;
    visible_rewards[0].utils_value = TETRONIMO_I;
    // rewards[1].name = "J Potion";
    // rewards[1].type = REWARD_TYPE_POTION;
    // rewards[1].subtype = TETRONIMO_J;

    // rewards[2].name = "T Potion";
    // rewards[2].type = REWARD_TYPE_POTION;
    // rewards[2].subtype = TETRONIMO_T;
}

