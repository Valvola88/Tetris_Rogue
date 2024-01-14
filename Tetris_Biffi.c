#include "Tetris.h"

void EmptyBegin(){}
void EmptyDraw(){}

#pragma region Variable Init

const int windowWidth = WINDOW_WIDTH;
const int windowHeight = WINDOW_HEIGHT;
const int startOffSetX = START_OFFSET_X;
const int startOffSetY = START_OFFSET_Y;
const int startPosX = STAGE_WIDTH / 2;
const int startPosY = 1;
const float startMoveTileDownTimer = 1.f;
const float startMoveTimeHoldTime = .25f;
const float moveDownHoldDelay= .1f;
const int visiblePieces = 5;

float currentMoveTileDownTimer;
float timeToMoveDown;
float currentMoveTimeHoldTime;
float timeToMoveDownHold;

int holdTetrominoType;
int alreadySwappedOnce;

int closeGame;
int hasToSpawnNewTetronimo;
int destroyCurrentTetronimo = 0;

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

Tile movablePowerUpTile;
Tile powerUpsTile[10];

char str_multiplier[9];
char real_str_multiplier[4];

Tetronimo mainTetronimo;

int oldDeletedSquare = -1;
int showRewardBox = 0;


#pragma endregion

#pragma region utils
int GetXPositionFromCellX(int x)
{
    return startOffSetX + TILE_SIZE * x; 
}

int GetYPositionFromCellY(int y)
{
    return startOffSetY + TILE_SIZE * y;
}

void SetTetronimoRotation(Tetronimo *tetro, const int rotation)
{
    tetro->rotation = rotation;
    tetro->current_shape = (int *)tetronimo_types[tetro->shape][rotation];
}

int SetTetronimoShape(Tetronimo *tetro, const int shape)
{
    if (!tetro) return 0;

    printf("X: %d, Y: %d", tetro->x, tetro->y);

    if (CheckRotateCollision(tetro->x, tetro->y, tetronimo_types[shape][tetro->rotation]))
        return 0;

    tetro->shape = shape;
    tetro->color = colorTypes[shape + 1];

    tetro->current_shape = (int *)tetronimo_types[tetro->shape][tetro->rotation];

    return 1;
}

void SpawnNewTetronimo(Tetronimo *tetro, const int shape)
{
    movablePowerUpTile.my_color = BLACK;

    tetro->x = startPosX;
    tetro->y = startPosY;

    SetTetronimoShape(tetro, shape);
    SetTetronimoRotation(tetro, 0);

    tetro->powerUpTile = -1;//GetRandomValue(0,4);
}

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

void UpdateStrings()
{
    const int tmp_score = score;
    memset(str_score, '0', 8);
    char score_char[8];
    sprintf(score_char, "%i", tmp_score);
    sprintf(&str_score[8 - strlen(score_char)], "%s", score_char);

    //sprintf(str_visible_level, "%i", visible_level);
    sprintf(str_lines_deleted, "%i", lines_deleted);
    sprintf(str_tetris_scored, "%i", tetris_scored);

}

void UpdateScore(int add)
{
    score += add * multiplier;
}

int CreateBlockUnder(int position)
{
    for(int iy = 0; iy < STAGE_HEIGHT - 2; iy++)
    {
        for(int ix = 1; ix < STAGE_WIDTH -1; ix++)
        {
            int offset = iy * STAGE_WIDTH + ix;

            stage[offset] = stage[offset + STAGE_WIDTH];
        }
    }

    for(int ix = 1; ix < STAGE_WIDTH - 1; ix++)
    {
        int offset = (STAGE_HEIGHT - 2) * STAGE_WIDTH + ix;
        if (ix == position)
        {
            stage[offset] = 0;
            continue;
        }

        stage[offset] = 11;
    }
    return 0;
}

int FallTetronimo()
{
    for(int i = 0; i < 8; i+= 2)
    {
        int x = mainTetronimo.x + mainTetronimo.current_shape[i];
        int y = mainTetronimo.y + mainTetronimo.current_shape[i + 1];
        

        printf("\nStage %d -> ", y * STAGE_WIDTH + x);

        while (stage[(y + 1) * STAGE_WIDTH + x] == 0)
        {
            y++;
        }
        

        stage[y * STAGE_WIDTH + x] = mainTetronimo.shape + 1;
    }

    printf("\n");
    hasToSpawnNewTetronimo = 1;
    destroyCurrentTetronimo = 1;
    return 1;
}

