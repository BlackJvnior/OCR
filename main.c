#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL_image.h"
#include <SDL/SDL.h>
#include <err.h>
#include "Binairisation/pixel_operations.h"
#include "Binairisation/monochrom.h"
#include "Segmentation/segmentation.h"
#include "string.h"

int main(int argc, char **argv)
{
    SDL_Surface *image_surface;
    SDL_Surface *screen_surface;

    if (argc != 2)
    {
        errx(1, "Not gooood");
    }
    else
    {
        init_sdl();
        char str[256];
        strcpy(str, "Images/");
        strcat(str, argv[1]);
        image_surface = load_image(str);
        //Display image
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        // Create a grayscaled version
        grayscale(image_surface);
        update_surface(screen_surface, image_surface);
        wait_for_keypressed();
        // Create a black and white version
        black_white(image_surface);
        update_surface(screen_surface, image_surface);
        // Create the associated matrix
        printf("Matrix : \n");
        Create_Matrix(image_surface);
        printf("\n\n\n");
        printf("The Segmentation founded : ");
        printf("\n\n\n");
        wait_for_keypressed();
        SDL_SaveBMP(image_surface, "out.bmp");

        //creating lists of lines and columns
        int lines[image_surface->h];
        int lines_final[image_surface->h];
        int cols[image_surface->w * 3];
        for (int tmp = 0; tmp < image_surface->w * 3; tmp++)
            cols[tmp] = -1;
        Line_Detection(image_surface, lines);
        checklines(lines, image_surface->h, lines_final);
        char_detection(image_surface, lines_final, cols);

        int nb_letters = get_number_letters(image_surface, cols);
        int nb_lines = get_number_lines(image_surface, lines_final);
        printf("Number of letters : %d \nNumber of lines : %d \n", nb_letters, nb_lines);
        struct letter **list_letters = create_letter_list(image_surface, lines_final, cols);
        space_mng(list_letters, nb_letters);

        SDL_FreeSurface(screen_surface);
        SDL_FreeSurface(image_surface);
        SDL_Quit();
    }
}