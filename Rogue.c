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

int visible_potions_slot = 3;
int visible_rewards_number = 3;

extern Reward REWARDS[];
extern Texture2D Potions[];
extern AnimationClip GfxEnemiesClip[];
extern ActiveTrinket TemplateActiveTrinkets[];
extern PassiveTrinket TemplatePassiveTrinkets[];
extern Enemy Enemies[];

extern int showRewardBox;

Vector2 center_white_screen = {256,35};
int green_rect;
int overkill;

int AddPlayerDamage(float damage)
{
    main_character.damage += damage;
    return 1; 
}

int AddPlayerPotionSlot(float _)
{
    visible_potions_slot += 1;
    if (visible_rewards_number >= 5)
        visible_rewards_number = 5;
    return 1; 
}

int AddPlayerVisibleReward(float _)
{
    visible_rewards_number += 1;
    if (visible_rewards_number >= 5)
        visible_rewards_number = 5;
    return 1; 
}

int DealNonLethalDamage()
{
    current_enemy.life -= main_character.damage;
    if (current_enemy.life <= .1f)
        current_enemy.life = .1f;

    float percent = (current_enemy.life / current_enemy.max_life);
    green_rect = 100 * percent;

    return 1;
}

void HealEnemy(float damage)
{
    current_enemy.life += damage;
    if (current_enemy.life >= current_enemy.max_life)
        current_enemy.life = current_enemy.max_life;

    float percent = (current_enemy.life / current_enemy.max_life);
    green_rect = 100 * percent;
}

void SetEnemy(int enemy_type)
{
    current_enemy = Enemies[enemy_type];
    green_rect = 100;
}

void RogueBegin()
{
    main_character.damage = 1;
    overkill = 0;
    TetrisLoadTexture(&(main_character.mytexture), "resources/texture/character.png", 2);

    for(int i = 0; i < 100; i++)
    {
        Inventory[i] = NULL;
    }

    trinket_in_inventory = 0;
    green_rect = 100;
    SetEnemy(0);

    current_active_trinket.name = NULL;
}

void UsePotion(int potion_number)
{
    if (potion_number >= visible_potions_slot)
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
    float percent = (current_enemy.life / current_enemy.max_life);
    green_rect = 100 * percent;

    if (current_enemy.life <= 0)
    {
        showRewardBox = 1;
        overkill = 1;
        SetEnemy(GetRandomValue(0,3));
    }

    return 1;
}

void EnemyAttack()
{
    int font_size = GetFontForContainer(current_enemy.current_action->name,(Vector2){180,40});
    ShoutString(current_enemy.current_action->name, center_white_screen.x,center_white_screen.y,2,font_size,BROWN);
    current_enemy.current_action->action();
    ChangeRandomActionEnemy(&current_enemy);
}

void RoguePiecePlaced()
{
    current_enemy.action_timer--;

    if (current_enemy.action_timer == 0)
    {  
        EnemyAttack();
        //int tArray[] = {2, 4};
        //CreateBlockUnder(tArray, 2);
        // TransformQueuedPieces(5, TETRONIMO_SMALL_O);
        // int font_size = GetFontForContainer("SMALL O ATTACK",(Vector2){180,40});
        // ShoutString("SMALL O ATTACK", center_white_screen.x,center_white_screen.y,2,font_size,BROWN);
        // current_enemy.action_timer = 5;
    }
}

void RogueLineScored()
{
    //printf("Attack");
    if (!overkill)
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

    current_enemy.mytexture->tick(current_enemy.mytexture, delta_time);
}

