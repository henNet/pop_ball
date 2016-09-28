DIR_HEADER_LIB_PATH=headers/
COMP_FILES=src/*.c
OBJECT_FILES=src/*.o
LIBSTATIC=-lSDL -lm -lSDL_mixer -lSDL_image -lSDL_ttf -lSDL_gfx
EXAMPLES=$(shell ls examples/exemplo*.c | wc -l)

all:
	gcc -I${DIR_HEADER_LIB_PATH} ${COMP_FILES} -c 
	mv *.o src/
	for i in `seq 1 ${EXAMPLES}`; \
	do \
		echo "Compiling Example $$i ";\
		gcc examples/exemplo$$i.c  ${OBJECT_FILES} -I${DIR_HEADER_LIB_PATH} -o bin/exemplo$$i ${LIBSTATIC};\
	done
clean:
	rm src/*.o
	rm bin/*
