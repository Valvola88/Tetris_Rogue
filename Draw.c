#include "Tetris.h"

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
void DrawTextCentral(char* str, int x,  int y, int font_size, Color color)
{
    const int len = strlen(str);
    const int text_size = MeasureText(str,font_size);

    int start_x = x - (text_size / 2);

    DrawText(str, start_x, y, font_size, color);
}

void DrawTetromino(
    const int start_x,
    const int start_y,
    const int *tetronimo,
    const Color c)
{
    for (int i = 0; i < 8; i +=2)
    {
        DrawRectangle(
            (start_x + tetronimo[i]) * TILE_SIZE + START_OFFSET_X,
            (start_y + tetronimo[i + 1]) * TILE_SIZE + START_OFFSET_Y,
            TILE_SIZE,
            TILE_SIZE,
            c
        );
    }
}

void DrawTetromino2(Tetronimo *tetronimo)
{
    DrawTetromino(
        tetronimo->x,
        tetronimo->y,
        tetronimo->current_shape,
        tetronimo->color
    );
}

void PrintTetronimo(Tetronimo *t){
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
