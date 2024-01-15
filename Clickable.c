#include "Tetris.h"


int TetrisSetTextureClickable(Clickable* click, Texture2D* texture)
{
    click->texture = texture;

    click->w = texture->width;
    click->h = texture->height;

    click->utils_value = -1;
    click->scale_dimension = 2;

    return 0;
}

int TetrisDrawClickable(Clickable* self)
{
    if (self->texture == NULL)
        return 0 ;

    if (self->name)
    {
        DrawTextCentral(self->name, self->x + (self->w * self->scale_dimension * .5f), self->y - 12, 10, BLACK);
    }

    Vector2 my_pos = {self->x, self->y};
    if (TetrisIsMouseInside(self))
    {
        DrawTextureEx(*(self->texture), my_pos, 0, self->scale_dimension, YELLOW);
    }
    else
    {
        DrawTextureEx(*(self->texture), my_pos, 0, self->scale_dimension, WHITE);
    }
        return 0;
}

int TetrisClick(Clickable* self)
{
    if (self == NULL)
        return 0;

    if (!TetrisIsMouseInside(self))
        return 0;

    self->Clicked(self->utils_value);

    return 1;
}

int TetrisIsMouseInside(Clickable* self)
{
    return (GetMouseX() > self->x && 
        GetMouseX() < self->x + self->w * self->scale_dimension) 
        && (GetMouseY() > self->y &&
        GetMouseY() < self->y + self->h * self->scale_dimension);
}