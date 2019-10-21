#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL_image.h"
#include <SDL/SDL.h>
#include <err.h>
#include "../Binairisation/pixel_operations.h"
#include "../Binairisation/monochrom.h"
#include "segmentation.h"

int main()
{
    SDL_Surface *image_surface;

    init_sdl();
    image_surface = load_image("../Binairisation/my_image.jpg");
    grayscale(image_surface);
    black_white(image_surface);

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

    SDL_FreeSurface(image_surface);
    SDL_Quit();
}
