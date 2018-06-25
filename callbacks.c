
#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "callbacks.h"

/*---------------- constantes physiques utilisees ---------------------*/
const double Viscosite_air = 0.000156; /* en Pa*s */
const double MasseVolAir = 1.225; /* en kg/m3 */
const double g = 9.81; /* en m*s^-2 */
const double vitesseSon = 340.3; /* en m*s^-1 */


extern GtkBuilder *builder;

/* ----------------- pour initialiser les spin buttons ----------------*/

void init_spin_button (GtkSpinButton *spb, double min_val, double max_val, double val, double step, int digits) {
	gtk_spin_button_set_digits (spb, digits) ;
	gtk_spin_button_set_range (spb, min_val, max_val) ;
	gtk_spin_button_set_value (spb, val) ;
	gtk_spin_button_set_increments (spb, step, step) ;
}

/*--------------------pour choisir le type d'avion ---------------------*/

void type_avion ()  {
	gboolean option_1,option_2,option_3;
	double VitesseModelisme_init, CordeModelisme_init,FlecheModelisme_init,EpaisseurModelisme_init, SurfaceModelisme_init;
	double VitesseULM_init, CordeULM_init, FlecheULM_init, EpaisseurULM_init, SurfaceULM_init;
	double VitesseTourisme_init, CordeTourisme_init, FlecheTourisme_init, EpaisseurTourisme_init, SurfaceTourisme_init ;

	/* recupere les spinbutton */
	GtkSpinButton *spinbutton_vitesse = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_vitesse"));
	GtkSpinButton *spinbutton_corde = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_corde"));
	GtkSpinButton *spinbutton_fleche = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_fleche"));
	GtkSpinButton *spinbutton_epaisseur = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_epaisseur"));
	GtkSpinButton *spinbutton_surface = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_surface"));
	GtkSpinButton *spinbutton_Cx = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_Cx"));
	GtkSpinButton *spinbutton_Cz = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_Cz"));
	GtkSpinButton *spinbutton_masse = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_masse"));

	/* recupere les radiobuttons type d'avion */
	GtkRadioButton *radiobutton1 = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton1"));
	GtkRadioButton *radiobutton2 = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton2"));
	GtkRadioButton *radiobutton3 = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton3"));

	option_1 = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton1));
	option_2 = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton2));
	option_3 = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton3));


	FILE *instructions;
	instructions = fopen("instructions", "rb");
	if (instructions == NULL) {
  	    fprintf (stderr, "Erreur ouverture fichier en lecture\n") ;
  	  }
  	else{
		fread(&VitesseModelisme_init, sizeof(double), 1, instructions);
		fread(&CordeModelisme_init, sizeof(double), 1, instructions);
		fread(&FlecheModelisme_init, sizeof(double), 1, instructions);
		fread(&EpaisseurModelisme_init, sizeof(double), 1, instructions);
		fread(&SurfaceModelisme_init, sizeof(double), 1, instructions);

		fread(&VitesseULM_init, sizeof(double), 1, instructions);
		fread(&CordeULM_init, sizeof(double), 1, instructions);
		fread(&FlecheULM_init, sizeof(double), 1, instructions);
		fread(&EpaisseurULM_init, sizeof(double), 1, instructions);
		fread(&SurfaceULM_init, sizeof(double), 1, instructions);

		fread(&VitesseTourisme_init, sizeof(double), 1, instructions);
		fread(&CordeTourisme_init, sizeof(double), 1, instructions);
		fread(&FlecheTourisme_init, sizeof(double), 1, instructions);
		fread(&EpaisseurTourisme_init, sizeof(double), 1, instructions);
		fread(&SurfaceTourisme_init, sizeof(double), 1, instructions);

  	}
	fclose(instructions);


	if (option_1){

		init_spin_button (spinbutton_vitesse, 0.0, 10000.0, VitesseModelisme_init, 0.1, 1);
		init_spin_button (spinbutton_corde, 0.0, 10000.0, CordeModelisme_init, 0.1, 1);
		init_spin_button (spinbutton_fleche, 0.0, 10000.0, FlecheModelisme_init, 0.1, 1);
		init_spin_button (spinbutton_epaisseur, 0.0, 10000.0, EpaisseurModelisme_init, 0.1, 1);
		init_spin_button (spinbutton_surface, 0.0, 10000.0, SurfaceModelisme_init, 0.1, 1);
		init_spin_button (spinbutton_masse, 0.0, 10000.0, 5.0, 0.1, 1);
		init_spin_button (spinbutton_Cz, 0.0, 10000.0, 5.0, 0.1, 1);
		init_spin_button (spinbutton_Cx, 0.0, 10000.0, 5.0, 0.1, 1);
	}
 	else if (option_2){
 		init_spin_button (spinbutton_vitesse, 0.0, 10000.0, VitesseULM_init, 0.1, 1);
 		init_spin_button (spinbutton_corde, 0.0, 10000.0, CordeULM_init, 0.1, 1);
 		init_spin_button (spinbutton_fleche, 0.0, 10000.0, FlecheULM_init, 0.1, 1);
 		init_spin_button (spinbutton_epaisseur, 0.0, 10000.0, EpaisseurULM_init, 0.1, 1);
 		init_spin_button (spinbutton_surface, 0.0, 10000.0, SurfaceULM_init, 0.1, 1);
 		init_spin_button (spinbutton_masse, 0.0, 10000.0, 5.0, 0.1, 1);
 		init_spin_button (spinbutton_Cz, 0.0, 10000.0, 5.0, 0.1, 1);
 		init_spin_button (spinbutton_Cx, 0.0, 10000.0, 5.0, 0.1, 1);
	}
 	else if (option_3){
 		init_spin_button (spinbutton_vitesse, 0.0, 10000.0, VitesseTourisme_init, 0.1, 1);
 		init_spin_button (spinbutton_corde, 0.0, 10000.0, CordeTourisme_init, 0.1, 1);
 		init_spin_button (spinbutton_fleche, 0.0, 10000.0, FlecheTourisme_init, 0.1, 1);
 		init_spin_button (spinbutton_epaisseur, 0.0, 10000.0, EpaisseurTourisme_init, 0.1, 1);
 		init_spin_button (spinbutton_surface, 0.0, 10000.0, SurfaceTourisme_init, 0.1, 1);
 		init_spin_button (spinbutton_masse, 0.0, 10000.0, 5.0, 0.1, 1);
 		init_spin_button (spinbutton_Cz, 0.0, 10000.0, 5.0, 0.1, 1);
 		init_spin_button (spinbutton_Cx, 0.0, 10000.0, 5.0, 0.1, 1);
	}
}

