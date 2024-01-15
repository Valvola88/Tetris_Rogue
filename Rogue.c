#include "Tetris.h"

#define MAX_POSSIBLE_POTION 5
#define MAX_POSSIBLE_VISIBLE_REWARDS 5

#define POSSIBLE_REWARDS 16

int potions[MAX_POSSIBLE_POTION] = {6,-1,-1, -1, -1};


Reward *current_rewards[MAX_POSSIBLE_VISIBLE_REWARDS];
Clickable rewards_buttons[MAX_POSSIBLE_POTION];

Character main_character;
Enemy current_enemy;

ActiveTrinket current_active_trinket;

PassiveTrinket *Inventory[100];
int trinket_in_inventory;

int visible_potions = 3;
int visible_rewards_number = 3;

extern Reward REWARDS[];
extern Texture2D Potions[];
extern ActiveTrinket TemplateActiveTrinkets[];
extern PassiveTrinket TemplatePassiveTrinkets[];
extern int EnemiesHealth[];
extern int EnemiesTimer[];

extern int showRewardBox;

int green_rect;

int AddPlayerDamage(int damage)
{
    main_character.damage += damage;
    return 1; 
}

int AddPlayerVisibleReward(int _)
{
    visible_rewards_number += 1;
    if (visible_rewards_number >= 5)
        visible_rewards_number = 5;
    return 1; 
}

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

    for(int i = 0; i < 100; i++)
    {
        Inventory[i] = NULL;
    }

    trinket_in_inventory = 0;
    green_rect = 100;
    SetEnemy(ENEMY_SIMPLE);
}

