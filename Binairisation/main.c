#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL_image.h"
#include <SDL/SDL.h>
#include <err.h>
#include "pixel_operations.h"
#include "monochrom.h"

int main()
{
    SDL_Surface *image_surface;
    SDL_Surface *screen_surface;

    init_sdl();
    image_surface = load_image("my_image.jpg");
    screen_surface = display_image(image_surface);
    wait_for_keypressed();
    grayscale(image_surface);
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    black_white(image_surface);
    update_surface(screen_surface, image_surface);
    Create_Matrix(image_surface);
    wait_for_keypressed();
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    return 0;
}