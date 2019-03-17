CC=gcc
C_SOURCES=$(wildcard *.c)
INCLUDE_FOLDERS=-I. 
LIBS=-lglut \
-lGL \
-lGLU

OUTPUT="GameOfLife"
RM=rm -f 

ALL: BUILD

BUILD:
	$(CC) $(C_SOURCES) $(INCLUDE_FOLDERS) $(LIBS) -o $(OUTPUT)

clean:
	$(RM) $(OUTPUT)