#include "raylib.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "Tetris.h"

int stage[] = 
{
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
};

#pragma region //L PIECE
const int tetronimo_L_0 [] =
{
     0,  0,
     0, -1,
     0,  1,
     1,  1
};
const int tetronimo_L_90 [] =
{
     0,  0,
     1,  0,
    -1,  0,
    -1,  1
};
const int tetronimo_L_180 [] =
{
     0,   0,
     0,   1,
     0,  -1,
    -1,  -1
};
const int tetronimo_L_270 [] =
{
      0,  0,
     -1,  0,
      1,  0,
      1, -1
};
#pragma endregion

#pragma region //J PIECE
int tetronimo_J_0 [] =
{
      0,  0,
      0, -1,
      0,  1,
     -1,  1
};
int tetronimo_J_90 [] =
{
     0,  0,
     1,  0,
    -1,  0,
     1,  1
};
int tetronimo_J_180 [] =
{
     0,   0,
     0,   1,
     0,  -1,
     1,  -1
};
int tetronimo_J_270 [] =
{
      0,  0,
     -1,  0,
      1,  0,
     -1, -1
};
#pragma endregion

#pragma region //S PIECE
int tetronimo_S_0 [] =
{
      0,  0,
      0, -1,
      1,  -1,
      -1,  0
};
int tetronimo_S_90 [] =
{
      0,  0,
      1,  0,
      1,  1,
     0,  -1
};
int tetronimo_S_180 [] =
{
      0,  0,
      0,  1,
      -1,  1,
      1,  0
};
int tetronimo_S_270 [] =
{
      0,  0,
      -1,  0,
      -1,  -1,
      0,  1
};
#pragma endregion

#pragma region //Z PIECE
int tetronimo_Z_0 [] =
{
      0,  0,
      0, -1,
      -1,  -1,
      1,  0
};
int tetronimo_Z_90 [] =
{
      0,  0,
     -1,  0,
      -1,  1,
     0,  -1
};
int tetronimo_Z_180 [] =
{
      0,  0,
      0,  1,
      1,  1,
      -1,  0
};
int tetronimo_Z_270 [] =
{
      0,  0,
      1,  0,
      1,  -1,
      0,  1
};
#pragma endregion

#pragma region //O PIECE
int tetronimo_O_0 [] =
{
    0, 0,
    0, 1,
    1, 0,
    1, 1
};
int tetronimo_O_90 [] =
{
    0, 0,
    0, 1,
    1, 0,
    1, 1
};
int tetronimo_O_180 [] =
{
    0, 0,
    0, 1,
    1, 0,
    1, 1
};
int tetronimo_O_270 [] =
{
    0, 0,
    0, 1,
    1, 0,
    1, 1
};
#pragma endregion

#pragma region //T PIECE
int tetronimo_T_0 [] =
{
    0,  0,
    0, -1,
    1,  0,
    0,  1
};
int tetronimo_T_90 [] =
{
    0,  0,
    -1, 0,
    0,  -1,
    1,  0
};
int tetronimo_T_180 [] =
{
    0,  0,
    0, -1,
    -1,  0,
    0,  1
};
int tetronimo_T_270 [] =
{
    0,  0,
    -1, 0,
    0,  1,
    1,  0
};
#pragma endregion

#pragma region //I PIECE
int tetronimo_I_0 [] =
{
    0,  0,
    0, -2,
    0, -1,
    0,  1
};
int tetronimo_I_90 [] =
{
    0,  0,
    -2, 0,
    -1, 0,
    1,  0
};
int tetronimo_I_180 [] =
{
    0,  0,
    0, -2,
    0, -1,
    0,  1
};
int tetronimo_I_270 [] =
{
    0,  0,
    -2, 0,
    -1, 0,
    1,  0
};
#pragma endregion

typedef struct Str_Tetronimo Tetronimo;

struct Str_Tetronimo{
    int *pieces;
    int rotation;
};


const int *tetromino_types[7][4] =
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
    const int *tetronimo,
    const Color c)
{
    for (int i = 0; i < 8; i +=2)
    {
        DrawRectangle(
            (start_x_pos + tetronimo[i]) * TILE_SIZE + start_offset_x,
            (start_y_pos + tetronimo[i + 1]) * TILE_SIZE + start_offset_y,
            TILE_SIZE,
            TILE_SIZE,
            c
        );
    }
}


const Color colorTypes[9] =
{
    {0,0,0,0},
    {255,161,0,255},
    {0,121,241,255},
    {0,158,47,255},
    {230,41,55,255},
    {235,249,0,255},
    {200,122,255,255},
    {102,199,255,255},
    {255,255,255,255}
};

