#include <stdio.h>   /* sprintf */
#include <stdlib.h>  /* atoi */
#include <string.h>  /* strlen, strcmp */
#include <ctype.h>   /* isdigit */
#include <math.h>

#include "callbacks.h"

extern GtkBuilder *builder;

/* initialiser les spin_button */

void init_spin_button (GtkSpinButton *spb, double min_val, double max_val, double val, double step, int digits) {
  gtk_spin_button_set_digits (spb, digits) ;
  gtk_spin_button_set_range (spb, min_val, max_val) ;
  gtk_spin_button_set_value (spb, val) ;
  gtk_spin_button_set_increments (spb, step, step) ;
}

void on_window1_realize (GtkObject *object, gpointer user_data){

	GtkSpinButton *spinbutton_vitesse = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_vitesse"));
	init_spin_button (spinbutton_vitesse, 0.0, 10000.0, 100.0, 0.1, 1);

	GtkSpinButton *spinbutton_poids = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_poids"));
	init_spin_button (spinbutton_poids, 0.0, 10000.0, 100.0, 0.1, 1);

	GtkSpinButton *spinbutton_finesse = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_finesse"));
	init_spin_button (spinbutton_finesse, 0.0, 10000.0, 100.0, 0.1, 1);
}


void on_window1_destroy(GtkObject *object, gpointer user_data){
  printf("Fermeture de la fenetre.\n");
  gtk_main_quit();
}



void rafrachir_affichage(){
	char valEpaiRe[256];
	char valCamb[256];
	char valRey[256];
	double Epaisseur, Corde, Fleche, Vitesse, Viscosite_air, valeur_epaisseurRelative, valeur_cambrure, valeur_reynolds;

	/* données que l'utilisateur doit rentrer */

	GtkSpinButton *spinbutton_vitesse = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_vitesse"));
	GtkSpinButton *spinbutton_poids = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_poids"));
	GtkSpinButton *spinbutton_finesse = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_finesse"));
	GtkSpinButton *spinbutton_corde = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_corde"));
	GtkSpinButton *spinbutton_fleche = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_fleche"));
	GtkSpinButton *spinbutton_epaisseur = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_epaisseur"));

	/* données que l'utilisateur veut obtenir */

	GtkLabel *epaisseurRelative = GTK_LABEL (gtk_builder_get_object (builder, "resultat_epaisseurRelative"));
	GtkLabel *reynolds = GTK_LABEL (gtk_builder_get_object (builder, "resultat_reynolds"));
	GtkLabel *cambrure = GTK_LABEL (gtk_builder_get_object(builder,"resultat_cambrure"));

	/* Recuperer le contenu des zones de saisie */
	Epaisseur = gtk_spin_button_get_value (spinbutton_epaisseur);
	Corde = gtk_spin_button_get_value (spinbutton_corde);
	Fleche= gtk_spin_button_get_value (spinbutton_fleche);
	Vitesse = gtk_spin_button_get_value (spinbutton_vitesse);
	Viscosite_air = 15,6*pow(10,-6);


	/* Traitement */
	valeur_epaisseurRelative = Epaisseur/Corde;
	sprintf (valEpaiRe, "%.1f mm", valeur_epaisseurRelative) ;
	valeur_cambrure = Fleche/Corde;
	sprintf (valCamb, "%.1f MPa", valeur_cambrure) ;
	valeur_reynolds = (Vitesse*Corde)/Viscosite_air;
	sprintf (valRey, "%.1f MPa", valeur_reynolds) ;

	/* affiche le resultat */
	gtk_label_set_text (epaisseurRelative ,valEpaiRe) ;
	gtk_label_set_text (cambrure, valCamb) ;
	gtk_label_set_text (reynolds,valRey) ;

}