int MirrorMainTetronimo()
{
    int new_rotation = mainTetronimo.rotation;
    int new_shape = mainTetronimo.shape;

    switch (new_shape)
    {
    case TETRONIMO_I:
    case TETRONIMO_T:
    case TETRONIMO_O:
        new_rotation = (new_rotation + 2) % 4;
        break;

    case TETRONIMO_J:
        new_shape = TETRONIMO_L;
        break;
    case TETRONIMO_L:
        new_shape = TETRONIMO_J;
        break;
        
    case TETRONIMO_S:
        new_shape = TETRONIMO_Z;
        break;
    case TETRONIMO_Z:
        new_shape = TETRONIMO_S;
        break;
    
    default:
        break;
    }

    if(!CheckRotateCollision(mainTetronimo.x, mainTetronimo.y, tetronimo_types[new_shape][new_rotation]))
    {
        SetTetronimoRotation(&mainTetronimo, new_rotation);
        SetTetronimoShape(&mainTetronimo, new_shape);
        return 1;
    }
    return 0;
}

#pragma endregion



#pragma region Main
void MainBeginPlay()
{
    RogueBegin();

    current_game_loop.tick = MainTick;
    current_game_loop.draw = MainDraw;


    currentMoveTileDownTimer = startMoveTileDownTimer;
    timeToMoveDown = currentMoveTileDownTimer;
    currentMoveTimeHoldTime = startMoveTimeHoldTime;
    timeToMoveDownHold = currentMoveTileDownTimer;

    time_t unixTime;
    time(&unixTime);

    SetRandomSeed(unixTime);

    SpawnNewTetronimo(&mainTetronimo, GetRandomValue(0,6));

    holdTetrominoType = -1;
    alreadySwappedOnce = 0;

    closeGame = 0;
    hasToSpawnNewTetronimo = 0;

    score = 0;
    lines_deleted = 0;
    tetris_scored = 0;
    level = 0;
    next_level_up = 1000;
    speed = .0f;
    visible_level = 1;

    memset(str_lines_deleted,'0',4);
    memset(str_tetris_scored,'0',4);
    //memset(str_visible_level,'0',4);

    for(int i = 0; i <= VISIBLE_PIECES;i++)
    {
        nextPieces[i] =GetRandomValue(0,6);
    }

    memcpy(stage, reset_stage, STAGE_DIMENSION * 4);

    UpdateStrings();

    preview_y = 0;

    TetrisChangeMusic(MUSIC_MAIN);

    //MULTIPLIER
    sprintf(str_multiplier, "%f", multiplier);
    memcpy(real_str_multiplier,str_multiplier,3);

    current_game_loop.begin_play = EmptyBegin;

    //PrintTetronimo(&mainTetronimo);
}

