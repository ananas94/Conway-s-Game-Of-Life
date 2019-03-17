#include "life.h"
static int stepTime = 1000;

void timer_increase_speed()
{
    if (stepTime < 5000)
        stepTime += 20;
}
void timer_decrease_speed()
{
    if (stepTime > 200)
        stepTime -= 20;
}

static short logic_timer_alive = 1;

void timer_set_logic_timer(void (*callback)(int))
{
    if (logic_timer_alive)
        glutTimerFunc(stepTime, callback, 1);
}

void timer_logic_execution_state_switch()
{
    logic_timer_alive ^= 1;
    if (logic_timer_alive)
        timer_set_logic_timer(logic_step);
}