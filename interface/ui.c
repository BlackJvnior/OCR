/*
 *  UI
 *  file: ui.c
 *  Description: Contains all conde to display the UI using gtk
 */

#include <stdlib.h>
#include "ui.h"

gchar *filename;

gchar *get_filename()
{
  return filename;
}

void on_open_image(GtkButton *openf, gpointer user_data)
{
  struct pair *p = user_data;
  GtkWidget *convert = p->convert;
  GtkWidget *image = p->image;
  GtkWidget *toplevel = gtk_widget_get_toplevel(image);
  GtkFileFilter *filter = gtk_file_filter_new();

  // Open a window to select the image to load
  GtkWidget *dialog = gtk_file_chooser_dialog_new("Ouvrir image",
                                                  GTK_WINDOW(toplevel), GTK_FILE_CHOOSER_ACTION_OPEN,
                                                  "OK", GTK_RESPONSE_ACCEPT, "ANNULER", GTK_RESPONSE_CANCEL,
                                                  NULL);

  gtk_file_filter_add_pixbuf_formats(filter);
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

  switch (gtk_dialog_run(GTK_DIALOG(dialog)))
  {
  case GTK_RESPONSE_ACCEPT:
  {
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    gtk_image_set_from_file(GTK_IMAGE(image), filename);
    gtk_button_set_label(openf, "REOUVRIR IMAGE");

    /* Enable callback to convert functions */
    g_signal_connect(convert, "clicked", G_CALLBACK(run_convert), NULL);
    break;
  }
  default:
    break;
  }
  gtk_widget_destroy(dialog);
}

GtkWidget *create_window()
{
  GtkWidget *window, *openf, *convert, *image, *box;

  /* Set up the UI */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "==> OCR(e) <==");

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  openf = gtk_button_new_with_label("OUVRIR IMAGE");
  convert = gtk_button_new_with_label("CONVERTIR");

  // Create the first window with the background image
  image = gtk_image_new_from_file("images/folder.png");

  /* Create the widget of the image */
  gtk_box_pack_start(GTK_BOX(box), image, TRUE, TRUE, 0);
  /* Create the widget of the open file button */
  gtk_box_pack_start(GTK_BOX(box), openf, FALSE, FALSE, 0);
  /* Create the widget of the convert button iff an image is loaded */
  gtk_box_pack_start(GTK_BOX(box), convert, FALSE, FALSE, 0);

  gtk_container_add(GTK_CONTAINER(window), box);

  struct pair *p = malloc(sizeof(struct pair));
  p->convert = convert;
  p->image = image;

  /* Connect signals */
  /* Show open dialog when opening a file */
  g_signal_connect(openf, "clicked", G_CALLBACK(on_open_image), p);
  /* Callback to convert functions is set after successfully loading image */
  /* Exit when the window is closed */
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  return window;
}

/* function for window icon */
GdkPixbuf *create_pixbuf()
{
  GdkPixbuf *pixbuf;
  GError *error = NULL;
  pixbuf = gdk_pixbuf_new_from_file("images/logo.png", &error);

  if (!pixbuf)
  {
    fprintf(stderr, "%s\n", error->message);
    g_error_free(error);
  }

  return pixbuf;
}
