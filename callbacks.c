#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "callbacks.h"

/*-----------------------------------------------constantes physiques utilisees-------------------------*/
const double Viscosite_air = 15.6*pow(10,-6); /* en Pa*s */
const double MasseVolAir = 1.225; /* en kg/m3 */
const double g=9.81; /* en m*s^-2 */
const double vitesseSon= 340.3; /* en m*s^-1 */

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
	init_spin_button (spinbutton_vitesse, 0.0, 10000.0, 5.0, 0.1, 1);

	GtkSpinButton *spinbutton_corde = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_corde"));
	init_spin_button (spinbutton_corde, 0.0, 10000.0, 5.0, 0.1, 1);

	GtkSpinButton *spinbutton_fleche = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_fleche"));
	init_spin_button (spinbutton_fleche, 0.0, 10000.0, 1.0, 0.1, 1);

	GtkSpinButton *spinbutton_epaisseur = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_epaisseur"));
	init_spin_button (spinbutton_epaisseur, 0.0, 10000.0, 2.0, 0.1, 1);

	GtkSpinButton *spinbutton_surface = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_surface"));
	init_spin_button (spinbutton_surface, 0.0, 10000.0, 10.0, 0.1, 1);

	GtkSpinButton *spinbutton_masse = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_masse"));
	init_spin_button (spinbutton_masse, 0.0, 10000.0, 5.0, 0.1, 1);

	GtkSpinButton *spinbutton_Cz = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_Cz"));
		init_spin_button (spinbutton_Cz, 0.0, 10000.0, 4.0, 0.1, 1);

	GtkSpinButton *spinbutton_Cx = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, "spinbutton_Cx"));
	init_spin_button (spinbutton_Cx, 0.0, 10000.0, 5.0, 0.1, 1);

}

/* --------------------------------- fonction pour griser les cases selon le radio button --------------------------------------*/

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