void UsePotion(int potion_number)
{
    if (potion_number >= visible_potions)
        return;

    if (potions[potion_number] < 0)
        return;


    if(!CheckRotateCollision(mainTetronimo.x, mainTetronimo.y, tetronimo_types[potions[potion_number]][mainTetronimo.rotation]))
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

int RogueAttack()
{

    current_enemy.life -= main_character.damage;
    float percent = ((float)(current_enemy.life) / (float)(EnemiesHealth[current_enemy.enemy_type]));
    green_rect = 100 * percent;

    if (current_enemy.life <= 0)
    {
        showRewardBox = 1;
    }

    return 1;
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
    RogueAttack();

    if (current_active_trinket.current_charge < current_active_trinket.charge)
    {
        current_active_trinket.current_charge++;
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

    if (IsKeyPressed(KEY_LEFT_SHIFT) &&
        current_active_trinket.current_charge == current_active_trinket.charge &&
        current_active_trinket.Activate)
    {
        printf("ACtoiva");
        if(current_active_trinket.Activate())
            current_active_trinket.current_charge = 0;
    }
}

void RogueDraw()
{
    for(int i = 0; i< visible_potions; i++)
    {
        if (potions[i] > -1)
        {
            TetrisDrawPowerUp(potions[i],16 + ((48 + 2) * i ),450, 2.f);
        }
    }

    if(current_active_trinket.textrue)
    {
        DrawTexture(*current_active_trinket.textrue, 300 ,450, WHITE);
        int fract = 48 / current_active_trinket.charge;
        for(int i = 0; i < current_active_trinket.charge; i++)
        {
            if (i < current_active_trinket.current_charge)
                DrawRectangle(280, 450 + fract * i, 10, fract, GREEN);
            else
                DrawRectangle(280, 450 + fract * i, 10, fract, WHITE);
            
            DrawRectangleLines(280, 450 + fract * i, 10, fract, BLACK);
        }
    }

    DrawTexture(main_character.mytexture, 16,16, WHITE);
    DrawTexture(current_enemy.mytexture, 400,16, WHITE);

    DrawText(TextFormat("%i", current_enemy.action_timer), 360,24,32,WHITE);
    //DrawText(TextFormat("%f", current_enemy.life), 380, 78,16,WHITE);

    DrawRectangle(372,68,104,14,BLACK);
    DrawRectangle(374,70,green_rect,10,GREEN);
}

void DrawTooltip(char* text)
{
    if (!text)
        return;

    DrawTextCentral(text, 256, 70, 16, BLACK);
}

void RogueRewardDraw()
{
    DrawRectangle(64,64,384, 150, WHITE);

    for(int i = 0; i < visible_rewards_number;i++)
    {
        if (TetrisIsMouseInside(&rewards_buttons[i]))
        {
            DrawTooltip(current_rewards[i]->tooltip);
        }
        TetrisDrawClickable(&rewards_buttons[i]);  
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

void RogueRewardTick(const float delta_time)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        int valid_click = 0;
        for(int i = 0; i < visible_rewards_number;i++)
        {
            {
                valid_click = valid_click + TetrisClick(&rewards_buttons[i]);
            }
        }

        if (valid_click)
        {
            current_game_loop.post_draw = EmptyDraw;
            current_game_loop.tick = MainTick;
        }
    } 
}

int SetActiveTrinket(int trinket)
{
    current_active_trinket = TemplateActiveTrinkets[trinket];

    return 1;
}

int AddPassiveTrinket(int trinket)
{
    Inventory[trinket_in_inventory] = &TemplatePassiveTrinkets[trinket];

    Inventory[trinket_in_inventory]->OnPickup(Inventory[trinket_in_inventory]->utils_value);
    trinket_in_inventory++;

   return 1;
}

void SetReward( int number,int reward, int x, int y)
{
    if (number < 0 || number > visible_rewards_number)
        return;
    
    current_rewards[number] = &REWARDS[reward];
    
    TetrisSetTextureClickable(&rewards_buttons[number], current_rewards[number]->textrue);
    rewards_buttons[number].name = current_rewards[number]->name;
    rewards_buttons[number].x = x;
    rewards_buttons[number].y = y;

    switch (current_rewards[number]->type)
    {
        case REWARD_TYPE_POTION:
            rewards_buttons[number].Clicked = AddPotion;
            rewards_buttons[number].utils_value = current_rewards[number]->subtype;
            break;
        case REWARD_TYPE_ACTIVE_TRINKET:
            rewards_buttons[number].Clicked = SetActiveTrinket;
            rewards_buttons[number].utils_value = current_rewards[number]->subtype;
            break;
        case REWARD_TYPE_PASSIVE_TRINKET:
            rewards_buttons[number].Clicked = AddPassiveTrinket;
            rewards_buttons[number].utils_value = current_rewards[number]->subtype;
            break;
    
    default:
        break;
    }

    return;
}

void SetRandomRewards(int amount)
{
    if (amount > visible_rewards_number)
        return;

    for(int i = 0 ; i < amount; i++)
    {
        int tmpx = 100 + (512 - 200 - REWARD_SIZE) * ((float)i / (float)(amount - 1));

        int reward = GetRandomValue(0, POSSIBLE_REWARDS);

        Texture2D *text = NULL;

        SetReward(
            i,
            reward,
            tmpx,
            150
        );

    }
}

void RogueRewardBegin()
{
    showRewardBox  = 0;
    current_game_loop.tick = RogueRewardTick;
    current_game_loop.post_draw = RogueRewardDraw;
    current_game_loop.begin_play = EmptyBegin;

    SetRandomRewards(visible_rewards_number);

    // for(int i = 0; i< 3;i++)
    // SetReward(
    //     i,
    //     "I Potion",
    //     REWARD_TYPE_POTION,
    //     i,
    //     100 + 100 * i,
    //     150,
    //     &Potions[i]
    // );
    // rewards[1].name = "J Potion";
    // rewards[1].type = REWARD_TYPE_POTION;
    // rewards[1].subtype = TETRONIMO_J;

    // rewards[2].name = "T Potion";
    // rewards[2].type = REWARD_TYPE_POTION;
    // rewards[2].subtype = TETRONIMO_T;
}

