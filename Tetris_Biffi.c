#include "Tetris.h"


#define WINDOW_HEIGHT 512
#define WINDOW_WIDTH 512
#define START_POS_Y 1
#define START_MOVE_TILE_DOWN_TIMER 1.f
#define START_MOVE_TIME_HOLD_TIMER .5f
#define MOVE_HOLD_DOWN_DELAY .1f
#define VISIBLE_PIECES 5
#define START_OFFSET_X (WINDOW_WIDTH / 2) - (STAGE_WIDTH / 2 * TILE_SIZE);
#define START_OFFSET_Y (WINDOW_WIDTH / 2) - (STAGE_HEIGHT / 2 * TILE_SIZE);



void EmptyBegin(){}

#pragma region Variable Init
const int windowWidth = WINDOW_WIDTH;
const int windowHeight = WINDOW_HEIGHT;
const int startOffSetX = START_OFFSET_X;
const int startOffSetY = START_OFFSET_Y;
const int startPosX = STAGE_WIDTH / 2;
const int startPosY = 1;
const float startMoveTileDownTimer = 1.f;
const float startMoveTimeHoldTime = .5f;
const float moveDownHoldDelay= .1f;
const int visiblePieces = 5;

int currentPosY;
int currentPosX;

float currentMoveTileDownTimer;
float timeToMoveDown;
float currentMoveTimeHoldTime;
float timeToMoveDownHold;

int currentTetrominoType;
int currentTetrominoRotation;
Color currentPieceColor;

int holdTetrominoType;
int alreadySwappedOnce;

int closeGame;
int spawnNewTetronimo;

int score;
char str_score[8];
int lines_deleted;
char str_lines_deleted[4];
int tetris_scored;
char str_tetris_scored[4];
int max_score = 0;
char str_max_score[8];


int stage[STAGE_DIMENSION];
int level;
int next_level_up;
int visible_level;

char str_visible_level[4];
float speed;
char str_speed[9];

int nextPieces[VISIBLE_PIECES + 1];

int preview_y;

float speed;

int lines_to_delete[4];

float deleteEffectTimer = 1.f;
float currentDeleteEffectTimer;
struct game_loop current_game_loop;

float multiplier = 1.0f;
int pice_in_a_row = 0;

#pragma endregion


typedef struct Str_Tetronimo Tetronimo;

struct Str_Tetronimo{
    int shape;
    int rotation;
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


void EmptyDraw(){}


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

int DeleteLines()
{
    int deleted_lines = 0;
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
            //memset(stage + offset,0,(STAGE_WIDTH - 2) * sizeof(int));
            lines_to_delete[deleted_lines] = y;

            deleted_lines++;
        }
    }

    return deleted_lines;
}

void FormatScore(char* score_array, int score)
{
    char* score_char;
    sprintf(score_char, "%d", score);

    int len = strlen(score_char);
    char *address = &score_array[8 - len];
    memset(score_array, '0', 9);
    strcpy_s(address, sizeof(char) * len,score_char);

}

void UpdateStrings()
{
    printf("Score: %i", score);
    const int tmp_score = score;
    memset(str_score, '0', 8);
    char score_char[8];
    sprintf(score_char, "%i", tmp_score);
    //printf("Score_2: %d ", score);
    sprintf(&str_score[8 - strlen(score_char)], "%s", score_char);

    sprintf(str_visible_level, "%i", visible_level);
    sprintf(str_lines_deleted, "%i", lines_deleted);
    sprintf(str_tetris_scored, "%i", tetris_scored);
    sprintf(str_speed, "%f", speed);
}

void MainBeginPlay()
{
    current_game_loop.tick = MainTick;
    current_game_loop.draw = MainDraw;

    currentPosY = startPosY;
    currentPosX = startPosX;
    currentMoveTileDownTimer = startMoveTileDownTimer;
    timeToMoveDown = currentMoveTileDownTimer;
    currentMoveTimeHoldTime = startMoveTimeHoldTime;
    timeToMoveDownHold = currentMoveTileDownTimer;

    time_t unixTime;
    time(&unixTime);

    SetRandomSeed(unixTime);
    currentTetrominoType = GetRandomValue(0,6);
    currentPieceColor = colorTypes[currentTetrominoType + 1];

    currentTetrominoRotation = 0;

    holdTetrominoType = -1;
    alreadySwappedOnce = 0;

    closeGame = 0;
    spawnNewTetronimo = 0;

    score = 0;
    lines_deleted = 0;
    tetris_scored = 0;
    level = 0;
    next_level_up = 1000;
    speed = .0f;

    memset(str_lines_deleted,'0',4);
    memset(str_tetris_scored,'0',4);
    memset(str_visible_level,'0',4);

    for(int i = 0; i <= VISIBLE_PIECES;i++)
    {
        nextPieces[i] =GetRandomValue(0,6);
    }

    memcpy(stage, reset_stage, STAGE_DIMENSION * 4);

    UpdateStrings();

    preview_y = 0;
    
    current_game_loop.begin_play = EmptyBegin;
}