/* -----------active les radiobuttons pour le choix de l'avion ------------- */

void on_radiobutton1_toggled(GtkObject *object, gpointer user_data){
	type_avion();
}
void on_radiobutton2_toggled(GtkObject *object, gpointer user_data){
	type_avion();
}
void on_radiobutton3_toggled(GtkObject *object, gpointer user_data){
	type_avion();
}

void on_window1_realize (GtkObject *object, gpointer user_data){
	type_avion();
}


/* ----------lorsque la fenetre se ferme, on enregistre les valeurs--------- */
void on_window1_destroy(GtkObject *object, gpointer user_data){
	printf("Fermeture de la fenetre.\n");

	GtkSpinButton *spinbutton_vitesse = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_vitesse"));
	GtkSpinButton *spinbutton_corde = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_corde"));
	GtkSpinButton *spinbutton_fleche = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_fleche"));
	GtkSpinButton *spinbutton_epaisseur = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_epaisseur"));
	GtkSpinButton *spinbutton_surface = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_surface"));
	GtkSpinButton *spinbutton_Cx = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_Cx"));
	GtkSpinButton *spinbutton_Cz = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_Cz"));
	GtkSpinButton *spinbutton_masse = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_masse"));

	double Epaisseur, Corde, Fleche, Vitesse, Surface, CoefT, CoefP, Masse;
	char msg[256];

	Epaisseur = gtk_spin_button_get_value (spinbutton_epaisseur);
	Corde = gtk_spin_button_get_value (spinbutton_corde);
	Fleche= gtk_spin_button_get_value (spinbutton_fleche);
	Vitesse = gtk_spin_button_get_value (spinbutton_vitesse);
	Surface = gtk_spin_button_get_value (spinbutton_surface);
	CoefP = gtk_spin_button_get_value (spinbutton_Cz);
	CoefT = gtk_spin_button_get_value (spinbutton_Cx);
	Masse = gtk_spin_button_get_value (spinbutton_masse);

	sprintf(msg, "%f %f %f %f %f %f %f %f", Epaisseur, Corde, Fleche, Vitesse, Surface, CoefT, CoefP, Masse);

  	FILE* valeurs_sauvergardees;
  	valeurs_sauvergardees = fopen("configuration", "w");
  	if (valeurs_sauvergardees == NULL) {
  	    fprintf (stderr, "Erreur ouverture fichier en lecture\n") ;
  	  }
  	else{
  		fwrite(msg,sizeof(char),256, valeurs_sauvergardees);
  	}
  	fclose(valeurs_sauvergardees);
  gtk_main_quit();
}

/* ------------fonction pour griser les cases selon le radio button------------ */

