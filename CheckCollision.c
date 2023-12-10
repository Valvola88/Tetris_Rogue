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