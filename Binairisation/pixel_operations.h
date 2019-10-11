
#ifndef SDL_PIXEL_OPERATIONS_H
#define SDL_PIXEL_OPERATIONS_H
#include <stdlib.h>

#include "SDL/SDL_image.h"
#include <SDL/SDL.h>

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void update_surface(SDL_Surface* screen, SDL_Surface* image);

#endif //SDL_PIXEL_OPERATIONS_H
