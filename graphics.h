#ifndef CGL_GRAPHIC_H
#define CGL_GRAPHIC_H
struct Texture;

int initTexture(struct Texture tex);
void reshape(int w, int h);
void display();
void reDisplay(int value);

typedef struct Texture
{
  unsigned int width;
  unsigned int height;
  unsigned int bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
  unsigned char *pixel_data;
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