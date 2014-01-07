
/*http://habrahabr.ru/post/111175/*/
#include <GL/glut.h>    
#include <stdio.h>
#include "life.h"
static char *backgroundTexture;
void reshape(int w, int h)
{
    if ((w!=700) || (h!=700)){
          glutReshapeWindow(700,700);
          printf("вот он reshape\n");
        }
    printf("reshape\n");

}
void mouseclick( int button, int state, int x, int y )
{
    printf("%d %d \n",x,y); 
}

char* readTexture(char* fileName)
{
    int rgbBytes,d,bytesPerRow;
    char *backgroundTexture, *otherDate;
    FILE *f;
    HeadGr head;
    f=fopen("texture.bmp","rb");
    if (f==NULL)
        return NULL;
    else
    {
        fread(&head,54,1,f);
        rgbBytes=head.biWidth*3;
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
    glClear(GL_COLOR_BUFFER_BIT);
    if(backgroundTexture==NULL)
    {
        glBegin(GL_QUADS);
            glColor3f(0.0, 1.0, 1.0);
            glVertex2i(0, 700);
            glVertex2i(0, 0);
            glVertex2i(700, 0);
            glVertex2i(700, 700);
        glEnd();
        glutSwapBuffers();
    }
    else
    {
        glDrawPixels(700, 700, GL_BGR, GL_UNSIGNED_BYTE, backgroundTexture);
        glutSwapBuffers();
    }
    printf("display \n");
}



int main (int argc, char * argv[])
{
        backgroundTexture=readTexture("texture.bmp");
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
       
        glutInitWindowSize(700, 700);
        glutCreateWindow("Lab5");
       
        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutMouseFunc( 
        mouseclick );
        glutMainLoop();
        free(backgroundTexture);
        return 0;
}

