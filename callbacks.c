
#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "callbacks.h"


extern GtkBuilder *builder;


void init_spin_button (GtkSpinButton *spb, double min_val, double max_val, double val, double step, int digits) {
	gtk_spin_button_set_digits (spb, digits) ;
	gtk_spin_button_set_range (spb, min_val, max_val) ;
	gtk_spin_button_set_value (spb, val) ;
	gtk_spin_button_set_increments (spb, step, step) ;
}



void on_window1_destroy(GtkObject *object, gpointer user_data){
	printf("Fermeture de la fenetre.\n");
	gtk_main_quit();
}


void on_window1_realize (GtkObject *object, gpointer user_data){

	GtkSpinButton *spinbutton_vitesse = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_vitesse"));
	init_spin_button (spinbutton_vitesse, 0.0, 10000.0, 10.0, 0.1, 1);

	GtkSpinButton *spinbutton_corde = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_corde"));
	init_spin_button (spinbutton_corde, 0.0, 10000.0, 10.0, 0.1, 1);

	GtkSpinButton *spinbutton_fleche = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_fleche"));
	init_spin_button (spinbutton_fleche, 0.0, 10000.0, 10.0, 0.1, 1);

	GtkSpinButton *spinbutton_epaisseur = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_epaisseur"));
	init_spin_button (spinbutton_epaisseur, 0.0, 10000.0, 10.0, 0.1, 1);

}

/* --------------------------------- fonction pour griser les cases inutilisées --------------------------------------*/

void griser(){
	gboolean option_profil,option_caracteristiques,option_lesDeux;

	GtkFrame *frame_resultat = GTK_FRAME (gtk_builder_get_object (builder, "frame_resultat"));
	GtkFrame *frame_donnee = GTK_FRAME (gtk_builder_get_object (builder, "frame_donnee"));
	GtkFrame *frame_type = GTK_FRAME (gtk_builder_get_object (builder, "frame_type"));
	GtkFrame *frame_carac = GTK_FRAME (gtk_builder_get_object (builder, "frame_carac"));
	GtkRadioButton *radiobutton_profil = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_profil"));
	GtkRadioButton *radiobutton_caracteristiques = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_caracteristiques"));
	GtkRadioButton *radiobutton_lesDeux = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_lesDeux"));

	option_profil = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_profil));
	option_caracteristiques = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_caracteristiques));
	option_lesDeux = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux));

	if (option_profil){
		gtk_widget_set_sensitive( GTK_WIDGET(frame_resultat), 1);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_donnee), 1);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_type), 0);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_carac), 0);
	}
	else if (option_caracteristiques){
		gtk_widget_set_sensitive( GTK_WIDGET(frame_resultat), 0);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_donnee), 0);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_type), 1);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_carac), 1);
	}
	else if (option_lesDeux){
		gtk_widget_set_sensitive( GTK_WIDGET(frame_resultat), 1);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_donnee), 1);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_type), 1);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_carac), 1);
		}
}

void on_radiobutton_profil_toggled(GtkObject *object, gpointer user_data){
	griser();
}

void on_radiobutton_caracteristiques_toggled(GtkObject *object, gpointer user_data){
	griser();
	}

void on_radiobutton_lesDeux_toggled(GtkObject *object, gpointer user_data){
	griser();
	}

 /* --------------------------------------  obtenir un profil --------------------------------------------- */


void on_button_rafraichir_clicked(GtkObject *object, gpointer user_data){
	char valEpaiRe[256];
	char valCamb[256];
	char valRey[256];
	double Epaisseur, Corde, Fleche, Vitesse, Viscosite_air, valeur_epaisseurRelative, valeur_cambrure, valeur_reynolds;

	/* données que l'utilisateur doit rentrer */

	GtkSpinButton *spinbutton_vitesse = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_vitesse"));
	GtkSpinButton *spinbutton_corde = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_corde"));
	GtkSpinButton *spinbutton_fleche = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_fleche"));
	GtkSpinButton *spinbutton_epaisseur = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_epaisseur"));

	/* données que l'utilisateur veut obtenir */

	GtkLabel *epaisseurRelative = GTK_LABEL (gtk_builder_get_object (builder, "resultat_epaisseurRelative"));
	GtkLabel *reynolds = GTK_LABEL (gtk_builder_get_object (builder, "resultat_reynolds"));
	GtkLabel *cambrure = GTK_LABEL (gtk_builder_get_object(builder,"resultat_cambrure"));
	GtkImage *resultat_image = GTK_IMAGE (gtk_builder_get_object (builder, "resultat_image"));

	/* Recuperer le contenu des zones de saisie */
	Epaisseur = gtk_spin_button_get_value (spinbutton_epaisseur);
	Corde = gtk_spin_button_get_value (spinbutton_corde);
	Fleche= gtk_spin_button_get_value (spinbutton_fleche);
	Vitesse = gtk_spin_button_get_value (spinbutton_vitesse);
	Viscosite_air = 15,6*pow(10,-6);

	/* Traitement */
	valeur_epaisseurRelative = Epaisseur/Corde;
	sprintf (valEpaiRe, "%.1f m", valeur_epaisseurRelative) ;
	valeur_cambrure = Fleche/Corde;
	sprintf (valCamb, "%.1f ", valeur_cambrure) ;
	valeur_reynolds = (Vitesse*Corde)/Viscosite_air;
	sprintf (valRey, "%.1f ", valeur_reynolds) ;

	/* affiche le resultat */
	gtk_label_set_text (epaisseurRelative, valEpaiRe) ;
	gtk_label_set_text (cambrure, valCamb) ;
	gtk_label_set_text (reynolds, valRey) ;

	if (valeur_epaisseurRelative<2){
		gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/convexe.png");
	}
	if (valeur_epaisseurRelative<5 &&  valeur_epaisseurRelative>2 ){
		gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/biconvexe.png");
	}
	if (valeur_epaisseurRelative>5 ){
		gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/supercritique.png");
	}
}



