#ifndef H_life
#define H_life


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
#define cellSize 20
#define ALIVE 1
#define DEAD_BY_LONELINESS 2
#define DEAD_BY_OVERCROWDING 3
#define windowH 699
#define windowW 699
#define fieldH (windowH+1)/2
#define fieldW (windowW+1)/2

#endif