void griser(){
	gboolean option_profil,option_caracteristiques,option_lesDeux;

	/* recupere les frames a griser */

	GtkFrame *frame_resultat = GTK_FRAME (gtk_builder_get_object (builder, "frame_resultat"));
	GtkFrame *frame_donnee = GTK_FRAME (gtk_builder_get_object (builder, "frame_donnee"));
	GtkFrame *frame_type = GTK_FRAME (gtk_builder_get_object (builder, "frame_type"));
	GtkFrame *frame_carac = GTK_FRAME (gtk_builder_get_object (builder, "frame_carac"));

	/* recupere les radiobuttons */

	GtkRadioButton *radiobutton_profil = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_profil"));
	GtkRadioButton *radiobutton_caracteristiques = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_caracteristiques"));
	GtkRadioButton *radiobutton_lesDeux = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_lesDeux"));

	option_profil = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_profil));
	option_caracteristiques = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_caracteristiques));
	option_lesDeux = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux));

	if (option_profil){		/* grise la deuxieme partie et degrise la premiere partie si option profil est active */
		gtk_widget_set_sensitive( GTK_WIDGET(frame_resultat), 1);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_donnee), 1);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_type), 0);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_carac), 0);
	}
	else if (option_caracteristiques){		 /* grise la premiere partie et degrise la deuxieme partie si option caracteristiques est active */
		gtk_widget_set_sensitive( GTK_WIDGET(frame_resultat), 0);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_donnee), 0);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_type), 1);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_carac), 1);
	}
	else if (option_lesDeux){ 	/* degrise tous les frames si l'option lesDeux est active*/
		gtk_widget_set_sensitive( GTK_WIDGET(frame_resultat), 1);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_donnee), 1);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_type), 1);
		gtk_widget_set_sensitive( GTK_WIDGET(frame_carac), 1);
	}
}


/* -----------------Pour activer les radios buttons pour choiri le type de resutat ---------------------*/
void on_radiobutton_profil_toggled(GtkObject *object, gpointer user_data){
	griser();
}

void on_radiobutton_caracteristiques_toggled(GtkObject *object, gpointer user_data){
	griser();
}

void on_radiobutton_lesDeux_toggled(GtkObject *object, gpointer user_data){
	griser();
}

 /* ------------------------------------------------------  obtenir un profil ------------------------------------------------------ */

/* -------------------------active les checkbuttons ---------------------*/

void on_checkbutton_Cz_toggled(GtkObject *object, gpointer user_data){
}
void on_checkbutton_Cx_toggled(GtkObject *object, gpointer user_data){
}
void on_checkbutton_masse_toggled(GtkObject *object, gpointer user_data){
}

/* ------------------------Le bouton rafraichir --------------------------*/