void UpdateScore(int add)
{
    score += add * multiplier;
}

void MainTick(const float delta_time)
{
        if (!alreadySwappedOnce && IsKeyPressed(KEY_SPACE))
        {
            alreadySwappedOnce = 1;
            TetrisPlaySfx(SFX_HOLD);

            if (holdTetrominoType == -1)
            {
                holdTetrominoType = currentTetrominoType;

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
                for(int i = 5; i>0;i--)
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


        timeToMoveDown -= delta_time;
        if (IsKeyPressed(KEY_E))
        {
            int nextTetronimoRotation = currentTetrominoRotation == 3 ? 0 : currentTetrominoRotation + 1;
            if (!CheckRotateCollision(
                currentPosX,
                currentPosY,
                tetromino_types[currentTetrominoType][nextTetronimoRotation]
            ))
            {
                currentTetrominoRotation = nextTetronimoRotation;            
                TetrisPlaySfx(SFX_ROTATE);
            }
        }
        
        if (IsKeyPressed(KEY_Q))
        {
            int nextTetronimoRotation = currentTetrominoRotation == 0 ? 3 : currentTetrominoRotation - 1;
            if (!CheckRotateCollision(
                currentPosX,
                currentPosY,
                tetromino_types[currentTetrominoType][nextTetronimoRotation]
            )){
                currentTetrominoRotation = nextTetronimoRotation;            
                TetrisPlaySfx(SFX_ROTATE);
            }
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            if (!CheckSideCollision(
                currentPosX,
                currentPosY,
                1,
                tetromino_types[currentTetrominoType][currentTetrominoRotation]))
                {
                currentPosX++;
                TetrisPlaySfx(SFX_MOVE);
                }
        }

        if (IsKeyPressed(KEY_LEFT))
        {            
            if (!CheckSideCollision(
                currentPosX,
                currentPosY,
                -1,
                tetromino_types[currentTetrominoType][currentTetrominoRotation]))
                {
                    TetrisPlaySfx(SFX_MOVE);
                    currentPosX--;
                }
        }

        if(IsKeyPressed(KEY_UP))
        {
            while (!CheckDownCollision(currentPosX, currentPosY, tetromino_types[currentTetrominoType][currentTetrominoRotation]))
            {
                currentPosY++;
                timeToMoveDown = currentMoveTileDownTimer;
            }

            TetrisPlaySfx(SFX_HARDLAND);
            spawnNewTetronimo= 1;
        }

        if(IsKeyDown(KEY_DOWN))
        {
            timeToMoveDownHold -= delta_time;
        }

        if(IsKeyReleased(KEY_DOWN))
        {
            currentMoveTimeHoldTime = startMoveTimeHoldTime;
        }

        if(timeToMoveDown <= 0 || IsKeyPressed(KEY_DOWN) ||  timeToMoveDownHold <= 0)
        {
            if (timeToMoveDownHold <= 0)
            {
                currentMoveTimeHoldTime -= moveDownHoldDelay;

                if (currentMoveTimeHoldTime < moveDownHoldDelay)
                    currentMoveTimeHoldTime = moveDownHoldDelay;
            }

            if (!CheckDownCollision(currentPosX, currentPosY, tetromino_types[currentTetrominoType][currentTetrominoRotation]))
            {
                currentPosY++;
                TetrisPlaySfx(SFX_MOVE);
            }
            else
            {
                spawnNewTetronimo = 1;
                TetrisPlaySfx(SFX_LAND);
            }
            timeToMoveDown = currentMoveTileDownTimer;
            timeToMoveDownHold = currentMoveTimeHoldTime;
        }
        
        if(spawnNewTetronimo)
        {
            spawnNewTetronimo = 0;

            int resetMultiplier = 1;

            const int *currTetronimo = tetromino_types[currentTetrominoType][currentTetrominoRotation];
            for (int i = 0; i < 8 ; i += 2){
                const int cellToPlace = (currentPosY + currTetronimo[i + 1]) * STAGE_WIDTH + currentPosX + currTetronimo[i];
                stage[cellToPlace] = currentTetrominoType + 1;
            }

            const int current_line_deleted = DeleteLines();

            if (current_line_deleted){

                resetMultiplier = 0;

                lines_deleted += current_line_deleted;

                if (current_line_deleted == 4)
                {
                    tetris_scored += 1;
                    UpdateScore(1000);
                    TetrisPlaySfx(SFX_TETRIS);

                    multiplier += .5f;
                    // sprintf(str_tetris_scored, "%i", tetris_scored);
                }
                else
                {

                    UpdateScore(current_line_deleted * 100);
                    TetrisPlaySfx(SFX_SINGLE);

                    multiplier += .1f;
                }

                
                visible_level = 1 + (score / 1000);

                if (score >= next_level_up)
                {
                    next_level_up += 1000;
                    TetrisPlaySfx(SFX_LVLUP);
                }

                speed = visible_level / 10.0f;
                if (speed > 1.4f)
                    speed = 1.4f;

                currentMoveTileDownTimer = startMoveTileDownTimer - speed;

                current_game_loop.tick = MainDeleteEffectTick;

                UpdateStrings();
            }

            alreadySwappedOnce = 0;
            currentPosY = startPosY;
            currentPosX = startPosX;
            
            currentTetrominoType = nextPieces[0];

            for(int i = 1; i<6;i++)
            {
                nextPieces[i-1] = nextPieces[i];
            }
            
            if (CheckRotateCollision(
                currentPosX,
                currentPosY,
                tetromino_types[currentTetrominoType][0]
                ))
                {
                    current_game_loop.tick = WaitForSpaceTick;
                    current_game_loop.post_draw = MainOverlayDraw;
                    //closeGame = 1;
                }

            
            nextPieces[5] = GetRandomValue(0,6);

            currentTetrominoRotation = 0;
            currentPieceColor = colorTypes[currentTetrominoType + 1];

            if(resetMultiplier)
                multiplier = 1.0f;

            printf("Multiplier: %f\n", multiplier);
        }
}

void MainDraw()
{

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
            


        //Current Piece
        DrawTetromino(
            startOffSetX,
            startOffSetY,
            currentPosX,
            currentPosY,
            tetromino_types[currentTetrominoType][currentTetrominoRotation],
            currentPieceColor
        );

        //Preview Piece
        preview_y = GetLowestPiecePosition(currentPosX,currentPosY,tetromino_types[currentTetrominoType][currentTetrominoRotation]);
        DrawTetromino(
            startOffSetX,
            startOffSetY,
            currentPosX,
            preview_y,
            tetromino_types[currentTetrominoType][currentTetrominoRotation],
            colorTypes[8]
        );

        #pragma region other_pieces

        


        //Hold Piece
        if (holdTetrominoType>= 0)
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

        //Next Pieces
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

        #pragma endregion

        //TEXT and Test Text
        //FormatScore(score_array, score);

        DrawText(str_score, 32, 320, 20, WHITE);
        DrawText(str_visible_level, 32, 360, 20, WHITE);
        DrawText(str_lines_deleted, 32, 400, 20, WHITE);
        DrawText(str_tetris_scored, 32, 440, 20, WHITE);
        DrawText(str_speed, 32, 480, 20, WHITE);
}

void MainDeleteEffectTick(const float delta_time)
{
    currentDeleteEffectTimer -= delta_time;

    if (currentDeleteEffectTimer <= 0)
    {
        for(int i = 0; i< 4; i++)
        {
            if (lines_to_delete[i] == -1)
                continue;
            
            CopyAllLineAbove(lines_to_delete[i]);
            lines_to_delete[i] = -1;
            
        }

        currentDeleteEffectTimer = deleteEffectTimer;
        current_game_loop.tick = MainTick;
    }

    int deletedLineCounter = 0;
    int squareToChange =  (10 - currentDeleteEffectTimer / .1);


    while(lines_to_delete[deletedLineCounter] > 0 && deletedLineCounter < 4)
    {
        const int offset = lines_to_delete[deletedLineCounter] * STAGE_WIDTH + 1;
        stage[offset + squareToChange] = 8;
        deletedLineCounter++;
    }
}

void MainOverlayDraw()
{
    DrawRectangle(64,64,384, 128, WHITE);

    DrawTextCentral("GAME OVER", 256,100,32,BLACK);
    DrawTextCentral(str_score, 256,140,32,BLACK);
}

void WaitForSpaceTick(const float delta_time)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        current_game_loop.begin_play = MainMenuBeginPlay;
        current_game_loop.post_draw = EmptyDraw;
        if (score > max_score)
        {
            max_score = score;
        }
    }
}

int main(int argc, char** argv)
{
    InitWindow(windowWidth, windowHeight, "Title");

    TetrisLoadMusic();

    SetTargetFPS(60);
    current_game_loop.begin_play = MainMenuBeginPlay;
    

    currentDeleteEffectTimer = 1.f;

    lines_to_delete[0] = -1;
    lines_to_delete[1] = -1;
    lines_to_delete[2] = -1;
    lines_to_delete[3] = -1;

    while(!WindowShouldClose() && (closeGame == 0))
    {
        TetrisLoopBgMusic();
        current_game_loop.begin_play();


        current_game_loop.tick(GetFrameTime());
        
        BeginDrawing();
        ClearBackground(GRAY);
        current_game_loop.draw();
        current_game_loop.post_draw();
        EndDrawing();
    }
    
    TetrisUnloadMusic();
    return 0;
}