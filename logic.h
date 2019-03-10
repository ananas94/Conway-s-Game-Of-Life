#ifndef CGL_LOGIC_H
#define CGL_LOGIC_H

void step(int value);
enum CELL_STATE
{
    NONE = 0,
    ALIVE = 1,
    DEAD_BY_LONELINESS = 2,
    DEAD_BY_OVERCROWDING =3
};


#endif