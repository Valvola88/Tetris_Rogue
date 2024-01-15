#include "Tetris.h"

#define MAX_POWERUPS 16

Texture2D PowerUps[MAX_POWERUPS];

Texture2D GfxInputKeys[GFX_KEY_LAST];

int TetrisLoadImages()
{
    for (int i = 0; i < MAX_POWERUPS; i++)
    {
        Image image = LoadImage("resources/texture/pu.png");
        ImageCrop(&image,(Rectangle){(i % 4) * 24,(i/4) * 24, 24, 24});
        ImageResize(&image, image.width * 2, image.height * 2);
        PowerUps[i] = LoadTextureFromImage(image);
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

void TetrisDrawPowerUp(const int pu,const int x,const int y)
{
    if (pu > MAX_POWERUPS)
        return;

    DrawTexture(PowerUps[pu],x,y,WHITE);
}

int TetrisUnloadImages()
{
    for(int i =0; i< MAX_POWERUPS;i++)
        UnloadTexture(PowerUps[i]);

    for(int i =0; i< GFX_KEY_LAST;i++)
        UnloadTexture(GfxInputKeys[i]);

    UnloadTexture(main_character.mytexture);
    UnloadTexture(current_enemy.mytexture);
    return 0;
}