void on_checkbutton_Cz_toggled(GtkObject *object, gpointer user_data){

}
void on_checkbutton_Cx_toggled(GtkObject *object, gpointer user_data){

}
void on_checkbutton_masse_toggled(GtkObject *object, gpointer user_data){

}

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
	double valeur_epaisseurRelative, valeur_cambrure, valeur_reynolds, valeur_portance, valeur_trainee, valeur_finesse, valeur_poids, valeur_mach;

	/* donnees que l'utilisateur doit rentrer */

	GtkSpinButton *spinbutton_vitesse = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_vitesse"));
	GtkSpinButton *spinbutton_corde = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_corde"));
	GtkSpinButton *spinbutton_fleche = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_fleche"));
	GtkSpinButton *spinbutton_epaisseur = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_epaisseur"));
	GtkSpinButton *spinbutton_surface = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_surface"));
	GtkSpinButton *spinbutton_Cx = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_Cx"));
	GtkSpinButton *spinbutton_Cz = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_Cz"));
	GtkSpinButton *spinbutton_masse = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_masse"));

	/* donnees facultatives */
	GtkCheckButton *checkbutton_Cx = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "checkbutton_Cx"));
	GtkCheckButton *checkbutton_Cz = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "checkbutton_Cz"));
	GtkCheckButton *checkbutton_masse = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "checkbutton_masse"));

	GtkLabel *labelPoids = GTK_LABEL (gtk_builder_get_object (builder, "labelPoids"));
	GtkLabel *labelPortance = GTK_LABEL (gtk_builder_get_object (builder, "labelPortance"));
	GtkLabel *labelTrainee = GTK_LABEL (gtk_builder_get_object (builder, "labelTrainee"));
	GtkLabel *labelFinesse = GTK_LABEL (gtk_builder_get_object (builder, "labelFinesse"));

	/* donn�es que l'utilisateur veut obtenir */

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

	GtkLabel *label_corde = GTK_LABEL (gtk_builder_get_object (builder, "label_corde"));
	GtkLabel *label_fleche = GTK_LABEL (gtk_builder_get_object (builder, "label_fleche"));
	GtkLabel *label_epaisseur = GTK_LABEL (gtk_builder_get_object(builder,"label_epaisseur"));
	char corde[256];
	char fleche[256];
	char epaisseur[256];


	/* Recuperer le contenu des zones de saisie */

	Epaisseur = gtk_spin_button_get_value (spinbutton_epaisseur);
	Corde = gtk_spin_button_get_value (spinbutton_corde);
	Fleche= gtk_spin_button_get_value (spinbutton_fleche);
	Vitesse = gtk_spin_button_get_value (spinbutton_vitesse);
	Surface = gtk_spin_button_get_value (spinbutton_surface);
	CoefP = gtk_spin_button_get_value (spinbutton_Cz);
	CoefT = gtk_spin_button_get_value (spinbutton_Cx);
	Masse = gtk_spin_button_get_value (spinbutton_masse);
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

	if (valeur_epaisseurRelative<2){
		gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/convexe.png");
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){
			gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/convexe.png");
			sprintf (corde, "10-50 m") ;
			gtk_label_set_text (label_corde, corde) ;
			sprintf (fleche, "20-60 m") ;
			gtk_label_set_text (label_fleche, fleche) ;
			sprintf (epaisseur, "30-70 m") ;
			gtk_label_set_text (label_epaisseur, epaisseur) ;
		}
	}
	if (valeur_epaisseurRelative<5 && valeur_epaisseurRelative>2 ){
		gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/biconvexe.png");
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){
			gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/biconvexe.png");
			sprintf (corde, "50-100 m") ;
			gtk_label_set_text (label_corde, corde) ;
			sprintf (fleche, "60-120 m") ;
			gtk_label_set_text (label_fleche, fleche) ;
			sprintf (epaisseur, "70-150 m") ;
			gtk_label_set_text (label_epaisseur, epaisseur) ;
		}
	}
	if (valeur_epaisseurRelative>5 ){
		gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/supercritique.png");
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){
			gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/supercritique.png");
			sprintf (corde, "80-90 m") ;
			gtk_label_set_text (label_corde, corde) ;
			sprintf (fleche, "70-80 m") ;
			gtk_label_set_text (label_fleche, fleche) ;
			sprintf (epaisseur, "80-100 m") ;
			gtk_label_set_text (label_epaisseur, epaisseur);
		}
	}
	if (valeur_cambrure>10 ){
		gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/creux.png");
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){
			gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/creux.png");
			sprintf (corde, "80-90 m") ;
			gtk_label_set_text (label_corde, corde) ;
			sprintf (fleche, "70-80 m") ;
			gtk_label_set_text (label_fleche, fleche) ;
			sprintf (epaisseur, "80-100 m") ;
			gtk_label_set_text (label_epaisseur, epaisseur);
		}
	}

	/* afficher le message */   /* valeur a changer c'etait juste un test */

	char modeleCorrect[256];

		if (valeur_mach < 0.3){
			sprintf(modeleCorrect,  "<b><span foreground=\"#006400\"> Modele correct </span></b>");
		}
		else {
			sprintf(modeleCorrect, "<b><span foreground=\"#FF0000\"> Modele incorrect, vitesse de l'aeronef trop importante  </span></b>");
		}

		gtk_label_set_markup(GTK_LABEL(label_message), modeleCorrect);

}



/* --------------------------------------  obtenir un parametre --------------------------------------------- */


