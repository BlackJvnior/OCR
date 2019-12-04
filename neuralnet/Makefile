#   Trainning Makfile

CC= gcc
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Werror -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

SRC= ../mysdl/mysdl.c ../preproc/preproc.c ../segmentation/segmentation.c neural.c loaderNN.c data_base.c trainning.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: trainning

trainning: ${OBJ}

.PHONY: clean

clean:
		${RM} ${OBJ}
		${RM} ${DEP}
		${RM} trainning

-include ${DEP}
