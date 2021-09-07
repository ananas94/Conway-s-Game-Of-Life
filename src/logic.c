#include "life.h"

static cell_state_t field[fieldW][fieldH];
static short neighbors_number[fieldW][fieldH];

void logic_cleanup_field()
{
    int i, j;
    for (i = 0; i < fieldW; i++)
        for (j = 0; j < fieldH; j++)
            field[i][j] = NONE;
}

static void
update_cell_neighbors_number(int x, int y)
{
    int k, g;
    if (logic_get_cell_state(x, y) != ALIVE)
        return;

    for (k = -1; k < 2; k++)
        for (g = -1; g < 2; g++)
            if (k != 0 || g != 0)
                if ((x + k) >= 0 && (y + g) >= 0 && (x + k) < fieldW && (y + g) < fieldH)
                    neighbors_number[x + k][y + g]++;
}

cell_state_t
logic_get_cell_state(int x, int y)
{
    if (x >= 0 && y >= 0 && x < fieldW && y < fieldH)
        return field[x][y];
    return -1;
}

static void
update_field_state(int x, int y)
{
    if (field[x][y] == ALIVE && neighbors_number[x][y] < 2)
        field[x][y] = DEAD_BY_LONELINESS;
    if (field[x][y] == ALIVE && neighbors_number[x][y] > 3)
        field[x][y] = DEAD_BY_OVERCROWDING;
    if (field[x][y] != ALIVE && neighbors_number[x][y] == 3)
        field[x][y] = ALIVE;
}

void logic_step(int unused)
{
    int i, j;
    //clear numb array
    for (i = 0; i < fieldW; i++)
        for (j = 0; j < fieldH; j++)
            neighbors_number[i][j] = 0;
    //counting number of alive cell's neighbors
    for (i = 0; i < fieldW; i++)
        for (j = 0; j < fieldH; j++)
            update_cell_neighbors_number(i, j);

    //making findings from numb array
    for (i = 0; i < fieldW; i++)
        for (j = 0; j < fieldH; j++)
            update_field_state(i,j);
    timer_set_logic_timer(logic_step);
}
void init_logic()
{
    glutTimerFunc(1000, logic_step, 1);
}

void logic_set_clean(int x, int y)
{
    if ( 0 <= x &&  x < fieldW && 0 <= y && y < fieldH )
        field[x][y]=NONE;
}
void logic_set_alive(int x, int y)
{
    if ( 0 <= x &&  x < fieldW && 0 <= y && y < fieldH )
        field[x][y]=ALIVE;
}