void rafraichir_affichage () {

	GtkComboBox *combobox_profil = GTK_COMBO_BOX (gtk_builder_get_object (builder, "combobox_profil"));
	GtkImage *image_profil = GTK_IMAGE (gtk_builder_get_object (builder, "image_profil"));
	GtkImage *resultat_image = GTK_IMAGE (gtk_builder_get_object (builder, "resultat_image"));

	GtkRadioButton *radiobutton_lesDeux = GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radiobutton_lesDeux"));

	GtkLabel *label_corde = GTK_LABEL (gtk_builder_get_object (builder, "label_corde"));
	GtkLabel *label_fleche = GTK_LABEL (gtk_builder_get_object (builder, "label_fleche"));
	GtkLabel *label_epaisseur = GTK_LABEL (gtk_builder_get_object(builder,"label_epaisseur"));
	char corde[256];
	char fleche[256];
	char epaisseur[256];

	int i = gtk_combo_box_get_active (combobox_profil) ;
	if (i==0){
		gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/convexe.png");
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){  /* lie les deux images lorsque radio button 'toutes les donnee' est activ� */
			gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/convexe.png");
		}

		/* Traitement */
		sprintf (corde, "10-50 m") ;
		gtk_label_set_text (label_corde, corde) ;
		sprintf (fleche, "20-60 m") ;
		gtk_label_set_text (label_fleche, fleche) ;
		sprintf (epaisseur, "30-70 m") ;
		gtk_label_set_text (label_epaisseur, epaisseur) ;

	}
	else if (i==1){
		gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/biconvexe.png");
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){  /* lie les deux images lorsque radio button 'toutes les donnee' est activ� */
			gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/biconvexe.png");
		}

		/* Traitement */
		sprintf (corde, "50-100 m") ;
		gtk_label_set_text (label_corde, corde) ;
		sprintf (fleche, "60-120 m") ;
		gtk_label_set_text (label_fleche, fleche) ;
		sprintf (epaisseur, "70-150 m") ;
		gtk_label_set_text (label_epaisseur, epaisseur) ;
	}
	else if (i==2){
		gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/creux.png");
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){  /* lie les deux images lorsque radio button 'toutes les donnee' est activ� */
			gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/creux.png");
		}

		/* Traitement */
		sprintf (corde, "80-90 m") ;
		gtk_label_set_text (label_corde, corde) ;
		sprintf (fleche, "70-80 m") ;
		gtk_label_set_text (label_fleche, fleche) ;
		sprintf (epaisseur, "80-100 m") ;
		gtk_label_set_text (label_epaisseur, epaisseur) ;
	}
	else if (i==3){
		gtk_image_set_from_file(GTK_IMAGE(image_profil), "images/supercritique.png");
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux))){  /* lie les deux images lorsque radio button 'toutes les donnee' est activ� */
			gtk_image_set_from_file(GTK_IMAGE(resultat_image), "images/supercritique.png");
		}
		/* Traitement */
		sprintf (corde, "110-150 m") ;
		gtk_label_set_text (label_corde, corde) ;
		sprintf (fleche, "130-180 m") ;
		gtk_label_set_text (label_fleche, fleche) ;
		sprintf (epaisseur, "160-220 m") ;
		gtk_label_set_text (label_epaisseur, epaisseur) ;
	}
}


void on_combobox_profil_changed (GtkObject *object, gpointer user_data) {
	rafraichir_affichage ();
}


/* --------------------------------------- enregistrer les donnees dans un fichier csv ------------------------------------------- */


