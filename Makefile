CC= gcc
CPPFLAGS= `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Werror -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl` -lSDL_image -lm
SRC= Binairisation/monochrom.c Binairisation/pixel_operations.c Segmentation/segmentation.c main.c

OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} *.bmp

fclean: clean
	${RM} main 

.PHONY: clean

-include ${DEP}