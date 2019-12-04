/*
**  OCR 404
**  file: main.c
**  description: link all the parts together and run everything
*/

#include <gtk/gtk.h>
#include <err.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "interface/ui.h"
#include "mysdl/mysdl.h"
#include "preproc/preproc.h"
#include "segmentation/segmentation.h"
#include "neuralnet/data_base.h"

GtkWidget *window;

/*
**  name: run_convert
**  description: This function is called when the "convert" button is pressed
**      on the gtk interface, it is the function that will run all the OCR
**      functions.
*/

void OCR(struct letter **l, int nb_letters)
{
  FILE *fp = fopen("Text.txt", "w");
  double resul_mat[16 * 16];
  struct NN *mynet = load_NN("neuralnet/NN_savefiles/OCR_NN_10");
  save_NN(mynet, "DEBUG");
  for (int i = 0; i < nb_letters; i++)
  {
    resizePixels(l[i]->mat, resul_mat, l[i]->width, l[i]->height, 16, 16);
    int j = 0;
    if (l[i]->space_after)
      fprintf(fp, "%c", ' ');
    while (j < 256 && resul_mat[j] == 1)
      j++;
    if (j == 256)
    {
      j = 0;
      while (j < l[i]->width && l[i]->mat[(l[i]->height / 2) + j * l[i]->width] == 1)
      {
        j++;
      }
      if (j == l[i]->width)
        fprintf(fp, "%c", '.');
      else
        fprintf(fp, "%c", 'l');
    }
    else
    {
      double *output = feedforward(mynet, resul_mat);
      char tmp = get_char(66, output);
      if (tmp == 'm')
      {
        if (l[i]->height > l[i]->width)
          tmp = 'j';
      }
      if (tmp == 'n')
      {
        if (resul_mat[15 + 15 * 16] == 0)
          tmp = 'p';
      }
      if (tmp == 'r')
      {
        if (resul_mat[8 + 15 * 16] == 1)
          tmp = 'g';
      }
      fprintf(fp, "%c", tmp);
    }
    if (l[i]->new_line)
      fprintf(fp, "%c", '\n');
  }
  fclose(fp);
}

/*
**  PLEASE DO NOT MODIFY
**  description: The main function only run the gtk+3 ui
*/

void run_convert(GtkButton *convert)
{
  // We close the file-choser window
  gtk_button_set_label(convert, "CONVERTING...");
  gtk_widget_destroy(window);

  // We start SDL and load the image
  init_sdl();
  gchar *file = get_filename();
  SDL_Surface *image = load_image(file);
  SDL_Surface *screen = NULL;

  /* Pre-processing
   * The 2nd arg of BnW is the multiplier of the split
   * If split set to 0 then img not splited
   */
  image = grayscale(image);
  //image = contrast(image);
  image = blackAndWhite(image, 0);

  //creating lists of lines and columns
  int lines[image->h];
  int lines_final[image->h];
  int cols[image->w * 3];
  for (int tmp = 0; tmp < image->w * 3; tmp++)
    cols[tmp] = -1;
  Line_Detection(image, lines);
  checklines(lines, image->h, lines_final);
  char_detection(image, lines_final, cols);

  int nb_letters = get_number_letters(image, cols);
  struct letter **list_letters = create_letter_list(image, lines_final, cols);
  space_mng(list_letters, nb_letters);
  OCR(list_letters, nb_letters);
  Create_Matrix(image);
  whole_segmentation(image);
  screen = display_image(image);
  SDL_FreeSurface(screen);
  SDL_Quit();
}

int main(int argc, char *argv[])
{
  GdkPixbuf *icon;
  gtk_init(&argc, &argv);
  window = create_window();
  icon = create_pixbuf();
  gtk_window_set_icon(GTK_WINDOW(window), icon);
  gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1080);
  gtk_widget_show_all(window);
  gtk_main();
  return 0;
}