void on_button_export_csv_clicked(GtkObject *object, gpointer user_data){
	double Epaisseur, Corde, Fleche, Vitesse, Surface, CoefT, CoefP, Masse;
	double valeur_epaisseurRelative, valeur_cambrure, valeur_reynolds, valeur_portance, valeur_trainee, valeur_finesse, valeur_poids, valeur_mach;

	/* donnees que l'utilisateur doit rentrer */

	GtkSpinButton *spinbutton_vitesse   = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_vitesse"));
	GtkSpinButton *spinbutton_corde     = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_corde"));
	GtkSpinButton *spinbutton_fleche    = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_fleche"));
	GtkSpinButton *spinbutton_epaisseur = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_epaisseur"));
	GtkSpinButton *spinbutton_surface = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_surface"));
	GtkSpinButton *spinbutton_Cx = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_Cx"));
	GtkSpinButton *spinbutton_Cz = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_Cz"));
	GtkSpinButton *spinbutton_masse = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_masse"));

	/* donnees facultatives */
	GtkCheckButton *checkbutton_Cx = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "checkbutton_Cx"));
	GtkCheckButton *checkbutton_Cz = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "checkbutton_Cz"));
	GtkCheckButton *checkbutton_masse = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "checkbutton_masse"));

	/* Recuperer le contenu des zones de saisie */
	Epaisseur = gtk_spin_button_get_value (spinbutton_epaisseur);
	Corde     = gtk_spin_button_get_value (spinbutton_corde);
	Fleche    = gtk_spin_button_get_value (spinbutton_fleche);
	Vitesse   = gtk_spin_button_get_value (spinbutton_vitesse);
	Surface = gtk_spin_button_get_value (spinbutton_surface);
	CoefP = gtk_spin_button_get_value (spinbutton_Cz);
	CoefT = gtk_spin_button_get_value (spinbutton_Cx);
	Masse = gtk_spin_button_get_value (spinbutton_masse);


	/* Traitement */
	valeur_epaisseurRelative = (Epaisseur/Corde)*100;
	valeur_cambrure          = Fleche/Corde;
	valeur_reynolds          = (Vitesse*Corde)/Viscosite_air;
	valeur_mach=Vitesse/vitesseSon;

	/* calcul de la portance */

if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_Cz))){
	valeur_portance = 0.5 *Surface*MasseVolAir*Vitesse*Vitesse*CoefP;
}
else{
}

/* calcul de la trainee*/

if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_Cx))){
	valeur_trainee = 0.5*Surface*MasseVolAir*Vitesse*Vitesse *CoefT;
}
else{
}
/* calcul du poids */

if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_masse))){
	valeur_poids = Masse * g ;
}
else{

}

/* calcul de la finesse */

if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_Cz)) && gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_Cx))){
	valeur_finesse = valeur_portance /valeur_trainee;
}
else{

}

	GtkFileChooserButton *filechooserbutton_csv = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "filechooserbutton_csv"));
	char *filename = gtk_file_chooser_get_filename(filechooserbutton_csv);

	FILE * file;
	file = fopen( filename, "w");

	fprintf(file, "Epaisseur (m); %.1f \n",Epaisseur);
	fprintf(file, "Corde (m); %.1f \n",Corde);
	fprintf(file, "Fleche (m); %.1f \n",Fleche);
	fprintf(file, "Vitesse (m/s); %.1f \n",Vitesse);
	fprintf(file, "Epaisseur Relative; %.1f \n",valeur_epaisseurRelative);
	fprintf(file, "Cambrure ; %.1f \n", valeur_cambrure);
	fprintf(file, "Reynolds ; %.1f \n", valeur_reynolds);
	fprintf(file, "Mach ; %.1f \n", valeur_mach);
	fprintf(file, "Portance (N) ; %.1f \n", valeur_portance);
	fprintf(file, "Trainee (N) ; %.1f \n", valeur_trainee);
	fprintf(file, "Finesse ; %.1f \n", valeur_finesse);
	fprintf(file, "Poids (kg) ; %.1f \n", valeur_poids);





	/* enregistrer le profil choisi avec le combobox ou selon les donnees obtenues  */

	GtkComboBox *combobox_profil = GTK_COMBO_BOX (gtk_builder_get_object (builder, "combobox_profil"));
	int i = gtk_combo_box_get_active (combobox_profil) ;
	if (i==0 && valeur_epaisseurRelative<2 ){
		fprintf(file, "profil ; convexe \n");
	}
	if (i==1 && (valeur_epaisseurRelative<5 && valeur_epaisseurRelative>2) ){
		fprintf(file, "profil ; biconvexe \n");
	}
	if (i==3 && valeur_epaisseurRelative>5  ){
		fprintf(file, "profil ; supercritique \n");
	}

	fclose(file);
}
