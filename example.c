
/*http://habrahabr.ru/post/111175/*/
#include <GL/glut.h>    
#include <stdio.h>
void reshape(int w, int h)
{
        glViewport(0, 0, w, h);
       
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, w, 0, h);
       
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}
void _mouseclick( int button, int state, int x, int y )
{
    printf("%d %d \n",x,y);
}
#pragma pack(push, 2)
typedef struct
{ 
  ushort    bfType;
  uint   bfSize;        
  ushort    bfReserved1; 
  ushort   bfReserved2; 
  uint   bfOffBits;    
  uint  biSize; 
  uint   biWidth; 
  uint   biHeight; 
  ushort   biBitCount; 
  ushort  biCompression; 
  uint  biSizeImage; 
  uint   biXPelsPerMeter; 
  uint   biYPelsPerMeter; 
  uint  biClrUsed; 
  uint  biClrImportant; 
}HeadGr;
#pragma pack(pop)
char* readImg(char* fileName)
{
    int rgbBytes,d,bytesPerRow;
    char *buf, *otherDate;
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
        buf=(char*)malloc(bytesPerRow*head.biHeight);
        otherDate=(char*) malloc(head.bfOffBits-54);
        fread(otherDate,(head.bfOffBits-54),1,f);
        fread(buf,bytesPerRow*head.biHeight,1,f);          
        fclose(f); 
        free(otherDate);
        return buf;
    }
}
void display()
{
    char *buf;
    glClear(GL_COLOR_BUFFER_BIT);
    buf=readImg("texture.bmp");
    if(buf==NULL)
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
        glDrawPixels(700, 700, GL_BGR, GL_UNSIGNED_BYTE, buf);
        glutSwapBuffers();
    }
    free(buf);
}
 
int main (int argc, char * argv[])
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
       
        glutInitWindowSize(700, 700);
        glutCreateWindow("Lab5");
       
        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutMouseFunc( _mouseclick );
        glutMainLoop();
       
        return 0;
}

