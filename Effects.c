#include "Tetris.h"



Tile tiles[40];

//Tile only_tile;

void TetrisTileEmptyTick(Tile *self, const float delta_time)
{

}

void TetrisTileMove(Tile *self, const float delta_time)
{

    self->x += self->velocity_x;
    self->y += self->velocity_y;

    self->velocity_y += 1;
}

void TetrisTileDraw(Tile *self)
{
    DrawRectangle(self->x,self->y,TILE_SIZE,TILE_SIZE,self->my_color);
    DrawRectangleLines(self->x,self->y,TILE_SIZE,TILE_SIZE,BLACK);
}

void EffectBegin()
{
    // only_tile.tick = TileMove;
    // only_tile.draw = TileDraw;
    // only_tile.isActive = 0;
    for(int i = 0; i<40;i++)
    {
        tiles[i].tick = TetrisTileMove;
        tiles[i].draw = TetrisTileDraw;
        tiles[i].isActive = 0;
    }   
}

void EffectTick(const float delta_time)
{
    // if (only_tile.isActive == 0)
    //     return;

    // only_tile.tick(&only_tile, delta_time);
    
    for(int i = 0; i <40 ;i++)
    {
        if (!tiles[i].isActive)
            continue;

        tiles[i].tick(&tiles[i], delta_time);

        if (tiles[i].y > WINDOW_HEIGHT + 10)
            tiles[i].isActive = false;
    }   
}

void EffectDraw()
{    
    // if (only_tile.isActive == 0)
    //     return;

    // only_tile.draw(&only_tile);
    for(int i = 0; i<40;i++)
    {
        if (!tiles[i].isActive)
            continue;

        tiles[i].draw(&tiles[i]);
    }       
}

void SpawnTile(const int x, const int y, const int number, Color color)
{
    // only_tile.x = x;
    // only_tile.y = y;
    // only_tile.my_color = color;

    // only_tile.velocity_x = GetRandomValue(-10,10);
    // only_tile.velocity_y = -10;

    // only_tile.isActive = 1;
    tiles[number].x = x;
    tiles[number].y = y;
    tiles[number].my_color = color;

    tiles[number].velocity_x = GetRandomValue(-10,10);
    tiles[number].velocity_y = -10;

    tiles[number].isActive = 1;
}

int DestroyTetronimoEffect(Tetronimo *tetronimo)
{
    for(int i = 0; i< 4; i++)
    {
        SpawnTile(
        START_OFFSET_X + (tetronimo->x + tetronimo->current_shape[i * 2]) * TILE_SIZE,
        START_OFFSET_Y + (tetronimo->y + tetronimo->current_shape[i * 2 + 1]) * TILE_SIZE, 
        i, tetronimo->color);
    }

    return 0;
}
