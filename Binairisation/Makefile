CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: monochrom


monochrom: pixel_operations.o monochrom.o

monochrom.o: pixel_operations.h

clean:
	${RM} *.o
	${RM} *.d
