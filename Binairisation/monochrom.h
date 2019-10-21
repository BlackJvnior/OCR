#ifndef MONOCHROM_H_
#define MONOCHROM_H_
#include "SDL/SDL_image.h"
#include <SDL/SDL.h>

void init_sdl();
SDL_Surface *load_image(char *path);
SDL_Surface *display_image(SDL_Surface *img);
void wait_for_keypressed();
void grayscale(SDL_Surface *image);
int *Create_Matrix(SDL_Surface *image);
void black_white(SDL_Surface *image);

#endif