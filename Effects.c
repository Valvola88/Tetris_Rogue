#include "Tetris.h"

typedef struct FadingString{

    char* myString;
    Vector2 myPosition;
    Vector2 myOrigin;
    int myFontSize;
    Color myColor;
    float myDuration;

    Vector2 myVelocity;
    float myRotation;

    int myColorEffect;

} FadingString;

#define MAX_TILES 40
#define MAX_FADING_STRINGS 10

Tile tiles[MAX_TILES];

Font fontDefault = { 0 };

FadingString fadingStrings[MAX_FADING_STRINGS];

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
    for(int i = 0; i< MAX_TILES;i++)
    {
        tiles[i].tick = TetrisTileMove;
        tiles[i].draw = TetrisTileDraw;
        tiles[i].isActive = 0;
    }

    for(int i =0; i < MAX_FADING_STRINGS;i++)
    {
        fadingStrings[i].myString = NULL;
    }
}

FadingString *GetFirstFadingString()
{
    for(int i = 0; i < MAX_FADING_STRINGS; i++)
    {
        if (fadingStrings[i].myString)
            continue;

        return &fadingStrings[i];
    }

    return NULL;
}

void InitString(FadingString *current_string, char* string, const int x, const int y, const float duration,const int fontSize, const Color color)
{
    current_string->myString = string;
    current_string->myPosition = (Vector2){ x, y};
    current_string->myDuration = duration;
    current_string->myFontSize = fontSize;
    current_string->myColor = color;
    current_string->myOrigin = (Vector2){
        MeasureText(current_string->myString, current_string->myFontSize) / 2,
        current_string->myFontSize / 2
        };
}


void ShoutStringExtra(char* string, const int x, const int y, const float duration,const int fontSize, const Color color, const Vector2 velocity, const float rotation, const int colorEffect)
{
    FadingString *current_string = GetFirstFadingString();
    if (current_string == NULL)
        return;
    
    Color c = color;
    if (colorEffect == EFFECT_COLOR_RANDOM)
        c = (Color){GetRandomValue(0,255),GetRandomValue(0,255),GetRandomValue(0,255), 255};
    
    InitString(current_string, string, x, y, duration, fontSize, c);
    current_string->myVelocity = velocity;
    current_string->myRotation = rotation;
    current_string->myColorEffect = colorEffect;
}

void ShoutString(char* string, const int x, const int y, const float duration,const int fontSize, const Color color)
{
    FadingString *current_string = GetFirstFadingString();
    if (current_string == NULL)
        return;

    InitString(current_string, string, x, y, duration, fontSize, color);
    current_string->myVelocity = (Vector2){0,0};
    current_string->myRotation = 0.f;
    current_string->myColorEffect = EFFECT_NORMAL;
}

void EffectTick(const float delta_time)
{
    // if (only_tile.isActive == 0)
    //     return;

    // only_tile.tick(&only_tile, delta_time);
    
    for(int i = 0; i < MAX_TILES ;i++)
    {
        if (!tiles[i].isActive)
            continue;

        tiles[i].tick(&tiles[i], delta_time);

        if (tiles[i].y > WINDOW_HEIGHT + 10)
            tiles[i].isActive = false;
    }

    for(int i = 0; i< MAX_FADING_STRINGS;i ++)
    {
        if (fadingStrings[i].myString == NULL)
            continue;
        
        fadingStrings[i].myDuration -= delta_time;

        fadingStrings[i].myPosition.x += fadingStrings[i].myVelocity.x * delta_time;
        fadingStrings[i].myPosition.y += fadingStrings[i].myVelocity.y * delta_time;

        float t = min(fadingStrings[i].myDuration, .5f);

        int a = fadingStrings[i].myColor.a;
        fadingStrings[i].myColor.a = a * (t * 2);

        if (fadingStrings[i].myDuration <= 0)
            fadingStrings[i].myString = NULL;
    }
}

void EffectDraw()
{
    for(int i = 0; i < MAX_TILES;i++)
    {
        if (!tiles[i].isActive)
            continue;

        tiles[i].draw(&tiles[i]);
    }

    for(int i = 0; i< MAX_FADING_STRINGS; i++)
    {
        if (fadingStrings[i].myString == NULL)
            continue;
        FadingString *current_string = &fadingStrings[i];
        
        DrawTextPro(fontDefault,
            current_string->myString,
            current_string->myPosition,
            current_string->myOrigin,
            current_string->myRotation,
            current_string->myFontSize,
            current_string->myFontSize / (float)10,
            current_string->myColor
            );
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

int DestroyTetronimoEffect(Tetromino *tetronimo)
{
    for(int i = 0; i < 4; i++)
    {
        SpawnTile(
        START_OFFSET_X + (tetronimo->x + tetronimo->current_shape[i * 2]) * TILE_SIZE,
        START_OFFSET_Y + (tetronimo->y + tetronimo->current_shape[i * 2 + 1]) * TILE_SIZE, 
        i, tetronimo->color);
    }

    return 0;
}
