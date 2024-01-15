#include "Tetris.h"

#define MAX_POWERUPS 16

Texture2D GfxPotions[MAX_POWERUPS];
Texture2D GfxActiveTrinket[MAX_POWERUPS];
Texture2D GfxPassiveTrinket[MAX_POWERUPS];


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
        UnloadTexture(GfxPotions[i]);

    for(int i =0; i< GFX_KEY_LAST;i++)
        UnloadTexture(GfxInputKeys[i]);

    UnloadTexture(main_character.mytexture);
    UnloadTexture(current_enemy.mytexture);
    return 0;
}