void on_button_rafraichir_clicked(GtkObject *object, gpointer user_data){
	char valEpaiRe[256];
	char valCamb[256];
	char valRey[256];
	char valPort[256];
	char valTrai[256];
	char valPoids[256];
	char valFin[256];
	char valMach[256];
	double Epaisseur, Corde, Fleche, Vitesse, Surface, CoefT, CoefP, Masse;
	double valeur_epaisseurRelative, valeur_cambrure, valeur_reynolds,valeur_portance, valeur_trainee,valeur_finesse, valeur_poids, valeur_mach;

	/* recupere les radiobuttons type d'avion */
	GtkRadioButton *radiobutton1 = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton1"));
	GtkRadioButton *radiobutton2 = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton2"));
	GtkRadioButton *radiobutton3 = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton3"));

	/* données que l'utilisateur doit rentrer */

	GtkSpinButton *spinbutton_vitesse = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_vitesse"));
	GtkSpinButton *spinbutton_corde = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_corde"));
	GtkSpinButton *spinbutton_fleche = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_fleche"));
	GtkSpinButton *spinbutton_epaisseur = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_epaisseur"));
	GtkSpinButton *spinbutton_surface = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_surface"));
	GtkSpinButton *spinbutton_Cx = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_Cx"));
	GtkSpinButton *spinbutton_Cz = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_Cz"));
	GtkSpinButton *spinbutton_masse = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_masse"));

	/* recupere les checkbuttons */

	GtkCheckButton *checkbutton_Cx = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "checkbutton_Cx"));
	GtkCheckButton *checkbutton_Cz = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "checkbutton_Cz"));
	GtkCheckButton *checkbutton_masse = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "checkbutton_masse"));

	/* pour activer les labels selon le checkbutton active */

	GtkLabel *labelPoids = GTK_LABEL (gtk_builder_get_object (builder, "labelPoids"));
	GtkLabel *labelPortance = GTK_LABEL (gtk_builder_get_object (builder, "labelPortance"));
	GtkLabel *labelTrainee = GTK_LABEL (gtk_builder_get_object (builder, "labelTrainee"));
	GtkLabel *labelFinesse = GTK_LABEL (gtk_builder_get_object (builder, "labelFinesse"));

	/* données que l'utilisateur veut obtenir */

	GtkLabel *epaisseurRelative = GTK_LABEL (gtk_builder_get_object (builder, "resultat_epaisseurRelative"));
	GtkLabel *reynolds = GTK_LABEL (gtk_builder_get_object (builder, "resultat_reynolds"));
	GtkLabel *mach = GTK_LABEL (gtk_builder_get_object (builder, "resultat_mach"));
	GtkLabel *cambrure = GTK_LABEL (gtk_builder_get_object(builder,"resultat_cambrure"));
	GtkLabel *portance = GTK_LABEL (gtk_builder_get_object (builder, "resultat_portance"));
	GtkLabel *trainee = GTK_LABEL (gtk_builder_get_object (builder, "resultat_trainee"));
	GtkLabel *finesse = GTK_LABEL (gtk_builder_get_object (builder, "resultat_finesse"));
	GtkLabel *poids = GTK_LABEL (gtk_builder_get_object (builder, "resultat_poids"));
	GtkLabel *label_message = GTK_LABEL(gtk_builder_get_object(builder, "label_message"));
	GtkImage *resultat_image = GTK_IMAGE (gtk_builder_get_object (builder, "resultat_image"));

	/* lier les donnees */

	GtkLabel *caracteristique_finesse = GTK_LABEL (gtk_builder_get_object (builder, "caracteristique_finesse"));
	GtkLabel *caracteristique_cambrure = GTK_LABEL (gtk_builder_get_object (builder, "caracteristique_cambrure"));
	GtkLabel *caracteristique_epaisseur = GTK_LABEL (gtk_builder_get_object(builder,"caracteristique_epaisseur"));
	GtkLabel *caracteristique_Cx= GTK_LABEL (gtk_builder_get_object(builder,"caracteristique_Cx"));
	GtkLabel *caracteristique_Cz = GTK_LABEL (gtk_builder_get_object(builder,"caracteristique_Cz"));
	char Val_finesse[256];
	char Val_cambrure[256];
	char Val_epaisseur[256];
	char Val_Cz[256];
	char Val_Cx[256];

	/* Recuperer le contenu des zones de saisie */

	Epaisseur = gtk_spin_button_get_value (spinbutton_epaisseur);
	Corde = gtk_spin_button_get_value (spinbutton_corde);
	Fleche= gtk_spin_button_get_value (spinbutton_fleche);
	Vitesse = gtk_spin_button_get_value (spinbutton_vitesse);
	Surface = gtk_spin_button_get_value (spinbutton_surface);
	CoefP = gtk_spin_button_get_value (spinbutton_Cz);
	CoefT = gtk_spin_button_get_value (spinbutton_Cx);
	Masse = gtk_spin_button_get_value (spinbutton_masse);

	/* active la couleur des labels */
	char couleurP[256];
	char couleurT[256];
	char couleurPds[256];
	char couleurF[256];

	/* Traitement */

	valeur_epaisseurRelative = (Epaisseur/Corde)*100;
		sprintf (valEpaiRe, "%.1f", valeur_epaisseurRelative) ;
	valeur_cambrure = Fleche/Corde;
		sprintf (valCamb, "%.1f ", valeur_cambrure) ;
	valeur_reynolds = (Vitesse*Corde)/Viscosite_air;
		sprintf (valRey, "%.0f ", valeur_reynolds) ;
	valeur_mach=Vitesse/vitesseSon;
		sprintf (valMach, "%.1f", valeur_mach);

		/* calcul de la portance */

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_Cz))){
		valeur_portance = 0.5 *Surface*MasseVolAir*Vitesse*Vitesse*CoefP;
		sprintf (valPort, "%.1f ", valeur_portance) ;
		gtk_label_set_text (portance, valPort) ;
		gtk_label_set_text (labelPortance,"Portance") ;
	}
	else{
		sprintf (valPort, " ") ;
		sprintf(couleurP,  "<span foreground=\"#7378AD\"> Portance non calculee</span>");
		gtk_label_set_markup(GTK_LABEL(labelPortance), couleurP) ;
	}

	/* calcul de la trainee*/

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_Cx))){
		valeur_trainee = 0.5*Surface*MasseVolAir*Vitesse*Vitesse *CoefT;
		sprintf (valTrai, "%.1f ", valeur_trainee) ;
		gtk_label_set_text (labelTrainee,"Trainee") ;
	}
	else{
		sprintf (valTrai, " ") ;
		sprintf(couleurT,  "<span foreground=\"#7378AD\"> Trainee non calculee</span>");
		gtk_label_set_markup(GTK_LABEL(labelTrainee), couleurT) ;
	}

	/* calcul du poids */

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_masse))){
		valeur_poids = Masse * g ;
		sprintf (valPoids, "%.1f ", valeur_poids) ;
		gtk_label_set_text (labelPoids,"Poids") ;
	}
	else{
		sprintf (valPoids, " ");
		sprintf(couleurPds,  "<span foreground=\"#7378AD\"> Poids non calculee </span>");
		gtk_label_set_markup(GTK_LABEL(labelPoids), couleurPds) ;
	}

	/* calcul de la finesse */

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_Cz)) && gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_Cx))){
		valeur_finesse = valeur_portance /valeur_trainee;
		sprintf (valFin, "%.1f ", valeur_finesse) ;
		gtk_label_set_text (labelFinesse,"Finesse") ;
	}
	else{
		sprintf (valFin, " ");
		sprintf(couleurF,  "<span foreground=\"#7378AD\"> Finesse non calculee </span>");
		gtk_label_set_markup(GTK_LABEL(labelFinesse), couleurF) ;
	}

	/* affiche le resultat */

	gtk_label_set_text (epaisseurRelative, valEpaiRe) ;
	gtk_label_set_text (cambrure, valCamb) ;
	gtk_label_set_text (reynolds, valRey) ;
	gtk_label_set_text (mach, valMach) ;
	gtk_label_set_text (portance, valPort) ;
	gtk_label_set_text (trainee, valTrai) ;
	gtk_label_set_text (finesse, valFin) ;
	gtk_label_set_text (poids, valPoids) ;


	/* affiche les images */
	GtkRadioButton *radiobutton_lesDeux = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_lesDeux"));
	GtkImage *image_profil = GTK_IMAGE (gtk_builder_get_object (builder, "image_profil")); // pour lier les images si 'toutes les donnees' est active

	if (Fleche<2){
		gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/convexe.png");
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){
			gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/convexe.png");
			sprintf (Val_finesse, "19.6 max (angle incidence de 4)") ;
			gtk_label_set_text (caracteristique_finesse, Val_finesse) ;
			sprintf (Val_cambrure, "2,3 %%") ;
			gtk_label_set_text (caracteristique_cambrure, Val_cambrure) ;
			sprintf (Val_epaisseur, "10-12 %%") ;
			gtk_label_set_text (caracteristique_epaisseur, Val_epaisseur) ;
			sprintf (Val_Cz, "0.26 (angle 0)") ;
			gtk_label_set_text (caracteristique_Cz, Val_Cz) ;
			sprintf (Val_Cx, "0.017  (angle 0)") ;
			gtk_label_set_text (caracteristique_Cx, Val_Cx) ;
		}
	}
	if (Fleche<2 && valeur_epaisseurRelative<2 ){
		gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/biconvexe.png");
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){
			gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/biconvexe.png");
			sprintf (Val_finesse, "12.6 max (angle incidence de 4)") ;
			gtk_label_set_text (caracteristique_finesse, Val_finesse) ;
			sprintf (Val_cambrure, "0%% ") ;
			gtk_label_set_text (caracteristique_cambrure, Val_cambrure) ;
			sprintf (Val_epaisseur, "12 %%") ;
			gtk_label_set_text (caracteristique_epaisseur, Val_epaisseur) ;
			sprintf (Val_Cz, "0 (angle 0)") ;
			gtk_label_set_text (caracteristique_Cz, Val_Cz) ;
			sprintf (Val_Cx, "0.013  (angle 0)") ;
			gtk_label_set_text (caracteristique_Cx, Val_Cx) ;
		}
	}

	if (Fleche>5 &&  valeur_trainee>5 ){
		gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/creux.png");
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){
			gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/creux.png");
			sprintf (Val_finesse, "16.25 max (angle incidence de 2)") ;
			gtk_label_set_text (caracteristique_finesse, Val_finesse) ;
			sprintf (Val_cambrure, "5.1 %% ") ;
			gtk_label_set_text (caracteristique_cambrure, Val_cambrure) ;
			sprintf (Val_epaisseur, "9-10 %%") ;
			gtk_label_set_text (caracteristique_epaisseur, Val_epaisseur) ;
			sprintf (Val_Cz, "0.36 (angle 0)") ;
			gtk_label_set_text (caracteristique_Cz, Val_Cz) ;
			sprintf (Val_Cx, "0.02  (angle 0)") ;
			gtk_label_set_text (caracteristique_Cx, Val_Cx) ;

		}
	}

	if (valeur_epaisseurRelative>16 ){
			gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/supercritique.png");
			if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){
				gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/supercritique.png");
				sprintf (Val_finesse, "16.25 max (angle incidence de 2)") ;
				gtk_label_set_text (caracteristique_finesse, Val_finesse) ;
				sprintf (Val_cambrure, "5.1 %%") ;
				gtk_label_set_text (caracteristique_cambrure, Val_cambrure) ;
				sprintf (Val_epaisseur, "9-10 %%") ;
				gtk_label_set_text (caracteristique_epaisseur, Val_epaisseur) ;
				sprintf (Val_Cz, "0.36 (angle 0)") ;
				gtk_label_set_text (caracteristique_Cz, Val_Cz) ;
				sprintf (Val_Cx, "0.02  (angle 0)") ;
				gtk_label_set_text (caracteristique_Cx, Val_Cx) ;
			}
		}

	/* afficher le message */

	char modele[256];

	if ( gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton1)) && Vitesse > 50){
		sprintf(modele, "<b><span foreground=\"#FF0000\"> Modele incorrect, vitesse trop importante  </span></b>");
	}
	else if ( gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton2)) && Vitesse > 70){
		sprintf(modele, "<b><span foreground=\"#FF0000\"> Modele incorrect, vitesse trop importante  </span></b>");
	}
	else if ( gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton3)) && Vitesse > 70){
		sprintf(modele, "<b><span foreground=\"#FF0000\"> Modele incorrect, vitesse trop importante  </span></b>");
	}
	if (valeur_mach < 0.3){
		sprintf(modele,  "<b><span foreground=\"#006400\"> Modele correct </span></b>");
	}
	else {
		sprintf(modele, "<b><span foreground=\"#FF0000\"> Modele incorrect, vitesse trop importante  </span></b>");
	}

	gtk_label_set_markup(GTK_LABEL(label_message), modele);

}



