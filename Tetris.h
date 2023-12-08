#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22
#define TILE_SIZE 16
#define TETRONIMO_SIZE 4

extern int stage[];

int CheckDownCollision(
    const int grid_pos_x,
    const int grid_pos_y,
    const int *tetronimo);

int CheckSideCollision(
    const int grid_pos_x,
    const int grid_pos_y,
    const int side_offset,
    const int *tetronimo);

int CheckRotateCollision(
    const int grid_pos_x,
    const int grid_pos_y,
    const int *tetronimo);