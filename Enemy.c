#include "Tetris.h"

// typedef struct Enemy{
    
//     int enemy_type;
//     char* name;
    
//     float life;
//     float max_life;

//     int action_timer;
//     int current_action_timer;

//     Action attacks[5];
//     int attack_number;
    
//     void(*death)();

//     AnimationClip *mytexture;

// } Enemy;

// typedef struct Action{

//     char* name;
//     float weight;
//     int timer;
//     void(*action)();

// }Action;
Enemy Enemies[4];

void CreateLineOneEmpty()
{
    int r[1] = {GetRandomValue(1,10)};
    CreateBlockUnder(r,1);
}

void CreateLineTwoEmpty()
{
    int r[2] = {
        GetRandomValue(1,5),
        GetRandomValue(6,10)
    };
    CreateBlockUnder(r,2);
}

void AtkSquareMagic()
{
    TransformQueuedPieces(3, TETRONIMO_O);
}

void AtkTMagic()
{
    TransformQueuedPieces(2, TETRONIMO_T);
}

void AtkSmallOMagic()
{
    TransformQueuedPieces(1, TETRONIMO_SMALL_O);
}

void AtkVampireFang()
{
    int r[3] = {
        GetRandomValue(1,3),
        GetRandomValue(4,7),
        GetRandomValue(8,10)
        };
    CreateBlockUnder(r,3);

}

void AtkSkullBash()
{
    int v[3];
    const int r = GetRandomValue(1,3);
    
    for(int i = 0; i< r; i++)
    {
        v[i] = GetRandomValue(1,10);
    }
    CreateBlockUnder(v,r);
}
#define ATK_BONE_BONK 0
#define ATK_SUPER_BONE_BONK 1
#define ATK_SQUARE_MAGIC 2
#define ATK_T_MAGIC 3
#define ATK_SMALL_O_MAGIC 4
#define VAMPIRE_FANG 5
#define SKULL_BASH 6
Action PossibleAttacks[] = 
{
    {"Bone Bonk", 2, 4, CreateLineOneEmpty},
    {"Super Bone Bonk", 1, 3, CreateLineTwoEmpty},
    {"Square-Attack", 1, 4, AtkSquareMagic},
    {"T-Attack", 1, 5, AtkTMagic},
    {"Tiny O-Attack", 1, 3, AtkSmallOMagic},
    {"Vampire Fang", 3, 4, AtkVampireFang},
    {"Skull Bash", 1, 5, AtkSkullBash}
};

Action *GetRandomAction(Action *list_of_actions[], int number)
{
    if (number == 1)
        return list_of_actions[0];

    int weight_values[100];
    int current_index = 0;
    for(int i = 0; i< number;i++)
    {
        for(int j = 0; j < list_of_actions[i]->weight; j++)
        {
            weight_values[current_index] = i;
            current_index++;
        }
    }
    int j = GetRandomValue(0, current_index - 1);
    //printf("J: %d", j);
    return(list_of_actions[weight_values[j]]);
}

void ResetActionEnemy(Enemy *e)
{
    e->action_timer = e->current_action->timer;
    e->current_action_timer = e->current_action->timer;
}

void ChangeRandomActionEnemy(Enemy *e)
{
    e->current_action = GetRandomAction(e->attacks, e->attack_number);
    ResetActionEnemy(e);
}

void InitEnemies(){

    Enemy *e = &Enemies[0];

    e->name = "Base Skeleton";
    e->max_life = 5.f;
    e->life = 5.f;
    e->attacks[0] = &PossibleAttacks[0];
    e->attacks[1] = &PossibleAttacks[1];
    e->attack_number = 2;
    ChangeRandomActionEnemy(e);
    e->mytexture = &GfxEnemiesClip[0];

    e = &Enemies[1];

    e->name = "Mage Base Skeleton";
    e->max_life = 4.f;
    e->life = 4.f;
    e->attacks[0] = &PossibleAttacks[0];
    e->attacks[1] = &PossibleAttacks[ATK_SQUARE_MAGIC];
    e->attack_number = 2;
    ChangeRandomActionEnemy(e);
    e->mytexture = &GfxEnemiesClip[1];

    e = &Enemies[2];

    e->name = "Skull";
    e->max_life = 6.f;
    e->life = 6.f;
    e->attacks[0] = &PossibleAttacks[SKULL_BASH];
    e->attacks[1] = &PossibleAttacks[ATK_SMALL_O_MAGIC];
    e->attacks[2] = &PossibleAttacks[ATK_T_MAGIC];
    e->attack_number = 3;
    ChangeRandomActionEnemy(e);
    e->mytexture = &GfxEnemiesClip[2];

    e = &Enemies[3];

    e->name = "Vampire Boss";
    e->max_life = 10.f;
    e->life = 10.f;
    e->attacks[0] = &PossibleAttacks[VAMPIRE_FANG];
    e->attacks[1] = &PossibleAttacks[ATK_T_MAGIC];
    e->attacks[2] = &PossibleAttacks[ATK_SMALL_O_MAGIC];
    e->attacks[3] = &PossibleAttacks[ATK_SQUARE_MAGIC];
    e->attack_number = 4;
    ChangeRandomActionEnemy(e);
    e->mytexture = &GfxEnemiesClip[3];
}
