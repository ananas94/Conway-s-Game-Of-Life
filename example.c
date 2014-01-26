
#include <GL/glut.h>    
#include <stdio.h>
#include "life.h"
static char *backgroundTexture;
static char *lifeTexture;
static char *lonelinessTexture;
static char *overcrowdingTexture;
static short field[fieldW][fieldH];
static short numb[fieldW][fieldH];
static short f=0;
void reshape(int w, int h)
{
  //  printf("%d %d \n",w, h );  here's some bag... sometimes w!=699 or h!=699
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
  printf("%d\n",y/cellSize );
}
void mouseMotion(int x, int y)
{
  if ((x/cellSize>=0 && x/cellSize<fieldW) && (y/cellSize>=0 && y/cellSize<fieldH))
   field[x/cellSize][y/cellSize]=ALIVE; 
}
char* readTexture(char* fileName, int alpha)
{
  int rgbBytes,d,bytesPerRow;
  char *backgroundTexture, *otherDate;
  FILE *f;
  HeadGr head;
  f=fopen(fileName,"rb");
  if (f==NULL)
      return NULL;
  else
  {
    fread(&head,54,1,f);
    rgbBytes=head.biWidth*(3+alpha);
    d=rgbBytes%4;
    bytesPerRow=d ? rgbBytes+(4-d)  :rgbBytes;
    backgroundTexture=(char*)malloc(bytesPerRow*head.biHeight);
    otherDate=(char*) malloc(head.bfOffBits-54);
    fread(otherDate,(head.bfOffBits-54),1,f);
    fread(backgroundTexture,bytesPerRow*head.biHeight,1,f);          
    fclose(f); 
    free(otherDate);
    return backgroundTexture;
  }
}
void display()
{
  int i,j;
  glClear(GL_COLOR_BUFFER_BIT);
  //background
  if(backgroundTexture==NULL)
  {
    glBegin(GL_QUADS);
      glColor3f(0.0, 1.0, 1.0);
      glVertex2i(0, 0);
      glVertex2i(windowW,0);
      glVertex2i(windowW,windowH);
      glVertex2i(0,windowH);
    glEnd();
  }
  else
  {
    glDrawPixels(windowW, windowH, GL_BGR, GL_UNSIGNED_BYTE, backgroundTexture);
  }
  //lines
  for (i=0;i<70;i++)
  {
    glBegin(GL_LINES);
      glColor3f(0.0, 0.0, 0.0);

      glVertex2i(0,i*cellSize);
      glVertex2i(windowW,i*cellSize);

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
  if (f)
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
                if ((i+k)>0 && (j+g)>0)
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
  glutTimerFunc(1000,step,1);
}
void reDisplay(int value)
{
  display();
  glutTimerFunc(30,reDisplay,2);
}
void keyboard(unsigned char key, int x, int y)
{
  if (key=' ')
    f^=1;
}
int main (int argc, char * argv[])
{
  backgroundTexture=readTexture("backgroundTexture.bmp",0);
  overcrowdingTexture=readTexture("overcrowding.bmp",1);
  lifeTexture=readTexture("life.bmp",1);
  lonelinessTexture=readTexture("loneliness.bmp",1);

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
  glutMainLoop();
  free(backgroundTexture);
  return 0;
}