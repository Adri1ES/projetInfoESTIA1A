
#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include <gtk/gtk.h>

G_MODULE_EXPORT void init_spin_button (GtkSpinButton *spb, double min_val, double max_val, double val, double step, int digits);
G_MODULE_EXPORT void on_window1_realize (GtkObject *object,gpointer user_data) ;
G_MODULE_EXPORT void on_window1_destroy (GtkObject *object,gpointer user_data) ;

G_MODULE_EXPORT void on_radiobutton1_toggled(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_radiobutton2_toggled(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_radiobutton3_toggled(GtkObject *object, gpointer user_data);

G_MODULE_EXPORT void on_radiobutton_profil_toggled(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_radiobutton_caracteristiques_toggled(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_radiobutton_lesDeux_toggled(GtkObject *object, gpointer user_data);

G_MODULE_EXPORT void on_checkbutton_Cz_toggled(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_checkbutton_Cx_toggled(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_checkbutton_masse_toggled(GtkObject *object, gpointer user_data);


G_MODULE_EXPORT void on_button_rafraichir_clicked(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_combobox_profil_changed (GtkObject *object, gpointer user_data);


G_MODULE_EXPORT void on_button_export_csv_clicked(GtkObject *object, gpointer user_data);

#endif /* CALLBACKS_H_ */
