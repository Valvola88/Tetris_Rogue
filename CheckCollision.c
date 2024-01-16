#include "Tetris.h"

int CheckDownCollision(
    const int grid_pos_x,
    const int grid_pos_y,
    const int *tetronimo)
    {    
    for (int i = 0; i < 8; i+= 2){
        const int currCoordX = grid_pos_x + tetronimo[i];
        const int currCoordY = (grid_pos_y + tetronimo[i + 1] + 1) * STAGE_WIDTH;
        if (stage[currCoordX + currCoordY] != 0)
            return 1; 

    }
    return 0;

}

int CheckSideCollision(
    const int grid_pos_x,
    const int grid_pos_y,
    const int side_offset,
    const int *tetronimo
){
    for (int i = 0; i < 8; i+= 2){
        const int currCoordX = grid_pos_x + tetronimo[i];
        const int currCoordY = (grid_pos_y + tetronimo[i + 1]) * STAGE_WIDTH;
        if (stage[currCoordX + currCoordY + side_offset] != 0)
            return 1; 

    }

    return 0;
}


int CheckRotateCollision(
    const int grid_pos_x,
    const int grid_pos_y,
    const int *tetronimo
)
{
    
    for (int i = 0; i < 8; i+= 2){
        const int currCoordX = grid_pos_x + tetronimo[i];
        const int currCoordY = (grid_pos_y + tetronimo[i + 1]) * STAGE_WIDTH;
        if (stage[currCoordX + currCoordY] != 0)
            return 1; 

    }

    return 0;
}

int GetLowestPiecePosition(
    const int grid_pos_x,
    const int grid_pos_y,
    const int *tetronimo
)
{
    int current_y = grid_pos_y;

    while (!CheckDownCollision(grid_pos_x, current_y, tetronimo))
    {
        current_y++;
    }
    
    return current_y;

}

void TestWallKickRotateLeft(Tetromino *myTetronimo, const int nextTetronimoRotation)
{
    int test_wall_kick;
    
    switch (myTetronimo->rotation)
    {
    case 0: test_wall_kick = WALLKICK_0_TO_270;
        break;
    
    case 1: test_wall_kick = WALLKICK_90_TO_0;
        break;
        
    case 2: test_wall_kick = WALLKICK_180_TO_90;
        break;
        
    case 3: test_wall_kick = WALLKICK_270_TO_180;
        break;
    }

    const int *table_to_look = wall_kick_offsets[test_wall_kick];
    if (myTetronimo->shape == TETRONIMO_I)
    {
        table_to_look = wall_kick_I_offsets[test_wall_kick];
    }

    int i = 0;
    while (i < 8)
    {
        {
            if (!CheckRotateCollision(
                myTetronimo->x + table_to_look[i],
                myTetronimo->y + table_to_look[i+ 1],
                tetronimo_types[myTetronimo->shape][nextTetronimoRotation]
            ))
            {
                myTetronimo->x += table_to_look[i];
                myTetronimo->y += table_to_look[i + 1];
                SetTetronimoRotation(myTetronimo, nextTetronimoRotation);            
                TetrisPlaySfx(SFX_ROTATE);
                return;
            }
        }
        i+= 2;
    }
    return;  
}

void TestWallKickRotateRight(Tetromino *myTetronimo, const int nextTetronimoRotation)
{
    int test_wall_kick;
    
    switch (myTetronimo->rotation)
    {
    case 0: test_wall_kick = WALLKICK_0_TO_90;
        break;
    
    case 1: test_wall_kick = WALLKICK_90_TO_180;
        break;
        
    case 2: test_wall_kick = WALLKICK_180_TO_270;
        break;
        
    case 3: test_wall_kick = WALLKICK_270_TO_0;
        break;
    }

    const int *table_to_look = wall_kick_offsets[test_wall_kick];
    if (myTetronimo->shape == TETRONIMO_I)
    {
        table_to_look = wall_kick_I_offsets[test_wall_kick];
    }

    int i = 0;
    while (i < 8)
    {
        {
            if (!CheckRotateCollision(
                myTetronimo->x + table_to_look[i],
                myTetronimo->y + table_to_look[i+ 1],
                tetronimo_types[myTetronimo->shape][nextTetronimoRotation]
            ))
            {
                myTetronimo->x += table_to_look[i];
                myTetronimo->y += table_to_look[i + 1];
                SetTetronimoRotation(myTetronimo, nextTetronimoRotation);            
                TetrisPlaySfx(SFX_ROTATE);
                return;
            }
        }
        i+= 2;
    }
    return;  
}