void RogueDraw()
{
    int begin_x = 12;
    int begin_y = 444;

    //POTIONS
    for(int i = 0; i< visible_potions_slot; i++)
    {
        DrawRectangleLines(begin_x, begin_y, 56, 56, BLACK);
        
        if (potions[i] > -1)
        {
            TetrisDrawPowerUp(potions[i],begin_x + 4, begin_y + 4, 2.f);
        }

        DrawRectangle(begin_x - 4, begin_y + 43, 17, 17, WHITE);
        DrawRectangleLines(begin_x - 4, begin_y + 43, 17, 17, BLACK);

        Color c = (potions[i] > -1) ? BLACK : GRAY;
        DrawTextureEx(GfxInputKeys[i], (Vector2){begin_x - 3, begin_y + 44}, 0, 1, c);

        begin_x += 66;
    }

    

    
    DrawRectangle(40,242,80,64,GRAY);
    DrawRectangleLines(40,242,80,64,BLACK);

    DrawRectangle(48,230, 64,16,WHITE);
    DrawRectangleLines(48,230, 64,16,BLACK);

    //KEY
    DrawRectangle(11,258,32,32,WHITE);
    DrawRectangleLines(11,258,32,32,BLACK);

    DrawRectangle(115,250,10,48,GRAY);
    DrawRectangleLines(115,249,10,48,BLACK);

    if(!current_active_trinket.name)
    {
        DrawTextCentral("ACTIVE", 48 +32, 230 + 2, 12, BLACK);

        DrawTextureEx(GfxInputKeys[GFX_KEY_SHIFT], (Vector2){12,259}, 0, 2, GRAY);
    }
    else
    {
        DrawTextCentral(current_active_trinket.name, 48 +32, 230 + 3, 10, BLACK);

        DrawTextureEx(*current_active_trinket.textrue, (Vector2){56,250}, 0, 2, (current_active_trinket.charge == current_active_trinket.current_charge) ? WHITE : GRAY);

        int fract = 48 / current_active_trinket.charge;

        for(int i = 0; i < current_active_trinket.charge; i++)
        {
            if (i < current_active_trinket.current_charge)
                DrawRectangle(115, 249 + 48 - (fract * (1 + i)), 10, fract, GREEN);
            else
                DrawRectangle(115, 249 + 48 - (fract * (1 + i)), 10, fract, WHITE);
            
            DrawRectangleLines(115, 249 + 48 - (fract * (1 + i)), 10, fract, BLACK);
        }

        Color c = (current_active_trinket.charge == current_active_trinket.current_charge) ? BLACK : GRAY;
        DrawTextureEx(GfxInputKeys[GFX_KEY_SHIFT], (Vector2){12,259}, 0, 2, c);
    }

    //DrawRectangle(18,336,124,72,WHITE);
    DrawRectangleLines(18,336,124,72,BLACK);

    DrawRectangle(32,326,96,16,WHITE);
    DrawRectangleLines(32,326,96,16,BLACK);

    DrawTextCentral("INVENTORY",34 + 48,328,12,BLACK);

    int first = max(trinket_in_inventory - 8, 0);
    int j = min(trinket_in_inventory - 1, 7);

    for(int i = 0; i < 8; i++)
    {
        if (first + i >= trinket_in_inventory)
            break;
        
        DrawTexture(*Inventory[first + i]->textrue, 26 + (j%4) * 28, 348 + (j/4) * 28, WHITE);
        j--;
    }
    if (trinket_in_inventory > 8)
    {
        DrawTexture(GfxPassiveTrinket[15], 110, 376, WHITE);
    }

    //DrawTexture(main_character.mytexture, 16,16, WHITE);
    
    //ENEMY
    DrawRectangle(372,6,120,120,SKYBLUE);
    DrawRectangleLines(372,6,120,120,BLACK);

    DrawRectangle(166,15,180,40,WHITE);
    DrawRectangleLines(166,15,180,40,BLACK);

    DrawRectangle(347,19,24,32,WHITE);
    DrawRectangleLines(347,19,24,32,BLACK);

    DrawTextureEx(*(current_enemy.mytexture->GetCurrentTexture((current_enemy.mytexture))), (Vector2){384,18},0,6,WHITE);

    DrawText(TextFormat("%i", current_enemy.action_timer), 351, 22,32,BLACK);
    //DrawText(TextFormat("%f", current_enemy.life), 380, 78,16,WHITE);

    DrawRectangle(380,108,104,14,BLACK);
    DrawRectangle(382,110,green_rect,10,green_rect >= 50 ? GREEN : green_rect >= 20 ? YELLOW : RED);
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

    for(int i = 0; i< visible_potions_slot; i++)
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
    // SetReward(
    // 0,
    // 14,
    // 100,
    // 150
    // );
}

void RogueRewardBegin()
{
    showRewardBox  = 0;
    current_game_loop.tick = RogueRewardTick;
    current_game_loop.post_draw = RogueRewardDraw;
    current_game_loop.begin_play = EmptyBegin;

    SetRandomRewards(visible_rewards_number);
    overkill = 0;

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

