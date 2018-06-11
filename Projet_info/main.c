#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "callbacks.h"

GtkBuilder *builder;

int main (int argc, char *argv[]) {
  GtkWidget  *window1;

  /* Initialisation de GTK */
  gtk_init (&argc, &argv);

  /* Creation des widgets de l'interface a partir du fichier XML de Glade, grace au builder GTK */
  builder = gtk_builder_new ();
  if (gtk_builder_add_from_file (builder, "interface.glade", NULL) == 0) {
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