void MainTick(const float delta_time)
{

    #pragma region Commands

        if (!alreadySwappedOnce && IsKeyPressed(KEY_SPACE))
        {
            alreadySwappedOnce = 1;
            TetrisPlaySfx(SFX_HOLD);

            if (holdTetrominoType == -1)
            {
                holdTetrominoType = mainTetronimo.shape;
                // SetRandomSeed(unixTime);

                SetTetronimoShape(&mainTetronimo, nextPieces[0]);

                for(int i = 1; i<6;i++)
                {
                    nextPieces[i-1] = nextPieces[i];
                }

                nextPieces[5] = GetRandomValue(0,6);
            }

            else
            {
                for(int i = 5; i>0;i--)
                {
                    nextPieces[i] = nextPieces[i-1];
                }

                nextPieces[0] = mainTetronimo.shape;

                SetTetronimoShape(&mainTetronimo, holdTetrominoType);

                holdTetrominoType = -1;       
            }

            mainTetronimo.x = startPosX;
            mainTetronimo.y = startPosY;

        }

        timeToMoveDown -= delta_time;
        if (IsKeyPressed(KEY_E))
        {
            int nextTetronimoRotation = (mainTetronimo.rotation + 1) % 4;
            
            if (!CheckRotateCollision(
                mainTetronimo.x,
                mainTetronimo.y,
                tetronimo_types[mainTetronimo.shape][nextTetronimoRotation]
            ))
            {
                SetTetronimoRotation(&mainTetronimo,nextTetronimoRotation);         
                TetrisPlaySfx(SFX_ROTATE);
            }
            else
                TestWallKickRotateRight(&mainTetronimo, nextTetronimoRotation);
       
        }
        
        if (IsKeyPressed(KEY_Q))
        {
            int nextTetronimoRotation = (mainTetronimo.rotation + 3) % 4;
            if (!CheckRotateCollision(
                mainTetronimo.x,
                mainTetronimo.y,
                tetronimo_types[mainTetronimo.shape][nextTetronimoRotation]
            )){
                SetTetronimoRotation(&mainTetronimo,nextTetronimoRotation);    
                //PrintTetronimo(&mainTetronimo);        
                TetrisPlaySfx(SFX_ROTATE);
            }
            else
                TestWallKickRotateLeft(&mainTetronimo ,nextTetronimoRotation);
            
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            if (!CheckSideCollision(
                mainTetronimo.x,
                mainTetronimo.y,
                1,
                tetronimo_types[mainTetronimo.shape][mainTetronimo.rotation]))
                {
                mainTetronimo.x++;
                TetrisPlaySfx(SFX_MOVE);
                }
        }

        if (IsKeyPressed(KEY_LEFT))
        {            
            if (!CheckSideCollision(
                mainTetronimo.x,
                mainTetronimo.y,
                -1,
                tetronimo_types[mainTetronimo.shape][mainTetronimo.rotation]))
                {
                    TetrisPlaySfx(SFX_MOVE);
                    mainTetronimo.x--;
                }
        }

        if(IsKeyPressed(KEY_UP))
        {
            while (!CheckDownCollision(mainTetronimo.x, mainTetronimo.y, tetronimo_types[mainTetronimo.shape][mainTetronimo.rotation]))
            {
                mainTetronimo.y++;
                timeToMoveDown = currentMoveTileDownTimer;
            }

            TetrisPlaySfx(SFX_HARDLAND);
            hasToSpawnNewTetronimo= 1;
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

            if (!CheckDownCollision(mainTetronimo.x, mainTetronimo.y, tetronimo_types[mainTetronimo.shape][mainTetronimo.rotation]))
            {
                mainTetronimo.y++;
                TetrisPlaySfx(SFX_MOVE);
            }
            else
            {
                hasToSpawnNewTetronimo = 1;
                TetrisPlaySfx(SFX_LAND);
            }
            timeToMoveDown = currentMoveTileDownTimer;
            timeToMoveDownHold = currentMoveTimeHoldTime;
        }
    #pragma endregion

    RogueInputTick(delta_time);

    if(hasToSpawnNewTetronimo)
    {

        hasToSpawnNewTetronimo = 0;
    
        int resetMultiplier = 1;
        
        const int *currTetronimo = tetronimo_types[mainTetronimo.shape][mainTetronimo.rotation];
        if (!destroyCurrentTetronimo)
        //Set tetronimo
        for (int i = 0; i < 8 ; i += 2){
            const int cellToPlace = (mainTetronimo.y + currTetronimo[i + 1]) * STAGE_WIDTH + mainTetronimo.x + currTetronimo[i];
            stage[cellToPlace] = mainTetronimo.shape + 1;

            if ((i / 2) ==  mainTetronimo.powerUpTile)
            {
                printf("T: %d",mainTetronimo.powerUpTile);

                powerUpsTile[0].my_color = BLACK;
                powerUpsTile[0].index = cellToPlace;
                int tx = (mainTetronimo.x + currTetronimo[i]) * TILE_SIZE + START_OFFSET_X;
                int ty = (mainTetronimo.y + currTetronimo[i + 1]) * TILE_SIZE + START_OFFSET_Y;
                powerUpsTile[0].x = tx;
                powerUpsTile[0].y = ty;
            }
        }

        destroyCurrentTetronimo = 0;
        //Check to delete Lines
        const int current_line_deleted = DeleteLines();

        if (current_line_deleted){
            
            //Rogue Scored
            for(int i = 0; i< current_line_deleted; i++)
                RogueLineScored();

            //Dont reset multiplier
            resetMultiplier = 0;

            lines_deleted += current_line_deleted;

            //tetris = 4 Lines
            if (current_line_deleted == 4)
            {
                RogueTetrisScored();

                tetris_scored += 1;
                //Add 1000 point
                UpdateScore(1000);
                TetrisPlaySfx(SFX_TETRIS);

                multiplier += 2.5f;
                // sprintf(str_tetris_scored, "%i", tetris_scored);
            }
            else
            {

                UpdateScore(current_line_deleted * 100);
                TetrisPlaySfx(SFX_SINGLE);

                multiplier += .5f;
            }

            if (multiplier > 9.9f)
                multiplier = 9.9f;
            
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

            //printf("Level: %s\n", str_visible_level);
        }
        else
        {
            RoguePiecePlaced();
        }

        alreadySwappedOnce = 0;
        
        SpawnNewTetronimo(&mainTetronimo, nextPieces[0]);

        for(int i = 1; i<6;i++)
        {
            nextPieces[i-1] = nextPieces[i];
        }
        
        if (CheckRotateCollision(
            mainTetronimo.x,
            mainTetronimo.y,
            tetronimo_types[mainTetronimo.shape][0]
            ))
            {
                //GAME OVER
                TetrisPlaySfx(SFX_GAME_OVER);
                TetrisChangeMusic(MUSIC_LOST);


                current_game_loop.tick = WaitForSpaceTick;
                current_game_loop.post_draw = MainOverlayDraw;
                //closeGame = 1;
            }

        
        nextPieces[5] = GetRandomValue(0,6);

        if(resetMultiplier)
            multiplier = 1.0f;

        sprintf(str_multiplier, "%f", multiplier);

        memcpy(real_str_multiplier,str_multiplier,3);
        //printf("Multiplier: %f\n", multiplier);
        
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
        DrawTetromino2(
            &mainTetronimo
        );

        //Preview Piece
        preview_y = GetLowestPiecePosition(mainTetronimo.x,mainTetronimo.y,tetronimo_types[mainTetronimo.shape][mainTetronimo.rotation]);

        DrawTetromino(
            mainTetronimo.x,
            preview_y,
            tetronimo_types[mainTetronimo.shape][mainTetronimo.rotation],
            colorTypes[8]
        );

        #pragma region other_pieces

        //Hold Piece
        if (holdTetrominoType>= 0)
        {
            DrawTetromino(
            -4,
            1,
            tetronimo_types[holdTetrominoType][0],
            colorTypes[holdTetrominoType + 1]
        );
        }

        //Next Pieces
        for(int i = 0; i < 5; i++)
        {
            int nextTetronimo = nextPieces[i];
            DrawTetromino(
            16,
            2 + 4 * i,
            tetronimo_types[nextTetronimo][0],
            colorTypes[nextTetronimo + 1]);
        }

        #pragma endregion

        //TEXT and Test Text
        //FormatScore(score_array, score);

        DrawText("Score:", 16, 240, 20, WHITE);
        DrawText(str_score, 16, 260, 20, WHITE);
        DrawText(TextFormat("Level: %i", visible_level), 16, 300, 20, WHITE);
        //DrawText(str_visible_level, 16 + MeasureText("Level: ",20), 300, 20, WHITE);
        DrawText(TextFormat("Multiplier: %s", real_str_multiplier), 16 , 340, 20, WHITE);
        //DrawText(str_lines_deleted, 32, 400, 20, WHITE);
        //DrawText(str_tetris_scored, 32, 440, 20, WHITE);
        //DrawText(str_speed, 32, 480, 20, WHITE);

    RogueDraw();
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
        oldDeletedSquare = -1;
        currentDeleteEffectTimer = deleteEffectTimer;

        if (showRewardBox)
        {
            current_game_loop.begin_play = RogueRewardBegin;
            current_game_loop.tick = WaitForSpaceTick;
        }
        else
            current_game_loop.tick = MainTick;
    }

    int deletedLineCounter = 0;
    int squareToChange =  (10 - currentDeleteEffectTimer / .1);


    


    while(lines_to_delete[deletedLineCounter] > 0 && deletedLineCounter < 4)
    {
        const int offset = lines_to_delete[deletedLineCounter] * STAGE_WIDTH + 1;

        if (squareToChange > oldDeletedSquare)
        {
            //printf("L %i, S %i\n", lines_to_delete[deletedLineCounter], squareToChange);
            SpawnTile(
                GetXPositionFromCellX(squareToChange),
                GetYPositionFromCellY(lines_to_delete[deletedLineCounter]),
                deletedLineCounter * 10 + squareToChange,
                colorTypes[stage[offset + squareToChange]]);    
        }

        stage[offset + squareToChange] = 8;
        deletedLineCounter++;
    }
    oldDeletedSquare = squareToChange;
}
#pragma endregion

