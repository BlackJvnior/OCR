#include <stdio.h>
#include <err.h>
#include "data_base.h"
#include "../segmentation/segmentation.h"
#include "../preproc/preproc.h"

struct letter **init_database(char *filename)
{
  init_sdl();
  SDL_Surface *image = load_image(filename);
  image = grayscale(image);
  image = blackAndWhite(image, 0);
  int lines[image->h];
  int lines_final[image->h];
  int cols[image->w * 3];
  for (int tmp = 0; tmp < image->w * 3; tmp++)
  {
    cols[tmp] = -1;
  }
  Line_Detection(image, lines);
  checklines(lines, image->h, lines_final);
  char_detection(image, lines_final, cols);
  int nb_letters = get_number_letters(image, cols);
  printf("This image has %i letters\n", nb_letters);
  int nb_lines = get_number_lines(image, lines_final);
  printf("It also has %i lines, according to my great intellect.\n", nb_lines);
  struct letter **list_letters = create_letter_list(image, lines_final, cols);

  SDL_FreeSurface(image);
  SDL_Quit();
  return list_letters;
}

static double **get_database_out(size_t nb_characters)
{
  double **outputs = malloc(sizeof(double *) * nb_characters);
  for (size_t i = 0; i < nb_characters; i++)
  {
    outputs[i] = calloc(nb_characters, sizeof(double));
    outputs[i][i] = 1.0;
  }
  return outputs;
}

void train(struct NN *MyNet, struct letter **l, int nb_letters)
{
  double **output_train = get_database_out(nb_letters);
  for (int i = 0; i < nb_letters; i++)
  {
    double resul_mat[256];
    resizePixels(l[i]->mat, resul_mat, l[i]->width, l[i]->height, 16, 16);
    /*int max = l[i]->height > l[i]->width ? l[i]->height : l[i]->width;

    for (int n = 0; n < max; n++)
      {
        for (int j = 0; j < max; j++)
        {
            printf("%d",(int)l[i]->mat[j + n * max]);
        }
        printf("|\n");
      }
      printf("\n");
    for (int n = 0; n < 16; n++)
      {
        for (int j = 0; j < 16; j++)
        {
            printf("%d",(int)resul_mat[j + n * 16]);
        }
        printf("|\n");
      }
      printf("\n");*/
    backprop(MyNet, resul_mat, output_train[i]);
  }
  for (int j = 0; j < nb_letters; j++)
    free(output_train[j]);
  free(output_train);
}
