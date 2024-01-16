#include "Tetris.h"

const Vector2 piecesVisualOffset[10] = {
    {26, 24},
    {26, 24},
    {26, 24},
    {26, 24},
    {34, 24},
    {26, 24},
    {18, 32},
    {26, 24},
    {34, 24},
    {24, 16},
};


void FormatScore(char* score_array, int score)
{
    char* score_char;
    sprintf(score_char, "%d", score);

    int len = strlen(score_char);
    char *address = &score_array[8 - len];
    memset(score_array, '0', 9);
    strcpy_s(address, sizeof(char) * len,score_char);

}

//Functions
void DrawTextCentral(const char* str, int x,  int y, int font_size, Color color)
{
    const int len = strlen(str);
    const int text_size = MeasureText(str,font_size);

    int start_x = x - (text_size / 2);

    DrawText(str, start_x, y, font_size, color);
}

void DrawTetrominoAbsolute(
    const int start_x,
    const int start_y,
    const int *tetronimo,
    const Color c)
{
    for (int i = 0; i < 8; i +=2)
    {
        DrawRectangle(
            start_x + tetronimo[i] * TILE_SIZE,
            start_y + tetronimo[i + 1] * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE,
            c
        );
    }
}

void DrawTetromino(
    const int tile_x,
    const int tile_y,
    const int *tetronimo,
    const Color c)
{
    DrawTetrominoAbsolute(tile_x * TILE_SIZE + START_OFFSET_X,
    tile_y * TILE_SIZE + START_OFFSET_Y,
    tetronimo,
    c);
    // for (int i = 0; i < 8; i +=2)
    // {
    //     DrawRectangle(
    //         (start_x + tetronimo[i]) * TILE_SIZE + START_OFFSET_X,
    //         (start_y + tetronimo[i + 1]) * TILE_SIZE + START_OFFSET_Y,
    //         TILE_SIZE,
    //         TILE_SIZE,
    //         c
    //     );
    // }
}


void DrawTetromino2(Tetromino *tetronimo)
{
    DrawTetromino(
        tetronimo->x,
        tetronimo->y,
        tetronimo->current_shape,
        tetronimo->color
    );
}

void DrawTetrominoOnWhiteCentered(const int up_left_x, const int up_left_y, int tetromino_shape)
{
    DrawRectangle(up_left_x,
        up_left_y,
        68,
        48,
        WHITE);
    DrawRectangleLines(up_left_x,
        up_left_y,
        68,
        48,
        BLACK);

    if (tetromino_shape >= 0)
    {
        DrawTetrominoAbsolute(up_left_x + piecesVisualOffset[tetromino_shape].x,
            up_left_y + piecesVisualOffset[tetromino_shape].y,
            tetronimo_types[tetromino_shape][0],
            colorTypes[tetromino_shape + 1]);
    }
}


void DrawTetrominoContainer(const int up_left_x, const int up_left_y, int tetromino_shape, const char* label)
{
    DrawRectangleLines(up_left_x,
        up_left_y,
        80,
        64,
        BLACK);
    
    DrawRectangle( up_left_x + 8,
        up_left_y - 12,
        64,
        16,
        WHITE);
    DrawRectangleLines(up_left_x + 8,
        up_left_y - 12,
        64,
        16,
        BLACK);
    DrawTextCentral(label,up_left_x + 40, up_left_y - 10, 12, BLACK);
    
    DrawTetrominoOnWhiteCentered(up_left_x + 6, up_left_y + 8, tetromino_shape);
}


void PrintTetronimo(Tetromino *t){
    printf("{x: %d | y: %d | shape: %d | rotation: %d \n",
        t->x,
        t->y,
        t->shape,
        t->rotation);

    for(int i = 0; i < 8; i+= 2)
    {
        printf("[%i,%i]\n", t->current_shape[i], t->current_shape[i+1]);
    }
}
