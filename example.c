
#include <GL/glut.h>    
#include <stdio.h>
#include "life.h"
static char *backgroundTexture;
static char *lifeTexture;
static char *lonelinessTexture;
static char *overcrowdingTexture;
static 
void reshape(int w, int h)
{
  //  printf("%d %d \n",w, h );  here's some bag... sometimes w!=700 or h!=700
  // but glutReshpeWindow don't change window size
    if ((w!=700) || (h!=700)){
          glutReshapeWindow(700,700);
        }
                    glViewport(0, 0, w, h);
           
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(0, w, 0, h);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
}
void mouseclick( int button, int state, int x, int y )
{
    printf("%d %d \n",x,y); 
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
    if(backgroundTexture==NULL)
    {
        glBegin(GL_QUADS);
            glColor3f(0.0, 1.0, 1.0);
              glVertex2i(0, 0);
              glVertex2i(700,0);
              glVertex2i(700,700);
              glVertex2i(0,700);
        glEnd();
    }
    else
    {
        glDrawPixels(700, 700, GL_BGR, GL_UNSIGNED_BYTE, backgroundTexture);
    }

    for (i=0;i<70;i++)
      {
        glBegin(GL_LINES);
          glColor3f(0.0, 0.0, 0.0);
          glVertex2i(0,i*20);
          glVertex2i(700,i*20);
        glEnd();
      }
      for (i=0;i<70;i++)
      {
        glBegin(GL_LINES);
          glColor3f(0.0, 0.0, 0.0);
          glVertex2i(i*20,0);
          glVertex2i(i*20,700);
        glEnd();
      }

    glutSwapBuffers();
}

int main (int argc, char * argv[])
{
        backgroundTexture=readTexture("backgroundTexture.bmp",0);
        overcrowdingTexture=readTexture("overcrowding.bmp",1);
        lifeTexture=readTexture("life.bmp",1);
        lonelinessTexture=readTexture("loneliness.bmp",1);


        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
        glutInitWindowSize(700, 700);
        glutCreateWindow("Lab5");       
        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutMouseFunc(mouseclick);
        glutMainLoop();
        free(backgroundTexture);
        return 0;
}

