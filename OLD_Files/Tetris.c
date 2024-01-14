#include "raylib.h"
#include "time.h"

#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22
#define TILE_SIZE 16
#define TETRONIMO_SIZE 4

int stage[] = 
{
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

#pragma region //L PIECE
const int tetronimo_L_0 [] =
{
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
};

const int tetronimo_L_90 [] =
{
    0, 0, 0, 0,
    1, 1, 1, 0,
    1, 0, 0, 0,
    0, 0, 0, 0
};
const int tetronimo_L_180 [] =
{
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
};
const int tetronimo_L_270 [] =
{
    0, 0, 1, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};
#pragma endregion

#pragma region //J PIECE
int tetronimo_J_0 [] =
{
    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
};
int tetronimo_J_90 [] =
{
    0, 1, 0, 0,
    0, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
};
int tetronimo_J_180 [] =
{
    0, 0, 1, 1,
    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0
};
int tetronimo_J_270 [] =
{
    0, 0, 0, 0,
    0, 1, 1, 1,
    0, 0, 0, 1,
    0, 0, 0, 0
};
#pragma endregion

#pragma region //S PIECE
int tetronimo_S_0 [] =
{
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0
};
int tetronimo_S_90 [] =
{
    0, 0, 0, 0,
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0
};
int tetronimo_S_180 [] =
{
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
};
int tetronimo_S_270 [] =
{
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};
#pragma endregion

#pragma region //Z PIECE
int tetronimo_Z_0 [] =
{
    0, 0, 1, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
};
int tetronimo_Z_90 [] =
{
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 1,
    0, 0, 0, 0
};
int tetronimo_Z_180 [] =
{
    0, 0, 1, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
};
int tetronimo_Z_270 [] =
{
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 1,
    0, 0, 0, 0
};
#pragma endregion

#pragma region //O PIECE
int tetronimo_O_0 [] =
{
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
};
int tetronimo_O_90 [] =
{
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
};
int tetronimo_O_180 [] =
{
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
};
int tetronimo_O_270 [] =
{
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
};
#pragma endregion

#pragma region //T PIECE
int tetronimo_T_0 [] =
{
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
};
int tetronimo_T_90 [] =
{
    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
};
int tetronimo_T_180 [] =
{
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
};
int tetronimo_T_270 [] =
{
    0, 1, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};
#pragma endregion

#pragma region //I PIECE
int tetronimo_I_0 [] =
{
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0
};
int tetronimo_I_90 [] =
{
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
};
int tetronimo_I_180 [] =
{
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0
};
int tetronimo_I_270 [] =
{
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
};
#pragma endregion


const int *tetronimo_types[7][4] =
{
    {tetronimo_L_0, tetronimo_L_90, tetronimo_L_180, tetronimo_L_270},
    {tetronimo_J_0, tetronimo_J_90, tetronimo_J_180, tetronimo_J_270},
    {tetronimo_S_0, tetronimo_S_90, tetronimo_S_180, tetronimo_S_270},
    {tetronimo_Z_0, tetronimo_Z_90, tetronimo_Z_180, tetronimo_Z_270},
    {tetronimo_O_0, tetronimo_O_90, tetronimo_O_180, tetronimo_O_270},
    {tetronimo_T_0, tetronimo_T_90, tetronimo_T_180, tetronimo_T_270},
    {tetronimo_I_0, tetronimo_I_90, tetronimo_I_180, tetronimo_I_270}
};

void DrawTetromino(
    const int start_offset_x,
    const int start_offset_y,
    const int start_x_pos,
    const int start_y_pos,
    const int *tetronimo)
{
    
        for(int y = 0; y < TETRONIMO_SIZE; y++)
        {
            for(int x = 0; x < TETRONIMO_SIZE; x++)
            {
                const int offset = y * TETRONIMO_SIZE + x;

                if(tetronimo[offset] == 1)
                {
                    DrawRectangle(
                        (start_x_pos + x) * TILE_SIZE + start_offset_x,
                        (start_y_pos + y) * TILE_SIZE + start_offset_y,
                        TILE_SIZE,
                        TILE_SIZE,
                        BLUE);
                }
            }
        }
}

int main(int argc, char** argv, char** environ)
{
    #pragma region 
    // TraceLog(LOG_INFO, "Number of arguments : %d", argc);

    // for(int i = 0; i < argc; i++)
    // {
    //     TraceLog(LOG_INFO, "Argument : %d = %s", i, argv[i]);
    // }

    // while(*environ != 0)
    // {
    //     TraceLog(LOG_INFO, "Argument : %s", *environ);
    //     environ++;
    // }
    #pragma endregion

    const int windowWidth = 512;
    const int windowHeight = 512;
    const int startOffSetX = ((windowWidth / 2) - (STAGE_WIDTH / 2 * TILE_SIZE));
    const int startOffSetY = ((windowHeight / 2) - (STAGE_HEIGHT / 2 * TILE_SIZE));
    const int startPosX = STAGE_WIDTH / 2;
    const int startPosY = 0;
    const float moveTileDownTimer = 1.f;

    int currentPosY = startPosY;
    int currentPosX = startPosX;
    float timeToMoveDown = moveTileDownTimer;

    time_t unixTime;
    time(&unixTime);

    SetRandomSeed(unixTime);
    int currentTetrominoSize = GetRandomValue(0,6);
    int currentTetrominoRotation = 0;

    InitWindow(windowWidth, windowHeight, "Title");

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        timeToMoveDown -= GetFrameTime();
        if (IsKeyPressed(KEY_E))
        {
            currentTetrominoRotation = currentTetrominoRotation == 3 ? 0 : currentTetrominoRotation + 1;            
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            currentPosX++;
        }

        if (IsKeyPressed(KEY_LEFT))
        {
            currentPosX--;
        }

        if(timeToMoveDown <= 0 || IsKeyPressed(KEY_DOWN))
        {
            const int belowOfTetromino = (currentPosY + 1) * STAGE_WIDTH + currentPosX;
            if(stage[belowOfTetromino] == 0)
            {
                currentPosY ++;
                timeToMoveDown = moveTileDownTimer;
            }
            else
            {
                const int currentTetrominoPosition = currentPosY * STAGE_WIDTH + currentPosX;
                stage[currentTetrominoPosition] = 1;
                currentPosY = startPosY;
            }
        }

        BeginDrawing();
        ClearBackground(RED);

        #pragma region //Draw Scenario
        for(int y = 0; y < STAGE_HEIGHT; y++)
        {
            for(int x = 0; x < STAGE_WIDTH; x++)
            {
                const int offset = y * STAGE_WIDTH + x;

                if(stage[offset] == 1)
                {
                    DrawRectangle(x * TILE_SIZE + startOffSetX, y * TILE_SIZE + startOffSetY, TILE_SIZE, TILE_SIZE, WHITE);
                }
                DrawRectangleLines(x * TILE_SIZE + startOffSetX, y * TILE_SIZE + startOffSetY, TILE_SIZE, TILE_SIZE, BLACK);
            }
        }
        #pragma endregion
        
        
        //DrawRectangle(startPosX * TILE_SIZE + startOffSetX, currentPosY * TILE_SIZE + startOffSetY, TILE_SIZE, TILE_SIZE, GREEN);
        DrawTetromino(
            startOffSetX,
            startOffSetY,
            currentPosX,
            currentPosY,
            tetronimo_types[currentTetrominoSize][currentTetrominoRotation]
        );
        EndDrawing();
    }

    return 0;
}