#ifndef H_life
#define H_life


#define cellSize 15
#define ALIVE 1
#define DEAD_BY_LONELINESS 2
#define DEAD_BY_OVERCROWDING 3
#define fieldH 40
#define fieldW 80
#define windowH fieldH*cellSize
#define windowW fieldW*cellSize
typedef struct Texture
{
  unsigned int   width;
  unsigned int   height;
  unsigned int   bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char  *pixel_data;
}TEXTURE;

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
}HeadGr;
#pragma pack(pop)

//graphics
extern int initTexture(struct Texture tex);
extern void reshape(int w, int h);
extern void display();
extern void reDisplay(int value);

//interface
extern void mouseMotion(int x, int y);
extern void mouseClick( int button, int state, int x, int y );
extern void keyboard(unsigned char key, int x, int y);
extern void funcKeys(int key, int x, int y);

//logic
extern void step(int value);

#endif
