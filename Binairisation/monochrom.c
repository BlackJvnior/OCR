//
// Created by mexane on 10/10/2019.
//
#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL_image.h"
#include <SDL/SDL.h>
#include <err.h>
#include "pixel_operations.h"

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1, "Could not initialize SDL: %s.\n", SDL_GetError());
}

SDL_Surface *load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

SDL_Surface *display_image(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE | SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
        img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if (SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // return the screen for further uses
    return screen;
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while (event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while (event.type != SDL_KEYUP);
}

void grayscale(SDL_Surface *image)
{
    SDL_LockSurface(image);
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
    unsigned long x;
    unsigned long y;
    unsigned long h = image->h;
    unsigned long w = image->w;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            pixel = get_pixel(image, x, y);
            SDL_GetRGBA(pixel, image->format, &r, &g, &b, &a);
            Uint8 new_color = (0.3 * r + 0.59 * g + 0.11 * b);
            pixel = SDL_MapRGBA(image->format, new_color, new_color, new_color, a);
            put_pixel(image, x, y, pixel);
        }
    }
    SDL_UnlockSurface(image);
}

int *Create_Matrix(SDL_Surface *image)
{
    SDL_LockSurface(image);
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
    unsigned long i = 0;
    unsigned long x;
    unsigned long y;
    unsigned long h = image->h;
    unsigned long w = image->w;
    int size = h * w;
    int matrix[size];
    for (int i = 0; i < size; ++i)
    {
        matrix[i] = 0;
    }
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            pixel = get_pixel(image, x, y);
            SDL_GetRGBA(pixel, image->format, &r, &g, &b, &a);
            if (r == 0)
            {
                matrix[i] = 1;
            }
            else
            {
                matrix[i] = 0;
            }
            i++;
        }
    }
    for (int i = 0; i < size; i++)
    {
        printf("%d", matrix[i]);
        if ((i + 1) % w == 0)
        {
            printf("\n");
        }
    }
    SDL_UnlockSurface(image);
    int *PointerToMatrix = matrix;
    return PointerToMatrix;
}

void black_white(SDL_Surface *image)
{
    SDL_LockSurface(image);
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
    unsigned long x;
    unsigned long y;
    unsigned long h = image->h;
    unsigned long w = image->w;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            pixel = get_pixel(image, x, y);
            SDL_GetRGBA(pixel, image->format, &r, &g, &b, &a);
            Uint8 new_color;
            if (r <= 127)
            {
                new_color = 0;
            }
            else
            {
                new_color = 255;
            }
            pixel = SDL_MapRGBA(image->format, new_color, new_color, new_color, a);
            put_pixel(image, x, y, pixel);
        }
    }
    SDL_UnlockSurface(image);
}