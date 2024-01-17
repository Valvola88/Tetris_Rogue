#include "Tetris.h"

#define MAX_POWERUPS 16
#define MAX_ENEMIES 4
#define ENEMY_FRAMERATE 4

Texture2D GfxPotions[MAX_POWERUPS];
Texture2D GfxActiveTrinket[MAX_POWERUPS];
Texture2D GfxPassiveTrinket[MAX_POWERUPS];
Texture2D GfxEnemiesTexture[MAX_ENEMIES][ENEMY_FRAMERATE];

void animationClipTick(AnimationClip *self, float delta_time)
{
    self->counter += delta_time;
    if (self->counter > 1.f / self->FPS)
    {
        self->current_frame = (self->current_frame +1) % self->max_frames;
        self->counter = 0;
    }
}

Texture2D *AnimationClipGetCurrentTexture(AnimationClip *self)
{
    return self->frames[self->current_frame];
}

AnimationClip GfxEnemiesClip[MAX_ENEMIES];
Texture2D GfxInputKeys[GFX_KEY_LAST];

int TetrisLoadImages()
{
    //LOAD POTIONS (ONE USE ITEM)
    for (int i = 0; i < MAX_POWERUPS; i++)
    {
        Image image = LoadImage("resources/texture/potion.png");
        ImageCrop(&image,(Rectangle){(i % 4) * 24,(i/4) * 24, 24, 24});
        GfxPotions[i] = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    //LOAD ACTIVE TRINKET
    for (int i = 0; i < MAX_POWERUPS; i++)
    {
        Image image = LoadImage("resources/texture/active.png");
        ImageCrop(&image,(Rectangle){(i % 4) * 24,(i/4) * 24, 24, 24});
        GfxActiveTrinket[i] = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    //LOAD PASSIVE TRINKET
    for (int i = 0; i < MAX_POWERUPS; i++)
    {
        Image image = LoadImage("resources/texture/passive.png");
        ImageCrop(&image,(Rectangle){(i % 4) * 24,(i/4) * 24, 24, 24});
        GfxPassiveTrinket[i] = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    //LOAD ENEMIES
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        for (int j = 0; j < ENEMY_FRAMERATE; j++)
        {
            Image image = LoadImage("resources/texture/enemies.png");
            ImageCrop(&image,(Rectangle){j * 16,i * 16, 16, 16});
            GfxEnemiesTexture[i][j] = LoadTextureFromImage(image);

            GfxEnemiesClip[i].frames[j] = &GfxEnemiesTexture[i][j];
            UnloadImage(image);
        }
        GfxEnemiesClip[i].max_frames = ENEMY_FRAMERATE;
        GfxEnemiesClip[i].current_frame = 0;
        GfxEnemiesClip[i].FPS = 4.f;
        GfxEnemiesClip[i].counter = 0.f;
        GfxEnemiesClip[i].tick = animationClipTick;
        GfxEnemiesClip[i].GetCurrentTexture = AnimationClipGetCurrentTexture;
    }

    for (int i = 0; i < GFX_KEY_LAST; i++)
    {
        Image image = LoadImage("resources/texture/input_key.png");
        ImageCrop(&image,(Rectangle){(i % 4) * 16,(i/4) * 16, 16, 16});
        ImageResize(&image, image.width, image.height);
        GfxInputKeys[i] = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    return 0;
}

int TetrisLoadTexture(Texture2D *texture, char* path, float scale)
{
    Image image = LoadImage(path);
    ImageResize(&image, image.width * scale, image.height * scale);
    *texture = LoadTextureFromImage(image);
    UnloadImage(image);

    return 0;
}  

void TetrisDrawPowerUp(const int pu,const int x,const int y, float scale)
{
    if (pu > MAX_POWERUPS)
        return;

    Vector2 my_pos = {x, y};
    DrawTextureEx(GfxPotions[pu], my_pos, 0, scale,WHITE);
}

int TetrisUnloadImages()
{
    for(int i =0; i< MAX_POWERUPS;i++)
    {
        UnloadTexture(GfxPotions[i]);
        UnloadTexture(GfxActiveTrinket[i]);
        UnloadTexture(GfxPassiveTrinket[i]);
    }

    for(int i =0; i< GFX_KEY_LAST;i++)
        UnloadTexture(GfxInputKeys[i]);

    UnloadTexture(main_character.mytexture);
    return 0;
}