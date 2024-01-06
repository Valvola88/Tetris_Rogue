#include "Tetris.h"

int TetrisSetTextureClickable(Clickable* click, Texture2D* texture)
{
    click->texture = texture;

    click->w = texture->width;
    click->h = texture->height;

    click->utils_value = -1;

    return 0;
}

int TetrisDrawClickable(Clickable* self)
{
    if (TetrisIsMouseInside(self))
    {
        DrawTexture(*(self->texture), self->x, self->y, YELLOW);
    }
    else
        DrawTexture(*(self->texture), self->x, self->y, WHITE);

        return 0;
}

int TetrisClick(Clickable* self)
{
    if (!TetrisIsMouseInside(self))
        return 0;

    self->Clicked(self->utils_value);

    return 1;
}

int TetrisIsMouseInside(Clickable* self)
{
    return (GetMouseX() > self->x && 
        GetMouseX() < self->x + self->w) 
        && (GetMouseY() > self->y &&
        GetMouseY() < self->y + self->h);
}