#include "Tetris.h"

#define MAX_POWERUPS 8

Texture2D PowerUps[MAX_POWERUPS];

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
}