/* -----------------------------------------------------  obtenir un parametre ------------------------------------------------------- */

/*---------------- pour lier les valeurs aux images selon le combobox choisi --------------------*/

void rafraichir_affichage () {


	GtkComboBox *combobox_profil = GTK_COMBO_BOX (gtk_builder_get_object (builder, "combobox_profil"));
	GtkImage *image_profil = GTK_IMAGE (gtk_builder_get_object (builder, "image_profil")); /* image du combobox */
	GtkImage *resultat_image = GTK_IMAGE (gtk_builder_get_object (builder, "resultat_image"));  /* image profil */

	GtkRadioButton *radiobutton_lesDeux = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_lesDeux"));

	GtkLabel *caracteristique_finesse = GTK_LABEL (gtk_builder_get_object (builder, "caracteristique_finesse"));
	GtkLabel *caracteristique_cambrure = GTK_LABEL (gtk_builder_get_object (builder, "caracteristique_cambrure"));
	GtkLabel *caracteristique_epaisseur = GTK_LABEL (gtk_builder_get_object(builder,"caracteristique_epaisseur"));
	GtkLabel *caracteristique_Cx= GTK_LABEL (gtk_builder_get_object(builder,"caracteristique_Cx"));
	GtkLabel *caracteristique_Cz = GTK_LABEL (gtk_builder_get_object(builder,"caracteristique_Cz"));
	char Val_finesse[256];
	char Val_cambrure[256];
	char Val_epaisseur[256];
	char Val_Cz[256];
	char Val_Cx[256];

	int i = gtk_combo_box_get_active (combobox_profil) ;

	if (i==0){
		gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/convexe.png");
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){  /* lie les deux images lorsque radio button 'toutes les donnees' est activé */
			gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/convexe.png");
		}

		/* Traitement */
		sprintf (Val_finesse, "19.6 max (angle incidence de 4)") ;
		gtk_label_set_text (caracteristique_finesse, Val_finesse) ;
		sprintf (Val_cambrure, "2,3 %%") ;
		gtk_label_set_text (caracteristique_cambrure, Val_cambrure) ;
		sprintf (Val_epaisseur, "10-12 %%") ;
		gtk_label_set_text (caracteristique_epaisseur, Val_epaisseur) ;
		sprintf (Val_Cz, "0.26 (angle 0)") ;
		gtk_label_set_text (caracteristique_Cz, Val_Cz) ;
		sprintf (Val_Cx, "0.017  (angle 0)") ;
		gtk_label_set_text (caracteristique_Cx, Val_Cx) ;
	}

	else if (i==1){
		gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/biconvexe.png");
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){  /* lie les deux images lorsque radio button 'toutes les donnees' est activé */
			gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/biconvexe.png");
		}

		/* Traitement */
		sprintf (Val_finesse, "12.6 max (angle incidence de 4)") ;
		gtk_label_set_text (caracteristique_finesse, Val_finesse) ;
		sprintf (Val_cambrure, "0 %% ") ;
		gtk_label_set_text (caracteristique_cambrure, Val_cambrure) ;
		sprintf (Val_epaisseur, "12 %%") ;
		gtk_label_set_text (caracteristique_epaisseur, Val_epaisseur) ;
		sprintf (Val_Cz, "0 (angle 0)") ;
		gtk_label_set_text (caracteristique_Cz, Val_Cz) ;
		sprintf (Val_Cx, "0.013  (angle 0)") ;
		gtk_label_set_text (caracteristique_Cx, Val_Cx) ;
	}

	else if (i==2){

		gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/creux.png");
			if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){  /* lie les deux images lorsque radio button 'toutes les donnees' est activé */
				gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/creux.png");
			}

			/* Traitement */
			sprintf (Val_finesse, "16.25 max (angle incidence de 2°)") ;
			gtk_label_set_text (caracteristique_finesse, Val_finesse) ;
			sprintf (Val_cambrure, "5.1 %% ") ;
			gtk_label_set_text (caracteristique_cambrure, Val_cambrure) ;
			sprintf (Val_epaisseur, "9-10 %%") ;
			gtk_label_set_text (caracteristique_epaisseur, Val_epaisseur) ;
			sprintf (Val_Cz, "0.36 (angle 0)") ;
			gtk_label_set_text (caracteristique_Cz, Val_Cz) ;
			sprintf (Val_Cx, "0.02  (angle 0)") ;
			gtk_label_set_text (caracteristique_Cx, Val_Cx) ;
	}

	else if (i==3){
		gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/supercritique.png");
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){  /* lie les deux images lorsque radio button 'toutes les donnees' est activé */
			gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/supercritique.png");
		}
		/* Traitement */
		sprintf (Val_finesse, "16.25 max (angle incidence de 2)") ;
		gtk_label_set_text (caracteristique_finesse, Val_finesse) ;
		sprintf (Val_cambrure, "5.1 %%") ;
		gtk_label_set_text (caracteristique_cambrure, Val_cambrure) ;
		sprintf (Val_epaisseur, "9-10 %%") ;
		gtk_label_set_text (caracteristique_epaisseur, Val_epaisseur) ;
		sprintf (Val_Cz, "0.36 (angle 0)") ;
		gtk_label_set_text (caracteristique_Cz, Val_Cz) ;
		sprintf (Val_Cx, "0.02  (angle 0)") ;
		gtk_label_set_text (caracteristique_Cx, Val_Cx) ;

	}
}