#pragma region Game Over
void MainOverlayDraw()
{
    DrawRectangle(64,64,384, 150, WHITE);

    DrawTextCentral("GAME OVER", 256,100,32,BLACK);
    DrawTextCentral(str_score, 256,140,32,BLACK);
    DrawTextCentral("Press SPACE to return to MENU", 256, 180, 20,BLACK);
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
#pragma endregion


int main(int argc, char** argv)
{
    InitWindow(windowWidth, windowHeight, "Title");

    TetrisLoadMusic();
    TetrisLoadImages();
    
    SetTargetFPS(60);
    current_game_loop.begin_play = MainMenuBeginPlay;
    

    currentDeleteEffectTimer = 1.f;

    lines_to_delete[0] = -1;
    lines_to_delete[1] = -1;
    lines_to_delete[2] = -1;
    lines_to_delete[3] = -1;

    EffectBegin();

    
    while(!WindowShouldClose() && (closeGame == 0))
    {

        current_game_loop.begin_play();
        TetrisLoopBgMusic();

        current_game_loop.tick(GetFrameTime());
        EffectTick(GetFrameTime());
        
        BeginDrawing();
        ClearBackground(GRAY);
        current_game_loop.draw();

        EffectDraw();

        current_game_loop.post_draw();
        EndDrawing();
    }
    
    TetrisUnloadImages();
    TetrisUnloadMusic();
    return 0;
}