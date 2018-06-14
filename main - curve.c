#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "callbacks.h"

/* bibliotheque specifique au projet*/
#include "gdkpixbuf_accessors.h"

GtkBuilder *builder;

/* Callbacks pour le signal de destruction de la fenetre principale */
G_MODULE_EXPORT void on_mainwindow_destroy (GtkObject *object, gpointer user_data) {
  gtk_main_quit () ;  /* Stopper la boucle GTK */
}

int X_toScreen (double Xval, double Xmin, double Xmax, int width) {
  return (((Xval - Xmin) * width) / (Xmax - Xmin)) ;
}

int Y_toScreen (double Yval, double Ymin, double Ymax, int height) {
  return (((Yval - Ymin) * height) / (Ymax - Ymin)) ;
}

double X_fromScreen (int xScreen, double Xmin, double Xmax, int width) {
  return Xmin + ((xScreen * (Xmax - Xmin)) / width) ;
}

double Y_fromScreen (int yScreen, double Ymin, double Ymax, int height) {
  return Ymin + ((yScreen * (Ymax - Ymin)) / height) ;
}

/* recuperation des coordonnees des points à afficher*/

int main (int argc, char *argv[]) {
  GtkWidget  *window1;

  GtkBuilder *builder = NULL ;
  GtkWindow  *mainwindow = NULL ;
  GtkImage   *image1 = NULL ;
  GdkPixbuf  *gdk_pixbuf = NULL ;
  int w, h ;
  int x, y ;
  double X, Y ;
  /* Initialisation de GTK */
  gtk_init (&argc, &argv);

  /* Creation des widgets de l'interface a partir du fichier XML de Glade, grace au builder GTK */
  builder = gtk_builder_new ();
  if (gtk_builder_add_from_file (builder, "projet_info.glade", NULL) == 0) {
    fprintf (stderr, "Erreur: ouverture du fichier GLADE\n") ;
    exit(EXIT_FAILURE);
  }

  /* Recuperation du widget de la fenetre principale */
  window1 = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));

  /* Connection des fonctions de rappel avec les signaux de l'interface */
  gtk_builder_connect_signals (builder, NULL);

  /* Changement de la fenetre principale a l'etat visible */
  gtk_widget_show (window1);

  /* Lancement de l'execution de la boucle GTK */
  gtk_main ();
  g_object_unref (G_OBJECT (builder));

  printf ("Fin du programme\n") ;

  /* Fin du programme */
  return EXIT_SUCCESS;
}
