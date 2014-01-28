#ifndef H_life
#define H_life


#define cellSize 15
#define ALIVE 1
#define DEAD_BY_LONELINESS 2
#define DEAD_BY_OVERCROWDING 3
#define windowH 500
#define windowW 1024
#define fieldH ((windowH+(cellSize-windowH%cellSize))/cellSize)
#define fieldW ((windowW+(cellSize-windowW%cellSize))/cellSize)
typedef struct Texture
{
  unsigned int   width;
  unsigned int   height;
  unsigned int   bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char  *pixel_data;
};



#endif
