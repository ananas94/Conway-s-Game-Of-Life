#ifndef array
#define array


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

#endif
