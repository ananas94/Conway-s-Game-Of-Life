#ifndef CGL_TIMER_H
#define CGL_TIMER_H

void timer_increase_speed();
void timer_decrease_speed();
void timer_set_logic_timer(void (*callback)(int));
void timer_logic_execution_state_switch();
#endif