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

void init_hscale (GtkHScale *hsc, double min_val, double max_val, double val, double step, int digits) {
  gtk_scale_set_digits (GTK_SCALE(hsc), digits) ;
  gtk_range_set_range (GTK_RANGE(hsc), min_val, max_val) ;
  gtk_range_set_increments (GTK_RANGE(hsc), step, step) ;
  gtk_range_set_value (GTK_RANGE(hsc), val) ;
}


void rafrachir_affichage(){
	char msg[256];
	char r_f[256];
	char r_c[256];
	double Force, Longueur, E_module, Limite, Diametre, IGz, val_fleche, val_contrainte ;

	/* Recuperer des pointeurs vers les widgets */

	GtkSpinButton *spinbutton_module = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_module"));
	GtkSpinButton *spinbutton_limite = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_limite"));
	GtkSpinButton *spinbutton_longueur = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_longueur"));
	GtkSpinButton *spinbutton_diametre = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_diametre"));
	GtkSpinButton *spinbutton_force = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_force"));

	GtkLabel *fleche = GTK_LABEL (gtk_builder_get_object (builder, "resultat_fleche"));
	GtkLabel *contrainte = GTK_LABEL (gtk_builder_get_object (builder, "resultat_contrainte"));
	GtkLabel *message = GTK_LABEL (gtk_builder_get_object(builder,"label_message"));

	/* Recuperer le contenu des zones de saisie */
	Force = gtk_spin_button_get_value (spinbutton_force);
	Longueur = gtk_spin_button_get_value (spinbutton_longueur);
	E_module = gtk_spin_button_get_value (spinbutton_module);
	Limite = gtk_spin_button_get_value (spinbutton_limite);
	Diametre = gtk_spin_button_get_value (spinbutton_diametre);

	/* Traitement */
	IGz = M_PI*Diametre*Diametre*Diametre*Diametre/64;
	val_fleche = (Force * Longueur * Longueur * Longueur) / (3 * E_module * 1000 * IGz);
	sprintf (r_f, "%.1f mm", val_fleche) ;
	val_contrainte = (Longueur * Force * Diametre) / (2 * IGz);
	sprintf (r_c, "%.1f MPa", val_contrainte) ;

	/* affiche le resultat */
	gtk_label_set_text (fleche, r_f) ;
	gtk_label_set_text (contrainte, r_c) ;

	/* determine s'il y a depassement */
	if (val_contrainte  < (Limite/2))
		sprintf(msg, "<b><span foreground=\"#006400\">Respecte la limite elastique</span></b>");
	else
		sprintf(msg, "<b><span foreground=\"#FF0000\">Depasse la limite elastique</span></b>");

	gtk_label_set_markup(message, msg);
}


void on_window1_realize (GtkObject *object, gpointer user_data){


	GtkSpinButton *spinbutton_module = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_module"));
	init_spin_button (spinbutton_module, 0.0, 10000.0, 100.0, 0.1, 1);

	GtkSpinButton *spinbutton_limite = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_limite"));
	init_spin_button (spinbutton_limite, 0.0, 10000.0, 100.0, 0.1, 1);

	GtkHScale *hscale_longueur = GTK_HSCALE (gtk_builder_get_object (builder, "hscale_longueur")) ;
	GtkSpinButton *spinbutton_longueur = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_longueur"));
	init_spin_button (spinbutton_longueur, 0.0, 10000.0, 100.0, 0.1, 1);
	init_hscale (hscale_longueur, 0.0, 10000.0, 100.0, 0.1, 1);

	GtkHScale *hscale_diametre = GTK_HSCALE (gtk_builder_get_object (builder, "hscale_diametre")) ;
	GtkSpinButton *spinbutton_diametre = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_diametre"));
	init_spin_button (spinbutton_diametre, 0.0, 10000.0, 100.0, 0.1, 1);
	init_hscale (hscale_diametre, 0.0, 1000.0, 100.0, 0.1, 1);

	GtkHScale *hscale_force = GTK_HSCALE (gtk_builder_get_object (builder, "hscale_force")) ;
	GtkSpinButton *spinbutton_force = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_force"));
	init_spin_button (spinbutton_force, 0.0, 10000.0, 100.0, 0.1, 1);
	init_hscale (hscale_force, 0.0, 10000.0, 100.0, 0.1, 1);

	double Force, Longueur, E_module, Diametre, Limite;
	FILE* fichier;
	  	if (fopen("configuration", "r") == 0) {
	  		fread(msg,sizeof(char),256, fichier);
	  	}
	  	fclose(fichier);
	  gtk_main_quit();
	}


