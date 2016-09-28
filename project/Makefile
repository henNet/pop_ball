LIBCOMP=../src/*.o
LIBSTATIC=-lSDL -lm -lSDL_mixer -lSDL_image -lSDL_ttf -lSDL_gfx
DIR_HEADER_LIB_PATH=../headers
DIR_HEADER_PROJECT_PATH=headers/


YOURFILES=src/*.c

BINARY=bin/main_pop_ball

all:
	gcc ${YOURFILES} ${LIBCOMP} -I${DIR_HEADER_LIB_PATH} -I${DIR_HEADER_PROJECT_PATH} -o ${BINARY} ${LIBSTATIC} 
clean:
	rm *.o
