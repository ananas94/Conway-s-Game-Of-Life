#ifndef CGL_GRAPHIC_H
#define CGL_GRAPHIC_H
struct Texture;


void graphics_change_draw_dead_state();
void init_graphics();

typedef struct Texture
{
  unsigned int width;
  unsigned int height;
  unsigned int bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
  char *pixel_data;
} TEXTURE;

#pragma pack(push, 2)
typedef struct
{
  unsigned short bfType;
  unsigned int bfSize;
  unsigned short bfReserved1;
  unsigned short bfReserved2;
  unsigned int bfOffBits;
  unsigned int biSize;
  unsigned int biWidth;
  unsigned int biHeight;
  unsigned short biBitCount;
  unsigned short biCompression;
  unsigned int biSizeImage;
  unsigned int biXPelsPerMeter;
  unsigned int biYPelsPerMeter;
  unsigned int biClrUsed;
  unsigned int biClrImportant;
} HeadGr;
#pragma pack(pop)
#endif