void on_combobox_profil_changed (GtkObject *object, gpointer user_data) {
	rafraichir_affichage ();
}


/* --------------------------------------- enregistrer les donnees dans un fichier csv ------------------------------------------- */


void on_button_export_csv_clicked(GtkObject *object, gpointer user_data){
	double Epaisseur, Corde, Fleche, Vitesse, Surface, CoefT, CoefP, Masse;
	double valeur_epaisseurRelative, valeur_cambrure, valeur_reynolds,valeur_portance, valeur_trainee,valeur_finesse, valeur_poids,valeur_mach;

	/* données que l'utilisateur doit rentrer */

	GtkSpinButton *spinbutton_vitesse = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_vitesse"));
	GtkSpinButton *spinbutton_corde = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_corde"));
	GtkSpinButton *spinbutton_fleche = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_fleche"));
	GtkSpinButton *spinbutton_epaisseur = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_epaisseur"));
	GtkSpinButton *spinbutton_surface = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_surface"));
	GtkSpinButton *spinbutton_Cx = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_Cx"));
	GtkSpinButton *spinbutton_Cz = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_Cz"));
	GtkSpinButton *spinbutton_masse = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_masse"));

	/* recupere les checkbuttons */

	GtkCheckButton *checkbutton_Cx = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "checkbutton_Cx"));
	GtkCheckButton *checkbutton_Cz = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "checkbutton_Cz"));
	GtkCheckButton *checkbutton_masse = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "checkbutton_masse"));

	GtkRadioButton *radiobutton_profil = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_profil"));
	GtkRadioButton *radiobutton_caracteristiques= GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_caracteristiques"));
	GtkRadioButton *radiobutton_lesDeux = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_lesDeux"));

	/* recupere le combobox */

	GtkComboBox *combobox_profil = GTK_COMBO_BOX (gtk_builder_get_object (builder, "combobox_profil"));

	/* Recuperer le contenu des zones de saisie */

	Epaisseur = gtk_spin_button_get_value (spinbutton_epaisseur);
	Corde = gtk_spin_button_get_value (spinbutton_corde);
	Fleche= gtk_spin_button_get_value (spinbutton_fleche);
	Vitesse = gtk_spin_button_get_value (spinbutton_vitesse);
	Surface = gtk_spin_button_get_value (spinbutton_surface);
	CoefP = gtk_spin_button_get_value (spinbutton_Cz);
	CoefT = gtk_spin_button_get_value (spinbutton_Cx);
	Masse = gtk_spin_button_get_value (spinbutton_masse);

	int i = gtk_combo_box_get_active (combobox_profil) ;


	/* Traitement */

	valeur_epaisseurRelative = (Epaisseur/Corde)*100;
	valeur_cambrure = Fleche/Corde;
	valeur_reynolds = (Vitesse*Corde)/Viscosite_air;
	valeur_mach=Vitesse/vitesseSon;

	GtkFileChooserButton *filechooserbutton_csv = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "filechooserbutton_csv"));
	char *filename = gtk_file_chooser_get_filename(filechooserbutton_csv);

	FILE * file;
	file = fopen( filename, "w");

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux)) || gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_profil))){
		fprintf(file, "-- Donnees rentrées --\n");
		fprintf(file, "Epaisseur (m); %.1f\n",Epaisseur);
		fprintf(file, "Corde (m); %.1f\n",Corde);
		fprintf(file, "Fleche (m); %.1f\n",Fleche);
		fprintf(file, "Vitesse (m/s); %.1f\n",Vitesse);
		fprintf(file, " ;  \n");
		fprintf(file, "-- Valeurs calculées --\n");
		fprintf(file, "Epaisseur Relative; %.1f\n",valeur_epaisseurRelative);
		fprintf(file, "Cambrure ; %.1f\n", valeur_cambrure);
		fprintf(file, "Reynolds ; %.1f\n", valeur_reynolds);
		fprintf(file, "Mach ; %.1f \n", valeur_mach);


	/* calcul du poids */

		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_masse))){
			valeur_poids = Masse * g ;
			fprintf(file, "Poids ; %.1f\n", valeur_poids);
		}

	/* calcul de la portance */

		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_Cz))){
			valeur_portance = 0.5 *Surface*MasseVolAir*Vitesse*Vitesse*CoefP;
			fprintf(file, "Portance ; %.1f\n", valeur_portance);
	}

	/* calcul de la trainee*/

		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_Cx))){
			valeur_trainee = 0.5*Surface*MasseVolAir*Vitesse*Vitesse *CoefT;
			fprintf(file, "Trainee ; %.1f\n", valeur_trainee);
		}

	/* calcul de la finesse */

		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_Cz)) && gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_Cx))){
			valeur_finesse = valeur_portance /valeur_trainee;
			fprintf(file, "Finesse ; %.1f\n", valeur_finesse);
		}

	/* enregistrer le profil choisi avec le combobox ou selon les donnees obtenues  */

		if (i==0 && Fleche<2 ){
			fprintf(file, "profil ; convexe\n");
		}
		if (i==1 && (Fleche<2 && valeur_epaisseurRelative<2) ){
			fprintf(file, "profil ; biconvexe\n");
		}
		if (i==2 && (Fleche>5 &&  valeur_trainee>5)){
			fprintf(file, "profil ; creux\n");
		}
		if (i==3 && valeur_epaisseurRelative>16   ){
			fprintf(file, "profil ; supercritique\n");
		}
	}
	else if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_caracteristiques))){
		if (i==0 ){
			fprintf(file, "profil ; convexe\n");
			fprintf(file,"finesse; 19.6 max (angle incidence de 4)\n");
			fprintf (file,"cambrure ; 2,3 %%\n") ;
			fprintf (file,"epaisseur ; 10-12 %%\n") ;
			fprintf (file,"Cz ; 0.26 (angle 0)\n") ;
			fprintf (file,"Cx ; 0.017  (angle 0)\n") ;
		}

		if (i==1){
			fprintf(file, "profil ; convexe\n");
			fprintf(file,"finesse; 12.6 max (angle incidence de 4)\n");
			fprintf (file,"cambrure ; 0 %%\n") ;
			fprintf (file,"epaisseur ; 12 %%\n") ;
			fprintf (file,"Cz ; 0 (angle 0)\n") ;
			fprintf (file,"Cx ; 0.013  (angle 0)\n") ;
		}

		if (i==2){
			fprintf(file, "profil ; convexe\n");
			fprintf(file,"finesse; 16.25 max (angle incidence de 2°)\n");
			fprintf (file,"cambrure ; 5.1 %%\n") ;
			fprintf (file,"epaisseur ; 9-10 %%\n") ;
			fprintf (file,"Cz ; 0.36 (angle 0)\n") ;
			fprintf (file,"Cx ; 0.02  (angle 0)\n") ;
		}

		if (i==3){
			fprintf(file, "profil ; convexe\n");
			fprintf(file,"finesse; 16.25 max (angle incidence de 2°)\n");
			fprintf (file,"cambrure ; 5.1 %%\n") ;
			fprintf (file,"epaisseur ; 9-10 %%\n") ;
			fprintf (file,"Cz ; 0.36 (angle 0)\n") ;
			fprintf (file,"Cx ; 0.02  (angle 0)\n") ;
		}
	}

	fclose(file);
}
