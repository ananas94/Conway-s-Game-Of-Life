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

#endif
