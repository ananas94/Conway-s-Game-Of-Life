CC=gcc
C_SOURCES=example.c 
INCLUDE_FOLDERS=-I. 
LIBS=-lglut \
-lGL \
-lGLU

OUTPUT="GameOfLife"
RM=rm -f 

ALL: BUILD

BUILD:
	$(CC) $(C_SOURCES) $(INCLUDE_FOLDERS) $(LIBS) -o $(OUTPUT)

CLEAN:
	$(RM) $(OUTPUT)