void on_window1_destroy(GtkObject *object, gpointer user_data){
  printf("Fermeture de la fenetre.\n");
  char msg[256];
  double Force, Longueur, E_module, Limite, Diametre ;
  GtkSpinButton *spinbutton_module = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_module"));
  	GtkSpinButton *spinbutton_limite = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_limite"));
  	GtkSpinButton *spinbutton_longueur = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_longueur"));
  	GtkSpinButton *spinbutton_diametre = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_diametre"));
  	GtkSpinButton *spinbutton_force = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_force"));
  	Force = gtk_spin_button_get_value (spinbutton_force);
  	Longueur = gtk_spin_button_get_value (spinbutton_longueur);
  	E_module = gtk_spin_button_get_value (spinbutton_module);
  	Limite = gtk_spin_button_get_value (spinbutton_limite);
  	Diametre = gtk_spin_button_get_value (spinbutton_diametre);
  	sprintf(msg, "%f %f %f %f %f", Diametre,E_module,Force,Longueur,Limite);
  	FILE* fichier;
  	if (fopen("configuration", "w") == 0) {
  		fwrite(msg,sizeof(char),256, fichier);
  	}
  	fclose(fichier);
  gtk_main_quit();
}



/* Configuration de la longueur*/

void on_hscale_longueur_value_changed (GtkObject *object) {
	GtkHScale *hscale_longueur = GTK_HSCALE(gtk_builder_get_object (builder, "hscale_longueur")) ;
	GtkSpinButton *spinbutton_longueur = GTK_SPIN_BUTTON(gtk_builder_get_object (builder, "spinbutton_longueur")) ;
	double val = gtk_range_get_value (GTK_RANGE(hscale_longueur));
	gtk_spin_button_set_value(spinbutton_longueur,  val) ;
}

void on_spinbutton_longueur_value_changed (GtkObject *object,gpointer user_data) {
	GtkHScale *hscale_longueur = GTK_HSCALE(gtk_builder_get_object (builder, "hscale_longueur")) ;
	GtkSpinButton *spinbutton_longueur = GTK_SPIN_BUTTON(gtk_builder_get_object (builder, "spinbutton_longueur")) ;
	double val = gtk_spin_button_get_value (spinbutton_longueur);
	gtk_range_set_value(GTK_RANGE(hscale_longueur), val) ;
	rafrachir_affichage();
}

/* Configuration Diametre */

void on_hscale_diametre_value_changed (GtkObject *object) {
	GtkHScale *hscale_diametre = GTK_HSCALE(gtk_builder_get_object (builder, "hscale_diametre")) ;
	GtkSpinButton *spinbutton_diametre = GTK_SPIN_BUTTON(gtk_builder_get_object (builder, "spinbutton_diametre")) ;
	double val = gtk_range_get_value (GTK_RANGE(hscale_diametre));
	gtk_spin_button_set_value(spinbutton_diametre,  val) ;
}

void on_spinbutton_diametre_value_changed (GtkObject *object,gpointer user_data) {
	GtkHScale *hscale_diametre = GTK_HSCALE(gtk_builder_get_object (builder, "hscale_diametre")) ;
	GtkSpinButton *spinbutton_diametre = GTK_SPIN_BUTTON(gtk_builder_get_object (builder, "spinbutton_diametre")) ;
	double val = gtk_spin_button_get_value (spinbutton_diametre);
	gtk_range_set_value(GTK_RANGE(hscale_diametre), val) ;
	rafrachir_affichage();
}