void CopyAllLineAbove(int start_y)
{
    for(int y = start_y; y> 0; y--)
    {
        for(int x = 1; x < STAGE_WIDTH -1; x++)
        {
            int offset = y * STAGE_WIDTH + x;
            int offsetAbove = (y - 1) * STAGE_WIDTH + x;

            stage[offset] = stage[offsetAbove];

        }
    }

    for(int x = 1; x< STAGE_WIDTH - 1; x++)
    {
        stage[x] = 0;
    }
}

void DeleteLines()
{
    for (int y = 0; y< STAGE_HEIGHT - 1;y++)
    {
        int checkLine = 1;
        for (int x = 1; x< STAGE_WIDTH - 1; x++)
        {
            const int offset = y * STAGE_WIDTH + x;

            if(stage[offset] == 0)
            {
                checkLine = 0;
                break;
            }
        }

        if (checkLine)
        {
            const int offset = y * STAGE_WIDTH + 1;
            memset(stage + offset,0,(STAGE_WIDTH - 2) * sizeof(int));
            CopyAllLineAbove(y);
        }
    }
}


int main(int argc, char** argv)
{
    const int windowWidth = 512;
    const int windowHeight = 512;
    const int startOffSetX = ((windowWidth / 2) - (STAGE_WIDTH / 2 * TILE_SIZE));
    const int startOffSetY = ((windowHeight / 2) - (STAGE_HEIGHT / 2 * TILE_SIZE));
    const int startPosX = STAGE_WIDTH / 2;
    const int startPosY = 0;
    const float moveTileDownTimer = 1.f;
    const int visiblePieces = 5;

    int currentPosY = startPosY;
    int currentPosX = startPosX;
    float timeToMoveDown = moveTileDownTimer;

    time_t unixTime;
    time(&unixTime);

    SetRandomSeed(unixTime);
    int currentTetrominoType = GetRandomValue(0,6);
    int currentTetrominoRotation = 0;
    Color currentPieceColor = colorTypes[currentTetrominoType + 1];

    int holdTetrominoType = -1;
    int alreadySwappedOnce = 0;

    int nextPieces[6] = 
    {
        GetRandomValue(0,6),
        GetRandomValue(0,6),
        GetRandomValue(0,6),
        GetRandomValue(0,6),
        GetRandomValue(0,6),
        GetRandomValue(0,6)
    };


    InitWindow(windowWidth, windowHeight, "Title");

    InitAudioDevice();

    Music bg_music = LoadMusicStream("bg_music.mp3");
    PlayMusicStream(bg_music);


    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        if (!IsMusicStreamPlaying(bg_music))
        {
            StopMusicStream(bg_music);
            PlayMusicStream(bg_music);
        }

        UpdateMusicStream(bg_music);

        if (!alreadySwappedOnce && IsKeyPressed(KEY_SPACE))
        {
            if (holdTetrominoType < 0)
            {
                holdTetrominoType = currentTetrominoType;
                alreadySwappedOnce = 1;

                currentPosY = startPosY;
                currentPosX = startPosX;
                // SetRandomSeed(unixTime);

                currentTetrominoType = nextPieces[0];

                for(int i = 1; i<6;i++)
                {
                    nextPieces[i-1] = nextPieces[i];
                }

                nextPieces[5] = GetRandomValue(0,6);
                currentTetrominoRotation = 0;
                currentPieceColor = colorTypes[currentTetrominoType + 1];
            }

            else
            {
                alreadySwappedOnce = 1;
                for(int i = 6; i>0;i--)
                {
                    nextPieces[i] = nextPieces[i-1];
                }

                nextPieces[0] = currentTetrominoType;

                currentTetrominoType = holdTetrominoType;
                holdTetrominoType = -1;

                currentPosY = startPosY;
                currentPosX = startPosX;
                // SetRandomSeed(unixTime);
                currentTetrominoRotation = 0;
                currentPieceColor = colorTypes[currentTetrominoType + 1];                
            }

        }


        timeToMoveDown -= GetFrameTime();
        if (IsKeyPressed(KEY_E))
        {
            int nextTetronimoRotation = currentTetrominoRotation == 3 ? 0 : currentTetrominoRotation + 1;
            if (!CheckRotateCollision(
                currentPosX,
                currentPosY,
                tetromino_types[currentTetrominoType][nextTetronimoRotation]
            ))
                currentTetrominoRotation = nextTetronimoRotation;            
        }
        
        if (IsKeyPressed(KEY_Q))
        {
            int nextTetronimoRotation = currentTetrominoRotation == 0 ? 3 : currentTetrominoRotation - 1;
            if (!CheckRotateCollision(
                currentPosX,
                currentPosY,
                tetromino_types[currentTetrominoType][nextTetronimoRotation]
            ))
                currentTetrominoRotation = nextTetronimoRotation;            
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            if (!CheckSideCollision(
                currentPosX,
                currentPosY,
                1,
                tetromino_types[currentTetrominoType][currentTetrominoRotation]))
                currentPosX++;
        }

        if (IsKeyPressed(KEY_LEFT))
        {            
            if (!CheckSideCollision(
                currentPosX,
                currentPosY,
                -1,
                tetromino_types[currentTetrominoType][currentTetrominoRotation]))
                currentPosX--;
        }

        if(IsKeyPressed(KEY_UP))
        {
            while (!CheckDownCollision(currentPosX, currentPosY, tetromino_types[currentTetrominoType][currentTetrominoRotation]))
            {
                currentPosY++;
                timeToMoveDown = moveTileDownTimer;
            }

            const int *currTetronimo = tetromino_types[currentTetrominoType][currentTetrominoRotation];
            for (int i = 0; i < 8 ; i += 2){
                const int cellToPlace = (currentPosY + currTetronimo[i + 1]) * STAGE_WIDTH + currentPosX + currTetronimo[i];
                stage[cellToPlace] = currentTetrominoType + 1;
            }

            DeleteLines();
            alreadySwappedOnce = 0;
            currentPosY = startPosY;
            currentPosX = startPosX;
            // SetRandomSeed(unixTime);
            
            currentTetrominoType = nextPieces[0];

            for(int i = 1; i<6;i++)
            {
                nextPieces[i-1] = nextPieces[i];
            }

            nextPieces[5] = GetRandomValue(0,6);


            currentTetrominoRotation = 0;
            currentPieceColor = colorTypes[currentTetrominoType + 1];
        }

        if(timeToMoveDown <= 0 || IsKeyPressed(KEY_DOWN))
        {
            if (!CheckDownCollision(currentPosX, currentPosY, tetromino_types[currentTetrominoType][currentTetrominoRotation]))
            {
                currentPosY++;
                timeToMoveDown = moveTileDownTimer;
            }
            else
            {
                const int *currTetronimo = tetromino_types[currentTetrominoType][currentTetrominoRotation];
                for (int i = 0; i < 8 ; i += 2){
                    const int cellToPlace = (currentPosY + currTetronimo[i + 1]) * STAGE_WIDTH + currentPosX + currTetronimo[i];
                    stage[cellToPlace] = currentTetrominoType + 1;
                }

                DeleteLines();
                alreadySwappedOnce = 0;
                currentPosY = startPosY;
                currentPosX = startPosX;
                // SetRandomSeed(unixTime);
                
                currentTetrominoType = nextPieces[0];

                for(int i = 1; i<6;i++)
                {
                    nextPieces[i-1] = nextPieces[i];
                }

                nextPieces[5] = GetRandomValue(0,6);


                currentTetrominoRotation = 0;
                currentPieceColor = colorTypes[currentTetrominoType + 1];
            }
        }
        



        BeginDrawing();
        ClearBackground(GRAY);

        #pragma region //Draw Scenario
        for(int y = 0; y < STAGE_HEIGHT; y++)
        {
            for(int x = 0; x < STAGE_WIDTH; x++)
            {
                const int offset = y * STAGE_WIDTH + x;

                if(stage[offset] != 0)
                {
                    Color c = colorTypes[stage[offset]];
                    DrawRectangle(x * TILE_SIZE + startOffSetX, y * TILE_SIZE + startOffSetY, TILE_SIZE, TILE_SIZE, c);
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
            tetromino_types[currentTetrominoType][currentTetrominoRotation],
            currentPieceColor
        );

        if (holdTetrominoType> 0)
        {
            DrawTetromino(
            64,
            64,
            0,
            0,
            tetromino_types[holdTetrominoType][0],
            colorTypes[holdTetrominoType + 1]
        );
        }

        for(int i = 0; i < 5; i++)
        {
            int nextTetronimo = nextPieces[i];
            DrawTetromino(
            512 - 64,
            100 + 64 * i,
            0,
            0,
            tetromino_types[nextTetronimo][0],
            colorTypes[nextTetronimo + 1]);
        }
        EndDrawing();
    }
    
    UnloadMusicStream(bg_music);   // Unload music stream buffers from RAM
    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)
    return 0;
}