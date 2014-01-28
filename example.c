
#include <GL/glut.h>  
#include <GL/gl.h>
#include <GL/glu.h> 
#include <stdio.h>
#include "life.h"
#include "Textures.h"
static unsigned int backgroundTexture;
static unsigned int lifeTexture;
static unsigned int lonelinessTexture;
static unsigned int overcrowdingTexture;
static short field[fieldW][fieldH];
static short numb[fieldW][fieldH];
static short itWorks=0;
static int stepTime=1000;

void reshape(int w, int h)
{
  //  here's some bag... sometimes w!=699 or h!=699
  // but glutReshpeWindow don't change window size
    if ((w!=windowW) || (h!=windowH)){
          glutReshapeWindow(windowW,windowH);
        }
    glViewport(0, 0, windowW+1, windowH+1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowW+1, windowH+1, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void mouseClick( int button, int state, int x, int y )
{
  if ((x/cellSize>=0 && x/cellSize<fieldW) && (y/cellSize>=0 && y/cellSize<fieldH))
    field[x/cellSize][y/cellSize]=ALIVE;
}
void mouseMotion(int x, int y)
{
  if ((x/cellSize>=0 && x/cellSize<fieldW) && (y/cellSize>=0 && y/cellSize<fieldH))
   field[x/cellSize][y/cellSize]=ALIVE; 
}
void display()
{
  int i,j;
  glClear(GL_COLOR_BUFFER_BIT);
  //background
 /* if(backgroundImg==NULL)
  {
    glBegin(GL_QUADS);
      glVertex2i(0, 0);
      glVertex2i(windowW,0);
      glVertex2i(windowW,windowH);
      glVertex2i(0,windowH);
    glEnd();
  }
  else*/
  { 
    glBindTexture(GL_TEXTURE_2D, backgroundTexture );
    glBegin(GL_QUADS);
      glColor3f(0.0, 1.0, 1.0);
      glTexCoord2d(0,0); glVertex2i(0, 0);      
      glTexCoord2d(0,1); glVertex2i(windowW,0);     
      glTexCoord2d(1,1); glVertex2i(windowW,80);        
      glTexCoord2d(1,0); glVertex2i(0,windowH);          
    glEnd();
//  glDrawPixels(windowW, windowH, GL_RGB, GL_UNSIGNED_BYTE, background.pixel_data);
  }
  //lines
  for (i=0;i<fieldH;i++)
  {
    glBegin(GL_LINES);
      glColor3f(0.0, 0.0, 0.0);
      glVertex2i(0,i*cellSize);
      glVertex2i(windowW,i*cellSize);
    glEnd();
  }
for (i=0;i<fieldW;i++)
  {
    glBegin(GL_LINES);
      glColor3f(0.0, 0.0, 0.0);
      glVertex2i(i*cellSize,0);
      glVertex2i(i*cellSize,windowH);
    glEnd();
  }

  //field
  for (i=0;i<fieldW;i++)
    for (j=0;j<fieldH;j++)
      if (field[i][j])
        {
          glBegin(GL_QUADS);
            if (field[i][j]==ALIVE)
              glColor3f(0.0, 1.0, 0.0);
            if (field[i][j]==DEAD_BY_LONELINESS)
              glColor3f(0.0,0.0,0.0);
            if (field[i][j]==DEAD_BY_OVERCROWDING)
              glColor3f(1.0,0.0,0.0);
            glVertex2i(i*cellSize, j*cellSize);
            glVertex2i((i+1)*cellSize,j*cellSize);
            glVertex2i((i+1)*cellSize,(j+1)*cellSize);
            glVertex2i(i*cellSize,(j+1)*cellSize);
          glEnd();
        }

  glutSwapBuffers();
}

void step(int value)
{  
  int i,j,k,g;
  if (itWorks)
  {
    for (i=0;i<fieldW;i++)
      for (j=0;j<fieldH;j++)
        numb[i][j]=0;
    for (i=0;i<fieldW;i++)
      for (j=0;j<fieldH;j++)
      {
        if (field[i][j]==ALIVE)
          for (k=-1;k<2;k++)
            for (g=-1;g<2;g++)
              if (k!=0 || g!=0)
                if ((i+k)>=0 && (j+g)>=0 &&(i+k)<fieldW && (j+g)<fieldH)
                  numb[i+k][j+g]++;
      }
    for (i=0;i<fieldW;i++)
      for (j=0;j<fieldH;j++)  
      {
        if (field[i][j]==ALIVE && numb[i][j]<2)
          field[i][j]=DEAD_BY_LONELINESS;
        if (field[i][j]==ALIVE && numb[i][j]>3)
          field[i][j]=DEAD_BY_OVERCROWDING;
        if (field[i][j]!=ALIVE && numb[i][j]==3)
          field[i][j]=ALIVE;
      } 
  }
  glutTimerFunc(stepTime,step,1);
}

void reDisplay(int value)
{
  display();
  glutTimerFunc(30,reDisplay,2);
}
void keyboard(unsigned char key, int x, int y)
{
  if (key=' ')
    itWorks^=1;
}
void funcKeys(int key, int x, int y)
{
  if (key==GLUT_KEY_DOWN)
    if (stepTime<5000) stepTime+=20;
  if (key==GLUT_KEY_UP)
    if (stepTime>200) stepTime-=20;
  if (key==GLUT_KEY_F1)
  {

  }
  if (key==GLUT_KEY_F9)
  {
    int i,j;
    for (i=0;i<fieldW;i++)
      for (j=0;j<fieldH;j++)
        field[i][j]=0;
  }
}
int main (int argc, char * argv[])
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
  glutInitWindowSize(windowW, windowH);
  glutCreateWindow("Lab5");       
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMouseFunc(mouseClick);
  glutMotionFunc(mouseMotion);
  glutTimerFunc(1000,step,1);
  glutTimerFunc(100,reDisplay,2);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(funcKeys);

  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &backgroundTexture);
  printf("%d\n", backgroundTexture );
  glBindTexture(GL_TEXTURE_2D, backgroundTexture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  glTexImage2D(GL_TEXTURE_2D,0, 3,background.width,background.height,0,GL_RGB8,GL_UNSIGNED_BYTE,background.pixel_data);
  printf("%s\n",gluErrorString(glGetError()) );

 /* glGenTextures(1, &lifeTexture);
  printf("%d\n", lifeTexture );
  glBindTexture(GL_TEXTURE_2D, lifeTexture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  glTexImage2D(GL_TEXTURE_2D,0, 3,16,16,0,GL_RGB8,GL_UNSIGNED_BYTE,lifeImg);*/


  glutMainLoop();
  return 0;
}