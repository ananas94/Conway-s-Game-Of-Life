
#include "life.h"

//here was dirty hack
//this header file have 127k+ lines
//and it was bitmap
//#include "Textures.h"

void reshape(int w, int h)
{
  /*  here's some bag... sometimes w!=windowW or h!=windowH
      but glutReshpeWindow don't change window size
      somewere i saw, that nobody can fix */
  if ((w != windowW) || (h != windowH))
  {
    glutReshapeWindow(windowW, windowH);
  }
  glViewport(0, 0, windowW, windowH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, windowW, windowH, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static void initWindow()
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(windowW, windowH);
  glutCreateWindow("Lab5");
  glutReshapeFunc(reshape);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  initWindow();
  init_user_input();
  init_graphics();

  init_logic();

  glutMainLoop();

  return 0;
}