/* --------------------------------------  obtenir un parametre --------------------------------------------- */


void rafraichir_affichage () {
	GtkRadioButton *radiobutton_profil = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_profil"));
	GtkRadioButton *radiobutton_caracteristiques = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_caracteristiques"));
	GtkRadioButton *radiobutton_lesDeux = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_lesDeux"));

	GtkComboBox *combobox_profil = GTK_COMBO_BOX (gtk_builder_get_object (builder, "combobox_profil"));
	GtkImage *image_profil = GTK_IMAGE (gtk_builder_get_object (builder, "image_profil"));
	GtkImage *resultat_image = GTK_IMAGE (gtk_builder_get_object (builder, "resultat_image"));

	int i = gtk_combo_box_get_active (combobox_profil) ;
			if (i==0){
			  gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/convexe.png");
			  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux)))
			  gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/convexe.png");
			}
			else if (i==1){
			  gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/biconvexe.png");
			  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux)))
			  gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/biconvexe.png");
			}
			else if (i==2){
			  gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/creux.png");
			  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux)))
			  gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/creux.png");
			}
			else if (i==3){
			  gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/supercritique.png");
			  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux)))
			  gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/supercritique.png");
			}
}

void on_combobox_profil_changed (GtkObject *object, gpointer user_data) {
	rafraichir_affichage ();
}

G_MODULE_EXPORT void on_button_export_csv_clicked(GtkObject *object, gpointer user_data){
	double Epaisseur, Corde, Fleche, Vitesse, Viscosite_air;
	double valeur_epaisseurRelative, valeur_cambrure, valeur_reynolds;
	/* données que l'utilisateur doit rentrer */

	GtkSpinButton *spinbutton_vitesse   = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_vitesse"));
	GtkSpinButton *spinbutton_corde     = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_corde"));
	GtkSpinButton *spinbutton_fleche    = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_fleche"));
	GtkSpinButton *spinbutton_epaisseur = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_epaisseur"));


	/* Recuperer le contenu des zones de saisie */
	Epaisseur = gtk_spin_button_get_value (spinbutton_epaisseur);
	Corde     = gtk_spin_button_get_value (spinbutton_corde);
	Fleche    = gtk_spin_button_get_value (spinbutton_fleche);
	Vitesse   = gtk_spin_button_get_value (spinbutton_vitesse);


	/* Traitement */
	Viscosite_air            = 15,6*pow(10,-6);
	valeur_epaisseurRelative = Epaisseur/Corde;
	valeur_cambrure          = Fleche/Corde;
	valeur_reynolds          = (Vitesse*Corde)/Viscosite_air;

	GtkFileChooserButton *filechooserbutton_csv = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "filechooserbutton_csv"));
	char *filename = gtk_file_chooser_get_filename(filechooserbutton_csv);

	FILE * file;
	file = fopen( filename, "w");

	fprintf(file, "epaisseur (m); %.1f \n",Epaisseur);
	fprintf(file, "corde (m); %.1f \n",Corde);
	fprintf(file, "fleche (m); %.1f \n",Fleche);
	fprintf(file, "vitesse (m/s); %.1f \n",Vitesse);
	fprintf(file, "Epaisseur Relative (m); %.1f \n",valeur_epaisseurRelative);
	fprintf(file, "Comparer ; %.1f \n", valeur_cambrure);
	fprintf(file, "reynolds ; %.1f \n", valeur_reynolds);

	GtkComboBox *combobox_profil = GTK_COMBO_BOX (gtk_builder_get_object (builder, "combobox_profil"));
	int i = gtk_combo_box_get_active (combobox_profil) ;
	if (i==0 || valeur_epaisseurRelative<2 )
	fprintf(file, "profil ; convexe \n");
	if (i==1 || (valeur_epaisseurRelative<5 && valeur_epaisseurRelative>2)  )
		fprintf(file, "profil ; biconvexe \n");
	if (i==3 || valeur_epaisseurRelative>5  )
			fprintf(file, "profil ; supercritique \n");

	fclose(file);

}

