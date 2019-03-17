#include "life.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Textures.h"

static int drawDead = 0;

void
graphics_change_draw_dead_state()
{
  drawDead ^= 1;
}

static unsigned int backgroundTexture;
static unsigned int lifeTexture;
static unsigned int lonelinessTexture;
static unsigned int overcrowdingTexture;

static int
initTexture(TEXTURE tex)
{
  int textureNum;
  glGenTextures(1, &textureNum);
  glBindTexture(GL_TEXTURE_2D, textureNum);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
               tex.width,
               tex.height,
               0,
               (tex.bytes_per_pixel == 3 ? GL_RGB : GL_RGBA),
               GL_UNSIGNED_BYTE, tex.pixel_data);
  return textureNum;
}

static TEXTURE *
readImg(char *fileName, int alpha)
{
  int rgbBytes, d, bytesPerRow, i, ob;
  char *Img, *otherDate;
  TEXTURE *t = malloc(sizeof(TEXTURE));
  FILE *f;
  HeadGr head;
  f = fopen(fileName, "rb");
  if (f == NULL)
    return NULL;
  else
  {
    fread(&head, 54, 1, f);
    rgbBytes = head.biWidth * (3 + alpha);
    d = rgbBytes % 4;
    bytesPerRow = d ? rgbBytes + (4 - d) : rgbBytes;
    Img = (char *)malloc(bytesPerRow * head.biHeight);
    otherDate = (char *)malloc(head.bfOffBits - 54);
    fread(otherDate, (head.bfOffBits - 54), 1, f);
    fread(Img, bytesPerRow * head.biHeight, 1, f);
    fclose(f);
    for (i = 0; i < bytesPerRow * head.biHeight; i += 3)
    {
      ob = *(Img + i);
      *(Img + i) = *(Img + i + 2);
      *(Img + 2 + i) = ob;
    }
    free(otherDate);
    (*t).width = head.biWidth;
    (*t).height = head.biHeight;
    (*t).bytes_per_pixel = 3 + alpha;
    (*t).pixel_data = Img;
    return t;
  }
}

static void
display()
{
  int i, j;
  glClear(GL_COLOR_BUFFER_BIT);
  //draw background
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, backgroundTexture);
  glBegin(GL_QUADS);
  glColor3f(1.0, 1.0, 1.0);
  glTexCoord2d(0, 0);
  glVertex2i(0, 0);
  glTexCoord2d(0, 1);
  glVertex2i(windowW, 0);
  glTexCoord2d(1, 1);
  glVertex2i(windowW, windowH);
  glTexCoord2d(1, 0);
  glVertex2i(0, windowH);
  glEnd();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //draw fields

  for (i = 0; i < fieldW; i++)
    for (j = 0; j < fieldH; j++)
    {
      cell_state_t state = logic_get_cell_state(i, j);
      if (state == NONE ||
          state != ALIVE && !drawDead)
        continue;

      glColor4f(1.0, 1.0, 1.0, 1.0);
      switch (state)
      {
      case ALIVE:
        glBindTexture(GL_TEXTURE_2D, lifeTexture);
        break;
      case DEAD_BY_LONELINESS:
        glBindTexture(GL_TEXTURE_2D, lonelinessTexture);
        break;
      case DEAD_BY_OVERCROWDING:
        glBindTexture(GL_TEXTURE_2D, overcrowdingTexture);
        break;
      }

      glBegin(GL_QUADS);
      glTexCoord2d(0, 0);
      glVertex2i(i * cellSize, j * cellSize);
      glTexCoord2d(0, 1);
      glVertex2i((i + 1) * cellSize, j * cellSize);
      glTexCoord2d(1, 1);
      glVertex2i((i + 1) * cellSize, (j + 1) * cellSize);
      glTexCoord2d(1, 0);
      glVertex2i(i * cellSize, (j + 1) * cellSize);
      glEnd();
    }

  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);

  //draw lines
  for (i = 0; i < fieldH; i++)
  {
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(0, i * cellSize);
    glVertex2i(windowW, i * cellSize);
    glEnd();
  }
  for (i = 0; i < fieldW; i++)
  {
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(i * cellSize, 0);
    glVertex2i(i * cellSize, windowH);
    glEnd();
  }
  glutSwapBuffers();
}

static void 
reDisplay(int value)
{
  display();
  glutTimerFunc(30, reDisplay, 2);
}



void init_graphics()
{
  glutDisplayFunc(display);
  glutTimerFunc(100, reDisplay, 2);
  //init textures
  TEXTURE *t = readImg("backgroundTexture.bmp", 0);
  backgroundTexture = initTexture(*t);

  free((*t).pixel_data);
  free(t);
  lifeTexture = initTexture(aliveCell);
  lonelinessTexture = initTexture(lonelyCell);
  overcrowdingTexture = initTexture(overpopulatedCell);
}