/* Configuration Force */

void on_hscale_force_value_changed (GtkObject *object) {
	GtkHScale *hscale_force = GTK_HSCALE(gtk_builder_get_object (builder, "hscale_force")) ;
	GtkSpinButton *spinbutton_force = GTK_SPIN_BUTTON(gtk_builder_get_object (builder, "spinbutton_force")) ;
	double val = gtk_range_get_value (GTK_RANGE(hscale_force));
	gtk_spin_button_set_value(spinbutton_force,  val) ;
}

void on_spinbutton_force_value_changed (GtkObject *object,gpointer user_data) {
	GtkHScale *hscale_force = GTK_HSCALE(gtk_builder_get_object (builder, "hscale_force")) ;
	GtkSpinButton *spinbutton_force = GTK_SPIN_BUTTON(gtk_builder_get_object (builder, "spinbutton_force")) ;
	double val = gtk_spin_button_get_value (spinbutton_force);
	gtk_range_set_value(GTK_RANGE(hscale_force), val) ;
	rafrachir_affichage();
}

/* Configuration du bouton  */


void on_button_export_csv_clicked(GtkObject *object, gpointer user_data){
	char msg[256];
	char *fichier_nom;
    double Force, Longueur, E_module, Diametre, Limite, IGz, val_fleche, val_contrainte ;
    GtkSpinButton *spinbutton_module = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_module"));
    GtkSpinButton *spinbutton_longueur = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_longueur"));
    GtkSpinButton *spinbutton_limite = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_limite"));
    GtkSpinButton *spinbutton_diametre = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_diametre"));
    GtkSpinButton *spinbutton_force = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_force"));
    GtkFileChooserButton *filechooserbutton_csv = GTK_FILE_CHOOSER(gtk_builder_get_object(builder,"filechooserbutton_csv"));

    /* Recuperer le contenu des zones de saisie */
    Force = gtk_spin_button_get_value (spinbutton_force);
    Longueur = gtk_spin_button_get_value (spinbutton_longueur);
    E_module = gtk_spin_button_get_value (spinbutton_module);
    Diametre = gtk_spin_button_get_value (spinbutton_diametre);
    fichier_nom =  gtk_file_chooser_get_filename(filechooserbutton_csv);

	/* affiche le resultat */
    IGz = M_PI*Diametre*Diametre*Diametre*Diametre/64;
    val_fleche = (Force * Longueur * Longueur * Longueur) / (3 * E_module * 1000 * IGz);
    val_contrainte = (Longueur * Force * Diametre) / (2 * IGz);

	sprintf(msg,"===DEBUT ecriture du fichier %s CSV\n",fichier_nom);

	/* Ajout du texte dans le fichier*/
	FILE* fichier;
	fichier = fopen(fichier_nom, "w");
	if (fichier != 0) {
		fprintf(fichier, "LONGUEUR (mm); %0.6f;\n", Longueur);
		fprintf(fichier, "DIAMETRE (mm); %0.6f;\n", Diametre);
		fprintf(fichier, "FORCE (N); %0.6f;\n", Force);
		fprintf(fichier, "MODULE D'YOUNG (GPa);%0.6f;\n", E_module);
		fprintf(fichier, "LIMITE ELASTIQUE (MPa); %0.6f;\n", Limite);
		fprintf(fichier, "FLECHE (mm); %0.6f;\n", val_fleche);
		fprintf(fichier, "CONTRAINTE MAXIMUM (MPa); %0.6f;\n", val_contrainte);
		}
	fclose(fichier);

	sprintf(msg,"=== FIN ecriture du fichier %s CSV",fichier_nom);
}
