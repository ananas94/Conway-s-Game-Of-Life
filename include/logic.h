#ifndef CGL_LOGIC_H
#define CGL_LOGIC_H

void logic_step(int unused);
typedef enum CELL_STATE
{
    NONE = 0,
    ALIVE = 1,
    DEAD_BY_LONELINESS = 2,
    DEAD_BY_OVERCROWDING = 3
} cell_state_t;

void logic_cleanup_field();

void logic_stop_processing();
void logic_start_processing();
cell_state_t logic_get_cell_state(int x, int y);
void logic_set_clean(int x, int y);
void logic_set_alive(int x, int y);
void init_logic();

#endif