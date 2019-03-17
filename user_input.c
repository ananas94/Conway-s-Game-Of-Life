#include "life.h"

void keyboard(unsigned char key, int x, int y)
{
  if (key = ' ')
    timer_logic_execution_state_switch();
}

void funcKeys(int key, int x, int y)
{
  switch (key)
  {
  case GLUT_KEY_DOWN:
  {
    timer_decrease_speed();
    break;
  }
  case GLUT_KEY_UP:
  {
    timer_increase_speed();
    break;
  }
  //case GLUT_KEY_F1:
  case GLUT_KEY_F2:
  {
    graphics_change_draw_dead_state();
    break;
  }
  case GLUT_KEY_F9:
  {
    logic_cleanup_field();
  }
  }
}

static int mousePressedButton;
void mouseClick(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN)
    mousePressedButton = button;
  else
    mousePressedButton = -1;

  mouseMotion(x, y);
}

void mouseMotion(int x, int y)
{
  int cellX = x / cellSize;
  int cellY = y / cellSize;
  if (mousePressedButton == GLUT_LEFT_BUTTON)
    logic_set_alive(cellX, cellY);
  /*if ( ( x / cellSize >= 0 && x / cellSize < fieldW ) &&
         ( y / cellSize >= 0 && y / cellSize < fieldH ))
      field[x / cellSize][y / cellSize] = ALIVE;*/
  if (mousePressedButton == GLUT_RIGHT_BUTTON)
    logic_set_clean(cellX, cellY);
  /*if ((x / cellSize >= 0 && x / cellSize < fieldW) && (y / cellSize >= 0 && y / cellSize < fieldH))
      field[x / cellSize][y / cellSize] = 0;*/
}

void init_user_input()
{
  glutMouseFunc(mouseClick);
  glutMotionFunc(mouseMotion);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(funcKeys);
}
