CC=gcc
C_SOURCES=$(wildcard src/*.c)
INCLUDE_FOLDERS=-I./include
LIBS=-lglut \
-lGL \
-lGLU

OUTPUT="GameOfLife"
RM=rm -f 

all: BUILD

BUILD:
	$(CC) $(C_SOURCES) $(INCLUDE_FOLDERS) $(LIBS) -o $(OUTPUT)

clean:
	$(RM) $(OUTPUT)
